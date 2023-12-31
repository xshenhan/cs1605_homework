#ifndef SNAKE_H
#define SNAKE_H
#include "item.h"
#include <vector>
#include <assert.h>

class Field;
enum Direction {UP, DOWN, LEFT, RIGHT};
typedef std::vector<std::vector<Item*>> Grid;

bool isWithin(int target, int low, int high);

class Snake
{
public:
    Snake(std::vector<Loc> body, int length, int health, Direction direction, Grid* item_map_ptr);
    Snake(Loc head, int length, int health, Direction direction, Grid* item_map_ptr);
    void initialize();
    bool operator == (const Snake* other);

    int getLength() const;
    int getHealth() const;
    std::vector<Loc> &getBody();
    Direction getDirection();
    Direction getBodyDirection(int);

    //蛇变换方向
    void changeDireciton(Direction new_direction);
    //蛇的头部在当前方向上的下一个位置
    Loc nextLoc();
    //蛇向当前方向移动
    bool move();

    //返回蛇碰到的物体种类
    Item* hitItem();
    //判断蛇与自己、边缘发生碰撞
    bool hitSelf();
    bool hitEdge();
    //判断蛇与其他蛇发生碰撞
    bool hitOtherSnake(std::vector<Snake*>);
    //判断蛇是否经过沼泽
    Marsh* touchMarsh();
    //判断蛇是否与陨石发生碰撞
    Aerolite* touchAerolite();
    bool isPartOfSnake(Loc loc);

    void addLength(int adding);
    void addHealth(int adding);
    void incEaten();
    void incKilled();
    int getEaten();
    int getKilled();

    //当前分数
    int score();

    // 设置吸铁石能力
    void setMagnetic(int);
    bool ableMagnetic();
    // 设置护盾复活能力
    void setRevival(int);

    int getHp();
    void addSpeed(int adding);
    int getMp();
    void incMp();
    void decMp();
    bool ableMove();

    int getMagnetic();
    int getRevival();
    void decMagnectic();

    bool death();

    //蛇在每次判断加速或减速前先返回到初始速度
    void recover();
    virtual bool isAI() {return false;}
    bool speed_buff = false;
    virtual Direction act(Field* state) { return this->direction; }

    //当前难度
    int level = 1;
protected:
    std::vector<Loc> body;
    int length;
    int max_health = 4;
    Direction direction;
    //包含所有物品的地图的指针
    Grid* item_map_ptr;
    int width;
    int height;

    int health;
    //蛇吃过的食物数量
    int eaten = 0;
    //蛇杀死的其他蛇的数量
    int killed = 0;
    //控制蛇移动的时钟循环
    int cycle_recorder = 1;

    //蛇重生的位置
    Loc rebornLocation;
    //蛇重生的方向
    Direction rebornDirection;
    int mp = 240;

    //蛇在改变方向后是否已完成移动，用于防止一次移动改变了两次方向
    bool finishmove = true;

    int magnetic = 0;
    int revival = 0;
    int speed = -30;
};

#endif // SNAKE_H
