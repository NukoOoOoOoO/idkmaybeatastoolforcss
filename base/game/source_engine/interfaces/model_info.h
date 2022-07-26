#pragma once

struct IModelInfo_t
{
    auto GetIndex( const char* name )
    {
        return Hikari::Memory->VirtualCall<int, 2>( this, name );
    }

    auto GetName( const void* model )
    {
        return Hikari::Memory->VirtualCall<const char*, 3>( this, model );
    }

    auto GetStudioModel( const void* model )
    {
        return Hikari::Memory->VirtualCall<studiohdr_t*, 28>( this, model );
    }
};
