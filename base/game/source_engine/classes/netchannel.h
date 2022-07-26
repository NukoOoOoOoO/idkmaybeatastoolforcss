#pragma once

class INetMsgHandler;
class INetMessage;

struct INetChannel_t
{
private:
	std::byte pad[0x8]{};
public:
	int outSequenceNr;
	int inSequenceNr;
	int outSequenceNrAck;
	int outReliableState;
	int inReliableState;
	int chokedPacket;

	auto GetAddress()
	{
		return Hikari::Memory->VirtualCall<const char*, 1>( this );
	}

	auto IsLoopback()
	{
		return Hikari::Memory->VirtualCall<bool, 6>( this );
	}

	auto SendNetMessage( INetMessage& msg, bool forceReliable = false, bool voice = false )
	{
		return Hikari::Memory->VirtualCall<bool, 40>( this, std::ref( msg ), forceReliable, voice );
	}
};


class INetMessage
{
public:
	virtual ~INetMessage()
	{
	};

	// Use these to setup who can hear whose voice.
	// Pass in client indices (which are their ent indices - 1).

	virtual void SetNetChannel( INetChannel_t* netchan ) = 0; // netchannel this message is from/for
	virtual void SetReliable( bool state ) = 0; // set to true if it's a reliable message

	virtual bool Process( void ) = 0; // calles the recently set handler to process this message

	virtual bool ReadFromBuffer( bf_read& buffer ) = 0; // returns true if parsing was OK
	virtual bool WriteToBuffer( bf_write& buffer ) = 0; // returns true if writing was OK

	virtual bool IsReliable( void ) const = 0; // true, if message needs reliable handling

	virtual int GetType( void ) const = 0; // returns module specific header tag eg svc_serverinfo
	virtual int GetGroup( void ) const = 0; // returns net message group of this message
	virtual const char* GetName( void ) const = 0; // returns network message name, eg "svc_serverinfo"
	virtual INetChannel_t* GetNetChannel( void ) const = 0;
	virtual const char* ToString( void ) const = 0; // returns a human readable string about message content
};

class CNetMessage : public INetMessage
{
public:
	CNetMessage()
	{
		m_bReliable = true;
		m_NetChannel = nullptr;
	}

	~CNetMessage() override
	{
	};

	int GetGroup() const override
	{
		return 0;
	}

	INetChannel_t* GetNetChannel() const override
	{
		return m_NetChannel;
	}

	void SetReliable( bool state ) override
	{
		m_bReliable = state;
	};

	bool IsReliable() const override
	{
		return m_bReliable;
	};

	void SetNetChannel( INetChannel_t* netchan ) override
	{
		m_NetChannel = netchan;
	}

	bool Process() override
	{
		return false;
	}; // no handler set

protected:
	bool m_bReliable; // true if message should be send reliable
	INetChannel_t* m_NetChannel; // netchannel this message is from/for
};

class CLC_RespondCvarValue : public CNetMessage
{
public:
	bool ReadFromBuffer( bf_read& buffer ) override
	{
		return true;
	};

	bool WriteToBuffer( bf_write& buffer ) override
	{
		return true;
	};

	const char* ToString() const override
	{
		return "string";
	};

	int GetType() const override
	{
		return 13;
	}

	const char* GetName() const override
	{
		return "CLC_RespondCvarValue";
	}

	void* m_pMessageHandler;

	bool Process() override
	{
		return true;
	}

	int m_iCookie;

	const char* m_szCvarName;
	const char* m_szCvarValue; // The sender sets this, and it automatically points it at m_szCvarNameBuffer when receiving.

	int m_eStatusCode;

private:
	char m_szCvarNameBuffer[256];
	char m_szCvarValueBuffer[256];
};

#define NUM_NEW_COMMAND_BITS		4
#define MAX_NEW_COMMANDS			((1 << NUM_NEW_COMMAND_BITS)-1)
#define NUM_BACKUP_COMMAND_BITS		3
#define MAX_BACKUP_COMMANDS			((1 << NUM_BACKUP_COMMAND_BITS)-1)

class CLC_Move : public CNetMessage
{
public:
	bool ReadFromBuffer( bf_read& buffer ) override
	{
		m_nNewCommands = buffer.ReadUBitLong( NUM_NEW_COMMAND_BITS );
		m_nBackupCommands = buffer.ReadUBitLong( NUM_BACKUP_COMMAND_BITS );
		m_nLength = buffer.ReadWord();
		m_DataIn = buffer;
		return buffer.SeekRelative( m_nLength );
	};

	bool WriteToBuffer( bf_write& buffer ) override
	{
		buffer.WriteUBitLong( GetType(), 6 );
		m_nLength = m_DataOut.GetNumBitsWritten();

		buffer.WriteUBitLong( m_nNewCommands, NUM_NEW_COMMAND_BITS );
		buffer.WriteUBitLong( m_nBackupCommands, NUM_BACKUP_COMMAND_BITS );

		buffer.WriteWord( m_nLength );

		return buffer.WriteBits( m_DataOut.GetData(), m_nLength );
	};

	const char* ToString() const override
	{
		return "";
	};

	int GetType() const override
	{
		return 9;
	}

	const char* GetName() const override
	{
		return "";
	}

	void* m_pMessageHandler;

	bool Process() override
	{
		return true;
	}

	int GetGroup() const override
	{
		return 11;
	}

	CLC_Move()
	{
		m_bReliable = false;
	}

public:
	int m_nBackupCommands;
	int m_nNewCommands;
	int m_nLength;
	bf_read m_DataIn;
	bf_write m_DataOut;
};

class NET_SetConVar : public CNetMessage
{
	bool ReadFromBuffer( bf_read& buffer ) override
	{
		return true;
	}

	bool WriteToBuffer( bf_write& buffer ) override
	{
		return true;
	}

	bool Process() override
	{
		return true;
	}

	const char* ToString() const override
	{
		return "";
	};

	int GetType() const override
	{
		return 5;
	}

	const char* GetName() const override
	{
		return "";
	}

	NET_SetConVar()
	{
	}

	NET_SetConVar( const char* name, const char* value )
	{
		cvar_t cvar;
		strcpy_s( cvar.name, 260, name );
		strcpy_s( cvar.value, 260, value );
		m_ConVars.AddToTail( cvar );
	}

public:
	using cvar_t = struct cvar_s
	{
		char name[260];
		char value[260];
	};

	CUtlVector<cvar_t> m_ConVars;
};

struct SVC_FixAngle
{
private:
	std::byte pad_0[0x10]{};
public:
	bool relative;
	Angle_t angle;
};
