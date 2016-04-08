#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class MenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void creatEffect(float dt);
    
	void gotoGameSense(Ref* sender);
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif // __Menu_SCENE_H__
