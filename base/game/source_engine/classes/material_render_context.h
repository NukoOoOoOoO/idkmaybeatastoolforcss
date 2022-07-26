#pragma once

struct MaterialRenderContext_t
{
    auto ClearBuffer( bool color, bool depth, bool stencil = false )
    {
        return Hikari::Memory->VirtualCall<void, 12>( this, color, depth, stencil );
    }

    auto Viewport( int x, int y, int w, int h )
    {
        return Hikari::Memory->VirtualCall<void, 38>( this, x, y, w, h );
    }

    auto GetViewport( int& x, int& y, int& w, int& h )
    {
        return Hikari::Memory->VirtualCall<void, 39>( this, std::ref( x ), std::ref( y ), std::ref( w ), std::ref( h ) );
    }

    auto ClearColor3UB( uint8_t r, uint8_t g, uint8_t b )
    {
        return Hikari::Memory->VirtualCall<void, 72>( this, r, g, b );
    }

    auto ClearColor3UB( uint8_t r, uint8_t g, uint8_t b, uint8_t a )
    {
        return Hikari::Memory->VirtualCall<void, 73>( this, r, g, b, a );
    }

    auto OverrideDepthEnable( bool enable, bool depthEnable )
    {
        return Hikari::Memory->VirtualCall<void, 74>( this, enable, depthEnable );
    }

    auto DrawScreenSpaceRect( Material_t* material, int destx, int desty, int w, int h, float src_x0, float src_y0, float src_x1, float src_y1, int src_w, int src_h,
                              void* renderable = nullptr, int dice_x = 1, int dice_y = 1 )
    {
        return Hikari::Memory->VirtualCall<void, 103>( this, material, destx, desty, w, h, src_x0, src_y0, src_x1, src_y1, src_w, src_h, renderable, dice_x, dice_y );
    }

    auto PushRenderTargetAndViewport()
    {
        return Hikari::Memory->VirtualCall<void, 108>( this );
    }

    auto PopRenderTargetAndViewport()
    {
        return Hikari::Memory->VirtualCall<void, 109>( this );
    }

    auto SetStencilEnable( bool v )
    {
        return Hikari::Memory->VirtualCall<void, 117>( this, v );
    }

    auto SetStencilFailOperation( int v )
    {
        return Hikari::Memory->VirtualCall<void, 118>( this, v );
    }

    auto SetStencilZFailOperation( int v )
    {
        return Hikari::Memory->VirtualCall<void, 119>( this, v );
    }

    auto SetStencilPassOperation( int v )
    {
        return Hikari::Memory->VirtualCall<void, 120>( this, v );
    }

    auto SetStencilCompareFunction( int v )
    {
        return Hikari::Memory->VirtualCall<void, 121>( this, v );
    }

    auto SetStencilReferenceValue( int v )
    {
        return Hikari::Memory->VirtualCall<void, 122>( this, v );
    }

    auto SetStencilTestMask( int v )
    {
        return Hikari::Memory->VirtualCall<void, 123>( this, v );
    }

    auto SetStencilWriteMask( int v )
    {
        return Hikari::Memory->VirtualCall<void, 124>( this, v );
    }
};
