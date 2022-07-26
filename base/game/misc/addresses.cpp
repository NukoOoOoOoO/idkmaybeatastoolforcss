#include "../../framework.h"
#include "../game.h"

void Game::Addresses::Setup()
{
    Paint = Modules::Engine->FindPattern( "55 8B EC 83 EC 2C 53 8B D9 8B 0D ? ? ? ? 56" );
    CalcView = Modules::Client->FindPattern( "E8 ? ? ? ? 8B 45 08 8B 8F", true );

    GetCSWepData = Modules::Client->FindPattern( "0F B7 81 ? ? ? ? 50 E8 ? ? ? ? 83 C4 04 C3" );
    GetActiveWeapon = Modules::Client->FindPattern( "E8 ? ? ? ? 8B C8 85 C9 74 16", true );
    GetDataDescMap = Modules::Client->FindPattern( "B8 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC CC 8D 41 F8" );
    GetPredDataMap = Modules::Client->FindPattern( "B8 ? ? ? ? C3 CC CC CC CC CC CC CC CC CC CC 55 8B EC A1 ? ? ? ? 56 51" );

    StartDrawing = Modules::MatSurface->FindPattern( "55 8B EC 64 A1 00 00 00 00 6A FF 68 ? ? ? ? 50 64 89 25 00 00 00 00 83 EC 14" );
    FinishDrawing = Modules::MatSurface->FindPattern( "55 8B EC 6A FF 68 ? ? ? ? 64 A1 00 00 00 00 50 64 89 25 00 00 00 00 51 56 6A 00" );

    GetEntityByIndex = Modules::Server->FindPattern( "E8 ? ? ? ? 53 8B F0", true );
    CreateBots = Modules::Server->FindPattern( "55 8B EC 83 EC 40 FF 15" );
    SetPlayerName = Modules::Server->FindPattern("E8 ? ? ? ? 8B 46 18 5F", true);
}
