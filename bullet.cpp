#include "bullet.h"

Bullet::~Bullet()
{
    this->x = NULL;
    this->y = NULL;
    this->w = NULL;
    this->h = NULL;
    this->speedY = NULL;
}

void Bullet::move()
{
    this->y += this->speedY;
}

void Bullet::destroy()
{
    SDL_DestroyTexture(this->texture);
    this->~Bullet();
}