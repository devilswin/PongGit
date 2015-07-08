#ifndef BALL_HPP
#define BALL_HPP
#include <include/Book/Entity.hpp>
#include <include/Book/ResourceIdentifiers.hpp>


#include <SFML/Graphics.hpp>


class Ball : public Entity
{
        public:
	    Ball(const TextureHolder &textures);
	    virtual unsigned int getCategory() const;
	    virtual sf::FloatRect getBoundingRect() const;
        private:
	    
	    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	    
        private:
	    
	    sf::Sprite mSprite;
	    
	    
};

#endif // BALL_HPP
