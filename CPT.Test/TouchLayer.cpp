#include "TouchLayer.h"


void TouchLayer::onTouchBegan(const std::vector<Touch*>& touches, cocos2d::Event *pEvent)
{
	auto touch = touches[0];
	log("the location is:%lf,%lf", touch->getLocationInView().x, touch->getLocationInView().y);
}

void TouchLayer::onTouchMoved(const std::vector<Touch*>& touches, cocos2d::Event *pEvent)
{
}

void TouchLayer::onTouchEnded(const std::vector<Touch*>& touches, cocos2d::Event *pEvent)
{
}

void TouchLayer::onTouchesCancelled(const std::vector<Touch*>& touches, Event  *event)
{
}

bool TouchLayer::init()
{
	if (Layer::init())
    {
		auto listener = EventListenerTouchAllAtOnce::create();
		//listener->setSwallowTouches(true);//设置是否想下传递触摸 
		listener->onTouchesBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(TouchLayer::onTouchMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		return true;
	}

	return false;
}

TouchLayer::~TouchLayer(void)
{
}
