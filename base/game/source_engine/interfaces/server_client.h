#pragma once

#include "../classes/server_class.h"

struct IServerGameDLL_t
{
    auto GetAllClasses()
    {
        return Hikari::Memory->VirtualCall<ServerClass*, 11>( this );
    }
};
