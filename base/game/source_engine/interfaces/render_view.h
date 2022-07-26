#pragma once

struct IRenderView_t
{
    auto SetAlpha( float v )
    {
        return Hikari::Memory->VirtualCall<void, 4>( this, v );
    }

    auto GetAlpha()
    {
        return Hikari::Memory->VirtualCall<float, 5>( this );
    }

    auto SetColor( float* v )
    {
        return Hikari::Memory->VirtualCall<void, 6>( this, v );
    }

    auto GetColor( float* v )
    {
        return Hikari::Memory->VirtualCall<void, 7>( this, v );
    }

    void SetColor( const Color_t& clr )
    {
        std::array d = {static_cast<float>(clr.r()), static_cast<float>(clr.g()), static_cast<float>(clr.b())};
        SetColor( d.data() );
    }
};
