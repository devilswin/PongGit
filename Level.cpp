#include "Level.hpp"

Level::Level()
        : difficulty(0)
{
        
        setLevelTime();                    
        setBallSpeed();                    
        setPaddleSize();                   
        setPointsPerHit();                 
			       
}

void Level::setBallSpeed()
{
        ballSpeed.x = 150*(1+difficulty/100);
        ballSpeed.y = ballSpeed.x;
}

void Level::setLevelTime()
{
        levelTime = sf::seconds(10+(10*difficulty));
}

void Level::setPaddleSize()
{
        paddleSize.x = 1 * (difficulty/100);
}

void Level::setPointsPerHit()
{
        pointsPerHit = 100 + (10 * difficulty);
}
void Level::setDifficulty(int diff)
{
        difficulty = diff;
}

sf::Vector2f Level::getBallSpeed()
{
       return ballSpeed; 
}

sf::Vector2f Level::getPaddleSize()
{
        return paddleSize;
}

sf::Time Level::getLevelTime()
{
        return levelTime;
}

int Level::getPointsPerHit()
{
        return pointsPerHit;
}
