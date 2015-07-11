#include <include/Book/Application.hpp>
#include <include/Book/Utility.hpp>
#include <include/Book/State.hpp>
#include <include/Book/StateIdentifiers.hpp>
#include <States/Include/GameState.hpp>
#include <States/Include/MenuState.hpp>
#include <States/Include/PauseState.hpp>
#include "CustomClock.hpp"
const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
        : mWindow(sf::VideoMode(1280, 720), "Pong", sf::Style::Close)
        , mTextures()
        , mFonts()
        , mPlayer()
        , mClock()
        , mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mClock))
        , mStatisticsText()
        , mStatisticsUpdateTime()
        , mStatisticsNumFrames(0)
{
        mWindow.setKeyRepeatEnabled(false);
        
        mFonts.load(Fonts::Main, "/Users/gabeorlanski/Desktop/Plse save battery/QT project/Pong/Media/Sansation.ttf");
        mTextures.load(Textures::TitleScreen, "/Users/gabeorlanski/Desktop/Plse save battery/QT project/Pong/Media/Textures/TitleScreen.png");
        
        mStatisticsText.setFont(mFonts.get(Fonts::Main));
        mStatisticsText.setPosition(5.f, 5.f);
        mStatisticsText.setCharacterSize(10u);
        
        registerStates();
        mStateStack.pushState(States::Menu);
}

void Application::run()
{
        sf::Clock clock;
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        
        while (mWindow.isOpen())
        {
	    sf::Time dt = clock.restart();
	    timeSinceLastUpdate += dt;
	    while (timeSinceLastUpdate > TimePerFrame)
	    {
		timeSinceLastUpdate -= TimePerFrame;
		
		processInput();
		update(TimePerFrame);
		
		// Check inside this loop, because stack might be empty before update() call
		if (mStateStack.isEmpty())
		        mWindow.close();
	    }
	    
	    updateStatistics(dt);
	    render();
        }
}

void Application::processInput()
{
        sf::Event event;
        while (mWindow.pollEvent(event))
        {
	    mStateStack.handleEvent(event);
	    
	    if (event.type == sf::Event::Closed)
		mWindow.close();
        }
}

void Application::update(sf::Time dt)
{
        mStateStack.update(dt);
}

void Application::render()
{
        mWindow.clear();
        
        mStateStack.draw();
        
        mWindow.setView(mWindow.getDefaultView());
        mWindow.draw(mStatisticsText);
        
        mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
        mStatisticsUpdateTime += dt;
        mStatisticsNumFrames += 1;
        if (mStatisticsUpdateTime >= sf::seconds(1.0f))
        {
	    mStatisticsText.setString("FPS: " + toString(mStatisticsNumFrames));
	    
	    mStatisticsUpdateTime -= sf::seconds(1.0f);
	    mStatisticsNumFrames = 0;
        }
}

void Application::registerStates()
{
        
        mStateStack.registerState<MenuState>(States::Menu);
        mStateStack.registerState<GameState>(States::Game);
        mStateStack.registerState<PauseState>(States::Pause);
        
}
