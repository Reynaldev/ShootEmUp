#pragma once

#include "gameobject.h"

class Bullet : public GameObject
{
public:
    float speedY = 0;

    ~Bullet();

    void move(float timeStep);
    void destroy();
};