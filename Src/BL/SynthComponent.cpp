#include "SynthComponent.h"

#include "BL/PickEngine.h"
#include "BL/SynthScene.h"

#include "Graphics/GraphicsNode.h"
#include "Graphics/GraphicsRectangle.h"
#include "Graphics/GraphicsText.h"
#include "Graphics/GraphicsScene.h"

SynthComponent::SynthComponent(SynthScene* scene)
	: SynthObject(scene)
	, PROPERTY_INIT(position, Vector2::ZERO)
	, PROPERTY_INIT(localAabbMin, Vector2::ZERO)
	, PROPERTY_INIT(localAabbMax, Vector2::ZERO)
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

bool SynthComponent::performPick(const PickInput& input, /*out*/PickResult& result)
{
	if ((input.pickFilter & PickObjectType::SynthComponent) == 0)
		return false;

	Vector2 worldAabbMin = position.getValue() + localAabbMin.getValue();
	Vector2 worldAabbMax = position.getValue() + localAabbMax.getValue();
	bool hit = PickEngine::pickRectangle(worldAabbMin, worldAabbMax, result);

	if (hit)
	{
		result.type = IPickable2D::PickObjectType::SynthComponent;
		result.hitPart = 0; // default
		// result.closestZ = 0; // TODO
	}

	return hit;
}

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
	mRenderRect->setFillColor(Color(0.8, 0.8, 0.8));
	mRenderRect->setBorderColor(Color(0.2, 0.2, 0.2));
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
