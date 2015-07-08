#ifndef PADDLE_HPP
#define PADDLE_HPP


#include <include/Book/Entity.hpp>
#include <include/Book/ResourceIdentifiers.hpp>


#include <SFML/Graphics.hpp>


class Paddle : public Entity
{
        public:
	    Paddle(const TextureHolder &textures, const bool isPlayer);
	    virtual unsigned int getCategory() const;
	    virtual sf::FloatRect getBoundingRect() const;
	   
        private:
	    
	    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	    
        private:
	    bool	        mPlayer;
	    sf::Sprite mSprite;
	    
	    
};

#endif // PADDLE_HPP
