#include "keyLayer.h"
#include "globalData.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

/*
 *	Function		:	// �������� 
 *	Description		:	// �������ܡ����ܵȵ����� 
 *	Calls			:	// �����������õĺ����嵥 
 *	Table Accessed	:	// �����ʵı����������ǣ�������ݿ�����ĳ��� 
 *	Table Updated	:	// ���޸ĵı����������ǣ�������ݿ�����ĳ���  
 *	Input			:	// �������˵��������ÿ����������  
                    	// �á�ȡֵ˵�����������ϵ��  
 *	Output			:	// �����������˵���� 
 *	Return			:	// ��������ֵ��˵�� 
 *	Others			:	// ����˵�� 
 */
bool keyLayer::init()
{
	if (!Layer::init()) {
		return false;
	}
	// add children widget
	auto winSize = Director::getInstance()->getVisibleSize();

	auto colorLayer =
		LayerColor::create(Color4B(200, 200, 200, 200), 2 * winSize.width / 3, 2 * winSize.width / 3);
	setContentSize(colorLayer->getContentSize());

	addChild(colorLayer, 1, "rootNode");
	
	addNubmerButton();
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	log("key layer create and init succeed");

	return true;
}

/*
 *	Function		:	// �������� 
 *	Description		:	// �������ܡ����ܵȵ����� 
 *	Calls			:	// �����������õĺ����嵥 
 *	Output			:	// �����������˵���� 
 *	Return			:	// ��������ֵ��˵�� 
 *	Others			:	// ����˵�� 
 */
void keyLayer::addNubmerButton()
{
	auto rootNode = getChildByName("rootNode");

	for (int i = 1; i <= 9; ++i) {
		int x = (i - 1) % 3;
		int y = (i - 1) / 3;
		auto btn = ui::Button::create();
		btn->setTitleText(num_to_str(i));
		btn->setTag(i);
		btn->setTitleFontSize(70.0f);
		int btnDistancex = (getContentSize().width - btn->getContentSize().width * 3) / 4;
		int btnDistancey = (getContentSize().height - btn->getContentSize().height * 3) / 4;
		btn->setAnchorPoint(Vec2(0.0f, 0.0f));
		btn->setPosition(
			Vec2(btnDistancex *( x + 1) + btn->getContentSize().width * x,
				btnDistancey * (y + 1) + btn->getContentSize().height * y));
		btn->setTitleColor(Color3B::BLACK);
		btn->addClickEventListener(CC_CALLBACK_1(keyLayer::buttonClickListener, this));
		rootNode->addChild(btn);
		log("keyLayer btn size: w = %f, h = %f", 
			btn->getContentSize().width, btn->getContentSize().height);
		btn = nullptr;
	}

	rootNode = nullptr;
}

/*
 *	Function		:	// �������� 
 *	Description		:	// �������ܡ����ܵȵ����� 
 *	Output			:	// �����������˵���� 
 *	Return			:	// ��������ֵ��˵�� 
 *	Others			:	// ����˵�� 
 */
void keyLayer::buttonClickListener(Ref *r)
{
	auto btn = static_cast<ui::Button*>(r);
	this->setVisible(false);
	static_cast<gameScene*>(getParent()->getParent())
		->setCheckNumber(_currentCheckIndex, btn->getTag());
	btn = nullptr;
}

/*
 *	Function		:	showWithCheck 
 *	Description		:	show the keylayer with the check index and
 *						set the check index to the arg
 *	Input			:	the button tag whitch you click 
 *	Others			:	
 */
void keyLayer::showWithCheck(int checkIndex)
{
	this->setVisible(true);
	this->setTouchEnabled(true);
	_currentCheckIndex = checkIndex;
}

/*
*	Function		:	// ��������
*	Description		:	// �������ܡ����ܵȵ�����
*/
bool keyLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

/*
*	Function		:	// ��������
*	Description		:	// �������ܡ����ܵȵ�����
*/
void keyLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	unused_event->stopPropagation();
}

/*
*	Function		:	// ��������
*	Description		:	// �������ܡ����ܵȵ�����
*/
void keyLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	setVisible(false);
	setTouchEnabled(false);
}