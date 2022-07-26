#pragma once

struct matrix3x4_t;
class Angle_t;

struct PlayerInfo_t
{
	char name[32];
	int userid;
	char guid[33];
	unsigned int friendsID;
	char friendName[32];
	bool fakePlayer;
	bool isHLTV;
	unsigned int customFiles[4];
	unsigned char filesDownloaded;
};

struct net_chan
{
	char pad_0000[36]; //0x0000
	int32_t m_out_sequence_nr; //0x0024
	char pad_0028[8]; //0x0028
	int32_t m_choked_packet; //0x0030
};


struct IEngineClient_t
{
	auto GetScreenSize( int& w, int& h )
	{
		return Hikari::Memory->VirtualCall<void, 5>( this, std::ref( w ), std::ref( h ) );
	}

	auto ServerCmd( const char* Command, bool ForceReliable )
	{
		return Hikari::Memory->VirtualCall<void, 7>( this, Command, ForceReliable );
	}

	auto GetPlayerInfo( int index, PlayerInfo_t* info )
	{
		return Hikari::Memory->VirtualCall<bool, 8>( this, index, info );
	}

	auto GetPlayerFromUserID( int uid )
	{
		return Hikari::Memory->VirtualCall<int, 9>( this, uid );
	}

	auto GetLocalPlayer()
	{
		return Hikari::Memory->VirtualCall<int, 12>( this );
	}

	auto GetViewAngles( const Angle_t& angle )
	{
		return Hikari::Memory->VirtualCall<void, 19>( this, std::ref( angle ) );
	}

	auto SetViewAngles( const Angle_t& angle )
	{
		return Hikari::Memory->VirtualCall<void, 20>( this, std::ref( angle ) );
	}

	auto IsInGame()
	{
		return Hikari::Memory->VirtualCall<bool, 26>( this );
	}

	const auto& WorldToScreenMatrix()
	{
		return Hikari::Memory->VirtualCall<const matrix3x4_t&, 36>( this );
	}

	auto GetNetChannelInfo()
	{
		return Hikari::Memory->VirtualCall<net_chan*, 72>( this );
	}

	auto ClientCmd_Unrestricted( const char* szCmdString )
	{
		return Hikari::Memory->VirtualCall<void, 106>( this, szCmdString );
	}
};
