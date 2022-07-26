#pragma once

struct IEngineServer_t
{
    auto GetPlayerUserID( void* edict )
    {
        return Hikari::Memory->VirtualCall<int, 15>( this, edict );
    }

    auto GetEntityCount()
    {
        return Hikari::Memory->VirtualCall<int, 17>( this );
    }

    auto EntityOfEntIndex( int index )
    {
        return Hikari::Memory->VirtualCall<void*, 19>( this, index );
    }

    auto ServerCommand( const char* cmd )
    {
        return Hikari::Memory->VirtualCall<void, 36>( this, cmd );
    }

    auto CreateFakeClient( const char* name )
    {
        return Hikari::Memory->VirtualCall<void*, 54>( this, name );
    }
};
