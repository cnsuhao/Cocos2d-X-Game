#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GameMenu.h"

USING_NS_CC;

//英雄儿女
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::createWithRect("HeroicalYouth", Rect(0, 0, 1136, 640));
		//glview = GLViewImpl::create("HeroicalYouth");
        director->setOpenGLView(glview);
		//影响从设计尺寸到手机屏幕的适配方案
		glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::FIXED_HEIGHT);
    }

	//从资源图片到设计尺寸的适配比例
	director->setContentScaleFactor(864.0f / 640.0f);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	// 添加资源搜索路径
	auto fileUtils = FileUtils::getInstance();
	std::vector<std::string> searchPaths;
	searchPaths.push_back("publishRes");
	searchPaths.push_back("publishRes/img");
	searchPaths.push_back("publishRes/fonts");
	searchPaths.push_back("publishRes/level");
	searchPaths.push_back("publishRes/map");
	searchPaths.push_back("publishRes/sound");
	fileUtils->setSearchPaths(searchPaths);

    // create a scene. it's an autorelease object
	auto scene = GameMenu::createScene();
    // run
    director->runWithScene(scene);
	//filetest
#if 0
	ValueMap levelinfo = FileUtils::getInstance()->getValueMapFromFile("level01.plist");
	ValueMap mapinfo = levelinfo["mapinfo"].asValueMap();
	ValueMap linfo = levelinfo["levelinfo"].asValueMap();
	CCLOG("level info=%s", mapinfo["mapfile"].asString().c_str());
	CCLOG("level info=%d", linfo["money"].asInt());
	ValueVector group = linfo["group"].asValueVector();
	CCLOG("一共有怪物波数%ld", group.size());
	for (int i = 0; i < group.size(); i++) {
		long npccount = group.at(i).asValueVector().size();
		ValueVector nowgroup = group.at(i).asValueVector();
		for (int j = 0; j < npccount; j++) {
			CCLOG("npc group %d type %d,hp %d", i + 1, nowgroup.at(j).asValueMap()["npctype"].asInt()
				, nowgroup.at(j).asValueMap()["npchp"].asInt());
		}
	}

#endif
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
