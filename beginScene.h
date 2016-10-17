#pragma once

#include "cocos2d.h"
#include <thread>

/*
 *	Author		:	YihaiDeng
 *	Date		:	2016-09-02
 *	Description	:	define the begin scene	
 */

class beginScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(beginScene);

	virtual void onExit();

private:
	void startMenuCB(cocos2d::Ref* r);
	void startMineCB(cocos2d::Ref* r);
	void exitMenuCB(cocos2d::Ref* r);

};