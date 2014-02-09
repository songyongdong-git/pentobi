//-----------------------------------------------------------------------------
/** @file libpentobi_base/Variant.h
    @author Markus Enzenberger
    @copyright GNU General Public License version 3 or later */
//-----------------------------------------------------------------------------

#ifndef LIBPENTOBI_BASE_VARIANT_H
#define LIBPENTOBI_BASE_VARIANT_H

#include <string>
#include "Color.h"
#include "Geometry.h"

namespace libpentobi_base {

using namespace std;

//-----------------------------------------------------------------------------

/** Game variant. */
enum class Variant
{
    classic,

    classic_2,

    duo,

    junior,

    trigon,

    trigon_2,

    trigon_3
};

/** Get name of game variant as in the GM property in Blokus SGF files. */
const char* to_string(Variant variant);

/** Get a short lowercase string without spaces that can be used as
    a identifier for a game variant.
    The strings used are "classic", "classic_2", "duo", "trigon", "trigon_2",
    "trigon_3", "junior" */
const char* to_string_id(Variant variant);

/** Parse name of game variant as in the GM property in Blokus SGF files.
    The parsing is case-insensitive, leading and trailing whitespaced are
    ignored.
    @param s
    @param[out] variant
    @result True if the string contained a valid game variant. */
bool parse_variant(const string& s, Variant& variant);

/** Parse short lowercase name of game variant as returned to_string_id().
    @param s
    @param[out] variant
    @result True if the string contained a valid game variant. */
bool parse_variant_id(const string& s, Variant& variant);

Color::IntType get_nu_colors(Variant variant);

Color::IntType get_nu_players(Variant variant);

const Geometry& get_geometry(Variant variant);

//-----------------------------------------------------------------------------

} // namespace libpentobi_base

#endif // LIBPENTOBI_BASE_VARIANT_H
