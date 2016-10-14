#pragma once

#include "Render/RenderSceneElement.h"

#include "Assist/Color.h"

class RenderScene;

class RenderLightSource : public RenderSceneElement
{
public:

	EnumBegin(LightType, DirectionalLight)
		DirectionalLight = 0,
		PointLight,
		SpotLight
	EnumEnd(LightType);

public:

	RenderLightSource(RenderScene* scene);
	~RenderLightSource();

	void lookAt(const Vector3& center, const Vector3& up = Vector3::UNIT_Y);
	
	LightType getLightType() const { return mLightType; }
	void setLightType(LightType val) { mLightType = val; }

	const Color& getIntensity() const { return mIntensity; }
	void setIntensity(const Color& val) { mIntensity = val; }

	float getLinearAttenuation() const { return mAttenuationLinear; }
	void setLinearAttenuation(float val) { mAttenuationLinear = val; }

	float getQuadraticAttenuation() const { return mAttenuationQuadratic; }
	void setQuadraticAttenuation(float val) { mAttenuationQuadratic = val; }

	float getAttenuationStart() const { return mAttenuationStart; }
	void setAttenuationStart(float val) { mAttenuationStart = val; }

	float getAttenuationEnd() const { return mAttenuationEnd; }
	void setAttenuationEnd(float val) { mAttenuationEnd = val; }

private:

	// NOTE: position of light is derived from the world transform
	// NOTE: direction of light is derived from the world transform (local +z)

	// Describes what kind of light source this is
	LightType mLightType;

	// Base color channel intesities of the light.
	Color mIntensity;
	
	// ===== ATTENUATION FACTORS =====
	// Describes how light is attenuated by distance. Attenuation is
	// the portion of light that hits a point at a certain distance.
	//
	// Attenuation A of light at a distance of D is controlled by 
	// the following equations:
	//   if D <= Dnear: A = 1
	//   if D >= Dfar:  A = 0
	//   otherwise:     A = 1 / (1 + kL*D + kQ*D^2);
	// where
	//   Dnear: distance at which attenuation starts
	//   Dfar:  distance at which attenuation ends
	//   kL:    the linear expression
	//   kQ:    the quadratic expression
	// NOTE: affected light types: point, spot
	float mAttenuationLinear;
	float mAttenuationQuadratic;
	float mAttenuationStart;
	float mAttenuationEnd;

	// ===== SPOTLIGHT FACTORS =====
	// NOTE: affected light types: spot
	float mCutoffAngle;
	// TODO add falloff

};

