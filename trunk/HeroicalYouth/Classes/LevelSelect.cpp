//
//  LevelSelect.cpp
//  towadgame
//
//  Created by zhao on 14-9-16.
//
//

#include "LevelSelect.h"
#include "LevelInfo.h"
#include "cocostudio/cocostudio.h"
#include "ui/cocosGui.h"
using namespace ui;
Scene * LevelSelect::createScene(){
    Scene * scene=Scene::create();
    auto layer=LevelSelect::create();
    scene->addChild(layer);
    return scene;
}

bool  LevelSelect::init(){
    if(!Layer::init())
    {
        return false;
    }
	//关卡选择响应优化
	auto node = CSLoader::createNode("levelSelectScene.csb");
	addChild(node);

	auto ui_levelSelect_1 = node->getChildByName("ui_levelSelect_1");

	auto level_1_Btn = static_cast<Button*>(ui_levelSelect_1->getChildByName("RootPanel")->getChildByName(
		"select_PageView")->getChildByName("Panel_1")->getChildByName("level_1"));

	level_1_Btn->addTouchEventListener([](Ref* sender, Widget::TouchEventType etype) {
		if (etype == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(LevelInfo::createScene());
		}
	});

    return true;
}
