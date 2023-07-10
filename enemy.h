#pragma once

#include "gameobject.h"

// Templates

class Enemy : public GameObject
{
public:
    double speedY = 0;
    int health = 0;

    ~Enemy();

    void create(double speed, int health);
    void move();
    void destroy();
};