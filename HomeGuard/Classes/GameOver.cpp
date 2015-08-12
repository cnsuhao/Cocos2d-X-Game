//
//  GameOver.cpp
//  towadgame
//
//  Created by zhao on 14-9-15.
//
//

#include "GameOver.h"
Scene * GameOver::createScene(){
    auto scene=Scene::create();
    auto layer=GameOver::create();
    scene->addChild(layer);
    return  scene;
}
bool GameOver::init()
{
    if(!Layer::init())
    {
        return false;
    }
    //加载游戏失败图片
    auto sp=Sprite::createWithSpriteFrameName("failedPanel.png");
    sp->setPosition(Director::getInstance()->getWinSize()/2);
    this->addChild(sp);
    auto listener=EventListenerTouchOneByOne::create();
    listener->onTouchBegan=[&](Touch * t,Event * e){
        Director::getInstance()->replaceScene(GameScene::createScene());
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    return true;
}