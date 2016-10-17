/*
 *	Copyright		:	open
 *	Author			:	YihaiDeng
 *	Date			:	2017-09-02
 *	Description		:	define beginScene class
 */
#include "beginScene.h"
#include "gameScene.h"
#include "MineScene.h"
#include "globalData.h"

USING_NS_CC;
#define CONVERT_TO_GL(X) Director::getInstance()->convertToGL(X)


/*
 *	Function		:	createScene
 *	Description		:	create the begin scene
 *	Calls			:	scene::create(), beginScene::create(), scene::addChild(Node)
 *	Input			:	null
 *	Output			:	null
 *	Return			:	scene* 
 *	Others			:	create a scene and add a layer in 
 */
Scene* beginScene::createScene()
{
	auto scene = Scene::create();
	auto layer = beginScene::create();
	scene->addChild(layer);
	return scene;
}

/*
 *	Function		:	init()
 *	Description		:	initiate beginScen  
 *	Calls			:	Layer::init(), Node::create(), addChild(Node)
 *	Input			:	null
 *	Output			:	null
 *	Return			:	if initiate succeed return true, else return false
 *	Others			:	add widget or event listener
 */
bool beginScene::init()
{
	if ( !Layer::init() ) {
		return false;
	}
	
	auto winSize = Director::getInstance()->getVisibleSize();

	auto rootNode = Node::create();
	
	MenuItemFont::setFontSize(40);

	auto beginMenu = MenuItemFont::create( 
		"start game", CC_CALLBACK_1(beginScene::startMenuCB, this) );
	auto startMineMenu = MenuItemFont::create(
		"start minesweeper", CC_CALLBACK_1(beginScene::startMineCB, this));
	auto exitMenu = MenuItemFont::create( 
		"exit game", CC_CALLBACK_1(beginScene::exitMenuCB, this) );
	auto menu = Menu::create( beginMenu, startMineMenu, exitMenu, NULL );

	menu->alignItemsVertically();

	addChild(menu);

	addChild(rootNode);
	return true;
}

/*
 *	Function		:	onExit()
 *	Description		:	// 函数功能、性能等的描述 
 *	Calls			:	// 被本函数调用的函数清单  
 *	Others			:	// 其它说明 
 */
void beginScene::onExit()
{
	Layer::onExit();
}

/*
 *	Function		:	startMenuCB
 *	Description		:	the call back func of startMenu
 *	Calls			:	
 *	Input			:	the trigger of event
 *	Output			:	NULL 
 *	Return			:	NULL
 *	Others			:	load the game resource and start the game
 */
void beginScene::startMenuCB(Ref* r)
{
	log("start the game");
	auto nextScene = gameScene::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

void beginScene::startMineCB(Ref* r)
{
	log("start minesweeper");
	auto nextScene = mineScene::createScene();
	Director::getInstance()->replaceScene(nextScene);
}

/*
 *	Function		:	exitMenuCB
 *	Description		:	the call back func of exitMenu
 *	Calls			:	
 *	Input			:	the trigger of event  
 *	Output			:	NULL
 *	Return			:	NULL
 *	Others			:	eixt game
 */
void beginScene::exitMenuCB(Ref* r)
{
	log("exit the game");
	exit(0);
}