#pragma once

struct IGameMovement_t
{
    auto ProcessMovement( void* player, CMoveData* moveData )
    {
        return Hikari::Memory->VirtualCall<void, 1>( this, player, moveData );
    }
};

struct CPlayerMove_t
{
    auto SetupMove(void* player, CUserCmd* cmd, void* moveHelper, CMoveData* moveData)
    {
        return Hikari::Memory->VirtualCall<void, 1>(this, player, cmd, moveHelper, moveData);
    }
};