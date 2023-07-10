#include "bullet.h"

Bullet::~Bullet()
{
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->speedY = 0;
    
    this->texture = NULL;
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