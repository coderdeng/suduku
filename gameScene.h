#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <thread>
#include <vector>
#include <string>
#include <map>

class gameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(gameScene);

	virtual void onEnter();
	virtual void onExit();

	virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void setCheckNumber(int index, int number);
	void reStartGame();
	void nextGame();

	void clickListener(cocos2d::Ref *ref);

private: // element
	cocos2d::Vector<cocos2d::ui::Button*> _numberArray;	// 存放九宫格数字的按钮 81 个
	std::vector<int> _numArray;

	int _blankCount;

private: // function
	void getData(const std::string &fileName, int offset);
	std::vector<int> computePossibleNums(int index) const;
	void drawSudoku();
	void drawNumber();
	bool checkGameOver() const;
	bool checkNumberLegitimate(int index, int objNum) const;
	void showTheMenu() const;
};