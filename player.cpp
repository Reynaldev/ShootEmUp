#include "player.h"

void Player::move()
{
    this->x += this->speedX;
    this->speedX = 0;
}

void Player::destroy()
{
    SDL_DestroyTexture(this->texture);
}