#include <intrin.h>
#include <mutex>

#include "../../../framework.h"
#include "../../game.h"
#include "../hooks.h"


#include "../../../thirdparty/imgui/imgui.h"
#include "../../../thirdparty/imgui/imgui_impl_dx9.h"
#include "../../../thirdparty/imgui/imgui_impl_win32.h"
#include "../../menu/menu.h"

namespace Game
{
    HRESULT EndScene::Hook( IDirect3DDevice9* device )
    {
        if ( static auto ret = reinterpret_cast<uintptr_t>(_ReturnAddress()); ret != reinterpret_cast<uintptr_t>(_ReturnAddress()) )
            return Original( device );

        static std::once_flag flag;
        std::call_once( flag, [&]
        {
            ImGui::CreateContext();
            ImGui::GetIO().MouseDrawCursor = true;
            ImGui_ImplDX9_Init( device );
            ImGui_ImplWin32_Init( window );
            ImGui::StyleColorsDark();
        } );


        if ( menuOpen )
        {
            IDirect3DStateBlock9* pixel_state = nullptr;

            D3DVIEWPORT9 d3d_viewport;
            device->GetViewport( &d3d_viewport );

            device->CreateStateBlock( D3DSBT_ALL, &pixel_state );
            pixel_state->Capture();
            //save
            device->SetVertexShader( nullptr );
            device->SetPixelShader( nullptr );
            device->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );

            device->SetRenderState( D3DRS_LIGHTING, FALSE );
            device->SetRenderState( D3DRS_FOGENABLE, FALSE );
            device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
            device->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );

            device->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
            device->SetRenderState( D3DRS_SCISSORTESTENABLE, TRUE );
            device->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
            device->SetRenderState( D3DRS_STENCILENABLE, FALSE );

            device->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE );
            device->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, TRUE );

            device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
            device->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
            device->SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE, TRUE );
            device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
            device->SetRenderState( D3DRS_SRCBLENDALPHA, D3DBLEND_INVDESTALPHA );
            device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
            device->SetRenderState( D3DRS_DESTBLENDALPHA, D3DBLEND_ONE );

            device->SetRenderState( D3DRS_SRGBWRITEENABLE, FALSE );
            device->SetRenderState( D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA );

            ImGui_ImplDX9_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            Menu::Render();

            ImGui::Render();

            ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData() );

            pixel_state->Apply();
            pixel_state->Release();
        }

        return Original( device );
    }

    HRESULT Reset::Hook( IDirect3DDevice9* Device, D3DPRESENT_PARAMETERS* Params )
    {
        ImGui_ImplDX9_InvalidateDeviceObjects();
        const long hr = Original( Device, Params );
        window = Params->hDeviceWindow;
        ImGui_ImplDX9_CreateDeviceObjects();
        return hr;
    }
}
