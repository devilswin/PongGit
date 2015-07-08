#include "Paddle.hpp"

#include <include/Book/ResourceHolder.hpp>
#include <include/Book/Utility.hpp>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>


Paddle::Paddle(const TextureHolder& textures, const bool isPlayer) 
        :   mPlayer(isPlayer)
         , mSprite(textures.get(Textures::Paddle))
      
        
{
        centerOrigin(mSprite);
        
}

void Paddle::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
        target.draw(mSprite,states);
        
        
}
unsigned int Paddle::getCategory() const
{
        if(mPlayer == true)
	    return Category::Plyr;
        else
	    return Category::Comp;
}

sf::FloatRect Paddle::getBoundingRect() const 
{
        return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}




