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

void CarePackage::create(SDL_Renderer* renderer, PackageType type)
{
    this->packageType = type;
    this->speedY = 50.0f + (float)(rand() % 200);
    this->setActive(true);

    string texturePath;
    switch (this->packageType)
    {
    case CP_HEALTH:
        texturePath = "assets/gfx/drop_health.png";
        break;
    case CP_AMMO:
        texturePath = "assets/gfx/drop_powerup.png";
        break;
    case CP_FIRESPEED:
        texturePath = "assets/gfx/drop_powerup.png";
        break;
    }

    this->init(renderer, texturePath);
}

void CarePackage::move(float timeStep)
{
    this->y += this->speedY * timeStep;
}

void CarePackage::get(Player &player)
{
    switch (this->packageType)
    {
    case CP_HEALTH:
        // cout << "You got health" << endl;
        player.setHealth(1 + (rand() & 3));
        break;
    case CP_AMMO:
        // cout << "You got ammo" << endl;
        player.increaseMaxAmmo();
        player.increaseAmmo(1);
        break;
    case CP_FIRESPEED:
        // cout << "You got firespeed upgrade" << endl;
        player.increaseFirespeed();
        break;
    }
}

void CarePackage::destroy()
{
    SDL_DestroyTexture(this->texture);
    this->~CarePackage();
}
