#pragma once

struct IEngineServer_t
{
    auto GetEntityCount()
    {
        return Hikari::Memory->VirtualCall<int, 17>( this );
    }

    auto EntityOfEntIndex( int index )
    {
        return Hikari::Memory->VirtualCall<void*, 19>( this, index );
    }
};
