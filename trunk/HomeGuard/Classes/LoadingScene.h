//
//  LoadingScene.h
//  towadgame
//
//  Created by zhao on 14-9-16.
//
//

#ifndef __towadgame__LoadingScene__
#define __towadgame__LoadingScene__
#include "cocos2d.h"
#include "ui/cocosGui.h"

using namespace cocos2d;
using namespace ui;

class Loading:public Layer
{
public :
    static Scene * createScene();
    CREATE_FUNC(Loading);
    bool  init();
	// 加载资源的数量. 
    int numberOfLoadedRes;
	//总共资源数量
    int numberCount;
    void loadResources();//从文件加载资源到内存
	//资源加载回调
    void loadingCallBack(cocos2d::Texture2D *texture);
    void logic(float dt);
    ui::LoadingBar * loading;
	cocos2d::ParticleSystemQuad* loadbarParticle;
};

#endif /* defined(__towadgame__LoadingScene__) */
