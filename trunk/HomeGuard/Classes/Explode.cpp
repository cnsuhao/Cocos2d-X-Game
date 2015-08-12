//
//  Explode.cpp
//  towadgame
//
//  Created by zhao on 14-9-12.
//
//

#include "Explode.h"
Explode * Explode::newExplode(int type,int x,int y){
    Explode * newExp=Explode::create();
    //添加动画
    Vector<SpriteFrame*> allf;
    for (int i=1;i<7; i++) {
        auto sf=SpriteFrameCache::getInstance()->getSpriteFrameByName(
                    StringUtils::format("explode%d_%d.png",type,i));
        allf.pushBack(sf);
    }
    Animation * a=Animation::createWithSpriteFrames(allf);
    a->setDelayPerUnit(0.3);
    auto sp=Sprite::create();
    
    newExp->addChild(sp);
    sp->runAction(Sequence::create(
                Animate::create(a),
                CallFuncN::create([](Node * obj){
                obj->getParent()->removeFromParentAndCleanup(true);
                  })                   ,
                NULL));
    newExp->setPosition(x,y);
    return newExp;
}
bool Explode::init(){
    if(!Node::init())
    {
		return false;
	}
    return true;
}