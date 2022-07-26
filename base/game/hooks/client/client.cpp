#include "../../../framework.h"
#include "../../game.h"
#include "../hooks.h"

namespace Game
{
    void __fastcall LevelInitPostEntity::Hook( void* ecx, void* edx )
    {
        Original( ecx, edx );
    }

    void __fastcall LevelShutdown::Hook( void* ecx, void* edx )
    {
        _clientLocalPlayer = nullptr;

        Original( ecx, edx );
    }
}
