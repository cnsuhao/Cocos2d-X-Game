#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StudyScene.h"
#include "Resource.h"
#include "QuestionBankScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

static const std::string _particleFiles[] = {
	"Particles/BoilingFoam.plist",
	"Particles/Galaxy.plist",
	"Particles/SmallSun.plist",
	"Particles/lines.plist",
	"Particles/Comet.plist",
	"Particles/LavaFlow.plist",
	"Particles/SpinningPeas.plist",
	"Particles/Flower.plist",
	"Particles/Phoenix.plist",
	"Particles/debian.plist",
};

// on "init" you need to initialize your instance
bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	//Node* mainSceneNode = NULL;
	//LanguageType languageType = Application::getInstance()->getCurrentLanguage();
	//if (languageType == LanguageType::CHINESE)
	//{
	//	mainSceneNode = CSLoader::createNode("MainScene_Chinese.csb");
	//}
	//else
	//{
	//	mainSceneNode = CSLoader::createNode("MainScene_English.csb");
	//}

	auto mainSceneNode = CSLoader::createNode("MainScene_Chinese.csb");

	addChild(mainSceneNode);

	/// 考试
	auto studyBtn = (Button*)mainSceneNode->getChildByTag(STUDY_TAG);
	studyBtn->setZoomScale(0.2f);
	studyBtn->setPressedActionEnabled(true);
	studyBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::onTouchStudyBtn, this));

	/// 题库设置
	auto questionBankSetBtn = (Button*)mainSceneNode->getChildByTag(EXAMSET_TAG);
	questionBankSetBtn->setZoomScale(0.2f);
	questionBankSetBtn->setPressedActionEnabled(true);
	questionBankSetBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::onTouchQuestionBankSet, this));

	/// 系统设置
	auto sysSetBtn = (Button*)mainSceneNode->getChildByTag(SET_TAG);
	sysSetBtn->setZoomScale(0.2f);
	sysSetBtn->setPressedActionEnabled(true);
	sysSetBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::onTouchSystemSetBtn, this));

	/// 关于
	auto aboutBtn = (Button*)mainSceneNode->getChildByTag(ABOUT_TAG);
	aboutBtn->setZoomScale(0.2f);
	aboutBtn->setPressedActionEnabled(true);
	aboutBtn->addTouchEventListener(CC_CALLBACK_2(MainScene::onTouchAboutBtn, this));

	/// 加载下雨离子
	cocos2d::ParticleSystemQuad* rainPartic = ParticleSnow::create();

	rainPartic->setLife(3);
	rainPartic->setLifeVar(1);

	// gravity
	rainPartic->setGravity(Vec2(0, -10));

	// speed of particles
	rainPartic->setSpeed(130);
	rainPartic->setSpeedVar(30);


	Color4F startColor = rainPartic->getStartColor();
	startColor.r = 0.9f;
	startColor.g = 0.9f;
	startColor.b = 0.9f;
	rainPartic->setStartColor(startColor);

	Color4F startColorVar = rainPartic->getStartColorVar();
	startColorVar.b = 0.1f;
	rainPartic->setStartColorVar(startColorVar);

	rainPartic->setEmissionRate(rainPartic->getTotalParticles() / rainPartic->getLife());

	rainPartic->setTexture(Director::getInstance()->getTextureCache()->addImage(s_snow));

	auto s = Director::getInstance()->getWinSize();
	if (rainPartic != nullptr)
	{
		rainPartic->setPosition(Vec2(s.width / 2, s.height));
	}

	mainSceneNode->addChild(rainPartic, 10);

	schedule(CC_SCHEDULE_SELECTOR(MainScene::update), 10.0f);

    return true;
}

void MainScene::update(float delta)
{

}

void MainScene::onTouchStudyBtn(Ref* sender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		Scene* scene = nullptr;
		scene = StudyScene::createScene();
		if (scene != nullptr)
		{
			SimpleAudioEngine::getInstance()->playEffect("audio/pickup_coin.mp3");
			Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0, scene, false));
		}
	}
}

void MainScene::onTouchQuestionBankSet(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		Scene* scene = nullptr;
		scene = QuestionBankScene::createScene();
		if (scene != nullptr)
		{
			SimpleAudioEngine::getInstance()->playEffect("audio/pickup_coin.mp3");
			Director::getInstance()->replaceScene(TransitionPageTurn::create(1.0, scene, false));
		}
	}
}

void MainScene::onTouchSystemSetBtn(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		SimpleAudioEngine::getInstance()->playEffect("audio/pickup_coin.mp3");
	}
}

void MainScene::onTouchAboutBtn(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		SimpleAudioEngine::getInstance()->playEffect("audio/pickup_coin.mp3");
	}
}




