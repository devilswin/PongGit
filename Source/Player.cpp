#include <include/Book/Player.hpp>
#include <include/Book/CommandQueue.hpp>
#include "Paddle.hpp"
#include <include/Book/Foreach.hpp>

#include <map>
#include <string>
#include <algorithm>
#include <iostream>

struct PaddleMover
{
	    PaddleMover(float vx, float vy)
	            : velocity(vx, vy)
	    {
	    }
	    
	    void operator() (Paddle& paddle, sf::Time) const
	    {
		paddle.accelerate(velocity/2.f);
		
	    }
	    
	    sf::Vector2f velocity;
};
struct PaddleStop
{
	    PaddleStop()
	    {
	    }
	    
	    void operator() (Paddle& paddle, sf::Time) const
	    {
		paddle.setPosition(paddle.getPosition());
		paddle.setVelocity(0.f,0.f);
	    }
	
};


Player::Player()
{
        // Set initial key bindings
        //mKeyBinding[sf::Keyboard::Left] = MoveLeft;
        //mKeyBinding[sf::Keyboard::Right] = MoveRight;
        mKeyBinding[sf::Keyboard::Left] = MoveUp;
        mKeyBinding[sf::Keyboard::Right] = MoveDown;
        mKeyBinding[sf::Keyboard::Space] = MoveNone;
        
        // Set initial action bindings
        initializeActions();	
        
        // Assign all categories to player's Paddle
        FOREACH(auto& pair, mActionBinding)
                        pair.second.category = Category::Plyr;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
        if (event.type == sf::Event::KeyPressed)
        {
	    // Check if pressed key appears in key binding, trigger command if so
	    auto found = mKeyBinding.find(event.key.code);
	    if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
		commands.push(mActionBinding[found->second]);
        }
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
        // Traverse all assigned keys and check if they are pressed
        FOREACH(auto pair, mKeyBinding)
        {
	    // If key is pressed, lookup action and trigger corresponding command
	    if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
		commands.push(mActionBinding[pair.second]);
        }
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
        // Remove all keys that already map to action
        for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
        {
	    if (itr->second == action)
		mKeyBinding.erase(itr++);
	    else
		++itr;
        }
        
        // Insert new binding
        mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
        FOREACH(auto pair, mKeyBinding)
        {
	    if (pair.second == action)
		return pair.first;
        }
        
        return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
        const float playerSpeed = 100;
        
        //mActionBinding[MoveLeft].action	 = derivedAction<Ball>(BallMover(-playerSpeed, 0.f));
        //mActionBinding[MoveRight].action = derivedAction<Ball>(BallMover(+playerSpeed, 0.f));
        mActionBinding[MoveNone].action  = derivedAction<Paddle>(PaddleStop());
        mActionBinding[MoveUp].action    = derivedAction<Paddle>(PaddleMover(0.f, -playerSpeed));
        mActionBinding[MoveDown].action  = derivedAction<Paddle>(PaddleMover(0.f, +playerSpeed));
     
        
}

bool Player::isRealtimeAction(Action action)
{
        switch (action)
        {
	    //case MoveLeft:
	    //case MoveRight:
	    case MoveDown:
	    case MoveUp:
	    case MoveNone:  
		return true;
		
	    default:
		return false;
        }
}
