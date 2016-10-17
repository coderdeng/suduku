#pragma once
#include <memory>
#include <vector>
#include <cocos2d.h>

class gameMap : public cocos2d::Layer
{
public:
	CREATE_FUNC(gameMap);

private:
	virtual bool init();
	bool initDate();
	void clickEventListener(cocos2d::Ref *r);
	void openBlackArea(int triggerIndex, std::vector<int> &boundary);
	
private:
	std::vector<int> _place;

};