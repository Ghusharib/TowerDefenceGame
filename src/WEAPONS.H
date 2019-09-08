#ifndef WEAPONS_H
#define WEAPONS_H
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class GeneralWeaponClass
{
    public:
        GeneralWeaponClass():
            BaseSprite(), BaseTexture()
        {
            if(!BaseTexture.loadFromFile("Images/MainBase.png"))
            {
                //HandleLoadingError
            }
            BaseSprite.setTexture(BaseTexture);

            reloadOutline.setSize(sf::Vector2f(40, 5));
            reloadOutline.setOutlineColor(sf::Color::Black);
            reloadOutline.setOutlineThickness(1);
            reloadOutline.setFillColor(sf::Color::Transparent);

            reloadInside.setFillColor(sf::Color::Cyan);


        }

    public:
        //Setter Methods
        void setBasePosition(float x, float y)
        {
            BaseSprite.setPosition(x, y);
        }

        void setTurretPosition(float x, float y)
        {
            TurretSprite.setOrigin((TurretTexture.getSize().x/2), TurretTexture.getSize().y);
            TurretSprite.setPosition(x + (TurretTexture.getSize().x/2), y + TurretTexture.getSize().y);
        }

        void setPostPlacedTurretPosition(float x, float y)
        {
            TurretSprite.setPosition(x, y);
        }

        void setTurretTexture(sf::Texture turret)
        {
            TurretTexture = turret;
            TurretSprite.setTexture(turret);
        }

        void setBulletTexture(sf::Texture bullet)
        {
            BulletTexture = bullet;
            BulletSprite.setTexture(bullet);
        }
        void unlock()
        {
            LockStatus = false;
            isFired = false;
        }
        void lockOnto(int n)
        {
            lockedOnto = n;
            LockStatus = true;
        }
        void rotateTurret(float rotation)
        {
            TurretSprite.setRotation(rotation);
        }

        void setReloadTime(sf::Time time)
        {
            reloadTime = time;
        }

        void updateTime(sf::Time time)
        {
            currentTime = currentTime + time;
        }

        void restartTimer()
        {
            currentTime = sf::seconds(0);
        }

        void fired()
        {
            isFired = true;
        }

        void reset()
        {
            isFired = false;
            BulletSprite.setPosition(BaseSprite.getPosition().x + 21.5f, BaseSprite.getPosition().y + 21.5f);
        }

        void moveBullet(int x, int y)
        {
            BulletSprite.setPosition(x + BulletSprite.getPosition().x , y + BulletSprite.getPosition().y);
        }

        void setBulletDirection(int x, int y)
        {
            BulletDirection.x = x;
            BulletDirection.y = y;
        }

        void setDamage(int n)
        {
            damage = n;
        }

        void setRadius(int n)
        {
            radius = n;
        }

        void setReturnMoney(int n)
        {
            returnMoney = n;
        }
        //Getter Methods
        sf::Vector2f getBasePosition()
        {
            return BaseSprite.getPosition();
        }

        sf::Vector2f getTurretPosition()
        {
            return TurretSprite.getPosition();
        }

        sf::Vector2f getBulletPosition()
        {
            return BulletSprite.getPosition();
        }

        sf::Vector2f getBulletDirection()
        {
            return BulletDirection;
        }

        sf::Sprite getBaseSprite()
        {
            BaseSprite.setTexture(BaseTexture);
            return BaseSprite;
        }

        sf::Sprite getTurretSprite()
        {
            TurretSprite.setTexture(TurretTexture);
            return TurretSprite;
        }

        sf::Sprite getBulletSprite()
        {
            BulletSprite.setTexture(BulletTexture);
            return BulletSprite;
        }

        sf::RectangleShape getReloadOutline()
        {
            if(TurretSprite.getRotation() > 90 && TurretSprite.getRotation() < 270)
                reloadOutline.setPosition(BaseSprite.getPosition().x, BaseSprite.getPosition().y - 10);
            else
                reloadOutline.setPosition(BaseSprite.getPosition().x, BaseSprite.getPosition().y + 55);
            return reloadOutline;
        }
        sf::RectangleShape getReloadInside()
        {
            if(TurretSprite.getRotation() > 90 && TurretSprite.getRotation() < 270)
                reloadInside.setPosition(BaseSprite.getPosition().x, BaseSprite.getPosition().y - 10);
            else
                reloadInside.setPosition(BaseSprite.getPosition().x, BaseSprite.getPosition().y + 55);

            if(currentTime.asSeconds()/reloadTime.asSeconds() >= 1)
            {
                reloadInside.setSize(sf::Vector2f(40, 5));
            }
            else
            {
                reloadInside.setSize(sf::Vector2f(40 * currentTime.asSeconds()/reloadTime.asSeconds(), 5));
            }
            return reloadInside;
        }
        bool isLocked()
        {
            return LockStatus;
        }

        int isLockedOn()
        {
            return lockedOnto;
        }

        int getRadius()
        {
            return radius;
        }

        sf::Time getTime()
        {
            return currentTime;
        }

        bool isReadyToFire()
        {
            if (currentTime > reloadTime)
                return true;
            else
                return false;
        }

        int getBulletSpeed()
        {
            return bulletSpeed;
        }

        bool fireStatus()
        {
            return isFired;
        }

        int getDamage()
        {
            return damage;
        }

        int getReturnMoney()
        {
            return returnMoney;
        }

        sf::Texture BaseTexture, TurretTexture, BulletTexture;
    private:
        sf::Sprite BaseSprite, TurretSprite, BulletSprite;
        bool LockStatus = false;
        int lockedOnto;
        sf::Time reloadTime;
        sf::Time currentTime = sf::seconds(0);
        sf::Vector2f BulletDirection;
        sf::RectangleShape reloadOutline, reloadInside;
        int bulletSpeed = 40;
        int damage;
        bool isFired = false;
        int radius;
        int returnMoney;
};

class Weapon1Class
{
    public:
    Weapon1Class()
        : BaseSprite(), BaseTexture(), TurretSprite(), TurretTexture()
        {
            if(!BaseTexture.loadFromFile("Images/MainBase.png"))
            {
                //Handle Loading Error
            }
            BaseSprite.setTexture(BaseTexture);

            if(!TurretTexture.loadFromFile("Images/Weapon1Top.png"))
            {
                //Handle Loading Error
            }
            TurretSprite.setTexture(TurretTexture);

            if(!BulletTexture.loadFromFile("Images/Weapon1Bullet.png"))
            {
                //Handle Loading Error
            }
            BulletSprite.setTexture(BulletTexture);

            Border.setSize(sf::Vector2f(180, 120));
            Border.setOutlineColor(sf::Color::Black);
            Border.setOutlineThickness(1.f);
            Border.setPosition(801.f, 81.f);

            BaseSprite.setPosition(Border.getPosition().x + 19, Border.getPosition().y + 40);
            TurretSprite.setPosition(BaseSprite.getPosition().x + 15.5f, BaseSprite.getPosition().y - 21.25f);

        }

    public:
        //Setter Methods
        void setBasePosition(float x, float y)
        {
            BaseSprite.setPosition(x, y);
        }

        void setTurretPosition(float x, float y)
        {
            TurretSprite.setPosition(x, y);
        }

        void resetPosition()
        {
            BaseSprite.setPosition(Border.getPosition().x + 19, Border.getPosition().y + 40);
            TurretSprite.setPosition(BaseSprite.getPosition().x + 15.5f, BaseSprite.getPosition().y - 21.25f);
        }
        //Getter Methods
        sf::Vector2f getBasePosition()
        {
            return BaseSprite.getPosition();
        }

        sf::Vector2f getTurretPosition()
        {
            return TurretSprite.getPosition();
        }

        sf::Sprite getBaseSprite()
        {
            return BaseSprite;
        }

        sf::Sprite getTurretSprite()
        {
            return TurretSprite;
        }

        sf::RectangleShape getBorder(int money)
        {
            if(money < cost)
            {
                Border.setFillColor(sf::Color::Red);
            }
            else
            {
                Border.setFillColor(sf::Color::White);
            }
            return Border;
        }

        int getCost()
        {
            return cost;
        }

        std::string getInfo()
        {
            return info;
        }

        sf::Time getReloadTime()
        {
            return reloadTime;
        }

        sf::Sprite getBullet()
        {
            return BulletSprite;
        }

        int getDamage()
        {
            return damage;
        }

        sf::Texture BaseTexture, TurretTexture, BulletTexture;
    private:
        sf::Sprite BaseSprite, TurretSprite, BulletSprite;
        sf::RectangleShape Border;
        int cost = 2500;
        int damage = 10;
        sf::Time reloadTime = sf::seconds(0.5);
        std::string info = "Weapon 1\nReload: 0.5s\nCost: $2500\nDamage: 10";
};

class Weapon2Class
{
    public:
    Weapon2Class()
        : BaseSprite(), BaseTexture(), TurretSprite(), TurretTexture()
        {
            if(!BaseTexture.loadFromFile("Images/MainBase.png"))
            {
                //Handle Loading Error
            }
            BaseSprite.setTexture(BaseTexture);

            if(!TurretTexture.loadFromFile("Images/Weapon2Top.png"))
            {
                //Handle Loading Error
            }
            TurretSprite.setTexture(TurretTexture);

            if(!BulletTexture.loadFromFile("Images/Weapon2Bullet.png"))
            {
                //Handle Loading Error
            }
            BulletSprite.setTexture(BulletTexture);

            Border.setSize(sf::Vector2f(180, 120));
            Border.setOutlineColor(sf::Color::Black);
            Border.setOutlineThickness(1.f);
            Border.setPosition(801.f, 202.f);

            BaseSprite.setPosition(Border.getPosition().x + 19, Border.getPosition().y + 40);
            TurretSprite.setPosition(BaseSprite.getPosition().x + 14.0f, BaseSprite.getPosition().y - 21.25f);
        }

    public:
        //Setter Methods
        void setBasePosition(float x, float y)
        {
            BaseSprite.setPosition(x, y);
        }

        void setTurretPosition(float x, float y)
        {
            TurretSprite.setPosition(x, y);
        }

        void resetPosition()
        {
            BaseSprite.setPosition(Border.getPosition().x + 19, Border.getPosition().y + 40);
            TurretSprite.setPosition(BaseSprite.getPosition().x + 14.0f, BaseSprite.getPosition().y - 21.25f);
        }
        //Getter Methods
        sf::Vector2f getBasePosition()
        {
            return BaseSprite.getPosition();
        }

        sf::Vector2f getTurretPosition()
        {
            return TurretSprite.getPosition();
        }

        sf::Sprite getBaseSprite()
        {
            return BaseSprite;
        }

        sf::Sprite getTurretSprite()
        {
            return TurretSprite;
        }


        sf::RectangleShape getBorder(int money)
        {
            if(money < cost)
            {
                Border.setFillColor(sf::Color::Red);
            }
            else
            {
                Border.setFillColor(sf::Color::White);
            }
            return Border;
        }

        int getCost()
        {
            return cost;
        }

        std::string getInfo()
        {
            return info;
        }

        sf::Time getReloadTime()
        {
            return reloadTime;
        }

        sf::Sprite getBullet()
        {
            return BulletSprite;
        }

        int getDamage()
        {
            return damage;
        }

        sf::Texture BaseTexture, TurretTexture, BulletTexture;
    private:
        sf::Sprite BaseSprite, TurretSprite, BulletSprite;
        sf::RectangleShape Border;
        int cost = 5000;
        int damage = 40;
        std::string info = "Weapon 2\nReload: 1s\nCost: $5000\nDamage: 40";
        sf::Time reloadTime = sf::seconds(1);
};

class Weapon3Class
{
    public:
    Weapon3Class()
        : BaseSprite(), BaseTexture(), TurretSprite(), TurretTexture()
        {
            if(!BaseTexture.loadFromFile("Images/MainBase.png"))
            {
                //Handle Loading Error
            }
            BaseSprite.setTexture(BaseTexture);

            if(!TurretTexture.loadFromFile("Images/Weapon3Top.png"))
            {
                //Handle Loading Error
            }
            TurretSprite.setTexture(TurretTexture);

            if(!BulletTexture.loadFromFile("Images/Weapon3Bullet.png"))
            {
                //Handle Loading Error
            }
            BulletSprite.setTexture(BulletTexture);

            Border.setSize(sf::Vector2f(180, 120));
            Border.setOutlineColor(sf::Color::Black);
            Border.setOutlineThickness(1.f);
            Border.setPosition(801.f, 323.f);

            BaseSprite.setPosition(Border.getPosition().x + 19, Border.getPosition().y + 40);
            TurretSprite.setPosition(BaseSprite.getPosition().x + 12.5f, BaseSprite.getPosition().y - 6.25f);

        }

    public:
        //Setter Methods
        void setBasePosition(float x, float y)
        {
            BaseSprite.setPosition(x, y);
        }

        void setTurretPosition(float x, float y)
        {
            TurretSprite.setPosition(x, y);
        }

        void resetPosition()
        {
            BaseSprite.setPosition(Border.getPosition().x + 19, Border.getPosition().y + 40);
            TurretSprite.setPosition(BaseSprite.getPosition().x + 12.5f, BaseSprite.getPosition().y - 6.25f);
        }
        //Getter Methods
        sf::Vector2f getBasePosition()
        {
            return BaseSprite.getPosition();
        }

        sf::Vector2f getTurretPosition()
        {
            return TurretSprite.getPosition();
        }

        sf::Sprite getBaseSprite()
        {
            return BaseSprite;
        }

        sf::Sprite getTurretSprite()
        {
            return TurretSprite;
        }


        sf::RectangleShape getBorder(int money)
        {
            if(money < cost)
            {
                Border.setFillColor(sf::Color::Red);
            }
            else
            {
                Border.setFillColor(sf::Color::White);
            }
            return Border;
        }

        int getCost()
        {
            return cost;
        }

        std::string getInfo()
        {
            return info;
        }

        sf::Time getReloadTime()
        {
            return reloadTime;
        }

        sf::Sprite getBullet()
        {
            return BulletSprite;
        }

        int getDamage()
        {
            return damage;
        }

        sf::Texture BaseTexture, TurretTexture, BulletTexture;
    private:
        sf::Sprite BaseSprite, TurretSprite, BulletSprite;
        sf::RectangleShape Border;
        int cost = 10000;
        int damage = 60;
        std::string info = "Weapon 3\nReload: 2s\nCost: $10000\nDamage: 60\nBig radius";
        sf::Time reloadTime = sf::seconds(2);
};

class PowerUpClass
{
    public:
        PowerUpClass()
        : PowerupSprite(), PowerupTexture(), Border()
        {

            if(!PowerupTexture.loadFromFile("Images/Powerup.png"))
            {
                //Handle Loading Error
            }
            PowerupSprite.setTexture(PowerupTexture);
            PowerupSprite.setOrigin(PowerupTexture.getSize().x/2, PowerupTexture.getSize().y/2);

            Border.setSize(sf::Vector2f(180, 105));
            Border.setOutlineColor(sf::Color::Black);
            Border.setOutlineThickness(1.f);
            Border.setPosition(801.f, 444.f);

            PowerupButton.setSize(sf::Vector2f(90, 75));
            PowerupButton.setOutlineColor(sf::Color::Yellow);
            PowerupButton.setOutlineThickness(5.f);
            PowerupButton.setFillColor(sf::Color::Yellow);
            PowerupButton.setPosition(885.f, 455.f);

            PowerupSprite.setPosition(Border.getPosition().x + PowerupTexture.getSize().x/2, Border.getPosition().y + PowerupTexture.getSize().y/2);
            PowerupAnimation.setFillColor(sf::Color::Yellow);
            PowerupAnimation.setPosition(400, 300);
        }

        sf::Sprite getSprite()
        {
            PowerupSprite.setTexture(PowerupTexture);
            return PowerupSprite;
        }

        sf::RectangleShape getBorder(int money)
        {
            if(money < cost)
            {
                Border.setFillColor(sf::Color::Red);
            }
            else
            {
                Border.setFillColor(sf::Color::White);
            }
            return Border;
        }
        sf::RectangleShape getButton()
        {
            return PowerupButton;
        }
        bool isUsed()
        {
            return usedAlready;
        }
        int getCost()
        {
            return cost;
        }
        sf::Vector2f getButtonPosition()
        {
            return PowerupButton.getPosition();
        }
        void use()
        {
            usedAlready = true;
        }
        void setPosition(int x, int y)
        {
            PowerupSprite.setPosition(x, y);
        }
        void resetPosition()
        {
            PowerupSprite.setPosition(Border.getPosition().x + PowerupTexture.getSize().x/2, Border.getPosition().y + PowerupTexture.getSize().y/2);
        }

        void resetUse()
        {
            usedAlready = false;
        }

        float getAnimationRadius()
        {
            return PowerupAnimation.getRadius();
        }

        void changeRadius(float x)
        {
            PowerupAnimation.setRadius((x/2) * 600);
            PowerupAnimation.setOrigin(PowerupAnimation.getRadius(), PowerupAnimation.getRadius());
        }
        sf::CircleShape getPowerupAnimationShape()
        {
            return PowerupAnimation;
        }
        sf::Texture PowerupTexture;
    private:
        sf::Sprite PowerupSprite;
        sf::RectangleShape Border;
        sf::RectangleShape PowerupButton;
        sf::CircleShape PowerupAnimation;
        bool usedAlready = false;
        int cost = 15000;
};
#endif
