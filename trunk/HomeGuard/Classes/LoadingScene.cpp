//
//  LoadingScene.cpp
//  towadgame
//
//  Created by zhao on 14-9-16.
//
//

#include "LoadingScene.h"
#include "LevelSelect.h"
#include "cocostudio/cocostudio.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

Scene * Loading::createScene()
{
    Scene * scene=Scene::create();
    auto layer=Loading::create();
    scene->addChild(layer);
    return scene;
}

bool  Loading::init()
{
    if(!Layer::init())
    {
        return false;
    }
 
	auto node = CSLoader::createNode("loadingScene.csb");
	node->setAnchorPoint(Vec2(0.5, 0.5));
	node->setPosition(Director::getInstance()->getWinSize().width / 2,
		Director::getInstance()->getWinSize().height / 2);
	addChild(node);

    auto load_ui = node->getChildByName("ui_loading_1_node");

	//初始化资源加载进度条
    loading = (LoadingBar *)load_ui->getChildByName("RootPanel")->getChildByName("res_LoadingBar");
    loading->setPercent(0);
	//获取资源加载特效
	loadbarParticle = (ParticleSystemQuad*)load_ui->getChildByName("RootPanel")->getChildByName("loadingbar_Particle");
    this->numberOfLoadedRes=1;
    this->numberCount=23;

    loadResources(); 

    this->schedule(schedule_selector(Loading::logic));
    return true;
}
//TODO resouce load class
void Loading::loadResources()
{
	//预加载音频文件
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(FileUtils::getInstance()->fullPathForFilename("sound/music.mp3").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/dead.wav" ).c_str());
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/button.wav").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/comeout.wav").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/shoot.wav").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/tip.wav").c_str() );
    numberOfLoadedRes++;
    SimpleAudioEngine::getInstance()->preloadEffect(FileUtils::getInstance()->fullPathForFilename("sound/dead.mp3").c_str() );
    numberOfLoadedRes++;

	//预加载图片资源
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("PlayResource.plist");
    numberOfLoadedRes++;
    Director::getInstance()->getTextureCache()->addImageAsync("playbg.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("playbg1.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("successfulBg.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("btn_back.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("btn_back_press.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("card_1.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("card_2.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("card_3.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("LevelInfoPanel.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("House.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("selectLevelBg.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("selectLevelBg1.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("selectLevelBg2.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("start_1.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("start_2.png", CC_CALLBACK_1(Loading::loadingCallBack, this));
}

void Loading::loadingCallBack(cocos2d::Texture2D *texture)
{
    numberOfLoadedRes++;
//	Sleep(50);
}
//更新UI
void Loading::logic(float dt)
{
    float percent = (float)numberOfLoadedRes / (float)numberCount * 100;
    loading->setPercent(percent);

	loadbarParticle->setPosition(loading->getPosition().x + loading->getCustomSize().width * numberOfLoadedRes / numberCount,
		loadbarParticle->getPosition().y);
    
	if (numberOfLoadedRes == numberCount)
	{
		Director::getInstance()->replaceScene(LevelSelect::createScene());
	}
}
