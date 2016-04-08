#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;


class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void addMonster1(float dt);
	void addMonster2(float dt);
	void addMonster3(float dt);

	// touch event
	bool touchBegan(Touch* touch);
	void touchMoved(Touch* touch);
	void touchEnded(Touch* touch);

	// physics
	bool onContactBegan(PhysicsContact &contact);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	Sprite* player;
	int diem = 0;
	Label *Score;
	float v1 = 500;
	float v2 = 230;
	float v3 = 500;
};

#endif // __HELLOWORLD_SCENE_H__
