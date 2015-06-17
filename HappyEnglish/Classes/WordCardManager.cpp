#include "cocos2d.h"
#include "WordCardManager.h"
#include "WordCard.h"
#include "ExaminationPaper.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
USING_NS_CC::ui;
using namespace CocosDenshion;

bool WordCardManager::init(cocos2d::ui::Layout* enLayout, cocos2d::ui::Layout* zhLayout)
{
	en_Layout = enLayout;
	zh_Layout = zhLayout;

	lineDrawNode = nullptr;

	wordCardLinkInfoList.clear();

	/// 初始化答题卷
	if (!ExaminationPaper::defaultInstance()->loadQuestionBank()) return false;

	createTest();

	return true;
}

void WordCardManager::update(cocos2d::Node* scene)
{
	for (uint32_t i = 0; i < CreateDrawNode.size(); ++i)
	{
		auto node = DrawNode::create();
		// Draw segment
		node->drawSegment(CreateDrawNode[i].p1, CreateDrawNode[i].p2, 6, Color4F(1, 0, 1, 0.5));
		scene->addChild(node);
	}

	CreateDrawNode.clear();

	for (uint32_t i = 0; i < MovePoints.size(); ++i){

		scene->removeChild(lineDrawNode);

		lineDrawNode = DrawNode::create();
		// Draw segment
		lineDrawNode->drawSegment(startPoint, MovePoints[i], 6, Color4F(1, 0, 1, 0.5));
		scene->addChild(lineDrawNode);
	}

	MovePoints.clear();
	for (uint32_t i = 0; i < DeletePoints.size(); ++i)
	{
		scene->removeChild(lineDrawNode);
	}
	DeletePoints.clear();

}

void WordCardManager::addCard(WordCard* cardLinkInfo)
{
	wordCardLinkInfoList.push_back(cardLinkInfo);
}

bool WordCardManager::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	auto target = static_cast<WordCard*>(event->getCurrentTarget());

	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	if (rect.containsPoint(locationInNode) && target->getPotDrawNode() == NULL)
	{
		target->setOpacity(100);
		log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);

		Size cardSize = target->getContentSize();
		float y = target->getType() == WordCard::CardType_ZH ? cardSize.height : 0;

		Vec2 drawPoint(cardSize.width / 2, y);

		startWordCard = target;
		pre_point = cur_point = startPoint = target->convertToWorldSpace(drawPoint);

		target->setPotDrawNode(drawPoint);
	
		return true;
	}

	return false;
}

void WordCardManager::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
	auto target = static_cast<WordCard*>(event->getCurrentTarget());
	Point location = touch->getLocation();
	cur_point = location;
	if ((pre_point - cur_point).getLengthSq() > 25){
		MovePoints.push_back(location);
		pre_point = cur_point;
	}
}

void WordCardManager::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	auto target = static_cast<WordCard*>(event->getCurrentTarget());
	target->setOpacity(255);

	WordCard::CardType destType = target->getType() == WordCard::CardType_ZH ? WordCard::CardType_EN : WordCard::CardType_ZH;
	WordCard* destTarget = destIsValid(destType, touch->getLocation());
	if (destTarget && destTarget->getPotDrawNode() == NULL)
	{
		Size cardSize = destTarget->getContentSize();
		float y = destTarget->getType() == WordCard::CardType_ZH ? cardSize.height : 0;

		Vec2 drawPoint(cardSize.width / 2, y);

		Vec2 destPoint = destTarget->convertToWorldSpace(drawPoint);
		MovePoints.push_back(destPoint);

		destTarget->setPotDrawNode(drawPoint);
		_segment segInfo = { startPoint, destPoint };
		CreateDrawNode.push_back(segInfo);
		SimpleAudioEngine::getInstance()->playEffect("audio/jump.mp3");
	}
	else
	{
		DeletePoints.push_back(touch->getLocation());
		startWordCard->removePotDrawNode();
	}
}

WordCard* WordCardManager::destIsValid(WordCard::CardType destType, Vec2 destPosion)
{
	WordCardLinkInfoList::iterator it = wordCardLinkInfoList.begin();
	for (; it != wordCardLinkInfoList.end(); ++it)
	{
		if ((*it)->getType() == destType)
		{
			Vec2 locationInNode = (*it)->convertToNodeSpace(destPosion);
			Size s = (*it)->getContentSize();
			Rect rect = Rect(0, 0, s.width, s.height);

			if (rect.containsPoint(locationInNode))
			{
				return *it;
			}
		}
	}

	return NULL;
}

bool WordCardManager::createTest()
{
	ExaminationPaper::Questoins questonInfo;
	if (!ExaminationPaper::defaultInstance()->getQuestion(questonInfo))
	{
		return false;
	}

	for (uint32_t i = 0; i < questonInfo.size(); ++i)
	{
		auto enWordCard = WordCard::create(questonInfo[i].EnQuestion, WordCard::CardType::CardType_EN);
		auto zhWordCard = WordCard::create(questonInfo[i].ZhQuestion, WordCard::CardType::CardType_ZH);

		en_Layout->addChild(enWordCard->getLayout());
		zh_Layout->addChild(zhWordCard->getLayout());
	 
		addCard(enWordCard);
		addCard(zhWordCard);


		/// 添加事件监听
		auto cardlistener = EventListenerTouchOneByOne::create();
		cardlistener->setSwallowTouches(true);

		cardlistener->onTouchBegan = CC_CALLBACK_2(WordCardManager::onTouchBegan, this);
		cardlistener->onTouchMoved = CC_CALLBACK_2(WordCardManager::onTouchMoved, this);
		cardlistener->onTouchEnded = CC_CALLBACK_2(WordCardManager::onTouchEnded, this);

		enWordCard->getEventDispatcher()->addEventListenerWithSceneGraphPriority(cardlistener, enWordCard);
		enWordCard->getEventDispatcher()->addEventListenerWithSceneGraphPriority(cardlistener->clone(), zhWordCard);
	}

	return true;
}