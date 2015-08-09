//
//  TD.h
//  towadgame
//
//  Created by zhao on 14-9-11.
//
//

#ifndef __towadgame__TD__
#define __towadgame__TD__

#include "cocos2d.h"
using namespace cocos2d;
class TD:public Node
{
public:
    CREATE_FUNC(TD);
    static TD * createNewTD(int type,int r,int c);
    bool init();
    int row;
    int col;
    float ang;
    int objEnemyIndex;
    int objx,objy;
    int type;
    int price;
    void roateAndShoot(float t);
    void shoot();
};

#endif /* defined(__towadgame__TD__) */
