#ifndef ITEM_H
#define ITEM_H

#include "field.h"

#include <string>
#include <map>
using namespace std;

map<string, Item> item;
enum ItemType {BASIC=0, FOOD, MAGNET, SHIELD, FIRSTAID, WARNING, OBSTACLE, WALL, AEROLITE, MARSH};

/*
    物品类:
        检查击中了哪条蛇
*/
class Item
{
public:
    Item(Loc);

    Snake* hitHeadSnake(vector<Snake*>);  // 需要把 Field 里存蛇的数组传进去
    Snake* hitBodySnake(vector<Snake*>);

    virtual void action(Snake*) = 0;
    virtual ItemType getName();
    ItemType name = BASIC;
    Loc location;
};

/*
    普通食物
    增加的长度默认为 1, 可通过 changeAddLength() 修改
*/
class Food: public Item
{
public:
    Food(Loc, int);  // 以指定增加长度来初始化

    virtual void action(Snake*);
    virtual ItemType getName();
    void changeAddLength(int);

    ItemType name = FOOD;
    int add_length = 1;
};

/*
    吸铁石
    让 Snake实例在 effective_time 时间里能吸收头部四周九宫格的 Item
    effective_time 跟随全局时钟变化
*/
class Magnet: public Item
{
public:
    Magnet(Loc, int);    // 以指定有效时长来初始化

    virtual void action(Snake*);
    virtual ItemType getName();
    ItemType name = MAGNET;
    int effective_time;
    int remain_time;    // 好像没什么用, 在 Snake 里有倒计时
};

/*
    护盾
    让 Snake实例在 effective_time 时间里具有护盾, 保护一次死亡
    effective_time 跟随全局时钟变化
    (护盾的保护机制在 Snake类中实现)
*/
class Shield: public Item
{
public:
    Shield(Loc, int);    // 以指定有效时长来初始化

    virtual void action(Snake*);
    virtual ItemType getName();
    ItemType name = SHIELD;
    int effective_time;
};

/*
    血包
    增加的血量默认为 1, 最多达到最大血量
*/
class Firstaid: public Item
{
public:
    Firstaid(Loc, int);     // 以能增加的血量值初始化

    virtual void action(Snake*);
    virtual ItemType getName();
    void changeAddHealth(int);

    ItemType name = FIRSTAID;
    int add_health = 1;
};

/*
    警报
    在倒计时结束后出现 *nextItem
*/
class Warning: public Item
{
public:
    Warning(Loc, int, Item*);    // 初始化倒计时长 和 终点物体

    virtual void action(Snake*);
    virtual ItemType getName();
    int counting;
    Item* nextItem;
    ItemType name = WARNING;
};

/*
    障碍
    不同障碍物有不同伤害量
*/
class Obstacle: public Item
{
public:
    Obstacle(Loc, int);  // 以伤害量初始化

    virtual void action(Snake*);
    virtual ItemType getName();
    int injury;
    ItemType name = OBSTACLE;
};

/*
    墙壁
    和地图边界相同 撞击死亡
*/
class Wall: public Item
{
public:
    Wall(Loc);

    virtual void action(Snake*);
    virtual ItemType getName();
    ItemType name = WALL;
};

/*
    陨石
    砸中头部死亡, 砸中身体则从砸中处截断以后部分
*/
class Aerolite: public Item
{
public:
    Aerolite(Loc);

    virtual void action(Snake*);
    virtual ItemType getName();
    ItemType name = AEROLITE;
};

/*
    沼泽
    只要蛇任何一部分在沼泽上 都将被减速
*/
class Marsh: public Item
{
public:
    Marsh(Loc, int);     // 以减速程度初始化

    virtual void action(Snake*);
    virtual ItemType getName();
    int decelerate;
    ItemType name = MARSH;
};


#endif //ITEM_H
