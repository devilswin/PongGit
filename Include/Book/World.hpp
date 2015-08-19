#ifndef BOOK_WORLD_HPP
#define BOOK_WORLD_HPP

#include <include/Book/ResourceHolder.hpp>
#include <include/Book/ResourceIdentifiers.hpp>
#include <include/Book/SceneNode.hpp>
#include <include/Book/SpriteNode.hpp>
#include <include/Book/CommandQueue.hpp>
#include <include/Book/Command.hpp>
#include <include/Book/Utility.hpp>
#include "Ball.hpp"
#include "Paddle.hpp"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include "Level.hpp"
#include <string>
#include <array>
#include <queue>


// Forward declaration
namespace sf
{
        class RenderWindow;
}

class World : private sf::NonCopyable
{
        public:
	    explicit							World(sf::RenderWindow& window);
	    void								update(sf::Time dt);
	    void								draw();
	    
	    CommandQueue&					getCommandQueue();
	    
	    
	    void								newLevel(Level &level); 
	    
	    
	    
        private:
	    void								setLevelTime(sf::Time Seconds);
	    void								loadTextures();
	    void								buildScene();
	    void								adaptPlayerPosition();
	    void								adaptPlayerVelocity();
	    void								checkCollision(Entity* ball, Entity* paddle,bool &hit);
	    
        private:
	    enum Layer
	    {
		Background,
		ball,
		paddle,
		cPaddle, 
		LayerCount
	    };
	    
	    
        private:
	    
	    
	    sf::RenderWindow&										mWindow;
	    bool													CAN_HIT;
	    sf::View												mWorldView;
	    TextureHolder											mTextures;
	    sf::Time												levelTime;
	    SceneNode												mSceneGraph;
	    std::array<SceneNode*, LayerCount>								mSceneLayers;
	    CommandQueue											mCommandQueue;
	    Ball*												mBall;
	    int													mPlayerScore,mCPUScore;
	    sf::FloatRect											mWorldBounds;
	    sf::Vector2f											mSpawnPosition;
	    Paddle*												mPaddle;
	    Paddle*												mCPUPaddle;
	    float												currentVelocity;
	    bool													hitCPU, hitPlayer;
	    sf::Vector2f											mBallSpeed;
	    
};

#endif // BOOK_WORLD_HPP
