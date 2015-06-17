#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "ui/CocosGUI.h"

#include "cocos2d.h"

class MainScene : public cocos2d::Layer
{

	enum SceneNode_Tag
	{
		STUDY_TAG = 1,
		EXAMSET_TAG = 2,
		SET_TAG,
		ABOUT_TAG
	};

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);

private:
	void update(float delta);

	void onTouchStudyBtn(Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void onTouchQuestionBankSet(Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void onTouchSystemSetBtn(Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	void onTouchAboutBtn(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	
};

#endif // __HELLOWORLD_SCENE_H__
