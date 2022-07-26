#pragma once

struct IPanel_t
{
    const char* GetName( uint32_t id )
    {
        return Hikari::Memory->VirtualCall<const char*, 36>( this, id );
    }
};
