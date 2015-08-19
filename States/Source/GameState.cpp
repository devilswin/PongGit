#include <States/Include/GameState.hpp>
#include <iostream>

#include <iostream>

GameState::GameState(StateStack& stack, Context context)
        : State(stack, context)
        , pScore()
        , cScore()
        , mWorld(*context.window)
        , mPlayer(*context.player)
        , mLvlTime(sf::seconds(0))
        , mIsPaused(false)
        , mDifficulty(0)
        
{
        
        
        mLevel.setDifficulty(mDifficulty);
        sf::Font& font = context.fonts->get(Fonts::Main);
        
        
        pScore.setFont(font);
        pScore.setString(std::to_string(int(std::floor(mLevel.getLevelTime().asSeconds() - mLvlTime.asSeconds()))));	
        pScore.setCharacterSize(70);
        centerOrigin(pScore);
        pScore.setPosition(context.window->getDefaultView().getSize().x/2.f, 100);
        mWorld.newLevel(mLevel);
        
        
        
}

void GameState::draw()
{
        
        mWorld.draw();
        sf::RenderWindow& window = *getContext().window;
        window.setView(window.getDefaultView());
        window.draw(pScore);
        
        
        
}

bool GameState::update(sf::Time dt)
{
        mWorld.update(dt);
        CommandQueue& commands = mWorld.getCommandQueue();
        mPlayer.handleRealtimeInput(commands);
        if(mIsPaused == false)
        {
	    
	    
	    if(mLvlTime.asSeconds() <= mLevel.getLevelTime().asSeconds() )
	    {
		mLvlTime += dt;
		mIsPaused = false;
		pScore.setString(std::to_string(int(std::floor(mLevel.getLevelTime().asSeconds() -mLvlTime.asSeconds() + 1))));
	    }
	    else
	    {
		mIsPaused = true;
		requestStackPush(States::NewLevel);
	    }
        }
        else
        {
	mDifficulty++;
	mIsPaused = false;
	
	mLvlTime = sf::seconds(0);
	mLevel.setDifficulty(mDifficulty);
	
	mWorld.newLevel(mLevel);
        }        
        return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
        // Game input handling
        CommandQueue& commands = mWorld.getCommandQueue();
        mPlayer.handleEvent(event, commands);
        
        // Escape pressed, trigger the pause screen
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	    requestStackPush(States::Pause);
        
        return true;
}

