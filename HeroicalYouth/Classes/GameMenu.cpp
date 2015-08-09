//
//  GameMenu.cpp
//  towadgame
//
//  Created by zhao on 14-9-16.
//
//

#include "GameMenu.h"
#include "LoadingScene.h"
#include "cocostudio/cocostudio.h"
#include "ui/cocosGui.h"
using namespace ui;
Scene * GameMenu::createScene(){
    Scene * scene=Scene::create();
    auto layer=GameMenu::create();
    scene->addChild(layer);
    return scene;
}

bool  GameMenu::init(){
    if(!Layer::init())
    {
        return false;
    }
   
	auto node = CSLoader::createNode("gameMenuScene.csb");
	addChild(node);

	auto gameMenu_ui = node->getChildByName("ui_gameMenu_1");

	//��ʼ��Ϸ��ť��Ϣ��Ӧ
	auto startgamebtn = (Button*)gameMenu_ui->getChildByName("startgame");
	startgamebtn->addTouchEventListener([](Ref* sender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(Loading::createScene());
		}
	});

	//��Ϸ����
	//��Ϸ����

    return true;
}
