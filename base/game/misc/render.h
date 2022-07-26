#pragma once

namespace Game::Render
{
    void Init();

    void DrawFilledRect( int x, int y, int w, int h, Color_t col );
    void DrawOutlinedRect( int x, int y, int w, int h, Color_t col );
    void DrawLine( int x, int y, int w, int h, Color_t col );
    void DrawOutlinedBox( int x, int y, int w, int h, Color_t col, Color_t col2 = Color_t( 10, 10, 10, 190 ) );

    Vector2D_t GetTextSize( const unsigned long& font, const std::string& text );
    void Text( HFont font, const std::string& text, int x, int y, bool centered, Color_t col );
    void Text( HFont, Vector2D_t pos, const std::string& str, Color_t clr, bool center = false );

    Vector2D_t GetScreenSize();
}

namespace Game::Fonts
{
    inline HFont ESP{};
    inline HFont WaterMark{};
}
