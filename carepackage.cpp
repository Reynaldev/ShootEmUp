#include "carepackage.h"

CarePackage::~CarePackage()
{
    this->x = 0;
    this->w = 0;
    this->x = 0;
    this->y = 0;
    this->speedY = 0;
    this->setActive(false);

    this->texture = NULL;
}

void CarePackage::create(PackageType type)
{
    this->packageType = type;
    this->speedY = 50.0f + (float)(rand() % 200);
}

void CarePackage::move(float timeStep)
{
    this->y += this->speedY * timeStep;
}

void CarePackage::destroy()
{
    SDL_DestroyTexture(this->texture);
    this->~CarePackage();
}