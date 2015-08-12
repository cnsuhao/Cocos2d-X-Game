//
//  GameOver.h
//  towadgame
//
//  Created by zhao on 14-9-15.
//
//

#ifndef __towadgame__GameOver__
#define __towadgame__GameOver__

#include "cocos2d.h"
#include "GameScene.h"
using namespace cocos2d;
class GameOver:public Layer
{
  public :
     CREATE_FUNC(GameOver);
     bool init();
     static Scene * createScene();
};
#endif /* defined(__towadgame__GameOver__) */
