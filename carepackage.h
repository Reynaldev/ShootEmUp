#pragma once

#include "main.h"
#include "gameobject.h"

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

    void create(PackageType type);
    void move(float timeStep);
    void destroy();
};