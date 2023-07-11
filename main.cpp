#include "main.h"
#include "window.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "text.h"
#include "playersettings.h"
#include "timer.h"

int main(int argc, char* argv[])
{
    // Initialize player settings
    PlayerSettings player;
    player.createPlayer("Dummy");

    Timer timer;

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
    bullet.speedY = -500.0f;
    bullet.init(gWindow.renderer, "Src/Gfx/bullet.png");

    string enemyTextures[6];
    enemyTextures[0] = "Src/Gfx/enemy1.png";
    enemyTextures[1] = "Src/Gfx/enemy2.png";
    enemyTextures[2] = "Src/Gfx/enemy3.png";
    enemyTextures[3] = "Src/Gfx/enemy4.png";
    enemyTextures[4] = "Src/Gfx/enemy5.png";
    enemyTextures[5] = "Src/Gfx/enemy6.png";

    // Vector that will be filled with total enemies each stage
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

            playerPlane.input(e);
        }

        // Calculate timestep
        float timeStep = timer.getTicks() / 1000.0f;

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
                enemy.y = 0 - enemy.h;

                enemy.init(gWindow.renderer, enemyTextures[rand() % 6]);
                enemy.create(100.0f + float(rand() % 201), abs(rand() % 10 - 6 + player.getLevel()));

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
                enemies[i].move(timeStep);

                if (enemies[i].y > SCREEN_HEIGHT)
                {
                    enemies[i].y = 0 - enemies[i].h;
                    enemies[i].x = abs(rand() % SCREEN_WIDTH - enemies[i].w);
                    enemies[i].speedY = 100.0f + float(rand() % 201);
                }

                enemies[i].render(gWindow.renderer, enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h, NULL, 180, NULL);

                // Destroy if it's collide with player's bullet and erase it from the vector
                if (enemies[i].collideWith(bullet.rect))
                {
                    enemies[i].destroy();
                    enemies.erase(enemies.begin() + i);
                    player.increaseHighscore(1);

                    continue;
                }

                // Detect collision with player
                if (enemies[i].collideWith(playerPlane.rect))
                {
                    player.setHealth(-1);

                    enemies[i].destroy();
                    enemies.erase(enemies.begin() + i);

                    continue;
                }
            }
        }

        // Move the bullet
        bullet.move(timeStep);
        
        // Only render the bullet if it's inside the window
        if (bullet.y > (0 - bullet.h))
        {
            bullet.render(gWindow.renderer, bullet.x, bullet.y, bullet.w, bullet.h);
        }
        else 
        {
            bullet.x = -100;

            if (playerPlane.ammo < playerPlane.maxAmmo)
                playerPlane.ammo++;
        }

        // Move player
        playerPlane.move(timeStep);
        playerPlane.shoot(bullet);

        // Restart timer
        timer.start();

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

        // Update UI
        // [Solved] These causes memory leak
        levelText = "Level: " + to_string(player.getLevel());
        levelTextUI.display(gWindow.renderer, white, levelText);

        higscoreText = "Highscore: " + to_string(player.getHighscore());
        highscoreTextUI.display(gWindow.renderer, white, higscoreText);

        healthText = "Health: " + to_string(player.getHealth());
        healthTextUI.display(gWindow.renderer, white, healthText);

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