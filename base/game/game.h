#pragma once

#include "modules.h"
#include "misc/addresses.h"
#include "source_engine/source_engine.h"
#include "misc/math.h"
#include "misc/render.h"
#include "hooks/hooks.h"

namespace Game
{
    inline Client::CCSPlayer_t* _clientLocalPlayer{};
    inline HWND window = nullptr;
    inline bool menuOpen = false;
    inline bool IsInNasa = false;
}
