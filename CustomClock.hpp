#ifndef CUSTOMCLOCK_HPP
#define CUSTOMCLOCK_HPP
#include <SFML/System/Clock.hpp>

class CustomClock : public sf::Clock
{
        public:
	    CustomClock();
	    void pause();
	    void pause(int currentTime);
	    int resume();
	    void clockReset();
	    bool isPaused();
        private:
	    bool mPaused;
	    int mCurrentTime;
	    
};

#endif // CUSTOMCLOCK_HPP
