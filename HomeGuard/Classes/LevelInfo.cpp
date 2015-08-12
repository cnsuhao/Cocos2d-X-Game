//
//  LevelInfo.cpp
//  towadgame
//
//  Created by zhao on 14-9-16.
//
//

#include "LevelInfo.h"
#include "GameScene.h"
#include "cocostudio/cocostudio.h"
#include "ui/cocosGui.h"

using namespace ui;
Scene * LevelInfo::createScene(){
    Scene * scene=Scene::create();
    auto layer=LevelInfo::create();
    scene->addChild(layer);
    return scene;
}

bool  LevelInfo::init(){
    if(!Layer::init())
    {
        return false;
    }

	auto node = CSLoader::createNode("levelInfoScene.csb");
	node->setAnchorPoint(Vec2(0.5, 0.5));
	node->setPosition(Director::getInstance()->getWinSize().width / 2,
		Director::getInstance()->getWinSize().height / 2);
	addChild(node);

	auto load_ui = node->getChildByName("ui_levelInfo_dlg");

	auto startBtn = (Button*)load_ui->getChildByName("RootPanel")->getChildByName("start");
	startBtn->addTouchEventListener([](Ref* sender, Widget::TouchEventType eType) {
		if (eType == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(GameScene::createScene());
		}
	});

	auto backBtn = (Button*)load_ui->getChildByName("RootPanel")->getChildByName("back");
	backBtn->addTouchEventListener([](Ref* sender, Widget::TouchEventType eType) {
		if (eType == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->replaceScene(GameScene::createScene());
		}
	});

	return true;

#if 0
    auto node= cocostudio::SceneReader::getInstance()->createNodeWithSceneFile("publish/scene04_levelinfo.json");
    this->addChild(node);
    node->setScaleX(1136/960.0);

    auto render=(cocostudio::ComRender*)node->getChildByTag(10012)->getComponent("GUIComponent");
    Button * btstart=(Button *)render->getNode()->getChildByTag(5)->getChildByTag(6);
    btstart->addTouchEventListener([](Ref* obj,Widget::TouchEventType et){
        if(et==Widget::TouchEventType::ENDED)
        {    Director::getInstance()->replaceScene(GameScene::createScene());        }
    });
    //执行ui动画
    auto act=cocostudio::ActionManagerEx::getInstance()->getActionByName("ui_levelinfo_1.json", "Animation0");
//     render->getNode()->runAction(act->get);
    act->play();
    return true;
#endif
}
