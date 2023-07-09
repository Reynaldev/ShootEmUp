#include "main.h"
#include "window.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

int main(int argc, char* argv[])
{
    // Initialize window
    Window gWindow;
    gWindow.init();

    // Initialize gameplay
    int level = 1;
    int enemyPerLevel = level * 2;

    // Initialize player
    Player player;
    player.w = 64;
    player.h = 64;
    player.x = (SCREEN_WIDTH - player.w) / 2;
    player.y = SCREEN_HEIGHT - player.h;
    player.init(gWindow.renderer, "Src/Gfx/player.png");

    // Initialize bullets
    Bullet bullet;
    bullet.w = 64;
    bullet.h = 64;
    bullet.x = -100;
    bullet.init(gWindow.renderer, "Src/Gfx/bullet.png");

    // Initialize enemies
    vector<Enemy> enemies;

    SDL_UpdateWindowSurface(gWindow.window);

    // Loop
    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;

            // Input
            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT:
                player.speedX = -10;
                break;
            case SDLK_RIGHT:
                player.speedX = 10;
                break;
            case SDLK_UP:
                if (player.ammo > 0)
                {
                    bullet.x = player.x + 5;
                    bullet.y = player.y;
                    bullet.speedY = -.25;

                    player.ammo--;
                }
                break;
            default:
                break;
            }
        }

        // Check if there are no enemies
        // If there's no enemy, then we initialize them
        if (enemies.size() <= 0)
        {
            for (int i = 0; i < enemyPerLevel; i++)
            {
                Enemy enemy;
                enemy.w = 64;
                enemy.h = 64;
                enemy.x = (((SCREEN_WIDTH - enemy.w) / 2) + ((player.w / 2) * i));
                enemy.y = player.h;
                enemy.init(gWindow.renderer, "Src/Gfx/enemy.png");

                enemies.push_back(enemy);
            }

            SDL_UpdateWindowSurface(gWindow.window);
        }

        // Render the window
        gWindow.render();

        // Render enemies if there are
        if (enemies.size() > 0)
        {
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i].render(gWindow.renderer, enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h);
            }
        }

        // Move the bullet
        bullet.move();
        
        // Only render the bullet if it's inside the window
        if (bullet.y > (0 - bullet.h))
        {
            bullet.render(gWindow.renderer, bullet.x, bullet.y, bullet.w, bullet.h);
        }
        else 
        {
            if (player.ammo < player.maxAmmo)
                player.ammo++;
        }

        // Move player
        player.move();

        // Render the player and check if it's out of the window's width
        if (player.x > SCREEN_WIDTH)
        {
            player.x = 0 - player.w;
        }
        else if (player.x < 0 - player.w)
        {
            player.x = SCREEN_WIDTH;
        }

        player.render(gWindow.renderer, player.x, player.y, player.w, player.h);

        SDL_RenderPresent(gWindow.renderer);
    }

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].destroy();
    }

    bullet.destroy();
    player.destroy();
    gWindow.quit();

    return 0;
}