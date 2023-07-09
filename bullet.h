#pragma once

#include "gameobject.h"

class Bullet : public GameObject
{
public:
    ~Bullet();

    double speedY = 0;

    void move();
    void destroy();
};