#ifndef _WORDCARDLINKMANAGER_H_
#define _WORDCARDLINKMANAGER_H_

#include <map>
#include <list>
#include "WordCard.h"
class WordCardManager
{
	struct _segment{
		cocos2d::Point p1;
		cocos2d::Point p2;
	};

	cocos2d::Point pre_point;
	cocos2d::Point cur_point;
	cocos2d::Point startPoint;

	std::vector<cocos2d::Point> MovePoints;
	std::vector<cocos2d::Point> DeletePoints;
	WordCard* startWordCard;
	cocos2d::DrawNode* lineDrawNode;
	std::vector<_segment> CreateDrawNode;
	std::vector<cocos2d::DrawNode*> saveDrawNode;
	cocos2d::DrawNode* startPotDrawNode;

public:
	typedef std::map<int, WordCard*> WordCardLinkInfoMap;
	struct WordCardLinkInfo
	{
		WordCardLinkInfo()
		{
			EnCard = nullptr;
			ZhCard = nullptr;
		};
		
		WordCardLinkInfo(WordCard* _EnCard, WordCard* _ZhCard)
		{
			EnCard = _EnCard;
			ZhCard = _ZhCard;
		}
		WordCard* EnCard;
		WordCard* ZhCard;
	};

	typedef std::list<WordCard*> WordCardLinkInfoList;

public:
	static WordCardManager* instance()
	{
		static WordCardManager inst;
		return &inst;
	}

	bool init(cocos2d::ui::Layout* enLayout, cocos2d::ui::Layout* zhLayout);

	void addCard(WordCard* cardLinkInfo);

	/// ¥¥Ω® ‘Ã‚
	bool createTest();

	void update(cocos2d::Node* scene);

private:
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);

	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	WordCard* destIsValid(WordCard::CardType destType, cocos2d::Vec2 destPosion);

private:
	WordCardLinkInfoList wordCardLinkInfoList;
	cocos2d::ui::Layout* en_Layout;
	cocos2d::ui::Layout* zh_Layout;
	

};


#endif//_WORDCARDLINKMANAGER_H_