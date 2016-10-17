#include "MineScene.h"
#include "Minesweeper.h"

USING_NS_CC;

#define TAG_ROOTNODE	100

Scene* mineScene::createScene()
{
	auto scene = Scene::create();
	auto layer = mineScene::create();
	scene->addChild(layer);
	return scene;
}

bool mineScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	auto rootNode = gameMap::create();

	addChild(rootNode, 1, TAG_ROOTNODE);
	return true;
}