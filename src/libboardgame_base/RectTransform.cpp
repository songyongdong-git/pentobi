//-----------------------------------------------------------------------------
/** @file libboardgame_base/RectTransform.cpp
    @author Markus Enzenberger
    @copyright GNU General Public License version 3 or later */
//-----------------------------------------------------------------------------

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "RectTransform.h"

namespace libboardgame_base {

//-----------------------------------------------------------------------------

CoordPoint TransfIdentity::get_transformed(CoordPoint p) const
{
    return p;
}

//-----------------------------------------------------------------------------

CoordPoint TransfRectRot90::get_transformed(CoordPoint p) const
{
    return CoordPoint(-p.y, p.x);
}

//-----------------------------------------------------------------------------

CoordPoint TransfRectRot180::get_transformed(CoordPoint p) const
{
    return CoordPoint(-p.x, -p.y);
}

//-----------------------------------------------------------------------------

CoordPoint TransfRectRot270::get_transformed(CoordPoint p) const
{
    return CoordPoint(p.y, -p.x);
}

//-----------------------------------------------------------------------------

CoordPoint TransfRectRefl::get_transformed(CoordPoint p) const
{
    return CoordPoint(-p.x, p.y);
}

//-----------------------------------------------------------------------------

CoordPoint TransfRectRot90Refl::get_transformed(CoordPoint p) const
{
    return CoordPoint(-p.y, -p.x);
}

//-----------------------------------------------------------------------------

CoordPoint TransfRectRot180Refl::get_transformed(CoordPoint p) const
{
    return CoordPoint(p.x, -p.y);
}

//-----------------------------------------------------------------------------

CoordPoint TransfRectRot270Refl::get_transformed(CoordPoint p) const
{
    return CoordPoint(p.y, p.x);
}

//-----------------------------------------------------------------------------

} // namespace libboardgame_base
