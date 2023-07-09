#include "main.h"
#include "window.h"
#include "player.h"
#include "bullet.h"

int main(int argc, char* argv[])
{
    // Initialize window
    Window gWindow;
    gWindow.Init();

    // Initialize player
    Player player;
    player.w = 64;
    player.h = 64;
    player.x = (SCREEN_WIDTH - player.w) / 2;
    player.y = SCREEN_HEIGHT - player.h;
    player.Init(gWindow.renderer, "Src/Gfx/player.png");

    // Initialize bullets
    Bullet bullet;
    bullet.w = 64;
    bullet.h = 64;
    bullet.x = -100;
    bullet.speedY = -2;
    bullet.Init(gWindow.renderer, "Src/Gfx/bullet.png");

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
                bullet.x = player.x;
                bullet.y = player.y;
                break;
            default:
                break;
            }
        }

        // Render the window
        gWindow.Render();

        // Move the bullet
        bullet.Move();
        bullet.Render(gWindow.renderer, bullet.x, bullet.y, bullet.w, bullet.h);

        // Move player
        player.Move();

        // Render the player and check if it's out of the window's width
        if (player.x > SCREEN_WIDTH)
        {
            player.x = 0 - player.w;
        }
        else if (player.x < 0 - player.w)
        {
            player.x = SCREEN_WIDTH;
        }

        player.Render(gWindow.renderer, player.x, player.y, player.w, player.h);

        SDL_RenderPresent(gWindow.renderer);
    }

    bullet.Destroy();
    player.Destroy();
    gWindow.Quit();

    return 0;
}