#pragma once

#include "gameobject.h"

class Enemy : public GameObject
{
public:
    ~Enemy();

    void destroy();
};