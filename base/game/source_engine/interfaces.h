#pragma once

#include "classes/bitflags.h"
#include "classes/color.h"
#include "classes/keyvalues.h"
#include "classes/bit_buff.h"
#include "classes/utls.h"
#include "datatypes/checksum_crc.h"
#include "datatypes/checksum_md5.h"
#include "datatypes/angle.h"
#include "datatypes/vectors.h"
#include "datatypes/matrix.h"
#include "datatypes/usercmd.h"
#include "datatypes/datamap.h"
#include "datatypes/definitions.h"
#include "datatypes/move_data.h"

#include "classes/models.h"
#include "classes/material.h"
#include "classes/material_render_context.h"
#include "classes/texture.h"
#include "classes/netchannel.h"

#include "interfaces/engine_client.h"
#include "interfaces/base_client.h"
#include "interfaces/cvar.h"
#include "interfaces/client_entity_list.h"
#include "interfaces/panel.h"
#include "interfaces/surface.h"
#include "interfaces/globalvars.h"
#include "interfaces/model_info.h"
#include "interfaces/engine_trace.h"
#include "interfaces/input.h"
#include "interfaces/material_system.h"
#include "interfaces/model_render.h"
#include "interfaces/render_view.h"
#include "interfaces/studio_render.h"
#include "interfaces/server_client.h"
#include "interfaces/game_movement.h"
#include "interfaces/engine_server.h"

namespace Game
{
    struct Interfaces_t
    {
        Interfaces_t();

        // engine.dll
        IEngineClient_t* EngineClient;
        IEngineServer_t* EngineServer;
        IRenderView_t* RenderView;
        IModelRender_t* ModelRender;
        INetChannel_t* NetChannel{};
        IEngineTrace_t* TraceClient;
        CGlobalVars_t* GlobalVars;
        IModelInfo_t* ModelInfo;

        // client.dll
        IBaseClientDll_t* Client;
        IClientEntityList_t* EntityList;
        void* ClientMode;
        IInput_t* Input;
        IGameMovement_t* ClientGameMovement;

        // server.dll
        IServerGameDLL_t* ServerDLL;
        IGameMovement_t* ServerGameMovement;
        CPlayerMove_t* PlayerMove;

        // from other dlls
        IPanel_t* Panel;
        ISurface_t* Surface;
        ICvar_t* Cvar;
        IStudioRender_t* StudioRender;
        IMaterialSystem_t* MaterialSystem;

        IDirect3DDevice9* D3D;


    private:
        class CInterfaceRegister
        {
            using InstantiateInterfaceFn = void* (__cdecl*)();
        public:
            InstantiateInterfaceFn pCreateFn;
            const char* szName;
            CInterfaceRegister* pNext;
        };

        template <typename T>
        T* GetInterface( void* interface_list, std::string_view interface_name );

        void DumpInterfaces( const std::string& mod, void* interface_list ) const;
    };

    template <typename T>
    T* Interfaces_t::GetInterface( void* interface_list, std::string_view interface_name )
    {
        if ( !interface_list )
            throw std::runtime_error( "Invalid interface list" );

        if ( interface_name.empty() )
            throw std::runtime_error( "Empty interface name" );

        for ( auto i = static_cast<CInterfaceRegister*>(interface_list); i != nullptr; i = i->pNext )
        {
            if ( std::string_view( i->szName ).compare( 0U, interface_name.length(), interface_name ) == 0
                && std::atoi( i->szName + interface_name.length() ) > 0 ||
                interface_name.compare( i->szName ) == 0 )
            {
                auto address = i->pCreateFn();
                Hikari::Logger->Success( std::format( "Found interface {} ==> {:#09X}", i->szName, reinterpret_cast<std::uintptr_t>(address) ) );
                return static_cast<T*>(address);
            }
        }

        throw std::runtime_error( std::format( "Failed to get interface {}", interface_name ) );
    }

    inline void Interfaces_t::DumpInterfaces( const std::string& mod, void* interface_list ) const
    {
        if ( !interface_list )
            throw std::runtime_error( "Invalid interface list" );

        std::vector<const char*> list;

        for ( auto i = static_cast<CInterfaceRegister*>(interface_list); i != nullptr; i = i->pNext )
        {
            if ( std::ranges::find( list, i->szName ) != list.end() )
                continue;

            // Hikari::Logger->Success( std::format( "{} ==> {} ", mod, i->szName ) );
            list.push_back( i->szName );
        }

        for ( const auto& l : list )
        {
            Hikari::Logger->Success( std::format( "{} ==> {}", mod, l ) );
        }
    }

    inline std::unique_ptr<Interfaces_t> Interfaces;
}
