#pragma once

#include "gameobject.h"

class Player : public GameObject
{
public:
    ~Player();

    double speedX = 0;
    double maxAmmo = 1;
    double ammo = maxAmmo;

    void Move();
    void Destroy();
};
