#include "../../framework.h"
#include "../game.h"
#include "hooks.h"
#include <intrin.h>
#include <mutex>

#include "../../thirdparty/minhook/MinHook.h"

#include "../../thirdparty/imgui/imgui.h"
#include "../../thirdparty/imgui/imgui_impl_dx9.h"
#include "../../thirdparty/imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

namespace Game
{
    Hook_t::Detour_t::Detour_t() : _source( nullptr ), _target( nullptr ), _hooked( false )
    {
    }

    Hook_t::Detour_t::~Detour_t()
    {
        Unhook();
    }

    void Hook_t::Detour_t::Hook( void* source, void* target, void** original, const std::string& name )
    {
        if ( this->_hooked )
            return;

        this->_name = name;
        if ( !source )
            throw std::runtime_error( std::format( "Invalid source function for {}", name ) );

        if ( !target )
            throw std::runtime_error( std::format( "Invalid target function for {}", name ) );

        this->_source = source;
        this->_target = target;

        if ( const auto status = MH_CreateHook( this->_source, this->_target, original ); status != MH_OK )
            throw std::runtime_error( std::format( "Failed to create hook for {}. r:{}", name,
                                                   MH_StatusToString( status ) ) );

        if ( MH_EnableHook( this->_source ) != MH_OK )
            throw std::runtime_error( std::format( "Failed to enable hook for {}", name ) );

        this->_hooked = true;
        Hikari::Logger->Success( std::format( "Hooked {}. {:#09X} --> {:#09X}", name,
                                              reinterpret_cast<std::uintptr_t>(this->_source),
                                              reinterpret_cast<std::uintptr_t>(this->_target) ) );
    }

    WNDPROC _WndProc;

    void Hook_t::Detour_t::Unhook()
    {
        if ( !this->_hooked )
            return;

        if ( MH_RemoveHook( this->_source ) != MH_OK )
            throw std::runtime_error( std::format( "Failed to remove hook for {}", this->_name ) );

        this->_hooked = false;

        /*Hikari::Logger->Success( std::format( "Unhooked {}. {:#09X} --> {:#09X}", this->_name,
                                              reinterpret_cast<std::uintptr_t>(this->_target),
                                              reinterpret_cast<std::uintptr_t>(this->_source) ) );*/
    }

    Hook_t::Hook_t()
    {
        if ( MH_Initialize() != MH_OK )
            throw std::runtime_error( "Failed to initialize hook" );

        Render::Init();

        D3DDEVICE_CREATION_PARAMETERS parameters{};
        Interfaces->D3D->GetCreationParameters( &parameters );
        _WndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr( window = parameters.hFocusWindow, GWL_WNDPROC, reinterpret_cast<LONG>(WndProc) ));

        EndScene.Hook( Hikari::Memory->VirtualFunction<42, void*>( Interfaces->D3D ), &EndScene::Hook, reinterpret_cast<void**>(&EndScene::Original), "IDirect3DDevice9::EndScene" );
        Reset.Hook( Hikari::Memory->VirtualFunction<16, void*>( Interfaces->D3D ), &Reset::Hook, reinterpret_cast<void**>(&Reset::Original), "IDirect3DDevice9::Reset" );

        Paint.Hook( Addresses::Paint.Cast<void*>(), &Paint::Hook, reinterpret_cast<void**>(&Paint::Original),
                    "CEngineVGui::Paint" );

        CHLCreateMove.Hook( Hikari::Memory->VirtualFunction<21, void*>( Interfaces->Client ), &CHLCreateMove::Hook, reinterpret_cast<void**>(&CHLCreateMove::Original),
                            "CHLClient::CreateMove" );

        LevelInitPostEntity.Hook( Hikari::Memory->VirtualFunction<6, void*>( Interfaces->Client ), &LevelInitPostEntity::Hook, reinterpret_cast<void**>(&LevelInitPostEntity::Original),
                                  "CHLClient::LevelInitPostEntity" );

        LevelShutdown.Hook( Hikari::Memory->VirtualFunction<7, void*>( Interfaces->Client ), &LevelShutdown::Hook, reinterpret_cast<void**>(&LevelShutdown::Original),
                            "CHLClient::LevelShutdown" );
    }

    Hook_t::~Hook_t()
    {
        menuOpen = false;

        ImGui_ImplDX9_Shutdown();
        if ( ImGui::GetCurrentContext() )
            ImGui::DestroyContext();

        SetWindowLongPtr( window, GWL_WNDPROC, reinterpret_cast<LONG>(_WndProc) );
    }

    LRESULT __stdcall WndProc( const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
    {
        if ( GetAsyncKeyState( VK_INSERT ) & 1 )
            menuOpen = !menuOpen;

        if ( menuOpen )
        {
            if ( ImGui::GetCurrentContext() )
                ImGui_ImplWin32_WndProcHandler( hWnd, uMsg, wParam, lParam );
            return true;
        }

        return CallWindowProc( _WndProc, hWnd, uMsg, wParam, lParam );
    }
}
