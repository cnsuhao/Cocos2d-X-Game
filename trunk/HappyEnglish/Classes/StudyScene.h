#ifndef _STUDYSCENE_H_
#define _STUDYSCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class StudyScene:public cocos2d::Layer
{
	enum SceneNode_Tag
	{
		Back_TAG = 1,
		CourseLayout_TAG = 2,
	};

	enum CourseLayout_Tag
	{
		CourseLayout_Exam1 = 1,
		CourseLayout_Exam2 = 2,
		CourseLayout_Exam3,
		CourseLayout_Exam4,
		CourseLayout_Exam5,
		CourseLayout_Exam6,
		CourseLayout_Exam7,
		CourseLayout_Exam8
	};

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(StudyScene);

private:
	void onTouchBackMainSceneBtn(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

};


#endif