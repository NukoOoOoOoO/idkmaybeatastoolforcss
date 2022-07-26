#pragma once

struct IStudioRender_t
{
    auto SetColor( float* v )
    {
        return Hikari::Memory->VirtualCall<void, 27>( this, v );
    }

    auto SetAlpha( float v )
    {
        return Hikari::Memory->VirtualCall<void, 28>( this, v );
    }

    void SetColor( const Color_t& clr )
    {
        std::array d = {static_cast<float>(clr.r()), static_cast<float>(clr.g()), static_cast<float>(clr.b())};
        SetColor( d.data() );
    }
};
