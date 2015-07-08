#ifndef LEVEL_HPP
#define LEVEL_HPP
#include <SFML/System.hpp>

class Level
{
        public:
	    
	    Level();
	    void		    setDifficulty(int diff);
	    sf::Vector2f   getBallSpeed();
	    sf::Vector2f   getPaddleSize();
	    sf::Time         getLevelTime();
	    int		    getPointsPerHit();
	    
        private:
	    
	    void		    setLevelTime();
	    void		    setBallSpeed();
	    void		    setPaddleSize();
	    void		    setPointsPerHit();
	    
        private:
	    
	    int			    difficulty;
	    sf::Vector2f	    ballSpeed;
	    sf::Vector2f	    paddleSize;
	    sf::Time		    levelTime;
	    int			    pointsPerHit;
	    
};

#endif // LEVEL_HPP
