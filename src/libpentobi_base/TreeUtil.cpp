//-----------------------------------------------------------------------------
/** @file libpentobi_base/TreeUtil.cpp */
//-----------------------------------------------------------------------------

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "TreeUtil.h"

namespace libpentobi_base {
namespace tree_util {

//-----------------------------------------------------------------------------

unsigned int get_move_number(const Tree& tree, const Node& node)
{
    unsigned int move_number = 0;
    const Node* current = &node;
    while (current != 0)
    {
        if (tree.get_move_ignore_invalid(*current).is_regular())
            ++move_number;
        if (tree.has_setup(*current))
            break;
        current = current->get_parent_or_null();
    }
    return move_number;
}

unsigned int get_moves_left(const Tree& tree, const Node& node)
{
    unsigned int moves_left = 0;
    const Node* current = node.get_first_child_or_null();
    while (current != 0)
    {
        if (tree.has_setup(*current))
            break;
        if (tree.get_move_ignore_invalid(*current).is_regular())
            ++moves_left;
        current = current->get_first_child_or_null();
    }
    return moves_left;
}

//-----------------------------------------------------------------------------

} // namespace tree_util
} // namespace libpentobi_base
