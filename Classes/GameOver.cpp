#include "GameOver.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	
	auto winSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	//auto winSize = Director::getInstance()->getVisibleSize();
    
	auto bg = DrawNode::create();
	bg->drawSolidRect(origin, winSize, Color4F::GREEN);
	//this->addChild(bg);
	auto bg1 = Sprite::create("image/bg2.png");
	bg1->setScaleX(1.5);
	bg1->setAnchorPoint(Vec2(0, 0));
	this->addChild(bg1);

	/*auto gameOver = MenuItemFont::create("Game Over !", CC_CALLBACK_1(GameOver::exitGame, this));
	gameOver->setColor(Color3B::RED);
	gameOver->setFontName("fonts/Marker Felt.tff");*/
	auto gameOver = MenuItemImage::create("image/gameover.png", "image/gameover.png", CC_CALLBACK_1(GameOver::exitGame, this));
    
	auto menu = Menu::createWithItems(gameOver, "\0");
	this->addChild(menu);

	
	auto boom = Sprite::create("image/boom4.png");
	boom->setPosition(winSize.width / 3, winSize.height / 3);
	//boom->setScale(1.7);
	//boom->setColor(Color3B::YELLOW);
	this->addChild(boom);
	CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/gameOver.mp3");
	//Sleep(3000);
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/menuBg.wav");

    return true;
}

void GameOver::exitGame(Ref* ref){
	Director::getInstance()->end();
}

