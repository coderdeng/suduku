#pragma once
#include "cocos2d.h"
#include "gameScene.h"

class menuLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(menuLayer);

private:
	void exitCB(cocos2d::Ref *r);
	void reGameCB(cocos2d::Ref *r);
	void nextGameCB(cocos2d::Ref *r);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	void addMenu();

private:

};