#pragma once

namespace Game::Util
{
    // bool CCSBotManager::BotAddCommand(int team, bool isFromConsole, const char* profileName, CSWeaponType weaponType, BotDifficultyType difficulty)
    Server::CCSPlayer_t* CreateBot(int team);
    void KickBot(Server::CCSPlayer_t* bot);
    Server::CCSPlayer_t* GetEntityByIndex(int index);
}