//-----------------------------------------------------------------------------
/** @file libboardgame_util/Timer.cpp */
//-----------------------------------------------------------------------------

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Timer.h"

namespace libboardgame_util {

//-----------------------------------------------------------------------------

Timer::Timer()
    : m_time_source(0)
{
}

Timer::Timer(TimeSource& time_source)
    : m_start(time_source()),
      m_time_source(&time_source)
{
}

void Timer::reset()
{
    m_start = (*m_time_source)();
}

void Timer::reset(TimeSource& time_source)
{
    m_time_source = &time_source;
    reset();
}

//----------------------------------------------------------------------------

} // namespace libboardgame_util
