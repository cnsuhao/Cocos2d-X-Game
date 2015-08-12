//
//  Enemy.cpp
//  towadgame
//
//  Created by zhao on 14-9-11.
//
//

#include "Enemy.h"
#include "GameScene.h"
#include "ui/cocosGUI.h"
using namespace ui;
Enemy * Enemy::createEnemy(int etype,Vector<MyPoint *> &ap){
    Enemy * newE=Enemy::create();
    newE->hp=50;

    Vector<SpriteFrame *> allF;
    
    for (int i=1 ; i<5; i++) {
        auto sf=SpriteFrameCache::getInstance()->getSpriteFrameByName(
                    StringUtils::format("enemyLeft%d_%d.png",etype,i));
        allF.pushBack(sf);
    }
    float delay=0;
    switch (etype) {
        case 1:
            delay=0.1;
            break;
        case 2:
            delay=0.05;
         break;
        case 3:
            delay=0.030;
           break;
        default:
            break;
    }

    auto animation=Animation::createWithSpriteFrames(allF);
    animation->setDelayPerUnit(delay);

    auto ani=Animate::create(animation);
    auto sp=Sprite::create();
    newE->addChild(sp);
    sp->runAction(RepeatForever::create(ani));

    auto hp=LoadingBar::create("sliderProgress2.png");
    hp->setTag(1000);
    hp->setPercent(100);
    newE->addChild(hp,1);
    hp->setPositionY(60);

    newE->allP=ap;
    newE->curPoint=0;
    newE->countPoint=ap.size();

    newE->ex=ap.at(0)->x;
    newE->ey=ap.at(0)->y;

    newE->setPosition(Vec2(ap.at(0)->x, ap.at(0)->y));
    newE->moveTo();
    return newE;
}
bool Enemy::init(){
    if(!Node::init())
    {
        return  false;
    }
       return true;
}
void Enemy::moveTo()
{
    MyPoint * oldPoint=allP.at(curPoint);
    if (curPoint<countPoint-1) {
        curPoint++;

        MyPoint * nowP=allP.at(curPoint);

        float lenth=Vec2(oldPoint->x, oldPoint->y).distance(Vec2(nowP->x, nowP->y));
        
        this->runAction(Sequence::create(
            MoveTo::create(lenth/50, Vec2(nowP->x,nowP->y)),
            CallFunc::create(CC_CALLBACK_0(Enemy::moveTo,this))
                    , NULL));
    }
    else
    {
        this->removeFromParentAndCleanup(true);
        GameScene::allEnemy.eraseObject(this);
        GameScene::getInstance()->changeHp(GameScene::getInstance()->hp-10);
    }
}
void Enemy::sHp(){
    auto hplayer=(LoadingBar*)this->getChildByTag(1000);
    hplayer->setPercent(hp/50.0*100);
}