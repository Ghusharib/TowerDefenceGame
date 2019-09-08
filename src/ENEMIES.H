#ifndef ENEMIES_H
#define ENEMIES_H
#include <SFML/Graphics.hpp>
#include <cmath>

class GeneralEnemyClass
{
    public:

        GeneralEnemyClass()
        : EnemyHealthBorder(), EnemyHealthInsideColour()
            {
                EnemyHealthBorder.setSize(sf::Vector2f(40.f, 5.f));
                EnemyHealthBorder.setOutlineColor(sf::Color::Black);
                EnemyHealthBorder.setOutlineThickness(1);
                EnemyHealthBorder.setFillColor(sf::Color::Transparent);

                EnemyHealthInsideColour.setSize(sf::Vector2f(40, 5));
                EnemyHealthInsideColour.setFillColor(sf::Color::Red);
            }
        //Setter Methods

        void setPosition(int x, int y)
        {
            sprite.setPosition(x, y);
        }

        void setTexture(sf::Texture textureToAdd)
        {
            texture = textureToAdd;
        }

        void setScore(int n)
        {
            EnemyScore = n;
        }

        void setHealth(int n)
        {
            EnemyHealth = n;
            TempHealth = n;
        }

        void reduceHealth(int n)
        {
            EnemyHealth -= n;
        }
        void incrementAttractionPoint()
        {
            attractedNumber++;
        }
        void nextAnimation()
        {
            currentAnimation++;
        }
        //Getter Methods

        sf::Vector2f getPosition()
        {
            return sprite.getPosition();
        }
        sf::Sprite getEnemySprite()
        {
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(currentAnimation%2 * 40, 0, 40, 40));
            return sprite;
        }
        int getHealth()
        {
            return EnemyHealth;
        }

        int getScore()
        {
            return EnemyScore;
        }

        int getReturnMoney()
        {
            return TempHealth;
        }

        int getAttractedNumber()
        {
            return attractedNumber;
        }

        sf::RectangleShape getHealthBorder()
        {
            EnemyHealthBorder.setPosition(sprite.getPosition().x, sprite.getPosition().y + 50);
            return EnemyHealthBorder;
        }

        sf::RectangleShape getHealthInside()
        {
            float multiple = EnemyHealth/TempHealth;
            EnemyHealthInsideColour.setSize(sf::Vector2f((multiple) * 40, 5));
            EnemyHealthInsideColour.setPosition(sprite.getPosition().x, sprite.getPosition().y + 50);
            return EnemyHealthInsideColour;
        }

        bool attractMovement(int move, int x, int y)
        {
            switch(attractedNumber)
            {
                case 0: case 2: case 4: case 8:
                    sprite.move(move, 0);
                    if (sprite.getPosition().x + 20 > x)
                        return true;
                    else
                        return false;
                    break;
                case 1: case 5: case 7:
                    sprite.move(0, -move);
                    if (sprite.getPosition().y + 20 < y)
                        return true;
                    else
                        return false;
                    break;
                case 3:
                    sprite.move(0, move);
                    if (sprite.getPosition().y + 20 > y)
                        return true;
                    else
                        return false;
                    break;
                case 6:
                    sprite.move(-move, 0);
                    if (sprite.getPosition().x + 20 < x)
                        return true;
                    else
                        return false;
                    break;
            }
        }

        bool isDead()
        {
            if (EnemyHealth < 0)
                return true;
            else
                return false;
        }

        sf::Texture texture;

    private:
        int EnemyScore;
        int EnemyHealth;
        float TempHealth;
        int attractedNumber = 0;
        int currentAnimation = 0;
        sf::Sprite sprite;
        sf::RectangleShape EnemyHealthBorder, EnemyHealthInsideColour;
};

class Enemy1Class
{
    public:
    Enemy1Class()
        :sprite(), texture()
        {
            if(!texture.loadFromFile("Images/Enemy1.png"))
            {
                //Handle Loading Error
            }
            sprite.setTexture(texture);
        }
    public:
        //Setter Methods

        void setPosition(int x, int y)
        {
            sprite.setPosition(x, y);
        }

        //Getter Methods

        sf::Vector2f getPosition()
        {
            return sprite.getPosition();
        }
        sf::Sprite getEnemySprite()
        {
            sprite.setTexture(texture);
            return sprite;
        }
        int getScore()
        {
            return EnemyScore;
        }
        int getHealth()
        {
            return EnemyHealth;
        }
        sf::Texture texture;

    private:
        int EnemyScore = 10;
        int EnemyHealth = 100;
        sf::Sprite sprite;
};

class Enemy2Class
{
    public:
    Enemy2Class()
        :sprite(), texture()
        {
            if(!texture.loadFromFile("Images/Enemy2.png"))
            {
                //Handle Loading Error
            }
            sprite.setTexture(texture);
        }
    public:
        //Setter Methods

        void setPosition(int x, int y)
        {
            sprite.setPosition(x, y);
        }

        //Getter Methods

        sf::Vector2f getPosition()
        {
            return sprite.getPosition();
        }
        sf::Sprite getEnemySprite()
        {
            sprite.setTexture(texture);
            return sprite;
        }
        int getScore()
        {
            return EnemyScore;
        }
        int getHealth()
        {
            return EnemyHealth;
        }
        sf::Texture texture;

    private:
        int EnemyScore = 50;
        int EnemyHealth = 175;
        sf::Sprite sprite;
};

class Enemy3Class
{
    public:
    Enemy3Class()
        :sprite(), texture()
        {
            if(!texture.loadFromFile("Images/Enemy3.png"))
            {
                //Handle Loading Error
            }
            sprite.setTexture(texture);
        }
    public:
        //Setter Methods

        void setPosition(int x, int y)
        {
            sprite.setPosition(x, y);
        }

        //Getter Methods

        sf::Vector2f getPosition()
        {
            return sprite.getPosition();
        }
        sf::Sprite getEnemySprite()
        {
            sprite.setTexture(texture);
            return sprite;
        }
        int getScore()
        {
            return EnemyScore;
        }
        int getHealth()
        {
            return EnemyHealth;
        }
        sf::Texture texture;

    private:
        int EnemyScore = 100;
        int EnemyHealth = 250;
        sf::Sprite sprite;
};
#endif
