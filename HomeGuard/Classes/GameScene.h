//
//  GameScene.h
//  towadgame
//
//  Created by zhao on 14-9-11.
//
//

#ifndef __towadgame__GameScene__
#define __towadgame__GameScene__
#include "cocos2d.h"
#include "Enemy.h"
#include "MyPoint.h"
#include "TD.h"
#include "Bullet.h"
#include "Explode.h"
#include "GameOver.h"
using namespace cocos2d;
class GameScene:public Layer
{
private:
      static GameScene * GS;
public:
  
    static GameScene * getInstance();
    
	int mapinfo[9][16];

    Vector<TD*> allTD;//保存所有塔
    CREATE_FUNC(GameScene);
    static Scene * createScene();
    bool init();
    Vector<MyPoint *> allPoint;//保存怪物移动轨迹所有点
    void initAllPoint(TMXTiledMap * map); //加载所有的对象
	//产生怪物
	void newEnemy(float t);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
	//添加塔的选择面板
	void addTDselect(int r,int c);
	//menu回调
	void selectTD(Ref *);
    int tdState; // 0选中一个目标位置 1塔的选择面板已经出现
    int nowRow,nowCol;//当前选中的行列

    static Vector<Enemy*> allEnemy;//所有敌人
    static Vector<Bullet*> allBullet;//所有子弹
    void update(float t);//游戏逻辑
    void initToolBar();//加载状态条
    long money;//金币
    int npcNumber_index;//当前波的第几个怪物
    int npcNumber_index_count;//当前波一共有几个怪物
    int npcNumber; //怪物波数
    int npcNumberCount;//怪物总共波数
    int hp;//玩家的生命
    void changeHp(int h);
    int levelNumber;//当前关卡编号
    void initLevel();//初始化当前关卡
    ValueMap levelinf; //关卡信息
};
#endif /* defined(__towadgame__GameScene__) */
