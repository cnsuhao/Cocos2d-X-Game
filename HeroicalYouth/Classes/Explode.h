//
//  Explode.h
//  towadgame
//
//  Created by zhao on 14-9-12.
//
//

#ifndef __towadgame__Explode__
#define __towadgame__Explode__
#include "cocos2d.h"
using namespace cocos2d;
class Explode:public Node
{
  public:
    CREATE_FUNC(Explode);
    static Explode * newExplode(int type,int x,int y);
    bool init();
};
#endif /* defined(__towadgame__Explode__) */
