#include "QuestionBankScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainScene.h"
#include <fstream>
#include "ExaminationPaper.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d::ui;
USING_NS_CC;

#ifdef WIN32

#include <direct.h>
#include <io.h>

#elif LINUX

#include <stdarg.h>
#include <sysstat.h>

#endif

#ifdef WIN32

#define ACCESS _access
#define MKDIR(a) _mkdir((a))

#elif LINUX

#define ACCESS access
#define MKDIR(a) mkdir((a),0755)

#endif

int CreatDir(char *pszDir)
{

#if 0
	int i = 0;
	int iRet;
	int iLen = strlen(pszDir);

	//鍦ㄦ湯灏惧姞/
	if (pszDir[iLen - 1] != '\\' && pszDir[iLen - 1] != '/')
	{
		pszDir[iLen] = '/';
		pszDir[iLen + 1] = '\0';
	}

	// 鍒涘缓鐩綍
	for (i = 0; i <= iLen; i++)
	{
		if (pszDir[i] == '\\' || pszDir[i] == '/')
		{
			pszDir[i] = '\0';

			//濡傛灉涓嶅瓨鍦�,鍒涘缓
			iRet = ACCESS(pszDir, 0);
			if (iRet != 0)
			{
				iRet = MKDIR(pszDir);
				if (iRet != 0)
				{
					return -1;
				}
			}
			//鏀寔linux,灏嗘墍鏈塡鎹㈡垚/
			pszDir[i] = '/';
		}
	}

#endif
	return 0;
}

QuestionBankScene::QuestionBankScene()
{
}

QuestionBankScene::~QuestionBankScene()
{
}

cocos2d::Scene* QuestionBankScene::createScene()
{
	auto scene = Scene::create();
	auto layer = QuestionBankScene::create();
	scene->addChild(layer);
	return scene;
}

bool QuestionBankScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	/// 鍔犺浇鍦烘櫙
	questionBankScene = CSLoader::createNode("ExaminationPaperScene.csb");
	addChild(questionBankScene);

	// 璁剧疆鏍囬
	Text* alert = Text::create("鑻辫棰樺簱", "fonts/FontKaTong.ttf", 48);
	alert->setColor(Color3B(159, 168, 176));
	alert->setPosition(Vec2(questionBankScene->getContentSize().width / 3.0, questionBankScene->getContentSize().height - 80));
	questionBankScene->addChild(alert);

	/// 杩斿洖
	auto backBtn = (Button*)questionBankScene->getChildByTag(SceneTag_Back);
	backBtn->setZoomScale(0.2f);
	backBtn->setPressedActionEnabled(true);
	backBtn->addTouchEventListener([](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			auto scene = MainScene::createScene();
			if (scene != nullptr)
			{
				SimpleAudioEngine::getInstance()->playEffect("audio/pickup_coin.mp3");
				Director::getInstance()->replaceScene(TransitionMoveInL::create(1.0, scene));
			}
		}
	});

	/// 淇濆瓨
	auto layout = questionBankScene->getChildByTag(SceneTag_Layout);
	auto saveBtn = (Button*)layout->getChildByTag(QuestionTag_SAVE);
	saveBtn->setZoomScale(0.2f);
	saveBtn->setPressedActionEnabled(true);
	saveBtn->addTouchEventListener(CC_CALLBACK_2(QuestionBankScene::onTouchSaveBtn, this));
	/// 閲嶇疆
	auto resetBtn = (Button*)layout->getChildByTag(QuestionTag_Reset);
	resetBtn->setZoomScale(0.2f);
	resetBtn->setPressedActionEnabled(true);
	resetBtn->addTouchEventListener(CC_CALLBACK_2(QuestionBankScene::onTouchResetBtn, this));


	return true;
}

void QuestionBankScene::onTouchSaveBtn(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != Widget::TouchEventType::ENDED) return;

	SimpleAudioEngine::getInstance()->playEffect("audio/pickup_coin.mp3");

	std::map<std::string, std::string > questionBankMap;
	auto layout = questionBankScene->getChildByTag(SceneTag_Layout);
	std::string value;
	for (uint32_t i = QuestionTag_1; i < QuestionTag_12;++i)
	{
		auto textFild = (TextField*)layout->getChildByTag(i);
		std::string str = textFild->getString();
		if (str.empty())
		{
			continue;
		}

		if (i % 2 == 0 && !value.empty())
		{
			questionBankMap.insert(std::make_pair(str, value));
		}
		else if (!str.empty() && i % 2 ==1)
		{
			value = str;
		}
	}

	char path[] = "C:\\ProgramData\\EnglishStudy\\";
	CreatDir(path);

	std::ofstream writeFile("C:\\ProgramData\\EnglishStudy\\ExamBank.db", std::ios::app |std::ios::binary);
	if (writeFile.is_open())
	{
		std::map<std::string, std::string >::iterator it = questionBankMap.begin();
		for (; it != questionBankMap.end();it++)
		{
			writeFile << it->first<<":";
			writeFile << it->second << std::endl;
		}

		writeFile.close();
	}

	ExaminationPaper::defaultInstance()->loadQuestionBank();
}

void QuestionBankScene::onTouchResetBtn(Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	SimpleAudioEngine::getInstance()->playEffect("audio/pickup_coin.mp3");
}

