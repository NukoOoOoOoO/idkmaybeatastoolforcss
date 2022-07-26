#include "../../../framework.h"
#include "../../game.h"
#include "../hooks.h"

namespace Game
{
    void __fastcall LevelInitPostEntity::Hook( void* ecx, void* edx )
    {
        Original( ecx, edx );

        _serverLocalPlayer = Util::GetEntityByIndex(1);
        
        _serverBot = Util::CreateBot(2);
    }

    void __fastcall LevelShutdown::Hook( void* ecx, void* edx )
    {
        _clientLocalPlayer = nullptr;
        _serverLocalPlayer = nullptr;

        Original( ecx, edx );
    }
}
