#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <include/Book/State.hpp>
#include <include/Book/World.hpp>
#include <include/Book/Player.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window.hpp>
#include <include/Book/Utility.hpp>
class GameState : public State
{
        public:
	    GameState(StateStack& stack, Context context);
	    
	    virtual void		draw();
	    virtual bool		update(sf::Time dt);
	    virtual bool		handleEvent(const sf::Event& event);
	    
	    
        private:
	    
	     sf::Text			pScore, cScore;
	    World				mWorld;
	    Player&			mPlayer;
	    int				mLevel;
};
#endif // GAMESTATE_HPP
