#pragma once
#include "cocos2d.h"
#include "gameScene.h"

class keyLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(keyLayer);
	virtual bool init();
	void showWithCheck(int checkIndex);

private: // menber function
	void addNubmerButton();
	void buttonClickListener(cocos2d::Ref *r);
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private: // menber
	int _currentCheckIndex;
};

