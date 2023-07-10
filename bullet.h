#pragma once

#include "gameobject.h"

class Bullet : public GameObject
{
public:
    double speedY = 0;

    void move();
    void destroy();
};