#include "../framework.h"
#include "modules.h"

namespace Game
{
    Modules_t::Modules_t( HMODULE handle )
    {
        this->_info = Hikari::ModuleInfo_t( handle );
    }

    Modules_t::Modules_t( const std::string& name )
    {
        this->_info = Hikari::ModuleInfo_t( name );

        // Change 0x4 accordingly
        if ( auto relative_address = Hikari::Address_t( reinterpret_cast<uintptr_t>(_info.GetProc( "CreateInterface" )) ).SelfOffset( 0x4 ); relative_address.IsValid() )
        {
            auto interface_fn = relative_address.Relative();
            // Change 0x6 accordingly
            this->_interface_list = interface_fn.Offset( 0x6 ).Dereference( 2 ).Cast<void*>();
        }
    }

    Hikari::Address_t Modules_t::FindPattern( const char* pattern, bool relative ) const
    {
        return Hikari::Memory->FindPattern( this->_info, pattern, relative );
    }

    Hikari::Address_t Modules_t::GetVTablePointer( const std::string& vtable ) const
    {
        return Hikari::Memory->GetVTablePointer( this->_info, vtable );
    }
}
