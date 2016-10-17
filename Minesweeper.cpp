#include "Minesweeper.h"
#include <random>
#include <ctime>
#include <iostream>
#include <ui/CocosGUI.h>
#include "globalData.h"

using namespace std;
USING_NS_CC;

#define L_ADD_PLACE_NUM(x)	do { if (x >= 0 && _place[x] != 9)_place[x]++; }while(0)
#define H_ADD_PLACE_NUM(x)	do { if (x < 100 && _place[x] != 9)_place[x]++; }while(0)

#define TAG_ROOTNODE	100

bool gameMap::init()
{
	if (!Layer::init()) {
		return false;
	}
	initDate();
	auto rootNode = Node::create();
	auto winSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i < 100; ++i) {
		auto btn = ui::Button::create("checknull.png");
		auto btnSize = btn->getContentSize();
		rootNode->addChild(btn, 1, i);
		//btn->setScale(1.5);
		auto beginOffset = winSize / 2 - btnSize * 5;
		btn->setAnchorPoint(Vec2(0, 0));
		btn->setPosition(
			Vec2((i % 10) * btnSize.width, (i / 10) * btnSize.height) + 
			Vec2(beginOffset.width, beginOffset.height)
		);
		btn->addClickEventListener(CC_CALLBACK_1(gameMap::clickEventListener, this));
	}
	addChild(rootNode, 1, TAG_ROOTNODE);
	return true;
}

bool gameMap::initDate()
{
	_place = vector<int>(10 * 10, 0);
	vector<int> tmp_place;
	for (int i = 0; i < 100; ++i) {
		tmp_place.push_back(i);
	}

	default_random_engine e(time(0));
	uniform_int_distribution<int> u(0, 100);
	for (int i = 0; i < 10; ++i) {
		int tmp = u(e) % tmp_place.size();
		int index = tmp_place.at(tmp);
		_place[index] = 9;
		
		// 右上角、右、右下
		if (index % 10 != 9) {
			L_ADD_PLACE_NUM(index - 9);
			H_ADD_PLACE_NUM(index + 1);
			H_ADD_PLACE_NUM(index + 11);
		}
		// 上
		if (index / 10 != 0)
			L_ADD_PLACE_NUM(index - 10);
		// 左上、左、左下
		if (index % 10 != 0) {
			L_ADD_PLACE_NUM(index - 11);
			L_ADD_PLACE_NUM(index - 1);
			H_ADD_PLACE_NUM(index + 9);
		}
		// 下
		if (index / 10 != 9)
			H_ADD_PLACE_NUM(index + 10);

		tmp_place.erase(tmp_place.begin() + tmp);
	}
	return true;
}

void gameMap::clickEventListener(Ref *r)
{
	auto cur_btn = static_cast<ui::Button*> (r);
	log("button tag = %d", cur_btn->getTag());
	vector<int> boundary; // 存放边界方块的index
	if (_place.at(cur_btn->getTag()) == 0) {
		openBlackArea(cur_btn->getTag(), boundary);
		log("boundary size : %d", boundary.size());
		for (auto v : boundary) {
			auto boundary_btn = static_cast<ui::Button*>(getChildByTag(TAG_ROOTNODE)->getChildByTag(v));
			boundary_btn->setTitleText(num_to_str(_place.at(v)));
			boundary_btn->setTitleColor(Color3B::BLACK);
			boundary_btn->setTitleFontSize(50.0f);
		}
	}
	else 
		cur_btn->setTitleText(num_to_str(_place.at(cur_btn->getTag())));
	cur_btn->setTitleColor(Color3B::BLACK);
	cur_btn->setTitleFontSize(50.0f);
}

void gameMap::openBlackArea(int tiggerIndex, vector<int> &boundary)
{
	if (tiggerIndex < 0 || tiggerIndex >= 100 || _place[tiggerIndex] < 0)
		return;
	if (_place[tiggerIndex] > 0) {
		boundary.push_back(tiggerIndex);
		return;
	}
	_place[tiggerIndex] = -1;
	openBlackArea(tiggerIndex - 10, boundary);
	if (tiggerIndex % 10 != 0)
		openBlackArea(tiggerIndex - 1, boundary);
	openBlackArea(tiggerIndex + 10, boundary);
	if (tiggerIndex % 10 != 9)
		openBlackArea(tiggerIndex + 1, boundary);
}