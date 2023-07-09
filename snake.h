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
    Snake(std::vector<Loc> body, int length, int max_health, Direction direction, Grid* item_map_ptr);
    Snake(Loc head, int length, int max_health, Direction direction, Grid* item_map_ptr);
    void initialize();
    bool operator == (const Snake* other);

    int getLength() const;
    int getHealth() const;
    std::vector<Loc> &getBody();

    void changeDireciton(Direction new_direction);
    Loc nextLoc();
    bool move();

    Item* hitItem();
    bool hitSelf();
    bool hitEdge();
    bool hitOtherSnake(std::vector<Snake*>);  // 在 Game 中可以把 field.snakes[1:] 传进来
    Marsh* touchMarsh();
    bool isPartOfSnake(Loc loc);

    void addLength(int adding);
    void addHealth(int adding);
    void incEaten();
    void incKilled();
    int getEaten();
    int getKilled();


    void setMagnetic(int);  // 设置吸铁石能力
    bool ableMagnetic();
    void setRevival(int);   // 设置护盾复活能力

    void addSpeed(int);
    bool ableMove();

    bool death();

    void recover();
    virtual bool isAI() { return false; }
    virtual Direction act(Field* state) { return this->direction; }
    //消除所有buff和debuff
protected:
    std::vector<Loc> body;
    int length;
    int max_health;
    Direction direction;
    Grid* item_map_ptr;
    int width;
    int height;
    int speed = -30;
    int health;
    int eaten = 0;
    int killed = 0;
    int cycle_recorder = 1;
    int magnetic = 0;
    int revival = 0;
};

#endif // SNAKE_H
