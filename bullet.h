#pragma once

#ifndef bullet.h
#include "gameobject.h"
#endif

class Bullet : public GameObject
{
public:
    ~Bullet();

    int speedY = 0;

    void Move();
    void Destroy();
};