#include <States/Include/GameState.hpp>


#include <iostream>

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, pScore()
, cScore()
, mWorld(*context.window)
, mPlayer(*context.player)


{
       
       
        
        sf::Font& font = context.fonts->get(Fonts::Main);
       
        
        pScore.setFont(font);
        pScore.setString(mWorld.getTimeStr());	
        pScore.setCharacterSize(70);
        centerOrigin(pScore);
        pScore.setPosition(context.window->getDefaultView().getSize().x/2.f, 100);
        
       
     
       
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
	pScore.setString(mWorld.getTimeStr());
	if(mWorld.getTime() == 0)
	{
	        mLevel += 1;
	        mWorld.newLevel(mLevel);
	        requestStackPush(States::Pause);
	        
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

