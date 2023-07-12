#pragma once

#include "main.h"
#include "gameobject.h"
#include "player.h"
#include "playersettings.h"

enum PackageType 
{
    CP_HEALTH,
    CP_AMMO,
    CP_FIRESPEED
};

class CarePackage : public GameObject
{
private:
    PackageType packageType;
    float speedY = 0;
public:
    ~CarePackage();

    void create(SDL_Renderer* renderer, PackageType type);
    void move(float timeStep);
    void get(Player &player);
    void destroy();
};