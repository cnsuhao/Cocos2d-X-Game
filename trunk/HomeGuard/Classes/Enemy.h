//
//  Enemy.h
//  towadgame
//
//  Created by zhao on 14-9-11.
//
//

#ifndef __towadgame__Enemy__
#define __towadgame__Enemy__
#include "cocos2d.h"
#include "MyPoint.h"
using namespace cocos2d;
class Enemy:public Node{
private:
    Vector<MyPoint *> allP;//每个点的坐标
public:
    int ex,ey;
    int hp;
    CREATE_FUNC(Enemy);
    int curPoint;//当前的点
    int countPoint;//总共的点
    static Enemy * createEnemy(int etype,Vector<MyPoint *> &ap);
    bool init();
    void moveTo();//定时任务，移动到目标点
    void sHp();//减少血
};

#endif /* defined(__towadgame__Enemy__) */
