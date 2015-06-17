#ifndef _EXAMSCENE_H_
#define _EXAMSCENE_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ExamScene :public cocos2d::Layer
{
	enum SceneNode_Tag
	{
		Back_TAG = 1,
		EnLayout_TAG =2,
		ZhLayout_TAG =3,
	};

	enum CourseLayout_Tag
	{
		CourseLayout_Exam1 = 1,
		CourseLayout_Exam2 = 2,
		CourseLayout_Exam3,
		CourseLayout_Exam4,
		CourseLayout_Exam5,
		CourseLayout_Exam6,
		CourseLayout_Exam7,
		CourseLayout_Exam8
	};

	struct _segment{
		cocos2d::Point p1;
		cocos2d::Point p2;
	};

	struct ExmamInfo
	{
		ExmamInfo(){};
		ExmamInfo(std::string en, std::string zh)
		{
			ENContent = en;
			ZHContent = zh;
		}

		std::string ENContent;
		std::string ZHContent;
	};

	cocos2d::ParticleSystemQuad*    _emitter;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(ExamScene);

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

protected:
	
	void onDraw(const cocos2d::Mat4 &transform, bool transformUpdated);
	cocos2d::CustomCommand _customCommand;

private:
	cocos2d::Point pre_point;
	cocos2d::Point cur_point;
	_segment seg;
	std::vector<_segment> segment;

	std::vector<_segment> segmentLine;

	cocos2d::DrawNode* drawnode;


private:
	cocos2d::Node* studyNodeScene;

};


#endif //_EXAMSCENE_H_