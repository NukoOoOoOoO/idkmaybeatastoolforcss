#pragma once

namespace Game
{
    #define CREATE_HOOK_DEFINE(name, type) \
    struct name { \
        using fn = std::remove_pointer_t<type>; \
        static fn Hook; \
        static fn* Original; \
    }; \
    inline name::fn* name::Original;

    CREATE_HOOK_DEFINE( Paint, void(__fastcall*)(void*, void*, unsigned int) );
    CREATE_HOOK_DEFINE( CHLCreateMove, void(__fastcall*)(void*, void*, int, float, bool) );
    CREATE_HOOK_DEFINE( EndScene, HRESULT(__stdcall*)(IDirect3DDevice9* ) );
    CREATE_HOOK_DEFINE( Reset, HRESULT(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS* ) );
    CREATE_HOOK_DEFINE( LevelInitPostEntity, void(__fastcall*)(void*, void*) );
    CREATE_HOOK_DEFINE( LevelShutdown, void(__fastcall*)(void*, void*) );

    CREATE_HOOK_DEFINE(GameMovement_CheckButtons, bool(__fastcall*)(void*, void*));

    extern LRESULT __stdcall WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

    struct Hook_t
    {
    private:
        struct Detour_t
        {
            Detour_t();
            ~Detour_t();

            void Hook( void* source, void* target, void** original, const std::string& name );
            void Unhook();

        private:
            void* _source;
            void* _target;
            std::string _name;
            bool _hooked;
        };

        Detour_t Paint;
        Detour_t CHLCreateMove;
        Detour_t EndScene;
        Detour_t Reset;
        Detour_t LevelInitPostEntity;
        Detour_t LevelShutdown;
        Detour_t CheckButton;

    public:
        Hook_t();
        ~Hook_t();
    };

    inline std::unique_ptr<Hook_t> Hooks;
}
