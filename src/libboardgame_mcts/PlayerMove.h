//-----------------------------------------------------------------------------
/** @file libboardgame_mcts/PlayerMove.h
    @author Markus Enzenberger
    @copyright GNU General Public License version 3 or later */
//-----------------------------------------------------------------------------

#ifndef LIBBOARDGAME_MCTS_PLAYER_MOVE_H
#define LIBBOARDGAME_MCTS_PLAYER_MOVE_H

#include <cstdint>

namespace libboardgame_mcts {

//-----------------------------------------------------------------------------

typedef uint_fast8_t PlayerInt;

//-----------------------------------------------------------------------------

template<typename MOVE>
struct PlayerMove
{
    PlayerInt player;

    MOVE move;

    PlayerMove() = default;

    PlayerMove(PlayerInt player, MOVE move)
    {
        this->player = player;
        this->move = move;
    }
};

//-----------------------------------------------------------------------------

} // namespace libboardgame_mcts

#endif // LIBBOARDGAME_MCTS_PLAYER_MOVE_H
