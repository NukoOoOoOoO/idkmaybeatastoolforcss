#pragma once
#include "../classes/client_class.h"

struct IBaseClientDll_t
{
    auto GetAllClasses()
    {
        return Hikari::Memory->VirtualCall<ClientClass_t*, 8>( this );
    }
};
