#include "StudyScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include "ExamScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace CocosDenshion;

cocos2d::Scene* StudyScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StudyScene::create();
	scene->addChild(layer);
	return scene;
}

bool StudyScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto studyNodeScene = CSLoader::createNode("StudyScene.csb");
	addChild(studyNodeScene);

	auto layout = studyNodeScene->getChildByTag(CourseLayout_TAG);

	auto exam1Btn = (Button*)layout->getChildByTag(CourseLayout_Exam1);
	exam1Btn->setZoomScale(0.2f);
	exam1Btn->setPressedActionEnabled(true);
	exam1Btn->addTouchEventListener([](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			auto scene = ExamScene::createScene();
			if (scene != nullptr)
			{
				SimpleAudioEngine::getInstance()->playEffect("audio/pickup_coin.mp3");
				Director::getInstance()->replaceScene(TransitionMoveInR::create(1.0, scene));
			}
		}
	});

	for (uint32_t i = CourseLayout_Exam1; i <= CourseLayout_Exam8; ++i)
	{
		auto examBtn = (Button*)layout->getChildByTag(i);
		if (i != CourseLayout_Exam1)
		{
			
			auto lockSprite = Sprite::create("EnglishExam/lock.png");
			lockSprite->setOpacity(230);
			log("x:%f, y:%f", examBtn->getPosition().x, examBtn->getPosition().y);
			lockSprite->setPosition(examBtn->getSize() / 2);
			examBtn->addChild(lockSprite);
		}

		TTFConfig ttfConfig("fonts/Schwarzwald.ttf", 32, GlyphCollection::NEHE);
		auto label1 = Label::createWithTTF(ttfConfig, "English\n   Exam", TextHAlignment::CENTER, 0);

		// Left
	//	auto label1 = LabelBMFont::create("English\n   Exam", "fonts/bitmapFontTest3.fnt");
		label1->setPosition(Vec2(label1->getContentSize().width/2+20, examBtn->getSize().height - 10 - label1->getContentSize().height / 2));
		examBtn->addChild(label1);
	}

	//加载动画： 
	auto *action = CSLoader::createTimeline("StudyScene.csb");
	studyNodeScene->runAction(action); 


	//播放动画： 
	action->gotoFrameAndPlay(0, 60, true);//从第0帧到60帧循环播放。还有其他重载函

	//返回首页按钮设置
	auto backMainSceneBtn = (Button*)studyNodeScene->getChildByTag(Back_TAG);
	backMainSceneBtn->setZoomScale(0.4);
	backMainSceneBtn->setPressedActionEnabled(true);
	backMainSceneBtn->addTouchEventListener(CC_CALLBACK_2(StudyScene::onTouchBackMainSceneBtn, this));

	return true;
}

void StudyScene::onTouchBackMainSceneBtn(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN:
	{
		log("Touch down");
	}
	break;
	case Widget::TouchEventType::MOVED:
		log("Touch move");
		break;
	case Widget::TouchEventType::ENDED:
	{
		auto scene = MainScene::createScene();
		if (scene != nullptr)
		{
			SimpleAudioEngine::getInstance()->playEffect("audio/pickup_coin.mp3");
			Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0, scene, true));
		}
		log("Touch up");
	}
	break;

	case Widget::TouchEventType::CANCELED:
		log("Touch canceled");
		break;
	default:
		break;
	}
}
