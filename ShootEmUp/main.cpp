#include "main.h"
#include "window.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "text.h"
#include "playersettings.h"
#include "timer.h"
#include "carepackage.h"

int main(int argc, char* argv[])
{
    // Set seed for RNG
    srand(time(NULL));

    // Initialize player settings
    PlayerSettings player;
    player.createPlayer("Dummy");

    // Initialize timer
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
    playerPlane.create(1, 5.0f);
    playerPlane.init(gWindow.renderer, "assets/gfx/player.png");

    // Initialize enemy textures
    string enemyTextures[6];
    for (int i = 0; i < 6; i++)
    {
        int index = i + 1;
        string filename = "assets/gfx/enemy" + to_string(index) + ".png";
        enemyTextures[i] = filename;
    }

    // Initialize bullets
    // bulletPool is to store bullet object for pooling.
    vector<Bullet> bulletPool;

    // bullets is to store bullet object for render and logic purpose.
    vector<Bullet> bullets;

    // Vector that will be filled with total enemies each stage
    vector<Enemy> enemies;

    // Care Package initialization
    PackageType carePackageType[3];
    carePackageType[0] = CP_HEALTH;
    carePackageType[1] = CP_AMMO;
    carePackageType[2] = CP_FIRESPEED;

    vector<CarePackage> carePackages;

    // Component
    SDL_Color white = { 0xff, 0xff, 0xff, 0xff };

    // Level text
    string levelText;
    Text levelTextUI;
    levelTextUI.create(28, "assets/fonts/Kenney_Pixel.ttf");

    // Highscore text
    string higscoreText;
    Text highscoreTextUI;
    highscoreTextUI.create(28, "assets/fonts/Kenney_Pixel.ttf");

    // Health text
    string healthText;
    Text healthTextUI;
    healthTextUI.create(28, "assets/fonts/Kenney_Pixel.ttf");

    string ammoText;
    Text ammoTextUI;
    ammoTextUI.create(28, "assets/fonts/Kenney_Pixel.ttf");
    
    string enemiesText;
    Text enemiesTextUI;
    enemiesTextUI.create(28, "assets/fonts/Kenney_Pixel.ttf");

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

        // Render the window
        gWindow.render();

        // Care Package
        if (!carePackages.empty())
        {
            for (int i = 0; i < carePackages.size(); i++)
            {
                carePackages[i].move(timeStep);
                carePackages[i].render(gWindow.renderer);

                // Destroy the package if it's outside the window
                if (carePackages[i].y > SCREEN_WIDTH)
                {
                    carePackages[i].destroy();
                    carePackages.erase(carePackages.begin() + i);
                }

                // Collision
                if (carePackages[i].collideWith(playerPlane.rect) && playerPlane.isActive())
                {
                    // Implement upgrade
                    carePackages[i].get(playerPlane);
                    
                    // Remove the entity from the vector
                    carePackages[i].destroy();
                    carePackages.erase(carePackages.begin() + i);
                }
            }
        }

        // Bullets
        while (bulletPool.size() < playerPlane.getAmmo())
        {
            Bullet bullet;
            bullet.w = 64;
            bullet.h = 64;
            bullet.speedY = -600.0f;
            bullet.init(gWindow.renderer, "assets/gfx/bullet.png");

            bulletPool.push_back(bullet);
        }

        // Bullet render, logic, etc.
        if (!bullets.empty())
        {
            for (int i = 0; i < bullets.size(); i++)
            {
                bullets[i].move(timeStep);
                
                // Only render the bullet if it's inside the window
                if (bullets[i].y > (0 - bullets[i].h))
                {
                    bullets[i].render(gWindow.renderer);
                }
                else 
                {
                    // Disable  the bullet
                    bullets[i].setActive(false);

                    // Remove it and store it to bulletPool vector
                    bulletPool.push_back(bullets[i]);
                    bullets.erase(bullets.begin() + i);

                    // Increase the ammo if it's less than the maximum ammo
                    if (playerPlane.getAmmo() < playerPlane.getMaxAmmo())
                        playerPlane.increaseAmmo(1);
                }
            }
        }

        // Check if there are no enemies
        // If there's no enemy, then we initialize them
        if (enemies.empty())
        {
            player.increaseLevel(1);
            int enemyPerLevel = player.getLevel() * 2;

            for (int i = 0; i < enemyPerLevel; i++)
            {
                Enemy enemy;
                enemy.w = 64;
                enemy.h = 64;
                enemy.x = abs((float)(rand() % SCREEN_WIDTH) - enemy.w);
                enemy.y = 0 - enemy.h;

                enemy.init(gWindow.renderer, enemyTextures[rand() % 6]);
                enemy.create(100.0f + float(rand() % 201), abs(rand() % 10 - 6 + player.getLevel()));

                enemies.push_back(enemy);
            }
        }
        else
        {
            // Execute the enemies if there are
            // Render
            for (int i = 0; i < enemies.size(); i++)
            {
                bool isDestroyed = false;

                enemies[i].move(timeStep);

                if (enemies[i].y > SCREEN_HEIGHT)
                {
                    enemies[i].y = 0 - enemies[i].h;
                    enemies[i].x = abs(rand() % SCREEN_WIDTH - enemies[i].w);
                    enemies[i].speedY = 100.0f + float(rand() % 201);
                }

                enemies[i].render(gWindow.renderer, NULL, 180, NULL);

                // Destroy if it's collided with player's bullet and erase it from the vector
                for (Bullet b : bullets)
                {
                    if (enemies[i].collideWith(b.rect) && b.isActive())
                    {
                        // Care package
                        bool spawnPackage = (rand() % 15 == 0) ? true : false;
                        if (spawnPackage)
                        {
                            CarePackage cp;
                            cp.w = 64;
                            cp.h = 64;
                            cp.x = enemies[i].x;
                            cp.y = enemies[i].y;
                            cp.create(gWindow.renderer, carePackageType[rand() % 3]);
                            carePackages.push_back(cp);
                        }

                        // Remove from the vector
                        enemies[i].destroy();
                        player.increaseHighscore(1);

                        isDestroyed = true;

                        break;
                    }
                }

                // Detect collision with player
                if (enemies[i].collideWith(playerPlane.rect) && playerPlane.isActive())
                {
                    // Decrease player health
                    playerPlane.setHealth(-1);

                    // Remove from the vector
                    enemies[i].destroy();
                    
                    isDestroyed = true;
                }

                if (isDestroyed)
                    enemies.erase(enemies.begin() + i);
            }
        }

        // Move player
        playerPlane.move(timeStep);
        
        if (SDL_GetTicks() >= playerPlane.nextFirespeed)
        {
            playerPlane.shoot(bulletPool, bullets);
            playerPlane.nextFirespeed = SDL_GetTicks() + 1000.0f / playerPlane.firespeed;
        }

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

        // Player collision

        // Render player
        playerPlane.render(gWindow.renderer);

        // Update UI
        // [Solved] These causes memory leak
        levelText = "Level: " + to_string(player.getLevel());
        levelTextUI.display(gWindow.renderer, white, levelText);

        higscoreText = "Highscore: " + to_string(player.getHighscore());
        highscoreTextUI.display(gWindow.renderer, white, higscoreText);

        healthText = "Health: " + to_string(playerPlane.getHealth());
        healthTextUI.display(gWindow.renderer, white, healthText);

        ammoText = "Ammo: " + to_string(playerPlane.getAmmo()) + " | " + to_string(playerPlane.getMaxAmmo());
        ammoTextUI.display(gWindow.renderer, white, ammoText);

        enemiesText = "Enemies left: " + to_string(enemies.size());
        enemiesTextUI.display(gWindow.renderer, white, enemiesText);

        // Render UI
        levelTextUI.render(gWindow.renderer, 0, SCREEN_HEIGHT - levelTextUI.h);
        highscoreTextUI.render(gWindow.renderer, (SCREEN_WIDTH - highscoreTextUI.w) / 2, SCREEN_HEIGHT - highscoreTextUI.h);
        healthTextUI.render(gWindow.renderer, SCREEN_WIDTH - healthTextUI.w, SCREEN_HEIGHT - healthTextUI.h);
        ammoTextUI.render(gWindow.renderer, 0, 0);
        enemiesTextUI.render(gWindow.renderer, SCREEN_WIDTH - enemiesTextUI.w, 0);

        SDL_RenderPresent(gWindow.renderer);
    }

    // Clean-up
    timer.~Timer();

    player.~PlayerSettings();

    levelTextUI.destroy();
    highscoreTextUI.destroy();
    healthTextUI.destroy();
    ammoTextUI.destroy();
    enemiesTextUI.destroy();

    for (int i = 0; i < carePackages.size(); i++)
    {
        carePackages[i].destroy();
    }
    carePackages.clear();

    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i].destroy();
    }
    enemies.clear();

    for (int i = 0; i < bulletPool.size(); i++)
    {
        bulletPool[i].destroy();
    }
    bulletPool.clear();

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i].destroy();
    }
    bullets.clear();
    
    playerPlane.destroy();

    gWindow.quit();

    return 0;
}