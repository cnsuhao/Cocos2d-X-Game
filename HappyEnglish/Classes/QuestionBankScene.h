#ifndef _QUESTIONBANKSCENE_H_
#define _QUESTIONBANKSCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class QuestionBankScene :public cocos2d::Layer
{
	enum SceneTag 
	{
		SceneTag_Back = 1,
		SceneTag_Layout = 2
	};

	enum QuestionTag
	{
		QuestionTag_1 = 1,
		QuestionTag_2 = 2,
		QuestionTag_3 = 3,
		QuestionTag_4 = 4,
		QuestionTag_5 = 5,
		QuestionTag_6 = 6,
		QuestionTag_7 = 7,
		QuestionTag_8 = 8,
		QuestionTag_9 = 9,
		QuestionTag_10 = 10,
		QuestionTag_11 = 11,
		QuestionTag_12 = 12,
		QuestionTag_SAVE = 20,
		QuestionTag_Reset = 21,
	};

public:
	QuestionBankScene();
	~QuestionBankScene();

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(QuestionBankScene);

private:
	void onTouchSaveBtn(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void onTouchResetBtn(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

private:
	cocos2d::Node* questionBankScene;


};


#endif //_QUESTIONBANKSCENE_H_