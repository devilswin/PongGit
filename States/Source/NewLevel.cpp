#include <States/Include/NewLevel.hpp>
#include <include/Book/Utility.hpp>
#include <include/Book/ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


NewLevel::NewLevel(StateStack& stack, Context context)
        : State(stack, context)
        , mBackgroundSprite()
        , mPausedText()
        , mCountText()
{
        sf::Font& font = context.fonts->get(Fonts::Main);
        sf::Vector2f viewSize = context.window->getView().getSize();
        
        mPausedText.setFont(font);
        mPausedText.setString("New Level");	
        mPausedText.setCharacterSize(70);
        centerOrigin(mPausedText);
        mPausedText.setPosition(0.5f * viewSize.x, 0.2f * viewSize.y);
        
        mCountText.setFont(font);
        mCountText.setCharacterSize(70);
        mCountText.setString(std::to_string(int(3)));	
        centerOrigin(mCountText);
        mCountText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void NewLevel::draw()
{
        sf::RenderWindow& window = *getContext().window;
        window.setView(window.getDefaultView());
        
        sf::RectangleShape backgroundShape;
        backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
        backgroundShape.setSize(window.getView().getSize());
        
        window.draw(backgroundShape);
        window.draw(mPausedText);
        window.draw(mCountText);
}

bool NewLevel::update(sf::Time dt)
{
        mCountDown += dt;
        if(!(mCountDown.asSeconds() < 4))
        {
	    requestStackPop();
        }
        
        mCountText.setString(std::to_string(int(std::floor(3 - mCountDown.asSeconds() + 1))));
        return false;
}

bool NewLevel::handleEvent(const sf::Event& event)
{
  
  
        return false;
        
        
        
     }
