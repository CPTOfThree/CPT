#pragma warning(disable:4996)
#include "StartGameScene.h"
#include "SelectLevelScene.h"

Scene* StartGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartGame::init()
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
	Widget *pWidget      = CPTLoadLayoutFromPath(CPT_START_GAME_SCENE_PATH);
	auto btnStartGame    = CPTFindControlByName(pWidget, CPT_START_GAME_BTN, Button);
	auto btnContinueGame = CPTFindControlByName(pWidget, CPT_CONTINUE_GAME_BTN, Button);

	btnContinueGame->addTouchEventListener(this, CPTMakeTEvent(StartGame::buttonContinueGameCallBack));
	btnStartGame   ->addTouchEventListener(this, CPTMakeTEvent(StartGame::buttonStartGameCallback));
	this->addChild(pWidget);

    return true;
} 


void StartGame::buttonStartGameCallback(Ref* pSender, TouchEventType touchType)
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
	// 切换到选择游戏的界面
	auto director = Director::getInstance();
	Scene* selectLevelScene = SelectLevel::createScene();
	director->replaceScene(selectLevelScene);
}

void StartGame::buttonContinueGameCallBack(cocos2d::Ref* pSender, TouchEventType touchType)
{

}
