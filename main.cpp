#include "main.h"
#include "window.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "text.h"
#include "playersettings.h"

int main(int argc, char* argv[])
{
    // Initialize player settings
    PlayerSettings player;
    player.createPlayer("Dummy");

    // Initialize window
    Window gWindow;
    gWindow.init();

    // Initialize player
    Player playerPlane;
    playerPlane.w = 64;
    playerPlane.h = 64;
    playerPlane.x = (SCREEN_WIDTH - playerPlane.w) / 2;
    playerPlane.y = SCREEN_HEIGHT - playerPlane.h;
    playerPlane.init(gWindow.renderer, "Src/Gfx/player.png");

    // Initialize bullets
    Bullet bullet;
    bullet.w = 64;
    bullet.h = 64;
    bullet.x = -100;
    bullet.init(gWindow.renderer, "Src/Gfx/bullet.png");

    // Initialize enemies
    vector<Enemy> enemies;

    // Component
    SDL_Color white = { 0xff, 0xff, 0xff, 0xff };

    // Level text
    string levelText;
    Text levelTextUI;
    levelTextUI.create(28, "Src/Fonts/Kenney_Pixel.ttf");

    // Highscore text
    string higscoreText;
    Text highscoreTextUI;
    highscoreTextUI.create(28, "Src/Fonts/Kenney_Pixel.ttf");

    // Health text
    string healthText;
    Text healthTextUI;
    healthTextUI.create(28, "Src/Fonts/Kenney_Pixel.ttf");

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
                playerPlane.speedX = -10;
                break;
            case SDLK_RIGHT:
                playerPlane.speedX = 10;
                break;
            case SDLK_UP:
                if (playerPlane.ammo > 0)
                {
                    bullet.x = playerPlane.x + sqrt(bullet.w);
                    bullet.y = playerPlane.y;
                    bullet.speedY = -.25;

                    playerPlane.ammo--;
                }
                break;
            default:
                break;
            }
        }

        // Update UI
        // [Solved] These causes memory leak
        levelText = "Level: " + to_string(player.getLevel());
        levelTextUI.display(gWindow.renderer, white, levelText);

        higscoreText = "Highscore: " + to_string(player.getHighscore());
        highscoreTextUI.display(gWindow.renderer, white, higscoreText);

        healthText = "Health: " + to_string(player.getHealth());
        healthTextUI.display(gWindow.renderer, white, healthText);

        // Check if there are no enemies
        // If there's no enemy, then we initialize them
        if (enemies.size() <= 0)
        {
            player.increaseLevel(1);
            int enemyPerLevel = player.getLevel() * 2;

            // cout << "Level: " << level << endl;
            // cout << "Enemies: " << enemyPerLevel << endl;

            for (int i = 0; i < enemyPerLevel; i++)
            {
                Enemy enemy;
                enemy.w = 64;
                enemy.h = 64;
                // enemy.x = (((SCREEN_WIDTH - enemy.w) / 2) + (enemy.w * i));
                enemy.x = ((SCREEN_WIDTH - (enemy.w * enemyPerLevel)) / 2) + (enemy.w * i);
                enemy.y = enemy.h;
                enemy.init(gWindow.renderer, "Src/Gfx/enemy.png");

                enemies.push_back(enemy);
            }
        }

        // Render the window
        gWindow.render();

        // Render enemies if there are
        if (enemies.size() > 0)
        {
            // Render
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i].render(gWindow.renderer, enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h);
            }

            // Detect collision
            for (int i = 0; i < enemies.size(); i++)
            {
                // Destroy if it's collide with player's bullet and erase it from the vector
                if (enemies[i].collideWith(bullet.rect))
                {
                    enemies[i].destroy();
                    enemies.erase(enemies.begin() + i);
                    player.increaseHighscore(1);
                }

                // Detect collision with player
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
            if (playerPlane.ammo < playerPlane.maxAmmo)
                playerPlane.ammo++;
        }

        // Move player
        playerPlane.move();

        // Render the player and check if it's out of the window's width
        if (playerPlane.x > SCREEN_WIDTH)
        {
            playerPlane.x = 0 - playerPlane.w;
        }
        else if (playerPlane.x < 0 - playerPlane.w)
        {
            playerPlane.x = SCREEN_WIDTH;
        }

        // Render player
        playerPlane.render(gWindow.renderer, playerPlane.x, playerPlane.y, playerPlane.w, playerPlane.h);

        // Render UI
        levelTextUI.render(gWindow.renderer, 0, SCREEN_HEIGHT - levelTextUI.h);
        highscoreTextUI.render(gWindow.renderer, (SCREEN_WIDTH - highscoreTextUI.w) / 2, SCREEN_HEIGHT - highscoreTextUI.h);
        healthTextUI.render(gWindow.renderer, SCREEN_WIDTH - healthTextUI.w, SCREEN_HEIGHT - healthTextUI.h);

        SDL_RenderPresent(gWindow.renderer);
    }

    // Clean-up
    player.~PlayerSettings();

    levelTextUI.destroy();
    highscoreTextUI.destroy();
    healthTextUI.destroy();

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].destroy();
    }

    bullet.destroy();
    playerPlane.destroy();

    gWindow.quit();

    return 0;
}