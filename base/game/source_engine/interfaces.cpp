#include "../../framework.h"
#include "interfaces.h"
#include "../modules.h"

namespace Game
{
    Interfaces_t::Interfaces_t()
    {
        const auto server = Modules::Server->GetInterfaceList();
        const auto engine = Modules::Engine->GetInterfaceList();
        const auto client = Modules::Client->GetInterfaceList();

        #if 0
        // DumpInterfaces( "server.dll", server );
        DumpInterfaces( "engine.dll", engine );
        // DumpInterfaces( "client.dll", client );
        #endif

        {
            EngineClient = GetInterface<IEngineClient_t>( engine, "VEngineClient014" );
            EngineServer = GetInterface<void>( engine, "VEngineServer023" );
            ModelInfo = GetInterface<IModelInfo_t>( engine, "VModelInfoClient006" );
            TraceClient = GetInterface<IEngineTrace_t>( engine, "EngineTraceClient003" );
            RenderView = GetInterface<IRenderView_t>( engine, "VEngineRenderView" );
            ModelRender = GetInterface<IModelRender_t>( engine, "VEngineModel" );
            GlobalVars = Modules::Engine->FindPattern( "A1 ? ? ? ? 8B 11 68" ).Offset( 8 ).Dereference().Cast<CGlobalVars_t*>();
        }

        {
            Client = GetInterface<IBaseClientDll_t>( client, "VClient017" );
            EntityList = GetInterface<IClientEntityList_t>( client, "VClientEntityList" );
            ClientGameMovement = GetInterface<IGameMovement_t>( client, "GameMovement" );
            Input = Modules::Client->FindPattern( "8B 0D ? ? ? ? 8B 01 FF 60 44" ).Offset( 2 ).Dereference( 2 ).Cast<IInput_t*>();
            ClientMode = Modules::Client->FindPattern( "B9 ? ? ? ? A1 ? ? ? ? 8B 80" ).Offset( 1 ).Dereference().Cast<void*>();
        }

        {
            ServerDLL = GetInterface<IServerGameDLL_t>( server, "ServerGameDLL010" );
            ServerGameMovement = GetInterface<IGameMovement_t>( server, "GameMovement" );
            PlayerMove = Modules::Server->FindPattern( "E8 ? ? ? ? 8B C8 E8 ? ? ? ? 5F 5E 5D C2 08 00", true ).Cast<CPlayerMove_t*(*)()>()();
        }

        Cvar = GetInterface<ICvar_t>( Modules::VStdLib->GetInterfaceList(), "VEngineCvar" );
        MaterialSystem = GetInterface<IMaterialSystem_t>( Modules::MaterialSystem->GetInterfaceList(), "VMaterialSystem" );
        StudioRender = GetInterface<IStudioRender_t>( Modules::StudioRender->GetInterfaceList(), "VStudioRender" );
        Panel = GetInterface<IPanel_t>( Modules::VGui->GetInterfaceList(), "VGUI_Panel009" );
        Surface = GetInterface<ISurface_t>( Modules::MatSurface->GetInterfaceList(), "VGUI_Surface030" );

        D3D = Modules::Shaderapidx9->FindPattern( "A1 ? ? ? ? 8D 53 08" ).Offset( 1 ).Dereference( 2 ).Cast<IDirect3DDevice9*>();
    }
}
