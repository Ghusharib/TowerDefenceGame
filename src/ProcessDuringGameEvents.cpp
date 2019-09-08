#include "GAME.H"


void Game::processDuringGameEvents(sf::Time BulletTime)
        {
            if (!enemiesAdded)
                typeOfEnemyToAdd();

            sf::Event event;

            while (mWindow.pollEvent(event))
            {
                switch(event.type)
                {
                    case sf::Event::MouseMoved:
                        break;
                    case sf::Event::Closed:
                        mWindow.close();
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            if(!PowerUp.isUsed() && Money - PowerUp.getCost() >= 0 &&
                               event.mouseButton.x > PowerUp.getButtonPosition().x && event.mouseButton.x < PowerUp.getButtonPosition().x + 90
                               && event.mouseButton.y > PowerUp.getButtonPosition().y && event.mouseButton.y < PowerUp.getButtonPosition().y + 75)
                            {
                                usingPowerUp = true;
                                PowerUp.use();
                                Money = Money - PowerUp.getCost();
                            }
                            else if (event.mouseButton.x > speedSelectionButton.getPosition().x && event.mouseButton.x < speedSelectionButton.getPosition().x + 45
                                    && event.mouseButton.y > speedSelectionButton.getPosition().y && event.mouseButton.y < speedSelectionButton.getPosition().y + 40)
                            {
                                speedMultiplier = 0.5;
                                changeEnemySpeed();
                            }
                            else if (event.mouseButton.x > speedSelectionButton.getPosition().x + 46 && event.mouseButton.x < speedSelectionButton.getPosition().x + 90
                                    && event.mouseButton.y > speedSelectionButton.getPosition().y && event.mouseButton.y < speedSelectionButton.getPosition().y + 40)
                            {
                                speedMultiplier = 1;
                                changeEnemySpeed();
                            }
                            else if (event.mouseButton.x > speedSelectionButton.getPosition().x + 91&& event.mouseButton.x < speedSelectionButton.getPosition().x + 135
                                    && event.mouseButton.y > speedSelectionButton.getPosition().y && event.mouseButton.y < speedSelectionButton.getPosition().y + 40)
                            {
                                speedMultiplier = 2;
                                changeEnemySpeed();
                            }
                            else if (event.mouseButton.x > speedSelectionButton.getPosition().x + 136 && event.mouseButton.x < speedSelectionButton.getPosition().x + 180
                                    && event.mouseButton.y > speedSelectionButton.getPosition().y && event.mouseButton.y < speedSelectionButton.getPosition().y + 40)
                            {
                                speedMultiplier = 4;
                                changeEnemySpeed();
                            }
                            else if(event.mouseButton.x > inGameHelpButton.getPosition().x && event.mouseButton.x < inGameHelpButton.getPosition().x + 60
                                    && event.mouseButton.y > inGameHelpButton.getPosition().y && event.mouseButton.y < inGameHelpButton.getPosition().y + 40)
                            {
                                loadHelpScreen = true;
                            }
                            else if(event.mouseButton.x > inGamePauseButton.getPosition().x && event.mouseButton.x < inGamePauseButton.getPosition().x + 60
                                    && event.mouseButton.y > inGamePauseButton.getPosition().y && event.mouseButton.y < inGamePauseButton.getPosition().y + 40)
                            {
                                gamePaused = true;
                            }
                        }
                }
            }

            sf::Time weaponTime = WeaponTimer.restart();

            for (int i = 0; i < totalWeapons; i++)
            {
                float rotateBy;
                Weapons[i].updateTime(weaponTime * speedMultiplier);
                if (Weapons[i].isLocked())
                    {
                        if(!isInRange(Weapons[i].getBasePosition(), Enemies[Weapons[i].isLockedOn()].getPosition(), Weapons[i].getRadius()))
                            {
                                Weapons[i].unlock();
                            }

                       rotateBy = (atan((Enemies[Weapons[i].isLockedOn()].getPosition().y - Weapons[i].getBasePosition().y)/(Enemies[Weapons[i].isLockedOn()].getPosition().x - Weapons[i].getBasePosition().x)))*(180/M_PI);
                       if (Weapons[i].getBasePosition().y > Enemies[Weapons[i].isLockedOn()].getPosition().y
                           && Weapons[i].getBasePosition().x < Enemies[Weapons[i].isLockedOn()].getPosition().x)
                       {
                            rotateBy = 90 - ((-1) * rotateBy);
                       }
                       else if (Weapons[i].getBasePosition().y < Enemies[Weapons[i].isLockedOn()].getPosition().y
                           && Weapons[i].getBasePosition().x < Enemies[Weapons[i].isLockedOn()].getPosition().x)
                       {
                            rotateBy = 90 + rotateBy;
                       }
                       else if(Weapons[i].getBasePosition().y < Enemies[Weapons[i].isLocked()].getPosition().y
                               && Weapons[i].getBasePosition().x > Enemies[Weapons[i].isLockedOn()].getPosition().x)
                       {
                            rotateBy = 180 + (90 - (rotateBy * (-1)));
                       }
                       else if (Weapons[i].getBasePosition().y > Enemies[Weapons[i].isLocked()].getPosition().y
                                && Weapons[i].getBasePosition().x > Enemies[Weapons[i].isLockedOn()].getPosition().x)
                       {
                           rotateBy = (270 + rotateBy);
                       }
                       Weapons[i].rotateTurret(rotateBy);

                        if(!isInRange(Weapons[i].getBasePosition(), Enemies[Weapons[i].isLockedOn()].getPosition(), Weapons[i].getRadius()))
                        {
                            Weapons[i].unlock();
                        }

                        int x = ((Enemies[Weapons[i].isLockedOn()].getPosition().x + 20) - (Weapons[i].getBasePosition().x + 21.5f))/10;
                        int y = ((Enemies[Weapons[i].isLockedOn()].getPosition().y + 20) - (Weapons[i].getBasePosition().y + 21.5f))/10;
                        Weapons[i].setBulletDirection(x, y);
                    }
                    else
                    {
                        for (int j = 0; j < totalEnemies; j++)
                        {
                            if(isInRange(Weapons[i].getBasePosition(), Enemies[j].getPosition(), Weapons[i].getRadius()))
                            {
                                Weapons[i].lockOnto(j);
                                break;
                            }
                        }
                    }

                    if(Weapons[i].fireStatus())
                        {
                            fireBullet(i);
                            if (hitTarget(i, Weapons[i].isLockedOn()))
                                Weapons[i].reset();
                        }
                    else if (Weapons[i].isReadyToFire() && Weapons[i].isLocked())
                        {
                            Weapons[i].reset();
                            Weapons[i].restartTimer();
                            Weapons[i].fired();
                            fireBullet(i);
                        }
                }

                for (int i = 0; i < totalEnemies; i++)
                {
                    if (Enemies[i].isDead())
                    {
                        Score = Score + Enemies[i].getScore();
                        Money = Money + Enemies[i].getReturnMoney() * 5;
                        Enemies.erase(Enemies.begin() + i);
                        totalEnemies--;

                        for (int j = 0; j < totalWeapons; j++)
                        {
                            Weapons[j].unlock();
                        }
                    }
                }

                if(towerHealth <= 0)
                {
                    GameOver = true;
                    Score = Score + Money * 0.1;
                }
                else if (totalEnemies == 0)
                {
                    playingGame = false;
                }

            }

void Game::changeEnemySpeed()
        {
            EnemySpeed = EnemySpeed/tempSpeedMultiplier;
            EnemySpeed = EnemySpeed * speedMultiplier;
            tempSpeedMultiplier = speedMultiplier;
        }

bool Game::hitTarget(int i, int j)
        {
            if (Weapons[i].getBulletPosition().x > Enemies[j].getPosition().x  - 20 && Weapons[i].getBulletPosition().x < Enemies[j].getPosition().x + 60
                && Weapons[i].getBulletPosition().y > Enemies[j].getPosition().y - 20 && Weapons[i].getBulletPosition().y < Enemies[j].getPosition().y + 60)
                {
                    Enemies[j].reduceHealth(Weapons[i].getDamage());
                    return true;
                }
            else if(Weapons[i].getBulletPosition().x < 0 || Weapons[i].getBulletPosition().x > 800 || Weapons[i].getBulletPosition().y < 50
                    || Weapons[i].getBulletPosition().y > 600)
            {
                return true;
            }
            else
                return false;
        }

void Game::fireBullet(int weapon)
        {
            Weapons[weapon].moveBullet(Weapons[weapon].getBulletDirection().x, Weapons[weapon].getBulletDirection().y);
        }

bool Game::isInRange(sf::Vector2f WeaponPosition, sf::Vector2f EnemyPosition, int boundaryRadius)
        {
            if (pow(pow((WeaponPosition.x + 21.5f) - (EnemyPosition.x), 2) + pow((WeaponPosition.y + 21.5f) - (EnemyPosition.y), 2), 0.5) <= boundaryRadius)
                {
                    return true;
                }
            else if (pow(pow((WeaponPosition.x + 21.5f) - (EnemyPosition.x + 40), 2) + pow((WeaponPosition.y + 21.5f) - (EnemyPosition.y), 2), 0.5) <= boundaryRadius)
                {
                    return true;
                }
            else if (pow(pow((WeaponPosition.x + 21.5f) - (EnemyPosition.x), 2) + pow((WeaponPosition.y + 21.5f) - (EnemyPosition.y + 40), 2), 0.5) <= boundaryRadius)
                {
                    return true;
                }
            else if (pow(pow((WeaponPosition.x + 21.5f) - (EnemyPosition.x + 40), 2) + pow((WeaponPosition.y + 21.5f) - (EnemyPosition.y + 40), 2), 0.5) <= boundaryRadius)
                {
                    return true;
                }
            else if (pow(pow((WeaponPosition.x + 21.5f) - (EnemyPosition.x + 20), 2) + pow((WeaponPosition.y + 21.5f) - (EnemyPosition.y + 20), 2), 0.5) >= boundaryRadius)
                {
                    return false;
                }
        }

void Game::typeOfEnemyToAdd()
        {
            int TempScore = Score;
            srand((int)time(0));
            while (TempScore > 0)
            {
                int n = (rand() % 3) + 1;
                switch (n)
                {
                case 1:
                    addEnemy(1);
                    TempScore = TempScore - 10;
                    break;

                case 2:
                    if (TempScore - 50 >= 0)
                    {
                        addEnemy(2);
                        TempScore = TempScore - 50;
                    }
                    break;

                case 3:
                    if (TempScore - 100 >= 0)
                    {
                        addEnemy(3);
                        TempScore = TempScore - 100;
                    }
                    break;
                }
            }
            enemiesAdded = true;
        }

void Game::addEnemy(int type)
        {
            GeneralEnemyClass newEnemy;
            switch (type)
            {
                case 1:
                    newEnemy.setTexture(Enemy1.texture);
                    newEnemy.setScore(Enemy1.getScore());
                    newEnemy.setHealth(Enemy1.getHealth());
                    break;
                case 2:
                    newEnemy.setTexture(Enemy2.texture);
                    newEnemy.setScore(Enemy2.getScore());
                    newEnemy.setHealth(Enemy2.getHealth());
                    break;
                case 3:
                    newEnemy.setTexture(Enemy3.texture);
                    newEnemy.setScore(Enemy3.getScore());
                    newEnemy.setHealth(Enemy3.getHealth());
                    break;
            }

            if (totalEnemies == 0)
                {
                    newEnemy.setPosition(0, 310);
                }
            else
                {
                    newEnemy.setPosition(Enemies[totalEnemies - 1].getPosition().x - 80, Enemies[totalEnemies - 1].getPosition().y);
                }
            Enemies.push_back(newEnemy);
            totalEnemies++;
        }

void Game::update(sf::Time deltaTime)
            {
                float time = deltaTime.asSeconds();
                int move = EnemySpeed * time;
                enemyAnimationTimer += deltaTime.asSeconds();

                for (int i = 0; i < totalEnemies; i++)
                {
                    if(enemyAnimationTimer >= switchTime)
                    {
                        Enemies[i].nextAnimation();
                    }

                    if(Enemies[i].attractMovement(move, attractionPoints[Enemies[i].getAttractedNumber()][0], attractionPoints[Enemies[i].getAttractedNumber()][1]))
                    {
                        Enemies[i].incrementAttractionPoint();
                    }
                    if (Enemies[i].getAttractedNumber() == 9)
                    {
                        towerHealth -= Enemies[i].getHealth();
                        Enemies.erase(Enemies.begin() + i);
                        totalEnemies--;
                        i = 0;
                    }
                }

                if (enemyAnimationTimer > switchTime)
                    enemyAnimationTimer = 0;
            }

void Game::runPowerupAnimation(float time)
        {
            PowerUp.setPosition(400, 300);
            powerupAnimationTimer += time;
            PowerUp.changeRadius(powerupAnimationTimer);

            if(PowerUp.getAnimationRadius() >= 300)
            {
                for(int i = 0; i < totalEnemies; i++)
                {
                    Score = Score + Enemies[i].getScore();
                    Money = Money + Enemies[i].getReturnMoney() * 5;
                    Enemies.erase(Enemies.begin() + i);
                }
                totalEnemies = 0;
                PowerUp.resetPosition();
                usingPowerUp = false;
            }
        }
void Game::duringGameRender()
        {
                mWindow.clear();
                mWindow.draw(mBackground);
                mWindow.draw(mapBackground);

                mWindow.draw(Weapon1.getBorder(Money));
                mWindow.draw(Weapon2.getBorder(Money));
                mWindow.draw(Weapon3.getBorder(Money));
                std::stringstream m;
                m << Money;
                MoneyText.setString("Money: $" + m.str());
                mWindow.draw(MoneyText);
                std::stringstream s;
                int temp = Score - 100;
                s << temp;
                ScoreText.setString("Score: " + s.str());
                mWindow.draw(ScoreText);
                mWindow.draw(Weapon1Text);
                mWindow.draw(Weapon2Text);
                mWindow.draw(Weapon3Text);
                mWindow.draw(WeaponsTitleBorder);
                mWindow.draw(WeaponsTitle);
                mWindow.draw(PowerUp.getBorder(Money));
                mWindow.draw(PowerUp.getButton());
                mWindow.draw(PowerupButtonText);

                mWindow.draw(Weapon1.getBaseSprite());
                mWindow.draw(Weapon1.getTurretSprite());
                mWindow.draw(Weapon2.getBaseSprite());
                mWindow.draw(Weapon2.getTurretSprite());
                mWindow.draw(Weapon3.getBaseSprite());
                mWindow.draw(Weapon3.getTurretSprite());

                if (speedMultiplier == 4)
                {
                    speedSelectionButton.setTextureRect(sf::IntRect(3 * 180, 0, 180, 40));
                }
                else
                {
                    int n = speedMultiplier;
                    speedSelectionButton.setTextureRect(sf::IntRect(n * 180, 0, 180, 40));
                }
                mWindow.draw(speedSelectionButton);

            for(int i = 0; i < totalWeapons; i++)
                {
                    mWindow.draw(Weapons[i].getBaseSprite());
                    mWindow.draw(Weapons[i].getTurretSprite());
                    mWindow.draw(Weapons[i].getReloadOutline());
                    mWindow.draw(Weapons[i].getReloadInside());

                    if (Weapons[i].fireStatus())
                    {
                        mWindow.draw(Weapons[i].getBulletSprite());
                    }
                }

            for (int i = 0; i < totalEnemies; i++)
                {
                    mWindow.draw(Enemies[i].getEnemySprite());
                    mWindow.draw(Enemies[i].getHealthBorder());
                    mWindow.draw(Enemies[i].getHealthInside());
                }

            if(usingPowerUp)
                {
                    mWindow.draw(PowerUp.getPowerupAnimationShape());
                }

            mWindow.draw(PowerUp.getSprite());
            float percentage = towerHealth/fullHealth;
            if (percentage <= 0)
                TowerHealthInside.setSize(sf::Vector2f(0, 20));
            else
                TowerHealthInside.setSize(sf::Vector2f(percentage * 200, 20));
            mWindow.draw(TowerHealthOutline);
            mWindow.draw(TowerHealthInside);

            mWindow.draw(inGameHelpButton);
            mWindow.draw(inGameHelpButtonText);

            mWindow.draw(inGamePauseButton);
            mWindow.draw(inGamePauseButtonText);
            toggle = false;

        }
