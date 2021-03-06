//-----------------------------------------------------------------------------
/** @file libpentobi_base/CallistoGeometry.cpp
    @author Markus Enzenberger
    @copyright GNU General Public License version 3 or later */
//-----------------------------------------------------------------------------

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "CallistoGeometry.h"

#include "libboardgame_util/Unused.h"

namespace libpentobi_base {

using libboardgame_base::CoordPoint;

//-----------------------------------------------------------------------------

namespace {

unsigned get_size_callisto(unsigned nu_players)
{
    if (nu_players == 2)
        return 16;
    LIBBOARDGAME_ASSERT(nu_players == 3 || nu_players == 4);
    return 20;
}

unsigned get_edge_callisto(unsigned nu_players)
{
    if (nu_players == 4)
        return 6;
    LIBBOARDGAME_ASSERT(nu_players == 2 || nu_players == 3);
    return 2;
}

bool is_onboard_callisto(unsigned x, unsigned y, unsigned width,
                         unsigned height, unsigned edge)
{
    unsigned dy = min(y, height - y - 1);
    unsigned min_x = (width - edge) / 2 > dy ? (width - edge) / 2 - dy : 0;
    unsigned max_x = width - min_x - 1;
    return x >= min_x && x <= max_x;
}

} // namespace

//-----------------------------------------------------------------------------

map<unsigned, shared_ptr<CallistoGeometry>> CallistoGeometry::s_geometry;

CallistoGeometry::CallistoGeometry(unsigned nu_colors)
{
    unsigned sz = get_size_callisto(nu_colors);
    m_edge = get_edge_callisto(nu_colors);
    Geometry::init(sz, sz);
}

const CallistoGeometry& CallistoGeometry::get(unsigned nu_colors)
{
    auto pos = s_geometry.find(nu_colors);
    if (pos != s_geometry.end())
        return *pos->second;
    shared_ptr<CallistoGeometry> geometry(new CallistoGeometry(nu_colors));
    return *s_geometry.insert(make_pair(nu_colors, geometry)).first->second;
}

auto CallistoGeometry::get_adj_coord(int x, int y) const -> AdjCoordList
{
    LIBBOARDGAME_UNUSED(x);
    LIBBOARDGAME_UNUSED(y);
    return AdjCoordList();
}

auto CallistoGeometry::get_diag_coord(int x, int y) const -> DiagCoordList
{
    DiagCoordList l;
    l.push_back(CoordPoint(x, y - 1));
    l.push_back(CoordPoint(x - 1, y));
    l.push_back(CoordPoint(x + 1, y));
    l.push_back(CoordPoint(x, y + 1));
    return l;
}

unsigned CallistoGeometry::get_period_x() const
{
    return 1;
}

unsigned CallistoGeometry::get_period_y() const
{
    return 1;
}

unsigned CallistoGeometry::get_point_type(int x, int y) const
{
    LIBBOARDGAME_UNUSED(x);
    LIBBOARDGAME_UNUSED(y);
    return 0;
}

bool CallistoGeometry::init_is_onboard(unsigned x, unsigned y) const
{
    return is_onboard_callisto(x, y, get_width(), get_height(), m_edge);
}

bool CallistoGeometry::is_center_section(unsigned x, unsigned y,
                                         unsigned nu_colors)
{
    auto size = get_size_callisto(nu_colors);
    if (x < size / 2 - 3 || y < size / 2 - 3)
        return false;
    x -= size / 2 - 3;
    y -= size / 2 - 3;
    if (x > 5 || y > 5)
        return false;
    return is_onboard_callisto(x, y, 6, 6, 2);
}

//-----------------------------------------------------------------------------

} // namespace libpentobi_base

