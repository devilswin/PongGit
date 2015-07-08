#include "Ball.hpp"
#include <include/Book/ResourceHolder.hpp>
#include <include/Book/Utility.hpp>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Ball::Ball(const TextureHolder& textures) 
        : mSprite(textures.get(Textures::Ball))
     
{
        centerOrigin(mSprite);
}

void Ball::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
        target.draw(mSprite,states);
       
       
}
unsigned int Ball::getCategory() const
{
        return Category::Ball;
}
sf::FloatRect Ball::getBoundingRect() const
{ 
        return getWorldTransform().transformRect( mSprite.getGlobalBounds()); 
}



