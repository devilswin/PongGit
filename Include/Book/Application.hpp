#ifndef BOOK_APPLICATION_HPP
#define BOOK_APPLICATION_HPP

#include <include/Book/ResourceHolder.hpp>
#include <include/Book/ResourceIdentifiers.hpp>
#include <include/Book/Player.hpp>
#include <include/Book/StateStack.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>


class Application
{
	public:
							Application();
		void					run();
		

	private:
		void					processInput();
		void					update(sf::Time dt);
		void					render();

		void					updateStatistics(sf::Time dt);
		void					registerStates();


	private:
		static const sf::Time			TimePerFrame;

		sf::RenderWindow			mWindow;
		TextureHolder			            mTextures;
	  	FontHolder				mFonts;
		Player					mPlayer;
		CustomClock				mClock;
		StateStack				mStateStack;

		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;
};

#endif // BOOK_APPLICATION_HPP
