#include "SynthComponent.h"

#include "BL/SynthScene.h"
#include "BL/PickCalculator2D.h"

#include "Graphics/GraphicsNode.h"
#include "Graphics/GraphicsRectangle.h"
#include "Graphics/GraphicsText.h"
#include "Graphics/GraphicsScene.h"

SynthComponent::SynthComponent(SynthScene* scene, const String& name, AudioComponent* audioComponent)
	: SynthObject(scene, name)
	, PROPERTY_INIT(position, Vector2::ZERO)
	, PROPERTY_INIT(localAabbMin, Vector2::ZERO)
	, PROPERTY_INIT(localAabbMax, Vector2::ZERO)
	, mAudioComponent(audioComponent)
	, mRenderNode(NULL)
	, mRenderRect(NULL)
	, mRenderText(NULL)
{
	createRender();

	// TODO update AABB

	propertyChangedEvent += Delegate<void(PropertyOwner*, PropertyBase*)>(this, &SynthComponent::onPropertyChanged);
}

SynthComponent::~SynthComponent()
{
	propertyChangedEvent -= Delegate<void(PropertyOwner*, PropertyBase*)>(this, &SynthComponent::onPropertyChanged);

	destroyRender();
}

// bool SynthComponent::performPick(const Picker2D::PickInput& input, /*out*/Picker2D::PickResult& result)
// {
// 	if ((input.pickFilter & Picker2D::ObjectType::SynthComponent) == 0)
// 		return false;
// 
// 	Vector2 worldAabbMin = position.getValue() + localAabbMin.getValue();
// 	Vector2 worldAabbMax = position.getValue() + localAabbMax.getValue();
// 
// 	Picker2D::PickResult resultInner;
// 	bool hit = PickCalculator2D::pickRectangle(worldAabbMin, worldAabbMax, input, resultInner);
// 
// 	if (hit)
// 	{
// 		result.hit = hit;
// 		result.type = Picker2D::ObjectType::SynthComponent;
// 		result.hitPart = 0; // default
// 		result.closestPoint = resultInner.closestPoint;
// 		result.closestDistance = resultInner.closestDistance;
// 		result.closestZ = 0; // TODO FIXME
// 	}
// 
// 	return hit;
// }

void SynthComponent::onPropertyChanged(PropertyOwner* propOwner, PropertyBase* prop)
{
	Assert(propOwner == this);

	if (prop->is(position))
	{
		// TODO
	}
}

void SynthComponent::createRender()
{
	mRenderNode = new GraphicsNode();
	mRenderRect = new GraphicsRectangle();
	mRenderText = new GraphicsText();

	mRenderText->setText("Test");
	mRenderText->setFontSize(18.0f);
	mRenderText->setFontFamily("Times New Roman");
	mRenderText->setTextAlignment(GraphicsText::TextAlignment::MidCenter);

	mRenderRect->setSize(Vector2(120,40));
	mRenderRect->setFillColor(Color(0.8f, 0.8f, 0.8f));
	mRenderRect->setBorderColor(Color(0.2f, 0.2f, 0.2f));
	mRenderRect->setBorderWidth(1.5f);

	mRenderNode->setPosition(Vector2(0, 0));
	mRenderNode->addObject(mRenderRect);
	mRenderNode->addObject(mRenderText);
	mScene->getRenderScene()->addNode(mRenderNode, NULL);
}

void SynthComponent::destroyRender()
{
	mScene->getRenderScene()->removeNode(mRenderNode);

	mRenderNode->removeObject(mRenderRect);
	mRenderNode->removeObject(mRenderText);
	
	delete mRenderRect; mRenderRect = NULL;
	delete mRenderText; mRenderText = NULL;
	delete mRenderNode; mRenderNode = NULL;
}
