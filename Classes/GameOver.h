#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void exitGame(Ref* ref);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOver);
};

#endif // __GAME_OVER_H__
