/**
 * @file	E:\Develop\Cocos2dx\GameSrc\HappyEnglish\Classes\WordCard.h
 *
 * @brief	Declares the word card class.
 */

#ifndef _WORDCARD_H_

/**
 * @def	_WORDCARD_H_
 *
 * @brief	A macro that defines wordcard h.
 *
 * @author	Azraelly
 * @date	2015/6/10
 */

#define _WORDCARD_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

/**
 * @class	WordCard
 *
 * @brief	A word card.
 *
 * @author	Azraelly
 * @date	2015/6/10
 */

class WordCard :public cocos2d::Sprite
{
public:

	/**
	 * @enum	CardType
	 *
	 * @brief	Values that represent card types.
	 */

	enum CardType
	{
		///< An enum constant representing the card type en option
		CardType_EN = 1,
		///< An enum constant representing the card type zh option
		CardType_ZH = 2,
	};

public:

	/**
	 * @fn	WordCard::WordCard(const std::string& name, const CardType& type);
	 *
	 * @brief	Constructor.
	 *
	 * @author	Azraelly
	 * @date	2015/6/10
	 *
	 * @param	name	The name.
	 * @param	type	The type.
	 */

	WordCard(const std::string& name, const CardType& type);
	~WordCard();

	virtual bool init();

	/**
	 * @fn	bool WordCard::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	 *
	 * @brief	Executes the touch began action.
	 *
	 * @author	Azraelly
	 * @date	2015/6/10
	 *
	 * @param [in,out]	touch	If non-null, the touch.
	 * @param [in,out]	event	If non-null, the event.
	 *
	 * @return	true if it succeeds, false if it fails.
	 */

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);


	static WordCard* create(const std::string& name, const CardType& type)
	{
		WordCard *pRet = new(std::nothrow) WordCard(name, type);
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

	/**
	 * @fn	std::string WordCard::getName()
	 *
	 * @brief	Gets the name.
	 *
	 * @author	Azraelly
	 * @date	2015/6/10
	 *
	 * @return	The name.
	 */

	std::string getName()
	{
		return cardName;
	}

	CardType getType()
	{
		return cardType;
	}

	cocos2d::ui::Layout* getLayout()
	{
		return cardLayout;
	}

	cocos2d::DrawNode* getPotDrawNode()
	{
		return potDrawNode;
	}

	/**
	 * @fn	void WordCard::setPotDrawNode(cocos2d::Vec2 drawPoint);
	 *
	 * @brief	Sets pot draw node.
	 *
	 * @author	Azraelly
	 * @date	2015/6/10
	 *
	 * @param	drawPoint	The draw point.
	 */

	void setPotDrawNode(cocos2d::Vec2 drawPoint);

	/**
	 * @fn	void WordCard::setSegmentDrawNode(cocos2d::Vec2 startPoint, cocos2d::Vec2 stopPoint);
	 *
	 * @brief	Sets segment draw node.
	 *
	 * @author	Azraelly
	 * @date	2015/6/10
	 *
	 * @param	startPoint	The start point.
	 * @param	stopPoint 	The stop point.
	 */

	void setSegmentDrawNode(cocos2d::Vec2 startPoint, cocos2d::Vec2 stopPoint);

	void removePotDrawNode()
	{
		cocos2d::log("****************end ref:%d", potDrawNode->getReferenceCount());
		removeChild(potDrawNode, true);
		potDrawNode = nullptr;
	}

private:
	cocos2d::TTFConfig getTTFConfig(CardType type);

private:
	/** @brief	Type of the card. */
	CardType cardType;
	/** @brief	Name of the card. */
	std::string cardName;
	static char* cardStyle[];
	/** @brief	The pot draw node. */
	cocos2d::DrawNode* potDrawNode;
	/** @brief	The card layout. */
	cocos2d::ui::Layout* cardLayout;
};

#endif // !_WORDCARD_H_

