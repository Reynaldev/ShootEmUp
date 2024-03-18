#pragma once

#include "gameobject.h"

// Templates

class Enemy : public GameObject
{
private:
    int health = 0;
public:
    float speedY = 0;

    ~Enemy();

    void create(float speed, int health);
    void move(float timeStep);
    void destroy();
};