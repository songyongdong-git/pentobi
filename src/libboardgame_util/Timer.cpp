//-----------------------------------------------------------------------------
/** @file libboardgame_util/Timer.cpp
    @author Markus Enzenberger
    @copyright GNU General Public License version 3 or later */
//-----------------------------------------------------------------------------

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "Timer.h"

#include "Assert.h"

namespace libboardgame_util {

//-----------------------------------------------------------------------------

Timer::Timer(TimeSource& time_source)
    : m_start(time_source()),
      m_time_source(&time_source)
{ }

double Timer::operator()() const
{
    LIBBOARDGAME_ASSERT(m_time_source);
    return (*m_time_source)() - m_start;
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
