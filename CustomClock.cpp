#include "CustomClock.hpp"

CustomClock::CustomClock()
        : mPaused(false)
        , mCurrentTime(0)
{
        
}

void CustomClock::pause()
{
        mPaused = true;
}
void CustomClock::pause(int CurrentTime)
{
        mCurrentTime = CurrentTime;
        mPaused = true;
}
bool CustomClock::isPaused()
{
        return mPaused;
}

void CustomClock::clockReset()
{
        mPaused = false;
        restart();
}

int CustomClock::resume()
{
        mPaused = false;
        restart();
        return mCurrentTime;
}
