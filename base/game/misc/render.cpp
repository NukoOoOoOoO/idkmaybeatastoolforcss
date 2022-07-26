#include "../../framework.h"
#include "../game.h"

namespace Game::Render
{
    Vector2D_t _screenSize;

    void Init()
    {
        Interfaces->Surface->SetFontGlyphSet( Fonts::ESP = Interfaces->Surface->CreatFont(), "Smallest Pixel-7", 11, FW_MEDIUM, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_OUTLINE, 0, 0 );
        Interfaces->Surface->SetFontGlyphSet( Fonts::WaterMark = Interfaces->Surface->CreatFont(), "04b03", 12, FW_BOLD, 0, 0, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW, 0, 0 );

        int width, height;
        Interfaces->EngineClient->GetScreenSize( width, height );
        _screenSize = Vector2D_t( static_cast<float>(width), static_cast<float>(height) );
    }

    void DrawFilledRect( const int x, const int y, const int w, const int h, Color_t col )
    {
        Interfaces->Surface->DrawSetColor( col.r(), col.g(), col.b(), col.a() );
        Interfaces->Surface->DrawFilledRect( x, y, x + w, y + h );
    }

    void DrawOutlinedRect( const int x, const int y, const int w, const int h, Color_t col )
    {
        Interfaces->Surface->DrawSetColor( col.r(), col.g(), col.b(), col.a() );
        Interfaces->Surface->DrawOutlinedRect( x, y, x + w, y + h );
    }

    void DrawLine( const int x, const int y, const int w, const int h, Color_t col )
    {
        Interfaces->Surface->DrawSetColor( col.r(), col.g(), col.b(), col.a() );
        Interfaces->Surface->DrawLine( x, y, w, h );
    }

    void DrawOutlinedBox( int x, int y, int w, int h, Color_t col, Color_t col2 )
    {
        DrawOutlinedRect( x - 1, y - 1, w + 2, h + 2, col2 );
        DrawOutlinedRect( x, y, w, h, col );
        DrawOutlinedRect( x + 1, y + 1, w - 2, h - 2, col2 );
    }

    Vector2D_t GetTextSize( const unsigned long& font, const std::string& text )
    {
        const auto buf = Hikari::String::ToUnicode( text );
        if ( buf.empty() )
            return {};

        int width, height;
        Interfaces->Surface->GetTextSize( font, buf.data(), width, height );

        return {static_cast<float>(width), static_cast<float>(height)};
    }

    void Text( HFont font, const std::string& text, int x, int y, bool centered, Color_t col )
    {
        int _x = x;
        const int _y = y;

        const auto buf = Hikari::String::ToUnicode( text );
        if ( buf.empty() )
            return;

        int width, height;
        Interfaces->Surface->GetTextSize( font, buf.data(), width, height );

        if ( centered )
            _x -= width / 2;

        Interfaces->Surface->DrawSetTextFont( font );
        Interfaces->Surface->DrawSetTextColor( col.r(), col.g(), col.b(), col.a() );
        Interfaces->Surface->DrawSetTextPos( _x, _y );
        Interfaces->Surface->DrawPrintText( buf.c_str(), buf.length() );
    }

    void Text( HFont font, Vector2D_t pos, const std::string& str, Color_t clr, bool center )
    {
        if ( str.empty() )
            return;

        if ( center )
        {
            const auto size = GetTextSize( font, str );
            pos.x -= size.x / 2.f;
        }

        Interfaces->Surface->DrawColoredTexted( font, static_cast<int>(pos.x), static_cast<int>(pos.y), clr.r(), clr.g(), clr.b(), clr.a(), str.data() );
    }

    Vector2D_t GetScreenSize()
    {
        return _screenSize;
    }
}
