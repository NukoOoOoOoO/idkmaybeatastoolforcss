#pragma once

#include "modules.h"
#include "misc/addresses.h"
#include "source_engine/source_engine.h"
#include "misc/math.h"
#include "misc/render.h"
#include "misc/utils.h"
#include "hooks/hooks.h"

namespace Game
{
    inline Client::CCSPlayer_t* _clientLocalPlayer{};
    inline Server::CCSPlayer_t* _serverLocalPlayer{};
    inline Server::CCSPlayer_t* _serverBot{};
    inline HWND window = nullptr;
    inline bool menuOpen = false;
    inline bool IsInNasa = false;
}
