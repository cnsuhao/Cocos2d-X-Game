//
//  Bullet.cpp
//  towadgame
//
//  Created by zhao on 14-9-12.
//
//

#include "Bullet.h"
Bullet* Bullet::newBullet(int type,int ang,int x,int y,int dx,int dy){
    Bullet * nb=Bullet::create();
    Sprite* bullet = Sprite::createWithSpriteFrameName("arrowBullet.png");
    
    nb->setPosition(x,y);
    bullet->setRotation(ang);
    nb->addChild(bullet);
//    float time=Vec2(x,y).distance(Vec2(dx,dy))/0.5;
   //    nb->px=x;
//    nb->py=y;
    nb->dx=dx;
    nb->dy=dy;
//
//         Vec2 shootVector = Vec2(dx,dy) - nb->getPosition();
//         shootVector.normalize();
//         auto farthestDistance = Director::getInstance()->getWinSize().width;
//         Vec2 overshotVector = shootVector * farthestDistance;
//         Vec2 offscreenPoint = (nb->getPosition() + overshotVector);
    nb->runAction(MoveTo::create(2, Vec2(dx,dy) ));

    nb->scheduleUpdate();
    return nb;
}

bool Bullet::init(){
    if(Node::init())
    {
        return true;
    }
    return false;
}
void Bullet::update(float t){
//    if(px<dx){px+=3;}
//    else{px-=3;}
//    if(py<dy){py+=3;}
//    else{py-=3;}
//     this->setPosition(px,py);
//    if(abs(this->px-dx)<=3&&abs(py-dy)<3)
    px=this->getPositionX();
    py=this->getPositionY();
//    CCLOG("%d,%d,%d,%d",px,py,dx,dy);
    if (abs(px-dx)<3 && abs(py-dy)<3) {
        
          this->removeFromParentAndCleanup(true);
    }
}