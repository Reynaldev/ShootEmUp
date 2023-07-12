#include "player.h"

Player::~Player()
{
    this->x = 0;
    this->y = 0;
    this->w = 0;
    this->h = 0;
    this->speedX = 0;
    this->firespeed = 0;
    this->nextFirespeed = 0;
    this->maxAmmo = 0;
    this->ammo = 0;
    this->setActive(false);
    
    this->texture = NULL;
}

void Player::create(int maxAmmo, float firespeed)
{
    this->maxAmmo = maxAmmo;
    this->ammo = this->maxAmmo;

    this->firespeed = firespeed;
}

void Player::input(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        if (e.key.keysym.sym == SDLK_LEFT)
            this->speedX = -200.0f;

        if (e.key.keysym.sym == SDLK_RIGHT)
            this->speedX = 200.0f;

        if (e.key.keysym.sym == SDLK_UP)
            this->isShoot = true;
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        if (e.key.keysym.sym == SDLK_LEFT)
            this->speedX = 0;

        if (e.key.keysym.sym == SDLK_RIGHT)
            this->speedX = 0;

        if (e.key.keysym.sym == SDLK_UP)
            this->isShoot = false;
    }
}

void Player::shoot(vector<Bullet>& bulletPool, vector<Bullet>& bullets)
{
    if (this->isShoot)
    {
        if (this->ammo <= 0)
            return;

        bulletPool.front().setActive(true);

        bulletPool.front().x = this->x + sqrt(bulletPool.front().w);
        bulletPool.front().y = this->y;

        bullets.push_back(bulletPool.front());
        bulletPool.erase(bulletPool.begin());

        this->ammo--;
    }
}

void Player::move(float timeStep)
{
    this->x += this->speedX * timeStep;
}

void Player::destroy()
{
    SDL_DestroyTexture(this->texture);
    this->~Player();
}