#include "HelloWorldScene.h"
#include <ctime>
#include "SimpleAudioEngine.h"
#include "GameOver.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	auto winSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/bg2.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bg2.wav", true);

	// Create background
	CCNode *nodeBg = CCNode::create();
	nodeBg->setAnchorPoint(Vec2(0, 0));

	auto Bg = Sprite::create("image/bg2.png");
	Bg->setAnchorPoint(Vec2(0, 0));
	Bg->setScaleX(1.5);

	nodeBg->addChild(Bg);

	auto bamboo1 = Sprite::create("image/stone1.png");
	bamboo1->setPosition(Vec2(bamboo1->getContentSize().width - bamboo1->getContentSize().width / 2 + 50, bamboo1->getContentSize().height / 2 - 50));
	bamboo1->setAnchorPoint(Vec2(0.5, 0.5));
	bamboo1->setScale(0.4);
	nodeBg->addChild(bamboo1);

	auto bamboo2 = Sprite::create("image/stone1.png");
	bamboo2->setAnchorPoint(Vec2(0.5, 0.5));
	bamboo2->setPosition(Vec2(bamboo2->getContentSize().width / 2 - 50, winSize.height - bamboo2->getContentSize().height / 2 + 50));
	bamboo2->setScale(0.4);
	/*bamboo2->setRotationX(60);
	bamboo2->setRotationY(60);*/
	nodeBg->addChild(bamboo2);

	auto bamboo3 = Sprite::create("image/stone1.png");
	bamboo3->setPosition(Vec2(bamboo3->getContentSize().width - bamboo3->getContentSize().width / 2 + 50, winSize.height - 150));
	bamboo3->setAnchorPoint(Vec2(0.5, 0.5));
	bamboo3->setScale(0.4);
	nodeBg->addChild(bamboo3);

	auto bamboo4 = Sprite::create("image/stone1.png");
	bamboo4->setAnchorPoint(Vec2(0.5, 0.5));
	bamboo4->setPosition(Vec2(bamboo4->getContentSize().width / 2 - 50, winSize.height - bamboo4->getContentSize().height / 2 + 450));
	bamboo4->setScale(0.4);
	/*bamboo2->setRotationX(60);
	bamboo2->setRotationY(60);*/
	nodeBg->addChild(bamboo4);

	//nodeBg->setTag(9);
	this->addChild(nodeBg);

	// create score
	std::string s = "Score: " + std::to_string(diem);
	Score =  Label::createWithTTF(s, "fonts/arial.ttf", 30);
	Score->setColor(Color3B::BLUE);
	Score->setPosition(winSize.width - Score->getContentSize().width, 10);
	this->addChild(Score);
	// player
	player = Sprite::create("image/player.png");
	player->setPosition(winSize.width / 2, winSize.height / 2); 
	player->setScale(0.2);
	this->addChild(player);
	auto playerBox = PhysicsBody::createBox(player->getContentSize());
	player->setTag(10);
	player->setPhysicsBody(playerBox);
	playerBox->setContactTestBitmask(0x1);
	playerBox->setDynamic(false);

	// add Monster.
	srand(time(NULL));
	this->schedule(schedule_selector(HelloWorld::addMonster1), 2);
	//if(diem > 15) this->schedule(schedule_selector(HelloWorld::addMonster2), 5);

	// event touch
	auto listenerEventTouch = EventListenerTouchOneByOne::create();
	listenerEventTouch->onTouchBegan = CC_CALLBACK_1(HelloWorld::touchBegan, this);
	listenerEventTouch->onTouchMoved = CC_CALLBACK_1(HelloWorld::touchMoved, this);
	listenerEventTouch->onTouchEnded = CC_CALLBACK_1(HelloWorld::touchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerEventTouch, this);


	//event physics contact
	auto listenerEventContact = EventListenerPhysicsContact::create();
	listenerEventContact->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerEventContact, this);


    return true;
}

void HelloWorld::addMonster1(float dt){

	auto winSize = Director::getInstance()->getVisibleSize();
	auto monster = Sprite::create("image/anime_bambo1.png");
	monster->setScale(0.065);
	//monster->setColor(Color3B::GREEN);
	auto monsterbox = PhysicsBody::createBox(monster->getContentSize());
	monster->setTag(1);
	monster->setPhysicsBody(monsterbox);
	monsterbox->setContactTestBitmask(0x1);

	int minY = 30;
	int maxY = winSize.height - minY;
	int minX = 30; 
	int maxX = winSize.width - minX;

	int randX, randY;

	do{
		randX = minX + rand() % (maxX - minX);
		randY = minY + rand() % (maxY - minY);
	} while (randX == player->getPosition().x && randY == player->getPosition().y);

	if (randX % 3 == 0){
		randX = 30;
	}
	else{
		if (randX % 2 == 0){
			randX = winSize.width - minX;
		}
		else{
			if (randY % 2 == 0) randY = 30;
			else{
				randY = winSize.height - minY;
			}
		}
	}

	monster->setPosition(Vec2(randX, randY));
	
	this->addChild(monster);
	
	/*auto actionScale = ScaleTo::create(2, 0.1);*/
	auto actionMoveTo = MoveTo::create(1.8, player->getPosition());
	auto actionRemove = RemoveSelf::create();
	
	monster->runAction(Sequence::create(actionMoveTo, DelayTime::create(3), actionRemove, nullptr));

}

void HelloWorld::addMonster2(float dt){

	auto winSize = Director::getInstance()->getVisibleSize();
	auto monster = Sprite::create("image/anime_bambo1.png");
	monster->setScale(0.065);
	monster->setColor(Color3B::GRAY);
	auto monsterbox = PhysicsBody::createBox(monster->getContentSize());
	monster->setTag(3);
	monster->setPhysicsBody(monsterbox);
	monsterbox->setContactTestBitmask(0x1);

	int minY = 20;
	int maxY = winSize.height - minY;
	int minX = 20;
	int maxX = winSize.width - minX;

	int randX, randY;

	do{
		randX = minX + rand() % (maxX - minX);
		randY = minY + rand() % (maxY - minY);
	} while (randX == player->getPosition().x && randY == player->getPosition().y);

	if (randX % 2 == 0){
		randX = 30;
	}
	else{
		if (randX % 3 == 0){
			randX = winSize.width - minX;
		}
		else{
			if (randY % 5 == 0) randY = 20;
			else{
				randY = winSize.height - minY;
			}
		}
	}

	monster->setPosition(Vec2(randX, randY));

	this->addChild(monster);
	float delX = monster->getPosition().x - player->getPosition().x;
	float delY = monster->getPosition().y - player->getPosition().y;
	float del = sqrtf(delX*delX + delY *delY);

	/*auto actionScale = ScaleTo::create(2, 0.1);*/
	auto actionMoveTo = MoveTo::create(del / v2, player->getPosition());
	auto actionRemove = RemoveSelf::create();

	monster->runAction(Sequence::create(actionMoveTo, DelayTime::create(3), actionRemove, nullptr));

}

void HelloWorld::addMonster3(float dt){

	auto winSize = Director::getInstance()->getVisibleSize();
	auto monster = Sprite::create("image/anime_bambo1.png");
	monster->setScale(0.065);
	monster->setColor(Color3B::RED);
	auto monsterbox = PhysicsBody::createBox(monster->getContentSize());
	monster->setTag(5);
	monster->setPhysicsBody(monsterbox);
	monsterbox->setContactTestBitmask(0x1);
	monsterbox->setGravityEnable(false);

	int minY = 10;
	int maxY = winSize.height - minY;
	int minX = 10;
	int maxX = winSize.width - minX;

	int randX, randY;

	do{
		randX = minX + rand() % (maxX - minX);
		randY = minY + rand() % (maxY - minY);
	} while (randX == player->getPosition().x && randY == player->getPosition().y);

	if (randY % 2 == 0) randX = 10;
	else{
		randX = winSize.width - minX;
	}

	monster->setPosition(Vec2(randX, randY));

	this->addChild(monster);

	/*auto actionScale = ScaleTo::create(2, 0.1);*/
	auto actionMoveTo = MoveTo::create(3, player->getPosition());
	auto actionRemove = RemoveSelf::create();

	monster->runAction(Sequence::create(actionMoveTo, DelayTime::create(3), actionRemove, nullptr));

}

bool HelloWorld::touchBegan(Touch* touch){
	return true;
}

void HelloWorld::touchMoved(Touch* touch){

	
}

void HelloWorld::touchEnded(Touch* touch){

	auto actionHide = Hide::create();
	/*player->runAction(actionHide);
	*/
	player->setVisible(false);

	auto bambooAttack = Sprite::create("image/bambooattack.png");
	bambooAttack->setPosition(player->getPosition());
	bambooAttack->setScale(0.2);
	this->addChild(bambooAttack);
	

	bambooAttack->runAction(Sequence::create(DelayTime::create(0.14), actionHide, nullptr));
	
	auto actionShow = Show::create();
	//auto actionFolow = Follow::create()
	player->runAction(Sequence::create(DelayTime::create(0.14), actionShow, nullptr));
	//player->setVisible(true);

	auto winSize = Director::getInstance()->getVisibleSize();

	auto bullet = Sprite::create("image/bullet_bamboo1.png");
	bullet->setPosition(player->getPosition().x, player->getPosition().y);
	this->addChild(bullet);



	// create physic body for bullet
	auto bulletBox = PhysicsBody::createBox(bullet->getContentSize());
	bullet->setTag(2);
	bulletBox->setContactTestBitmask(0x1);
	bullet->setPhysicsBody(bulletBox);
	bulletBox->setGravityEnable(false);
	
	auto locationTouch = touch->getLocation();

	Vec2 offSet = locationTouch - player->getPosition() ;
	offSet.normalize();

	Vec2 t = Director::getInstance()->getVisibleOrigin();
	t.normalize();
	auto shoot = 1000 * (offSet) + bullet->getPosition();

	float s = sqrtf(shoot.x * shoot.x + shoot.y * shoot.y);
	float v = 440 + ((locationTouch.x > player->getPosition().x || locationTouch.y > player->getPosition().y) ? 1000 : 0);
	auto actionMoveTo = MoveTo::create(s / v, shoot);
	auto actionRemove = RemoveSelf::create();

	bullet->runAction(Sequence::create(actionMoveTo, actionRemove, nullptr));

	/*CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.12);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/knife.wav");*/
	
}

bool HelloWorld::onContactBegan(PhysicsContact &contact){
	auto shape1 = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto shape2 = (Sprite*)contact.getShapeB()->getBody()->getNode();


	int tag1 = shape1->getTag();
	int tag2 = shape2->getTag();

	if (tag1 != 2 && tag2 != 2){
		shape1->setPosition(shape1->getPosition().x, shape1->getPosition().y - shape1->getContentSize().height);
	}

	if (tag1 == 1 && tag2 == 2 || tag1 == 2 && tag2 == 1 || tag1 == 2 && tag2 == -1 || tag1 == -1 && tag2 == 2){

		auto boom = Sprite::create("image/boom3.png");
		boom->setPosition(shape1->getPosition());
		boom->setScale(0.8);
		boom->setColor(Color3B::GREEN);
		this->addChild(boom);
		auto actionDelay = DelayTime::create(1);
		auto actionRemove = RemoveSelf::create();
		boom->runAction(Sequence::create(actionDelay, actionRemove, nullptr));
		/*his->removeChild(shape1);
		this->removeChild(shape2);*/
		shape1->removeFromParent();
		shape2->removeFromParent();
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.4);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/monsterdied1.wav");
		diem++;
	}

	if (tag1 == 2 && tag2 == 3 || tag1 == 3 && tag2 == 2){
		if (tag1 == 3){
			shape1->setTag(-3);
		}
		if (tag2 == 3){
			shape2->setTag(-3);
		}
	}

	if (tag1 == -3 && tag2 == 2 || tag1 == 2 && tag2 == -3){

		auto boom = Sprite::create("image/boom1.png");
		boom->setPosition(shape1->getPosition());
		boom->setScale(0.4);
		boom->setColor(Color3B::RED);
		this->addChild(boom);
		auto actionDelay = DelayTime::create(1);
		auto actionRemove = RemoveSelf::create();
		boom->runAction(Sequence::create(actionDelay, actionRemove, nullptr));
		/*his->removeChild(shape1);
		this->removeChild(shape2);*/
		shape1->removeFromParent();
		shape2->removeFromParent();

		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.4);
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/monsterdied1.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/monsterdied1.wav");
		diem++;
	}

	

	if (tag1 == 2 && tag2 == 5 || tag1 == 5 && tag2 == 2){
		diem++;

		//// Bom 1-----------------------------------
		//auto boom = Sprite::create("image/boom3.png");
		//boom->setPosition(shape1->getPosition());
		//boom->setScale(0.4);
		////boom->setColor(Color3B::RED);
		//this->addChild(boom);
		//auto actionMoveTo1 = MoveTo::create(0.2, Vec2(0, 0));
		//auto actionRemove = RemoveSelf::create();
		//boom->runAction(Sequence::create(actionMoveTo1, actionRemove, nullptr));
		//---------------------------------------

		auto add1 = Sprite::create("image/bamboo3.png");
		add1->setScale(0.4);
		add1->setPosition(shape2->getPosition());
		this->addChild(add1);
		add1->setTag(-1);
		auto add1Box = PhysicsBody::createBox(add1->getContentSize());
		//add1Box->setGravityEnable(false);
		add1->setPhysicsBody(add1Box);
		add1Box->setContactTestBitmask(0x1);

		float v = 100;
		float s = sqrtf((player->getPosition().x - shape1->getPosition().x) * (player->getPosition().x - shape1->getPosition().x) + (player->getPosition().y - shape1->getPosition().y) * (player->getPosition().y - shape1->getPosition().y));

		auto actionMoveTo = MoveTo::create(0, Vec2(shape1->getPosition().x, shape1->getPosition().y - add1->getContentSize().height));
		auto _actionMoveTo = MoveTo::create(s / v + 0.2, player->getPosition());
		auto actionRemove1 = RemoveSelf::create();

		add1->runAction(Sequence::create(actionMoveTo, _actionMoveTo, actionRemove1, nullptr));

		auto add2 = Sprite::create("image/bamboo3.png");
		add2->setScale(0.4);
		add2->setPosition(shape1->getPosition().x - add2->getContentSize().width / 2, shape1->getPosition().y + add1->getContentSize().height);
		
		this->addChild(add2);
		add2->setTag(-1);
		auto add2Box = PhysicsBody::createBox(add2->getContentSize());
		//add2Box->setGravityEnable(false);
		add2->setPhysicsBody(add2Box);
		add2Box->setContactTestBitmask(0x1);
		

		auto actionMoveTo2 = MoveTo::create(0, Vec2(shape1->getPosition().x + add2->getContentSize().width, shape1->getPosition().y));
		auto _actionMoveTo2 = MoveTo::create(s / v, player->getPosition());
		auto actionRemove2 = RemoveSelf::create();

		add2->runAction(Sequence::create(actionMoveTo2, _actionMoveTo2, actionRemove2, nullptr));

		this->removeChild(shape1);
		this->removeChild(shape2);

		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.4);
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/monsterdied1.wav");

	}

	if (tag1 == 10 || tag2 == 10){
		if (tag1 == 1 || tag1 == 3 || tag1 == 5 || tag1 == -3 || tag1 == -1 || tag2 == -1 || tag2 == 5 || tag2 == 1 || tag2 == 3 || tag2 == -3){
			auto boom = Sprite::create("image/boom4.png");
			boom->setPosition(player->getPosition());
			//boom->setScale(1.7);
			//boom->setColor(Color3B::YELLOW);
			this->addChild(boom);
			
			//auto actionDelay = DelayTime::create(2);
			//auto actionRemove = RemoveSelf::create();
			//boom->runAction(Sequence::create(actionDelay, nullptr));
			/*this->removeChildByTag(tag1);
			this->removeChildByTag(tag2);
			this->removeChild(player);*/
			player->setVisible(false);
			//Director::getInstance()->pause();
			//Sleep(5000); // Sleeping 2 sec before replace new Scene so gamer can see game over
			auto senceGameOver = GameOver::createScene();
			Director::getInstance()->replaceScene(senceGameOver);
		}
	}

	std::string s = "Score: " + std::to_string(diem);
	Score->setString(s);
	if (diem == 20){
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/newMonster.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/newMonster.wav");
		this->schedule(schedule_selector(HelloWorld::addMonster2), 5);
		diem++;
	}
	if (diem == 55){
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/gamegb1.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/gamegb1.wav", true);
		this->schedule(schedule_selector(HelloWorld::addMonster2), 2);
		diem++;
	}
	if (diem == 35){
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/newMonster1.wav");
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/newMonster1.wav");
		this->schedule(schedule_selector(HelloWorld::addMonster3), 3.3);
		
		diem++;
	}

	return true;
}