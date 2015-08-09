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

    Vector<TD*> allTD;//����������
    CREATE_FUNC(GameScene);
    static Scene * createScene();
    bool init();
    Vector<MyPoint *> allPoint;//��������ƶ��켣���е�
    void initAllPoint(TMXTiledMap * map); //�������еĶ���
	//��������
	void newEnemy(float t);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
	//�������ѡ�����
	void addTDselect(int r,int c);
	//menu�ص�
	void selectTD(Ref *);
    int tdState; // 0ѡ��һ��Ŀ��λ�� 1����ѡ������Ѿ�����
    int nowRow,nowCol;//��ǰѡ�е�����

    static Vector<Enemy*> allEnemy;//���е���
    static Vector<Bullet*> allBullet;//�����ӵ�
    void update(float t);//��Ϸ�߼�
    void initToolBar();//����״̬��
    long money;//���
    int npcNumber_index;//��ǰ���ĵڼ�������
    int npcNumber_index_count;//��ǰ��һ���м�������
    int npcNumber; //���ﲨ��
    int npcNumberCount;//�����ܹ�����
    int hp;//��ҵ�����
    void changeHp(int h);
    int levelNumber;//��ǰ�ؿ����
    void initLevel();//��ʼ����ǰ�ؿ�
    ValueMap levelinf; //�ؿ���Ϣ
};
#endif /* defined(__towadgame__GameScene__) */
