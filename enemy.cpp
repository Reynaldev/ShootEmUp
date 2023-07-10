#include "enemy.h"

void Enemy::destroy()
{
    SDL_DestroyTexture(this->texture);
}