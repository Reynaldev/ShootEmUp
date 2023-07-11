#pragma once

#include "gameobject.h"

// Templates

class Enemy : public GameObject
{
public:
    float speedY = 0;
    int health = 0;

    ~Enemy();

    void create(float speed, int health);
    void move(float timeStep);
    void destroy();
};