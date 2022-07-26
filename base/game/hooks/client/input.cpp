#include "../../../framework.h"
#include "../../game.h"
#include "../hooks.h"

namespace Game
{
    [[maybe_unused]] static void __stdcall CreateMove( int sequence_number, float input_sample_frametime, bool active, bool& sendpacket )
    {
        CHLCreateMove::Original( Interfaces->Client, nullptr, sequence_number, input_sample_frametime, active );

        const auto* cmd = &Interfaces->Input->m_pCommands[sequence_number % 90];
        auto* verifiedCmd = &Interfaces->Input->m_pVerifiedCommands[sequence_number % 90];

        if ( !cmd || !verifiedCmd || !active )
            return;


        _clientLocalPlayer = Interfaces->EntityList->Get<Client::CCSPlayer_t*>( Interfaces->EngineClient->GetLocalPlayer() );

        if (_clientLocalPlayer)
        {
            if (_clientLocalPlayer->IsAlive() )
            {
            }
        }

        /*if (_local && _local->IsAlive())
        {
            const auto oldAngles = cmd->viewangles;


            IsInNasa = false;
            if ( g_cfg.LagExploit )
            {
                if ( GetAsyncKeyState( 'R' ) || GetAsyncKeyState( VK_CAPITAL ) )
                {
                    Interfaces->Engine->GetNetChannelInfo()->m_out_sequence_nr += g_cfg.LagExploitValue;
                    IsInNasa = true;
                }

                if ( cmd->weaponselect )
                {
                    Interfaces->Engine->GetNetChannelInfo()->m_out_sequence_nr += 500;
                    IsInNasa = true;
                }
            }

            if ( g_cfg.FakeLag )
            {
                if ( Interfaces->Engine->GetNetChannelInfo()->m_choked_packet < g_cfg.FakelagValue )
                    sendpacket = false;
            }
            #1#

            Movement::CreateMove( cmd );

            auto weapon = _local->GetActiveWeapon();
            Aimbot::CreateMove( cmd, sendpacket );

            if ( weapon )
            {
                if ( cmd->buttons.HasFlag( IN_ATTACK ) && weapon->GetWeaponData()->GetWeaponType() != WeaponType_C4 )
                {
                    if ( !Aimbot::CanShoot( weapon, cmd ) )
                        cmd->buttons.RemoveFlag( IN_ATTACK );
                }
            }

            Antiaim::CreateMove( cmd, sendpacket );

            if ( cmd->buttons.HasFlag( IN_ATTACK ) )
                cmd->viewangles -= _local->GetPunchAngle() * 2.0f;

            Math::CorrectMovement( oldAngles, cmd );
        }*/

        verifiedCmd->m_cmd = *cmd;
        verifiedCmd->m_crc = cmd->GetCheckSum();
    }

    __declspec(naked) void __fastcall CHLCreateMove::Hook( void* ecx, void* edx, int sequence_number,
                                                           float input_sample_frametime, bool active )
    {
        // @formatter:off ¡ª disable formatter after this line
        __asm
        {
            push ebp
            mov ebp, esp;
            push ebx;
            push esp;
            push dword ptr[active];
            push dword ptr[input_sample_frametime];
            push dword ptr[sequence_number];
            call CreateMove
                pop ebx
                pop ebp
                retn 0Ch
        }
        // @formatter:on ¡ª enable formatter after this line
    }
}
