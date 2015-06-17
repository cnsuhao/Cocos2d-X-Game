#include "ExamScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StudyScene.h"
#include "WordCardManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace CocosDenshion;

cocos2d::Scene* ExamScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ExamScene::create();
	scene->addChild(layer);
	return scene;
}

bool ExamScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	/// 加载场景
	studyNodeScene = CSLoader::createNode("ExamScene.csb");

	addChild(studyNodeScene);

	// 设置标题
	Text* alert = Text::create("English Study Exam", "fonts/Schwarzwald.ttf", 48);
	alert->setColor(Color3B(159, 168, 176));
	alert->setPosition(Vec2(studyNodeScene->getContentSize().width / 2.0, studyNodeScene->getContentSize().height - 30));
	studyNodeScene->addChild(alert);

	/// 返回试题选择界面
	auto backBtn = (Button*)studyNodeScene->getChildByTag(Back_TAG);
	backBtn->setZoomScale(0.2f);
	backBtn->setPressedActionEnabled(true);
	backBtn->addTouchEventListener([](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type){
		if (type == Widget::TouchEventType::ENDED)
		{
			auto scene = StudyScene::createScene();
			if (scene != nullptr)
			{
				SimpleAudioEngine::getInstance()->playEffect("audio/pickup_coin.mp3");
				Director::getInstance()->replaceScene(TransitionMoveInL::create(1.0, scene));
			}
		}
	});


	/// 英文Layout
	auto enLayout = (Layout*)studyNodeScene->getChildByTag(EnLayout_TAG);
	enLayout->setLayoutType(LayoutType::HORIZONTAL);
	//enLayout->setClippingEnabled(true);


	auto zhLayout = (Layout*)studyNodeScene->getChildByTag(ZhLayout_TAG);
	zhLayout->setLayoutType(LayoutType::HORIZONTAL);
	//enLayout->setClippingEnabled(true);

	WordCardManager::instance()->init(enLayout, zhLayout);

	std::string filename = "Particles/Upsidedown.plist";
	_emitter = ParticleSystemQuad::create(filename);
	studyNodeScene->addChild(_emitter, 10);
	return true;
}


void ExamScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(ExamScene::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void ExamScene::onDraw(const cocos2d::Mat4 &transform, bool transformUpdated)
{
	WordCardManager::instance()->update(studyNodeScene);
}

bool ExamScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	Point location = touch->getLocation();
	pre_point = cur_point = location;

	drawnode = DrawNode::create();
	studyNodeScene->addChild(drawnode);

	// Draw 4 circles
	for (int i = 0; i < 4; i++)
	{
		drawnode->drawDot(cur_point, 4 * (4 - i), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
	}

	return true;
}
void ExamScene::onTouchMoved(Touch *touch, Event *unused_event)
{
	//Point location = touch->getLocation();
	//cur_point = location;
	//if ((pre_point - cur_point).getLengthSq() > 25){
	//	seg.p1 = pre_point;
	//	seg.p2 = cur_point;
	//	segmentLine.push_back(seg);
	//	pre_point = cur_point;
	//}
}
void ExamScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	Point location = touch->getLocation();
	cur_point = location;

	seg.p1 = pre_point;
	seg.p2 = cur_point;
	segment.push_back(seg);
	pre_point = cur_point;
	segmentLine.push_back(seg);

	// Draw 4 circles
	for (int i = 0; i < 4; i++)
	{
		drawnode->drawDot(cur_point, 4 * (4 - i), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
	}

	if ((pre_point - cur_point).getLengthSq() > 25){
		seg.p1 = pre_point;
		seg.p2 = cur_point;
		segment.push_back(seg);
		segmentLine.push_back(seg);
		pre_point = cur_point;
	}
}
