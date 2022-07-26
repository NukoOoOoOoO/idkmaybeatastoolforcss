#pragma once

namespace Client
{
    struct IClientRenderable_t
    {
        auto ShouldDraw()
        {
            return Hikari::Memory->VirtualCall<bool, 3>( this );
        }

        auto SetupBones( matrix3x4_t* pBoneToWorldOut, int MaxBones, int BoneMask, float CurrentTime )
        {
            return Hikari::Memory->VirtualCall<bool, 16>( this, pBoneToWorldOut, MaxBones, BoneMask, CurrentTime );
        }

        auto GetModel()
        {
            return Hikari::Memory->VirtualCall<const void*, 9>( this );
        }
    };

    struct IClientNetworkable_t
    {
        auto GetClientClass()
        {
            return Hikari::Memory->VirtualCall<ClientClass_t*, 2>( this );
        }

        auto GetIndex()
        {
            return Hikari::Memory->VirtualCall<int, 9>( this );
        }
    };

    struct CBaseEntity_t
    {
        IClientRenderable_t* GetRenderable()
        {
            return reinterpret_cast<IClientRenderable_t*>(reinterpret_cast<std::uintptr_t>(this) + sizeof( void* ));
        }

        IClientNetworkable_t* GetNetworkable()
        {
            return reinterpret_cast<IClientNetworkable_t*>(reinterpret_cast<std::uintptr_t>(this) + sizeof( void* ) * 2);
        }

        NETVAR_CLIENT( Vector3D_t, GetVecMins, "C_BaseEntity->m_vecMins" )
        NETVAR_CLIENT( Vector3D_t, GetVecMaxs, "C_BaseEntity->m_vecMaxs" )
        NETVAR_CLIENT( matrix3x4_t, GetCoordinateFrame, "C_BaseEntity->m_rgflCoordinateFrame" )
        NETVAR_CLIENT( int, GetMoveType, "C_BaseEntity->m_MoveType" )
        NETVAR_CLIENT( bool, IsDormant, "C_BaseEntity->m_bDormant" )

        auto GetAbsOrigin()
        {
            return Hikari::Memory->VirtualCall<Vector3D_t&, 9>( this );
        }

        Datamap_t* GetPredDatamap()
        {
            return Hikari::Memory->VirtualCall<Datamap_t*, 15>( this );
        }

        auto IsPlayer()
        {
            return Hikari::Memory->VirtualCall<bool, 131>( this );
        }
    };

    struct CBaseAnimating_t : CBaseEntity_t
    {
        NETVAR_CLIENT( int, GetHitboxSet, "C_BaseAnimating->m_nHitboxSet" )
    };

    struct CBaseCombatWeapon_t : CBaseEntity_t
    {
        NETVAR_CLIENT( int, GetWeaponID, "C_BaseCombatWeapon->m_iWeaponID" )
        NETVAR_CLIENT( int, GetWeaponInfoIndex, "C_BaseCombatWeapon->m_nWeaponInfoIndex" )
        NETVAR_CLIENT( int, GetClip1, "C_BaseCombatWeapon->m_iClip1" )
        NETVAR_CLIENT( float, GetNextPrimaryAttack, "C_BaseCombatWeapon->m_flNextPrimaryAttack" )
        NETVAR_CLIENT( float, GetNextSecondaryAttack, "C_BaseCombatWeapon->m_flNextSecondaryAttack" )
        NETVAR_CLIENT( float, GetReloadStart, "C_BaseCombatWeapon->m_flReloadStart" )
        NETVAR_CLIENT( std::size_t, GetOwner, "C_BaseCombatWeapon->m_hOwnerEntity" )
        NETVAR_CLIENT( float, GetThrowTime, "C_BaseCSGrenade->m_fThrowTime" )
    };

    class CCSWeaponInfo_t
    {
        #define MAX_WEAPON_STRING	80
        #define MAX_WEAPON_PREFIX	16
        #define MAX_WEAPON_AMMO_NAME 32
        #define NUM_SHOOT_SOUND_TYPES 16

        virtual void Parse( void*, const char* ) = 0;
    public:
        bool bParsedScript; //0x0004
        bool bLoadedHudElements; //0x0005
        char szClassName[MAX_WEAPON_STRING]; //0x0006
        char szPrintName[MAX_WEAPON_STRING]; //0x0056
        char szViewModel[MAX_WEAPON_STRING]; //0x00A6
        char szWorldModel[MAX_WEAPON_STRING]; //0x00F6
        char szAnimationPrefix[MAX_WEAPON_PREFIX]; //0x0146
        char pad_0156[2]; //0x0156
        int32_t iSlot; //0x0158
        int32_t iPosition; //0x015C
        int32_t iMaxClip1; //0x0160
        int32_t iMaxClip2; //0x0164
        int32_t iDefaultClip1; //0x0168
        int32_t iDefaultClip2; //0x016C
        int32_t iWeight; //0x0170
        int32_t iRumbleEffect; //0x0174
        bool bAutoSwitchTo; //0x0178
        bool bAutoSwitchFrom; //0x0179
        char pad_017A[2]; //0x017A
        int32_t iFlags; //0x017C
        char szAmmo1[MAX_WEAPON_AMMO_NAME]; //0x0180
        char szAmmo2[MAX_WEAPON_AMMO_NAME]; //0x01A0
        char aShootSounds[NUM_SHOOT_SOUND_TYPES][MAX_WEAPON_STRING]; //0x01C0
        int32_t iAmmoType; //0x06C0
        int32_t iAmmo2Type; //0x06C4
        bool m_bMeleeWeapon; //0x06C8
        bool m_bBuiltRightHanded; //0x06C9
        bool m_bAllowFlipping; //0x06CA
        char pad_06CB[1]; //0x06CB
        int32_t iSpriteCount; //0x06CC
        void* iconActive; //0x06D0
        void* iconInactive; //0x06D4
        void* iconAmmo; //0x06D8
        void* iconAmmo2; //0x06DC
        void* iconCrosshair; //0x06E0
        void* iconAutoaim; //0x06E4
        void* iconZoomedCrosshair; //0x06E8
        void* iconZoomedAutoaim; //0x06EC
        void* iconSmall; //0x06F0
        bool bShowUsageHint; //0x06F4
        char pad_06F5[3]; //0x06F5
        float m_flMaxSpeed; //0x06F8
        int32_t m_WeaponType; //0x06FC
        bool bFullAuto; //0x0700
        char pad_0701[3]; //0x0701
        int32_t m_iTeam; //0x0704
        float m_flBotAudibleRange; //0x0708
        float m_flArmorRatio; //0x070C
        int32_t m_iCrosshairMinDistance; //0x0710
        int32_t m_iCrosshairDeltaDistance; //0x0714
        bool m_bCanUseWithShield; //0x0718
        char m_WrongTeamMsg[32]; //0x0719
        char m_szAnimExtension[16]; //0x0739
        char m_szShieldViewModel[64]; //0x0749
        char m_szAddonModel[MAX_WEAPON_STRING]; //0x0789
        char m_szDroppedModel[MAX_WEAPON_STRING]; //0x07D9
        char m_szSilencerModel[MAX_WEAPON_STRING]; //0x0829
        char pad_0879[3]; //0x0879
        int32_t m_iMuzzleFlashStyle; //0x087C
        float m_flMuzzleScale; //0x0880
        int32_t m_iPenetration; //0x0884
        int32_t m_iDamage; //0x0888
        float m_flRange; //0x088C
        float m_flRangeModifier; //0x0890
        int32_t m_iBullets; //0x0894
        float m_flCycleTime; //0x0898
        bool m_bAccuracyQuadratic; //0x089C
        char pad_089D[3]; //0x089D
        float m_flAccuracyDivisor; //0x08A0
        float m_flAccuracyOffset; //0x08A4
        float m_flMaxInaccuracy; //0x08A8
        float m_flSpread; //0x08AC
        float m_flSpreadAlt; //0x08B0
        float m_flInaccuracyCrouch; //0x08B4
        float m_flInaccuracyCrouchAlt; //0x08B8
        float m_flInaccuracyStand; //0x08BC
        float m_flInaccuracyStandAlt; //0x08C0
        float m_flInaccuracyJump; //0x08C4
        float m_flInaccuracyJumpAlt; //0x08C8
        float m_flInaccuracyLand; //0x08CC
        float m_flInaccuracyLandAlt; //0x08D0
        float m_flInaccuracyLadder; //0x08D4
        float m_flInaccuracyLadderAlt; //0x08D8
        float m_flInaccuracyFire; //0x08DC
        float m_flInaccuracyFireAlt; //0x08E0
        float m_flInaccuracyMove; //0x08E4
        float m_flInaccuracyMoveAlt; //0x08E8
        float m_flRecoveryTimeStand; //0x08EC
        float m_flRecoveryTimeCrouch; //0x08F0
        float m_flInaccuracyReload; //0x08F4
        float m_flInaccuracyAltSwitch; //0x08F8
        float m_flTimeToIdleAfterFire; //0x08FC
        float m_flIdleInterval; //0x0900
        int32_t m_iWeaponPrice; //0x0904
        int32_t m_iDefaultPrice; //0x0908
        int32_t m_iPreviousPrice; //0x090C
    }; //Size: 0x0910

    struct CCSWeapon_t : CBaseCombatWeapon_t
    {
        auto GetWeaponData()
        {
            return Game::Addresses::GetCSWepData.Cast<CCSWeaponInfo_t* (__thiscall*)( void* )>()( this );
        }

        auto GetInaccuracy()
        {
            return Hikari::Memory->VirtualCall<float, 376>( this );
        }

        auto GetSpread()
        {
            return Hikari::Memory->VirtualCall<float, 377>( this );
        }

        auto UpdateAccuracy()
        {
            return Hikari::Memory->VirtualCall<void, 378>( this );
        }
    };

    struct CBaseCombatCharacter_t : CBaseAnimating_t
    {
        NETVAR_CLIENT( float, GetNextAttack, "C_BasePlayer->m_flNextAttack" )
        NETVAR_CLIENT( uint32_t, GetWeapons, "C_BasePlayer->m_hMyWeapons" )
    };

    struct CBasePlayer_t : CBaseCombatCharacter_t
    {
        NETVAR_CLIENT( int, GetLifeState, "C_BasePlayer->m_lifeState" )
        NETVAR_CLIENT( int, GetHealth, "C_BasePlayer->m_iHealth" )
        NETVAR_CLIENT( Vector3D_t, GetViewOffset, "C_BasePlayer->m_vecViewOffset[0]" )
        NETVAR_CLIENT( int, GetTeam, "C_BaseEntity->m_iTeamNum" );
        NETVAR_CLIENT( Vector3D_t, GetVelocity, "C_BasePlayer->m_vecVelocity[0]" );
        NETVAR_CLIENT( Angle_t, GetPunchAngle, "C_BasePlayer->m_vecPunchAngle" )
        NETVAR_CLIENT( bitflag_t, GetFlag, "C_BasePlayer->m_fFlags" )
        NETVAR_CLIENT( bool, deadflag, "C_BasePlayer->deadflag" )
        NETVAR_CLIENT( int, GetTickBase, "C_BasePlayer->m_nTickBase" )
        NETVAR_CLIENT( Vector3D_t, GetOrigin, "C_BaseEntity->m_vecOrigin" )
        NETVAR_CLIENT( uintptr_t, GetGroundEntityHandle, "C_BasePlayer->m_hGroundEntity" )
        NETVAR_CLIENT( float, GetMaxSpeed, "C_BasePlayer->m_flMaxspeed" )
        NETVAR_CLIENT( float, GetSurfaceFrction, "C_BasePlayer->m_surfaceFriction" )
        NETVAR_CLIENT( int8_t, GetWaterLevel, "DT_BasePlayer->m_nWaterLevel" )

        Vector3D_t GetEyePos()
        {
            return GetOrigin() + GetViewOffset();
        }

        auto IsAlive()
        {
            return Hikari::Memory->VirtualCall<bool, 130>( this );
        }

        auto GetActiveWeapon()
        {
            return Game::Addresses::GetActiveWeapon.Cast<CCSWeapon_t* (__thiscall*)( void* )>()( this );
        }
    };

    struct CCSPlayer_t : CBasePlayer_t
    {
        NETVAR_CLIENT( int, GetArmor, "C_CSPlayer->m_ArmorValue" );
        NETVAR_CLIENT( float, GetFlashDuration, "C_CSPlayer->m_flFlashDuration" );
        NETVAR_CLIENT( float, GetFlashMaxAlpha, "C_CSPlayer->m_flFlashMaxAlpha" );
    };
}

namespace Server
{
    struct CBaseEntity_t
    {
        NETVAR_SERVER(Vector3D_t, GetMins, "C_BaseEntity->m_vecMins");
        NETVAR_SERVER(Vector3D_t, GetMaxs, "C_BaseEntity->m_vecMaxs");
        NETVAR_SERVER(Vector3D_t, GetAbsVelocity, "C_BaseEntity->m_vecAbsVelocity");
        NETVAR_SERVER(Vector3D_t, GetVelocity, "C_BaseEntity->m_vecVelocity");
    };

    struct CBaseCombatCharacter_t : CBaseEntity_t
    {
        
    };

    struct CBasePlayer_t : CBaseCombatCharacter_t
    {
        NETVAR_SERVER(float, GetMaxSpeed, "C_BasePlayer->m_flMaxspeed");
        NETVAR_SERVER(const char*, GetPlayerName, "C_BasePlayer->m_szNetname");
    };

    struct CCSPlayer_t : CBasePlayer_t
    {
        void ChangeTeam(int team)
        {
            return Hikari::Memory->VirtualCall<void, 91>(this, team);
        }

        void InitialSpawn()
        {
            return Hikari::Memory->VirtualCall<void, 326>(this);
        }

        void Spawn()
        {
            return Hikari::Memory->VirtualCall<void, 22>(this);
        }
    };
}
