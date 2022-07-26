#include "../../framework.h"
#include "../game.h"
#include "addresses.h"
#include "utils.h"

namespace Game::Util
{
    Server::CCSPlayer_t* GetEntityByIndex( int index )
    {
        return Addresses::GetEntityByIndex.Cast<Server::CCSPlayer_t*(*)( int )>()( index );
    }

    Server::CCSPlayer_t* CreateBot(int team)
    {
        auto botEdict = Interfaces->EngineServer->CreateFakeClient("1337");
        if ( const auto botUnk = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(botEdict) + 12))
        {
            const auto player = Hikari::Memory->VirtualCall<Server::CCSPlayer_t*, 5>(botUnk);
            player->ChangeTeam(team);
            player->InitialSpawn();
            player->Spawn();
            return player;
        }

        throw std::runtime_error("Failed to create bot");
    }

    void KickBot(Server::CCSPlayer_t* bot)
    {
        if (!bot)
            return;

        const auto edict = *reinterpret_cast<void**>(reinterpret_cast<uintptr_t>(bot) + 24);
        Interfaces->EngineServer->ServerCommand(std::format("kickid {};", Interfaces->EngineServer->GetPlayerUserID(edict)).data());
    }
}
