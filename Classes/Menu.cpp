#include "Menu.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{

    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	auto winSize = Director::getInstance()->getVisibleSize();

	/*auto button = MenuItemImage::create("image/button1.png", "image/clicked.png");
	button->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("image/button1.png"));
	button->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("image/clicked.png"));
	button->setCallback(CC_CALLBACK_1(MenuScene::gotoGameSense, this));
	button->setPosition(winSize.width / 2, winSize.height / 2);*/
	
	auto origin = Director::getInstance()->getVisibleOrigin();
	//auto winSize = Director::getInstance()->getVisibleSize();

	// music background
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/menuBg.wav");
	// ---------------

	
	// -------------------------------

	auto bg = DrawNode::create();
	bg->drawSolidRect(origin, winSize, Color4F::Color4F(1.1, 2, 1.01, 2));
	//this->addChild(bg);
	auto bg1 = Sprite::create("image/bg2.png");
	bg1->setScaleX(1.5);
	bg1->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg1);

	auto menuPlay = MenuItemFont::create("Play", CC_CALLBACK_1(MenuScene::gotoGameSense, this));
	auto menuPlayClicked = MenuItemFont::create("Play");
	
	//auto item1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuScene::gotoGameSense, this), menuPlay, menuPlayClicked, nullptr);
	auto playButton = MenuItemImage::create("image/buttonplay1.png", "image/buttonplay1.png", CC_CALLBACK_1(MenuScene::gotoGameSense, this));
	auto menu = Menu::createWithItems(playButton, "\0");
	this->addChild(menu, 2);

	// Create effect sprite run
	srand(time(NULL));
	this->schedule(schedule_selector(MenuScene::creatEffect), 1.6);

    return true;
}

void MenuScene::gotoGameSense(Ref* sender){
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void MenuScene::creatEffect(float dt){

	// creat Sprite
	auto ef1 = Sprite::create("image/anime_bambo1.png");
	ef1->setScale(0.065);
	this->addChild(ef1);

	// creat Position for bamboo effect
	auto winSize = Director::getInstance()->getVisibleSize();
	float minY = 30;
	float maxY = winSize.height - 30;

	float posX = /*ef1->getContentSize().width / 2*/ 30;
	float posY = rand() % (int)(maxY - minY) + minY;

	ef1->setPosition(posX, posY);

	float v = 340;
	// Create and run action for sprite to effect game
	auto actionMoveTo = MoveTo::create(winSize.width / v, Vec2(winSize.width, posY));
	auto actionRemove = RemoveSelf::create();

	ef1->runAction(Sequence::create(actionMoveTo, actionRemove, nullptr));
}
