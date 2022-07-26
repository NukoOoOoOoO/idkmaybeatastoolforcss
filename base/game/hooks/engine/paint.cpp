#include "../../../framework.h"
#include "../../game.h"
#include "../hooks.h"

namespace Game
{
    void __fastcall Paint::Hook( void* ecx, void* edx, unsigned mode )
    {
        Original( ecx, edx, mode );

        static auto StartDrawing = Addresses::StartDrawing.Cast<void(__thiscall*)( void* )>();
        static auto FinishDrawing = Addresses::FinishDrawing.Cast<void(__thiscall*)( void* )>();
        Interfaces->Surface->SetCursorAlwaysVisible( menuOpen );
        if ( mode & 1 )
        {
            StartDrawing( Interfaces->Surface );

            if ( Interfaces->EngineClient->IsInGame() )
            {
                // Esp::Paint();
            }

            FinishDrawing( Interfaces->Surface );
        }
    }
}
