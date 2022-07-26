#include "../../../framework.h"
#include "../../game.h"

KeyValues_t::KeyValues_t( std::string name )
{
    Initialize( name.data() );
}

void KeyValues_t::Initialize( char* name )
{
    static auto func = Game::Modules::Engine->FindPattern( "FF 15 ? ? ? ? 83 C4 08 89 06 8B C6" ).Offset( -0x42 ).Cast<bool(__thiscall*)( void*, char* )>();
    func( this, name );
}

bool KeyValues_t::LoadFromBuffer( const char* resource_name, const char* buffer, void* file_system, const char* path_id )
{
    static auto func = Game::Modules::Engine->FindPattern( "55 8B EC 83 EC 38 53 8B 5D 0C" ).Cast<bool(__thiscall*)( void*, const char*, const char*, void*, const char* )>();
    return func( this, resource_name, buffer, file_system, path_id );
}
