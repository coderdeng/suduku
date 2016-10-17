#pragma once
#include <cocos2d.h>

class mineScene : public cocos2d::Layer
{
public:
	CREATE_FUNC(mineScene);
	static cocos2d::Scene* createScene();

private:
	virtual bool init();

};