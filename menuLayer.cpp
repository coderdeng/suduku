#include "menuLayer.h"

USING_NS_CC;

#define	ROOT_NODE		"ROOTNODE"

/*
 *	Function		:	init
 *	Description		:	init the menu layer 
 *	Calls			:	// 被本函数调用的函数清单 
 *	Output			:	// 对输出参数的说明。 
 *	Return			:	// 函数返回值的说明 
 *	Others			:	// 其它说明 
 */
bool menuLayer::init()
{
	log("menuLayer::init() begin");
	
	if (!Layer::init()) {
		return false;
	}
	auto winSize = Director::getInstance()->getVisibleSize();
	auto rootNode = LayerColor::create(
		Color4B(200, 200, 200, 200), winSize.width / 2, winSize.height);

	setContentSize(rootNode->getContentSize());

	addChild(rootNode, 1, ROOT_NODE);

	addMenu();

	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	
	log("menuLayer::init() end");
	return true;
}

/*
 *	Function		:	addMenu
 *	Description		:	add the menu into this layer 
 *	Others			:	// 其它说明 
 */
void menuLayer::addMenu()
{
	log("addMenu begin");
	MenuItemFont::setFontSize(50);
	
	auto menuReGame = MenuItemFont::create("restart", CC_CALLBACK_1(menuLayer::reGameCB, this));
	auto menuExitGame = MenuItemFont::create("exit game", CC_CALLBACK_1(menuLayer::exitCB, this));
	auto menuNextGame = MenuItemFont::create("next game", CC_CALLBACK_1(menuLayer::nextGameCB, this));

	menuReGame->setColor(Color3B::BLACK);
	menuExitGame->setColor(Color3B::BLACK);
	menuNextGame->setColor(Color3B::BLACK);

	auto layerSize = getContentSize();

	menuReGame->setPosition(Vec2(-layerSize.width / 2, 0 + 100));
	menuExitGame->setPosition(Vec2(-layerSize.width / 2, 0));
	menuNextGame->setPosition(Vec2(-layerSize.width / 2, 0 - 100));

	auto menu = Menu::create(menuReGame, menuExitGame, menuNextGame, NULL);
	
	getChildByName(ROOT_NODE)->addChild(menu);
	log("addMenu ends");
}

/*
 *	Function		:	// 函数名称 
 *	Description		:	// 函数功能、性能等的描述 
 */
void menuLayer::reGameCB(Ref *r)
{
	log("restart game");
	static_cast<gameScene*>(getParent()->getParent())->reStartGame();
}

/*
 *	Function		:	// 函数名称 
 *	Description		:	// 函数功能、性能等的描述 
 */
void menuLayer::exitCB(Ref *r)
{
	log("eixt game");
	exit(1);
}

/*
 *	Function		:	// 函数名称 
 *	Description		:	// 函数功能、性能等的描述 
 */
void menuLayer::nextGameCB(Ref *r)
{
	log("next game");
	static_cast<gameScene*>(getParent()->getParent())->nextGame();
}

/*
*	Function		:	// 函数名称
*	Description		:	// 函数功能、性能等的描述
*/
bool menuLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

/*
*	Function		:	// 函数名称
*	Description		:	// 函数功能、性能等的描述
*/
void menuLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	log("menuLayer ontouchmoved");
	unused_event->stopPropagation();
}

/*
*	Function		:	// 函数名称
*	Description		:	// 函数功能、性能等的描述
*/
void menuLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	setVisible(false);
	setTouchEnabled(false);
}