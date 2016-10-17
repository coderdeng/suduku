/*
 *	Copyright		:	open
 *	Author			:	YihaiDeng
 *	Date			:	2016-9-03
 *	Description		:	scene of the game, about draw the sudoku
 *						and the number, and other game logic
 *						just as check the number whether legitimate
 *						and the event listener of user touch
 */

#include "gameScene.h"
#include "globalData.h"
#include "keyLayer.h"
#include "menuLayer.h"
#include <string>
#include <sstream>
#include <random>
#include <ctime>

#define CONVERT_TO_GL(X)	Director::getInstance()->convertToGL(X)
#define WIN_SIZE			Director::getInstance()->getVisibleSize()

#define ROOT_NODE			"rootNode"
#define MENU_LAYER			"menuLayer"
#define KEY_LAYER			"keyLayer"

USING_NS_CC;

/*
 *	Function		:	createScene()
 *	Description		:	create the scene of the game 
 *	Calls			:	Scene::create(), gameScene::create(), 
 *						Scene::addChild()
 *	Return			:	return a scene of the game
 *	Others			:	NULL
 */
Scene* gameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = gameScene::create();
	scene->addChild(layer);
	return scene;
}

/*
 *	Function		:	init()
 *	Description		:	initiate hte gameScene layer
 *	Calls			:	gameScene::drawSudoku(), gameScene::drawNumber()
 *	Return			:	if initite succeed return true,
 *						else return false
 *	Others			:	it will be called by gameScene::create()
 */
bool gameScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	_blankCount = 81;
	initDataLine();

	auto rootNode = Node::create();
	auto keylayer = keyLayer::create();
	auto menulayer = menuLayer::create();
	
	// key layer setting
	keylayer->setAnchorPoint(Vec2(0.5f, 0.5f));
	keylayer->setPosition(
		Vec2(WIN_SIZE.width / 2 - keylayer->getContentSize().width / 2,
			WIN_SIZE.height / 3));
	keylayer->setVisible(false);

	// menu layer setting
	menulayer->setAnchorPoint(Vec2(0, 0));
	menulayer->setPosition(Vec2(0, 0));
	menulayer->setVisible(false);
	
	rootNode->addChild(keylayer, 2, KEY_LAYER);
	rootNode->addChild(menulayer, 3, MENU_LAYER);

	setKeyboardEnabled(true);

	addChild(rootNode, 1, ROOT_NODE);

	drawSudoku();
	drawNumber();

	log("init succeed");

	return true;
}

/*
 *	Function		:	drawSudoku
 *	Description		:	draw sudoku back check 
 *	Calls			:	cocos2d-x func 
 *	Others			:	draw a 9 * 9 check of the game
 */
void gameScene::drawSudoku()
{
	log("draw sudoku begin");
	for (int y = 0; y < 9; ++y) {
		for (int x = 0; x < 9; ++x) {
			auto tmp_btn = ui::Button::create("checknull.png");
			tmp_btn->setScale(2);
			tmp_btn->setTitleText(num_to_str(y * 9 + x));
			tmp_btn->setAnchorPoint(Vec2(0, 1));
			tmp_btn->setPosition(
				CONVERT_TO_GL( Vec2( 80*x, 140*y + 10 ) ) );
			tmp_btn->setTag(y * 9 + x);
			_numberArray.pushBack(tmp_btn);
			auto rootNode = getChildByName(ROOT_NODE);
			rootNode->addChild(tmp_btn);
		}
	}
	log("draw Sudoku over");
}

/*
 *	Function		:	drawNumber 
 *	Description		:	draw the number on the sudoku 
 *	Calls			:	getData(string, offset)
 *	Others			:	load the data from the file
 *						and draw them on the checks
 *						offset of the tables, (line - 1) * 164
 *						add 
 */
void gameScene::drawNumber()
{
	log("draw number begin");
	std::string fileName = FileUtils::getInstance()->fullPathForFilename("tables.dt");
	getData(fileName, (DATA_LINE_INDEX - 1)*164);

	for (auto tmp_btn : _numberArray) {
		tmp_btn->setTitleText(num_to_str(_numArray.at(tmp_btn->getTag())));
		tmp_btn->setTitleFontSize(30);
		tmp_btn->setTitleColor(Color3B::BLACK);
		if (tmp_btn->getTitleText() != "") {
			tmp_btn->loadTextureNormal("checkfull.png");
			--_blankCount;
		}
		else
			tmp_btn->addClickEventListener(CC_CALLBACK_1(gameScene::clickListener, this));
	}
	log("draw number over");
}

/*
 *	Function		:	checkGameOver 
 *	Description		:	check the game weather it over
 *	Calls			:	null 
 *	Return			:	if game over return true
 *						else return false
 *	Others			:	just judge the number-check if full 
 */
bool gameScene::checkGameOver() const
{
	log("black count: %d", _blankCount);
	if (_blankCount == 0) {
		return true;
	}
	else
		return false;
}

/*
 *	Function		:	checkNumberLegitimate 
 *	Description		:	check the input number weather legitimate 
 *	Calls			:	null
 *	Input			:	_possibleNums
 *	Return			:	if number legitimate return true
 *						else return false
 *	Others			:	use the _possibleNums to check the number
 */
bool gameScene::checkNumberLegitimate(int index, int objNum) const
{
	std::vector<int> possibleNums(computePossibleNums(index));
	for (auto v : possibleNums) {
		if (v == objNum)
			return true;
	}
	return false;
}

/*
 *	Function		:	getData
 *	Description		:	get the sudoku data from file and offset 
 *						and pop some number 
 *	Input			:	fileName(string), the file name
 *						offset(int), whitch line datas offset
 *	Others			:	create the random num by tmie
 *						if random num == 0 push 0 into _numArray
 *						expression that is null
 */
void gameScene::getData(const std::string &fileName, int offset)
{
	log("get data begin");
	std::default_random_engine e(time(0));
	std::uniform_int_distribution<unsigned> u(0, 1);

	ssize_t fileSize;
	char *filePtr = 
		(char*)FileUtils::getInstance()->getFileData(fileName, "r", &fileSize);
	if (filePtr == nullptr)return;

	std::string lineStr(filePtr+offset, 164);
	std::istringstream iss(lineStr);

	int num;
	while (iss >> num) {
		if (u(e))
			_numArray.push_back(num);
		else
			_numArray.push_back(0);
	}
	
	delete filePtr;
	filePtr = nullptr;

	log("get data over");
}

/*
 *	Function		:	computePossibleNums 
 *	Description		:	compute the possible number of each null check
 *	Input			:	the check button index
 *	Output			:	the possible numbers of index check button
 *	Others			:	
 */
std::vector<int> gameScene::computePossibleNums(int index) const
{
	int i = index / 9;
	int j = index % 9;
	std::vector<int> possible_v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // 每一个index的合法数
	for (int x = 0; x < 9; ++x) {
		if (_numArray.at(i * 9 + x)) {
			possible_v[_numArray.at(i * 9 + x) - 1] = 0;
		}
	}
	for (int y = 0; y < 9; ++y) {
		if (_numArray.at(y * 9 + j)) {
			possible_v[_numArray.at(y * 9 + j) - 1] = 0;
		}
	}
	return possible_v;
}

/*
 *	Function		:	onEnter
 *	Description		:	inherit from the Layer 
 *						executed when the layer enter the scene
 *	Others			:	add some function when layer enter
 */
void gameScene::onEnter()
{
	Layer::onEnter();
}

/*
 *	Function		:	onExit
 *	Description		:	inherit from the layer
 *						executed when the layer exit the scene
 *	Others			:	add some function when layer exit
 */
void gameScene::onExit()
{
	log("gameScene::onExit()");
	Layer::onExit();
	removeAllChildren();
	Director::getInstance()->purgeCachedData();
	TextureCache::getInstance()->removeAllTextures();
}

/*
 *	Function		:	clickListener
 *	Description		:	the button click listener 
 *	Calls			:	 
 *	Input			:	ref(Ref*), the event source 
 *	Output			:	the button's tag 
 *	Others			:	offer the plant of number to user to select
 */
void gameScene::clickListener(Ref *ref)
{
	auto keylayer = static_cast<keyLayer*>
		(getChildByName(ROOT_NODE)->getChildByName(KEY_LAYER));
	auto menulayer = static_cast<keyLayer*>
		(getChildByName(ROOT_NODE)->getChildByName(MENU_LAYER));

	if (keylayer->isVisible() || menulayer->isVisible()) {
		keylayer->setVisible(false);
		keylayer->setTouchEnabled(false);
		menulayer->setVisible(false);
		menulayer->setTouchEnabled(false);
		return;
	}

	auto btn = static_cast<ui::Button*>(ref);

	keylayer->showWithCheck(btn->getTag());
}

/*
 *	Function		:	setCheckNumber
 *	Description		:	set the number to index black
 *	Calls			:	checkNumberLegitimate, checkGameOver
 *	Input			:	// 输入参数说明，包括每个参数的作  
                    	// 用、取值说明及参数间关系。  
 *	Others			:	check the number weather legitimate and set the back color
 */
void gameScene::setCheckNumber(int index, int number)
{
	auto rootNode = getChildByName(ROOT_NODE);
	auto btn = static_cast<ui::Button*>(rootNode->getChildByTag(index));

	// 如果设置的数字不变， 不用继续
	if (_numArray.at(index) == number)return;
	// 数字不合法
	if (!checkNumberLegitimate(index, number)) {
		// 该块不为空
		if (_numArray.at(index) != 0)
			++_blankCount;
		btn->setColor(Color3B::RED);
		_numArray[index] = 0;
	}
	// 数字合法
	else {
		// 该块原来为空
		if (_numArray.at(index) == 0)
			--_blankCount;
		btn->setColor(Color3B::GREEN);
		_numArray[index] = number;
	}

	btn->setTitleText(num_to_str(number));
	// 检查游戏是否结束并进入下一局
	if (checkGameOver()) {
		DATA_LINE_INDEX++;
		auto nextScene = gameScene::createScene();
		Director::getInstance()->replaceScene(nextScene);
	}
}

/*
 *	Function		:	onKeyReleased 
 *	Description		:	the key released event listener
 *	Calls			:	// 被本函数调用的函数清单  
 *	Input			:	
 *	Output			:	// 对输出参数的说明。 
 *	Return			:	
 *	Others			:	// 其它说明 
 */
void gameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	log("gameScene::onKeyReleased begin");
	static int firstTime = 0;
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
	case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:
		if (firstTime == 0) {
			firstTime = time(0);
			break;
		}
		if (time(0) - firstTime < 2) {
			writeLineToFile();
			exit(1);
		}
		else
			firstTime = 0;
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_M:
	case cocos2d::EventKeyboard::KeyCode::KEY_MENU:
		showTheMenu();
		break;
	default:
		break;
	}
	log("gameScene::onKeyReleased end");
}

/*
 *	Function		:	showTheMenu
 *	Description		:	add the menu into the game scene 
 *	Output			:	// 对输出参数的说明。 
 *	Return			:	// 函数返回值的说明
 *	Others			:	// 其它说明 
 */
void gameScene::showTheMenu() const
{
	auto rootNode = getChildByName(ROOT_NODE);
	auto menulayer = static_cast<menuLayer*>(rootNode->getChildByName(MENU_LAYER));
	menulayer->setVisible(!menulayer->isVisible());
	menulayer->setTouchEnabled(menulayer->isVisible());
}
/*
 *	Function		:	// 函数名称 
 *	Description		:	// 函数功能、性能等的描述 
 *	Return			:	// 函数返回值的说明 
 *	Others			:	// 其它说明 
 */
void gameScene::reStartGame()
{
	auto newScene = gameScene::createScene();
	Director::getInstance()->replaceScene(newScene);
}

/*
 *	Function		:	// 函数名称 
 *	Description		:	// 函数功能、性能等的描述 
 *	Others			:	// 其它说明 
 */
void gameScene::nextGame()
{
	++DATA_LINE_INDEX;
	auto nextScene = gameScene::createScene();
	Director::getInstance()->replaceScene(nextScene);
}