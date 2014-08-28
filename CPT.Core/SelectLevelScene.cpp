#pragma warning(disable:4996)

#include "SelectLevelScene.h"

Scene* SelectLevel::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = SelectLevel::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectLevel::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
 //   auto closeItem = MenuItemImage::create(
 //                                          "CloseNormal.png",
 //                                          "CloseSelected.png",
 //                                          CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
 //   
	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
 //                               origin.y + closeItem->getContentSize().height/2));

 //   // create menu, it's an autorelease object
 //   auto menu = Menu::create(closeItem, NULL);
 //   menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    //auto label = LabelTTF::create("Hello World", "Arial", 24);
    //
    //// position the label on the center of the screen
    //label->setPosition(Vec2(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    //this->addChild(label, 1);

    //// add "HelloWorld" splash screen"
    //auto sprite = Sprite::create("HelloWorld.png");

    //// position the sprite on the center of the screen
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);

	static char* levelButtons[] = { 
						CPT_SELECT_LEVEL_BUTTON_NAME_1, 
						CPT_SELECT_LEVEL_BUTTON_NAME_2, 
						CPT_SELECT_LEVEL_BUTTON_NAME_3, 
						CPT_SELECT_LEVEL_BUTTON_NAME_4,
						CPT_SELECT_LEVEL_BUTTON_NAME_5,
						CPT_SELECT_LEVEL_BUTTON_NAME_6
	};

	const int BTN_COUNT = 6;

	auto selectLevelLayeout = CPTLoadLayoutFromPath(CPT_SELECT_LEVEL_SCENE_PATH);

	for (int i = 0; i < BTN_COUNT; i++)
	{
		auto levelButton = CPTFindControlByName(selectLevelLayeout, levelButtons[i], Button);
		levelButton->addTouchEventListener(this, CPTMakeTEvent(SelectLevel::selectLevelCallback));
	}

	this->addChild(selectLevelLayeout);

    return true;
} 


void SelectLevel::selectLevelCallback(Ref* pSender, TouchEventType touchType)
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}
