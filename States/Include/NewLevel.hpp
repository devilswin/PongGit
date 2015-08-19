#ifndef NEWLEVEL
#define NEWLEVEL

#include <include/Book/State.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class NewLevel : public State
{
	public:
							NewLevel(StateStack& stack, Context context);

		virtual void		draw();
		virtual bool		update(sf::Time dt);
		virtual bool		handleEvent(const sf::Event& event);


	private:
		sf::Sprite			mBackgroundSprite;
		sf::Text			mPausedText;
		sf::Text			mCountText;
		sf::Time			mCountDown;
		

};

#endif // NEWLEVEL

