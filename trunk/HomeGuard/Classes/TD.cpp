//
//  TD.cpp
//  towadgame
//
//  Created by zhao on 14-9-11.
//
//

#include "TD.h"
#include "GameScene.h"
#include "Enemy.h"
#include "Bullet.h"
TD * TD::createNewTD(int type,int r,int c)
{
    TD * newTD=TD::create();
    if (type==1) {
    newTD->price=200;
    auto baseplate = Sprite::createWithSpriteFrameName("baseplate.png");
        baseplate->setAnchorPoint(Vec2::ZERO);
    newTD->addChild(baseplate);
        baseplate->setTag(10);
    newTD->setAnchorPoint(Vec2::ZERO);
    newTD->setPosition(c*72,r*72);
    newTD->type=type;
    newTD->row=r;
    newTD->col=c;
    auto rotateArrow = Sprite::createWithSpriteFrameName("arrow.png");
    rotateArrow->setPosition(36,55);
    rotateArrow->setTag(11);
    baseplate->addChild(rotateArrow);
    newTD->schedule(schedule_selector(TD::roateAndShoot), 0.5);
    }
    return newTD;
}

bool TD::init()
{
    if(!Node::init())
    {
        return false;
    }
    return true;
}

void TD::roateAndShoot(float t)
{
    if(GameScene::allEnemy.size()==0)
    {
		return ;
	}

	auto rotateArrow=this->getChildByTag(10)->getChildByTag(11);

    float lenth=0;
    int index=0;
    for (int i=0; i<GameScene::allEnemy.size(); i++) {
        auto nowEnemy=GameScene::allEnemy.at(i);
        if (lenth==0) {
            lenth=this->getPosition().distance(nowEnemy->getPosition());
        }
		else{
          if(this->getPosition().distance(nowEnemy->getPosition())<lenth){
				lenth=this->getPosition().distance(nowEnemy->getPosition());
				 index=i;
             }
        }
    }

    objEnemyIndex=index;
	Vec2 rotateVector = GameScene::allEnemy.at(index)->getPosition() - this->getPosition();
	float rotateRadians = rotateVector.getAngle();
	float rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians);
	this->ang = rotateDegrees;

	float speed = 0.5 / M_PI;
	float rotateDuration = fabs(rotateRadians * speed);

	rotateArrow->runAction(Sequence::create(
		RotateTo::create(rotateDuration, rotateDegrees),
		CallFunc::create(CC_CALLBACK_0(TD::shoot, this)), NULL));
}
void TD::shoot()
{
    if(GameScene::allEnemy.size()==0){
		return;
	}

    if(objEnemyIndex>GameScene::allEnemy.size()-1){
		return;
	}

    auto bullet=Bullet::newBullet(1, this->ang, col*72+36, row*72+46,
                                  GameScene::allEnemy.at(objEnemyIndex)->getPosition().x,  GameScene::allEnemy.at(objEnemyIndex)->getPosition().y);
    this->getParent()->addChild(bullet,10);
    GameScene::allBullet.pushBack(bullet);
}