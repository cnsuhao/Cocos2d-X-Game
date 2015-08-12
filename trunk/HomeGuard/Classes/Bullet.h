//
//  Bullet.h
//  towadgame
//
//  Created by zhao on 14-9-12.
//
//

#ifndef __towadgame__Bullet__
#define __towadgame__Bullet__
#include "cocos2d.h"
using namespace cocos2d;
class Bullet:public Node
{
  public:
    int px,py;
    int dx,dy;//目标点
    int mx,my;
    static Bullet* newBullet(int type,int ang,int x,int y,int dx,int dy);
    CREATE_FUNC(Bullet);
    bool init();
    void update(float t);
};
#endif /* defined(__towadgame__Bullet__) */
