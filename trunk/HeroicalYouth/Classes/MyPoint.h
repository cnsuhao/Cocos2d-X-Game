//
//  MyPoint.h
//  towadgame
//
//  Created by zhao on 14-9-11.
//
//

#ifndef __towadgame__MyPoint__
#define __towadgame__MyPoint__
#include "cocos2d.h"
using namespace cocos2d;
class MyPoint:public Ref
{
    public :
    int x;
    int y;
    CREATE_FUNC(MyPoint);
    bool init()
    {
        return true;
    }
};
#endif /* defined(__towadgame__MyPoint__) */
