//-----------------------------------------------------------------------------
/** @file libboardgame_util/StringUtil.h
    @author Markus Enzenberger
    @copyright GNU General Public License version 3 or later */
//-----------------------------------------------------------------------------

#ifndef LIBBOARDGAME_UTIL_STRING_UTIL_H
#define LIBBOARDGAME_UTIL_STRING_UTIL_H

#include <sstream>
#include <string>
#include <vector>

namespace libboardgame_util {

using namespace std;

//-----------------------------------------------------------------------------

template<typename T>
bool from_string(const string& s, T& t)
{
    istringstream in(s);
    in >> t;
    return ! in.fail();
}

template<>
bool from_string(const string& s, string& t);

/** Get a letter representing a coordinate.
    Returns 'a' to 'z' for i between 0 and 25 and continues with 'aa','ab'...
    for coordinates larger than 25. */
string get_letter_coord(unsigned i);

vector<string> split(const string& s, char separator);

string time_to_string(double seconds, bool with_seconds_as_double = false);

template<typename T>
string to_string(const T& t)
{
    ostringstream buffer;
    buffer << t;
    return buffer.str();
}

string to_lower(string s);

string trim(const string& s);

string trim_right(const string& s);

//-----------------------------------------------------------------------------

} // namespace libboardgame_util

#endif // LIBBOARDGAME_UTIL_STRING_UTIL_H
