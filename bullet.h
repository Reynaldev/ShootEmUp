#pragma once

#include "gameobject.h"

class Bullet : public GameObject
{
public:
    double speedY = 0;

    ~Bullet();

    void move();
    void destroy();
};