#include "GAME.H"

void Game::processPreGameEvents()
        {
                sf::Event event;
                while (mWindow.pollEvent(event))
                {
                    switch (event.type)
                    {
                    case sf::Event::MouseMoved:
                        for (int i = 0; i < totalWeapons; i++)
                        {
                            if (selectedPlacedWeapon && i == selectedPlacedWeaponNumber)
                            {
                                continue;
                            }
                            else if (event.mouseMove.x < Weapons[i].getBasePosition().x + 63.75 && event.mouseMove.x > Weapons[i].getBasePosition().x  - 21.25 && event.mouseMove.y < Weapons[i].getBasePosition().y + 63.75 && event.mouseMove.y > Weapons[i].getBasePosition().y - 21.25)
                            {
                                Radius.setFillColor(sf::Color(242,43,21,128));
                                toggle = true;
                                break;
                            }
                        }
                        if (event.mouseMove.x > 0 && event.mouseMove.x < 257.25 && event.mouseMove.y > 278.25 && event.mouseMove.y < 376.25)
                            Radius.setFillColor(sf::Color(242,43,21,128));
                        else if (event.mouseMove.x < 257.25 && event.mouseMove.x > 157.75 && event.mouseMove.y < 333.75 && event.mouseMove.y > 118.75)
                            Radius.setFillColor(sf::Color(242,43,21,128));
                        else if (event.mouseMove.x < 378.25 && event.mouseMove.x > 157.75 && event.mouseMove.y < 217.25 && event.mouseMove.y > 118.75)
                            Radius.setFillColor(sf::Color(242,43,21,128));
                        else if (event.mouseMove.x < 378.25 && event.mouseMove.x > 278.75   && event.mouseMove.y > 118.75)
                            Radius.setFillColor(sf::Color(242,43,21,128));
                        else if (event.mouseMove.x < 624.25 && event.mouseMove.x > 278.25 && event.mouseMove.y > 449.75 && event.mouseMove.y < 550)
                            Radius.setFillColor(sf::Color(242,43,21,128));
                        else if (event.mouseMove.x < 624.25 && event.mouseMove.x > 524.75 && event.mouseMove.y > 225.75 && event.mouseMove.y < 550)
                            Radius.setFillColor(sf::Color(242,43,21,128));
                        else if (event.mouseMove.x < 624.25 && event.mouseMove.x > 435.75 && event.mouseMove.y > 225.75 && event.mouseMove.y < 325.25)
                            Radius.setFillColor(sf::Color(242,43,21,128));
                        else if (event.mouseMove.x < 536.25 && event.mouseMove.x > 435.75 && event.mouseMove.y < 325.25)
                            Radius.setFillColor(sf::Color(242,43,21,128));
                        else if (event.mouseMove.x > 435.75 && event.mouseMove.y < 157.25)
                            Radius.setFillColor(sf::Color(242,43,21,128));
                        else if(selectedPlacedWeapon && event.mouseMove.x > sellWeaponButton.getPosition().x && event.mouseMove.x < sellWeaponButton.getPosition().x + 180
                               && event.mouseMove.y > sellWeaponButton.getPosition().y && event.mouseMove.y < sellWeaponButton.getPosition().y + 40)
                               Radius.setFillColor(sf::Color(48, 159, 29, 128));
                        else if (event.mouseMove.x < 21.25 || event.mouseMove.x > 778.75 || event.mouseMove.y < 71.25 || event.mouseMove.y > 528.75)
                            Radius.setFillColor(sf::Color(242,43,21,128));
                        else if(!toggle)
                            Radius.setFillColor(sf::Color(255,255,255,128));


                        if (isDragging1)
                        {
                            Weapon1.setBasePosition(event.mouseMove.x - 21.25f, event.mouseMove.y - 21.25f);
                            Weapon1.setTurretPosition(Weapon1.getBasePosition().x + 15.5f, Weapon1.getBasePosition().y - 21.25f);
                            Radius.setPosition(event.mouseMove.x - 100, event.mouseMove.y - 100);
                        }
                        if (isDragging2)
                        {
                            Weapon2.setBasePosition(event.mouseMove.x - 21.25, event.mouseMove.y - 21.25);
                            Weapon2.setTurretPosition(Weapon2.getBasePosition().x + 14.f, Weapon2.getBasePosition().y - 21.25f);
                            Radius.setPosition(event.mouseMove.x - 100, event.mouseMove.y - 100);
                        }
                        if (isDragging3)
                        {
                            Weapon3.setBasePosition(event.mouseMove.x - 21.25, event.mouseMove.y - 21.25);
                            Weapon3.setTurretPosition(Weapon3.getBasePosition().x + 12.5f, Weapon3.getBasePosition().y - 6.25f);
                            Radius.setPosition(event.mouseMove.x - 175, event.mouseMove.y - 175);
                        }
                        if (selectedPlacedWeapon)
                        {
                            Weapons[selectedPlacedWeaponNumber].setBasePosition(event.mouseMove.x - 21.25, event.mouseMove.y - 21.25);
                            Weapons[selectedPlacedWeaponNumber].setPostPlacedTurretPosition(event.mouseMove.x, event.mouseMove.y);
                            Radius.setRadius(Weapons[selectedPlacedWeaponNumber].getRadius());
                            Radius.setPosition(event.mouseMove.x - Weapons[selectedPlacedWeaponNumber].getRadius(), event.mouseMove.y - Weapons[selectedPlacedWeaponNumber].getRadius());
                        }

                        break;
                    case sf::Event::MouseButtonPressed:
                        if(event.mouseButton.button == sf::Mouse::Left)
                        {
                            if (event.mouseButton.x >= PlayButtonBorder.getPosition().x && event.mouseButton.x <= PlayButtonBorder.getPosition().x + 180 && event.mouseButton.y >= PlayButtonBorder.getPosition().y && event.mouseButton.y >= PlayButtonBorder.getPosition().x + 30)
                            {
                                playingGame = true;
                                enemiesAdded = false;
                                EnemySpeed = Score/50 + 75;
                                speedMultiplier = 1;
                                tempSpeedMultiplier = 1;
                            }
                            else if (Money - Weapon1.getCost() >= 0 && event.mouseButton.x > Weapon1.getBasePosition().x && event.mouseButton.x < Weapon1.getBasePosition().x + 42.5f && event.mouseButton.y > Weapon1.getBasePosition().y && event.mouseButton.y < Weapon1.getTurretPosition().y + 64.25f)
                            {
                                Radius.setRadius(100);
                                Radius.setPosition(event.mouseButton.x - 100, event.mouseButton.y - 100);
                                isDragging1 = true;
                            }
                            else if (Money - Weapon2.getCost() >= 0 && event.mouseButton.x > Weapon2.getBasePosition().x && event.mouseButton.x < Weapon2.getBasePosition().x + 42.5f && event.mouseButton.y > Weapon2.getBasePosition().y && event.mouseButton.y < Weapon2.getTurretPosition().y + 63.25f)
                            {
                                Radius.setRadius(100);
                                Radius.setPosition(event.mouseButton.x - 100, event.mouseButton.y - 100);
                                isDragging2 = true;
                            }
                            else if (Money - Weapon3.getCost() >= 0 && event.mouseButton.x > Weapon3.getBasePosition().x && event.mouseButton.x < Weapon3.getBasePosition().x + 42.5f && event.mouseButton.y > Weapon3.getBasePosition().y && event.mouseButton.y < Weapon3.getTurretPosition().y + 51.25)
                            {
                                Radius.setRadius(175);
                                Radius.setPosition(event.mouseButton.x - 175, event.mouseButton.y - 175);
                                isDragging3 = true;
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
                            else
                            {
                                for (int i = 0; i < totalWeapons; i++)
                                {
                                    if (event.mouseButton.x > Weapons[i].getBasePosition().x && event.mouseButton.x < Weapons[i].getBasePosition().x + 42.5
                                        && event.mouseButton.y > Weapons[i].getBasePosition().y && event.mouseButton.y < Weapons[i].getBasePosition().y + 42.5)
                                    {
                                        selectedPlacedWeapon = true;
                                        selectedPlacedWeaponNumber = i;
                                        Radius.setRadius(Weapons[selectedPlacedWeaponNumber].getRadius());
                                        preBasePosition = Weapons[selectedPlacedWeaponNumber].getBasePosition();
                                        preTurretPosition = Weapons[selectedPlacedWeaponNumber].getTurretPosition();
                                        break;
                                    }
                                    else
                                    {
                                        selectedPlacedWeapon = false;
                                    }
                                }
                            }
                        }
                        break;
                    case sf::Event::MouseButtonReleased:
                        for (int i = 0; i < totalWeapons; i++)
                        {
                            if (event.mouseButton.x < Weapons[i].getBasePosition().x + 63.75 && event.mouseButton.x > Weapons[i].getBasePosition().x  - 21.25 && event.mouseButton.y < Weapons[i].getBasePosition().y + 63.75 && event.mouseButton.y > Weapons[i].getBasePosition().y - 21.25)
                            {
                                if(selectedPlacedWeapon && i == selectedPlacedWeaponNumber)
                                    continue;
                                invalidPlace();
                                toggle = true;
                                break;
                            }
                        }
                        if (event.mouseButton.x > 0 && event.mouseButton.x < 257.25 && event.mouseButton.y > 278.25 && event.mouseButton.y < 376.25)
                            invalidPlace();
                        else if (event.mouseButton.x < 257.25 && event.mouseButton.x > 157.75 && event.mouseButton.y < 333.75 && event.mouseButton.y > 118.75)
                            invalidPlace();
                        else if (event.mouseButton.x < 378.25 && event.mouseButton.x > 157.75 && event.mouseButton.y < 217.25 && event.mouseButton.y > 118.75)
                            invalidPlace();
                        else if (event.mouseButton.x < 378.25 && event.mouseButton.x > 278.75   && event.mouseButton.y > 118.75)
                            invalidPlace();
                        else if (event.mouseButton.x < 624.25 && event.mouseButton.x > 278.25 && event.mouseButton.y > 449.75 && event.mouseButton.y < 550)
                            invalidPlace();
                        else if (event.mouseButton.x < 624.25 && event.mouseButton.x > 524.75 && event.mouseButton.y > 225.75 && event.mouseButton.y < 550)
                            invalidPlace();
                        else if (event.mouseButton.x < 624.25 && event.mouseButton.x > 435.75 && event.mouseButton.y > 225.75 && event.mouseButton.y < 325.25)
                            invalidPlace();
                        else if (event.mouseButton.x < 536.25 && event.mouseButton.x > 435.75 && event.mouseButton.y < 325.25)
                            invalidPlace();
                        else if (event.mouseButton.x > 435.75 && event.mouseButton.y < 157.25)
                            invalidPlace();
                        else if (event.mouseButton.x < 21.25 || event.mouseButton.x > 778.75 || event.mouseButton.y < 71.25 || event.mouseButton.y > 528.75)
                            invalidPlace();
                        else if (isDragging1 && Money - Weapon1.getCost() >= 0)
                        {
                            addNewWeapon(Weapon1.getBasePosition(), Weapon1.getTurretPosition(), 1);
                            Weapon1.resetPosition();
                            isDragging1 = false;
                        }
                        else if (isDragging2 && Money - Weapon2.getCost() >= 0)
                        {
                            addNewWeapon(Weapon2.getBasePosition(), Weapon2.getTurretPosition(), 2);
                            Weapon2.resetPosition();
                            isDragging2 = false;
                        }
                        else if (isDragging3 && Money - Weapon3.getCost() >= 0)
                        {
                            addNewWeapon(Weapon3.getBasePosition(), Weapon3.getTurretPosition(), 3);
                            Weapon3.resetPosition();
                            isDragging3 = false;
                        }
                        else if(!toggle)
                        {
                            placedIncorrectly = false;
                        }

                        if (placedIncorrectly && selectedPlacedWeapon)
                        {
                            if(event.mouseButton.x > sellWeaponButton.getPosition().x && event.mouseButton.x < sellWeaponButton.getPosition().x + 180
                               && event.mouseButton.y > sellWeaponButton.getPosition().y && event.mouseButton.y < sellWeaponButton.getPosition().y + 40)
                            {
                                Money = Money + Weapons[selectedPlacedWeaponNumber].getReturnMoney();
                                Weapons.erase(Weapons.begin() + selectedPlacedWeaponNumber);
                                totalWeapons--;
                                selectedPlacedWeapon = false;
                            }
                            else
                            {
                                Weapons[selectedPlacedWeaponNumber].setBasePosition(preBasePosition.x, preBasePosition.y);
                                Weapons[selectedPlacedWeaponNumber].setPostPlacedTurretPosition(preTurretPosition.x, preTurretPosition.y);
                                selectedPlacedWeapon = false;
                            }
                        }
                        else
                        {
                            selectedPlacedWeapon = false;
                        }
                        break;
                    case sf::Event::MouseLeft:
                            invalidPlace();
                        break;
                    case sf::Event::Closed:
                        mWindow.close();
                        break;
                    }
                }
            }

void Game::addNewWeapon(sf::Vector2f position, sf::Vector2f turret, int WeaponType)
        {
            if (position.x < 100 && position.y > 500)
            {
                //Do not do anything
            }
            else
            {
                GeneralWeaponClass newWeapon;
                newWeapon.setBasePosition(position.x, position.y);
                switch (WeaponType){
                    case 1:
                    newWeapon.setTurretTexture(Weapon1.TurretTexture);
                    newWeapon.setBulletTexture(Weapon1.BulletTexture);
                    newWeapon.setReloadTime(Weapon1.getReloadTime());
                    newWeapon.setDamage(Weapon1.getDamage());
                    newWeapon.setReturnMoney(Weapon1.getCost() * 0.5);
                    Money -= Weapon1.getCost();
                    break;

                    case 2:
                    newWeapon.setTurretTexture(Weapon2.TurretTexture);
                    newWeapon.setBulletTexture(Weapon2.BulletTexture);
                    newWeapon.setReloadTime(Weapon2.getReloadTime());
                    newWeapon.setDamage(Weapon2.getDamage());
                    newWeapon.setReturnMoney(Weapon2.getCost() * 0.5);
                    Money -= Weapon2.getCost();
                    break;

                    case 3:
                    newWeapon.setTurretTexture(Weapon3.TurretTexture);
                    newWeapon.setBulletTexture(Weapon3.BulletTexture);
                    newWeapon.setReloadTime(Weapon3.getReloadTime());
                    newWeapon.setDamage(Weapon3.getDamage());
                    newWeapon.setReturnMoney(Weapon3.getCost() * 0.5);
                    Money-= Weapon3.getCost();
                    break;
                }
                newWeapon.setTurretPosition(turret.x, turret.y);
                newWeapon.setRadius(Radius.getRadius());
                Weapons.push_back(newWeapon);
                totalWeapons++;
            }
        }


void Game::invalidPlace()
        {
            Weapon1.resetPosition();
            isDragging1 = false;
            Weapon2.resetPosition();
            isDragging2 = false;
            Weapon3.resetPosition();
            isDragging3 = false;
            placedIncorrectly = true;
        }
void Game::preGameRender()
        {
                mWindow.clear();
                mWindow.draw(mBackground);
                mWindow.draw(mapBackground);

                if (selectedPlacedWeapon)
                {
                    selectionBox.setPosition(Weapons[selectedPlacedWeaponNumber].getBasePosition());
                    mWindow.draw(selectionBox);
                    std::stringstream returnMoney;
                    returnMoney << Weapons[selectedPlacedWeaponNumber].getReturnMoney();
                    sellWeaponText.setString("Sell for $" + returnMoney.str() + "\nDrag here to sell");
                    mWindow.draw(sellWeaponButton);
                    mWindow.draw(sellWeaponText);
                }
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
                if (isDragging1 || isDragging2 || isDragging3 || selectedPlacedWeapon)
                {
                    mWindow.draw(Radius);
                }
                mWindow.draw(Weapon1.getBaseSprite());
                mWindow.draw(Weapon1.getTurretSprite());
                mWindow.draw(Weapon2.getBaseSprite());
                mWindow.draw(Weapon2.getTurretSprite());
                mWindow.draw(Weapon3.getBaseSprite());
                mWindow.draw(Weapon3.getTurretSprite());

                for(int i = 0; i < totalWeapons; i++)
                {
                    mWindow.draw(Weapons[i].getBaseSprite());
                    mWindow.draw(Weapons[i].getTurretSprite());
                }

                mWindow.draw(PlayButtonBorder);
                mWindow.draw(PlayButton);

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
