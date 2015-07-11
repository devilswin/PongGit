#include <include/Book/World.hpp>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>

#include <algorithm>
#include <cmath>

#include <cmath>
#include <cstdio>
#include <ctime>

World::World(sf::RenderWindow& window, CustomClock clock)
        : mWindow(window)
        , CAN_HIT(true)
        , mWorldView(window.getDefaultView())
        , mTextures() 
        , levelClock(clock)
        , levelTime(sf::seconds(5))
        , mSceneGraph()
        , mSceneLayers()
        , mPlayerScore(0)
        , mWorldBounds(0.f, 0.f, mWorldView.getSize().x, mWorldView.getSize().y)
        , mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
        , mLevelNumber(0)
        
{
        
        loadTextures();
        buildScene();
        
        // Prepare the view
        mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
    
        
        
        
        if(mBall->getPosition().x +25>= mWorldBounds.width)
	    mBall->setVelocity(-1.f*mBall->getVelocity().x, mBall->getVelocity().y);
        
        else if(mBall->getPosition().x <= 25.f)
	    mBall->setVelocity(-1.f*mBall->getVelocity().x, mBall->getVelocity().y);
        
        if(mBall->getPosition().y +25>= mWorldBounds.height)
	    mBall->setVelocity(mBall->getVelocity().x,-1.f *mBall->getVelocity().y);
        
        else if(mBall->getPosition().y <= 25.f)
	    mBall->setVelocity(mBall->getVelocity().x,-1.f *mBall->getVelocity().y);
        
        
        if(mCPUPaddle->getPosition().y > mWorldBounds.height-50.f)
        {
	    mCPUPaddle->setPosition(mCPUPaddle->getPosition().x, mWorldBounds.height-50.f);
	    
        }
        if(mCPUPaddle->getPosition().y <50.f)
        {
	    mCPUPaddle->setPosition(mCPUPaddle->getPosition().x, 50.f);
	    
        }
        
        checkCollision(mBall,mPaddle,CAN_HIT);
        checkCollision(mBall, mCPUPaddle, CAN_HIT);
        if(mBall->getPosition().x >= 200 && mBall->getPosition().x <= mWorldBounds.width - 200)
        {
	    CAN_HIT = true;
        }
        
        
        
        
        
        
        mCPUPaddle->setPosition(mCPUPaddle->getPosition().x, mBall->getPosition().y);
        
        

        
        
        while (!mCommandQueue.isEmpty())
	    mSceneGraph.onCommand(mCommandQueue.pop(), dt);
        adaptPlayerVelocity();
        
        // Regular update step, adapt position (correct if outside view)
        mSceneGraph.update(dt);
        adaptPlayerPosition();
        if(mBall->getPosition().x < mPaddle->getPosition().x-50)
        {
	    mCPUScore += 1;
	    mBall->setPosition(mSpawnPosition);
	    mBall->setVelocity(400, 50);
        }
       
}

void World::draw()
{
        mWindow.setView(mWorldView);
        
        //Draws all of the parts necesary, each of the states and
        mWindow.draw(mSceneGraph);
        
}

CommandQueue& World::getCommandQueue()
{
        return mCommandQueue;
}

void World::loadTextures()
{
        
        mTextures.load(Textures::Paddle, "/Users/gabeorlanski/Desktop/Plse save battery/QT project/Pong/Media/Textures/paddle.png");
        mTextures.load(Textures::Ball, "/Users/gabeorlanski/Desktop/Plse save battery/QT project/Pong/Media/Textures/ball.png");
        mTextures.load(Textures::Desert, "/Users/gabeorlanski/Desktop/Plse save battery/QT project/Pong/Media/Textures/Desert.png");	
}

void World::buildScene()
{
        hitPlayer = false;
        hitCPU = false;
        // Initialize the different layers
        for (std::size_t i = 0; i < LayerCount; ++i)
        {
	    SceneNode::Ptr layer(new SceneNode());
	    mSceneLayers[i] = layer.get();
	    
	    mSceneGraph.attachChild(std::move(layer));
        }
        
        // Prepare the tiled background
        sf::Texture& texture = mTextures.get(Textures::Desert);
        sf::IntRect textureRect(mWorldBounds);
        texture.setRepeated(true);
        
        
        // Add the background sprite to the scene
        std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
        backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
        mSceneLayers[Background]->attachChild(std::move(backgroundSprite));
        
        
        std::unique_ptr<Paddle> mPlayer(new Paddle(mTextures, true));
        mPaddle = mPlayer.get();
        mPaddle->rotate(90);
        mPaddle->setPosition(100,mWorldBounds.height / 2.f);
        mSceneLayers[paddle]->attachChild(std::move(mPlayer));   
        
        std::unique_ptr<Paddle> mComputer(new Paddle(mTextures, false));
        mCPUPaddle = mComputer.get();
        mCPUPaddle->rotate(270);
        mCPUPaddle->setPosition(mWorldBounds.width-100,mWorldBounds.height / 2.f);    
        mSceneLayers[cPaddle]->attachChild(std::move(mComputer));
        
        
        
        // Add player's Ball
        std::unique_ptr<Ball> pBall(new Ball(mTextures));
        mBall = pBall.get();
        mBall->setPosition(mSpawnPosition);
        //        mBall->setVelocity(-50,45);
        mBall->setVelocity(-400,-400);
        mSceneLayers[ball]->attachChild(std::move(pBall));
        
        
        
        
        
        currentVelocity = 100;
        
        
}

void World::adaptPlayerPosition()
{
        // Keep player's position inside the screen bounds, at least borderDistance units from the border
        sf::FloatRect viewBounds(mWorldView.getCenter() - mWorldView.getSize() / 2.f, mWorldView.getSize());
        float borderDistance = 25.f;
        
        sf::Vector2f position = mBall->getPosition();
        position.x = std::max(position.x, viewBounds.left + borderDistance);
        position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
        position.y = std::max(position.y, viewBounds.top + borderDistance);
        position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
        mBall->setPosition(position);
        borderDistance = 50.f;
        
        position = mPaddle->getPosition();
        position.x = std::max(position.x, viewBounds.left + borderDistance);
        position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
        position.y = std::max(position.y, viewBounds.top + borderDistance);
        position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
        mPaddle->setPosition(position);
        
        position = mCPUPaddle->getPosition();
        position.x = std::max(position.x, viewBounds.left + borderDistance);
        position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
        position.y = std::max(position.y, viewBounds.top + borderDistance);
        position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
        mCPUPaddle->setPosition(position);
}

void World::adaptPlayerVelocity()
{
        sf::Vector2f velocity = mPaddle->getVelocity();
        
        // If moving diagonally, reduce velocity (to have always same velocity)
        if (velocity.x != 0.f && velocity.y != 0.f)
	    mPaddle->setVelocity(velocity / std::sqrt(2.f));
        
}

std::string World::getTimeStr()
{
      
	    return std::to_string(int(std::floor(levelTime.asSeconds()-levelClock.getElapsedTime().asSeconds()))) ;
      
}

int World::getTime()
{
       return int(std::floor(levelTime.asSeconds()-levelClock.getElapsedTime().asSeconds()));
}

void World::checkCollision(Entity *ball,Entity *paddle, bool &hit)
{
        if(ball->getBoundingRect().intersects(paddle->getBoundingRect()) && hit == true)
        {
	    if( ball->getPosition().y - ball->getBoundingRect().height >= paddle->getPosition().y- paddle->getBoundingRect().height && ball->getPosition().y + ball->getBoundingRect().height<=paddle->getPosition().y + paddle->getBoundingRect().height)
		ball->setVelocity(-1.f*ball->getVelocity().x, ball->getVelocity().y);
	    else 
		
		ball->setVelocity(ball->getVelocity().x, -2.f* ball->getVelocity().y);
	    hit = false;
        }
}

void World::setLevelTime(sf::Time Seconds)
{
        levelTime = Seconds;
        
        
}

void World::newLevel(int level)
{
        mPlayerScore = 0;
        mLevel.setDifficulty(level);
        setLevelTime(mLevel.getLevelTime());
        levelClock.restart();
}

