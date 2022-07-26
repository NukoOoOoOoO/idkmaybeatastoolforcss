#pragma once

struct IConVar_t
{
	using FnChangeCallback_t = void(*)( void* var, const char* pOldValue, float flOldValue );
	char pad_0x0000[0x4];
	IConVar_t* _next;
	bool _registered;
	const char* _name;
	const char* _helpString;
	bitflag_t flags;
	char pad_0x0018[0x4];
	IConVar_t* _parent;
	const char* _defaultValue;
	const char* _string;
	int _stringLength;
	float _valueFloat;
	int _valueInt;
	bool _hasMin;
	float _minValue;
	bool _hasMax;
	float _maxValue;
	FnChangeCallback_t change_callback;

	auto SetValue( const char* v )
	{
		return Hikari::Memory->VirtualCall<void, 10>( this, v );
	}

	auto SetValue( float v )
	{
		return Hikari::Memory->VirtualCall<void, 11>( this, v );
	}

	auto SetValue( int v )
	{
		return Hikari::Memory->VirtualCall<void, 12>( this, v );
	}

	auto SetValue( bool v )
	{
		return Hikari::Memory->VirtualCall<void, 12>( this, static_cast<int>(v) );
	}

	[[nodiscard]] int GetInt() const
	{
		return this->_valueInt;
	}

	[[nodiscard]] bool GetBool() const
	{
		return this->_valueInt > 0;
	}

	[[nodiscard]] float GetFloat() const
	{
		return this->_valueFloat;
	}

	[[nodiscard]] bool HasMin() const
	{
		return this->_hasMin;
	}

	[[nodiscard]] bool HasMax() const
	{
		return this->_hasMax;
	}

	[[nodiscard]] float GetMax() const
	{
		return this->_maxValue;
	}

	[[nodiscard]] float GetMin() const
	{
		return this->_minValue;
	}

	[[nodiscard]] const char* GetString() const
	{
		return this->_string;
	}

	[[nodiscard]] const char* GetDefault() const
	{
		return this->_defaultValue;
	}
};

struct ICvar_t
{
	IConVar_t* FindVar( const char* name )
	{
		return Hikari::Memory->VirtualCall<IConVar_t*, 12>( this, name );
	}

	void PrintToConsole(Color_t clr, const char* str)
	{
		return Hikari::Memory->VirtualCallCdecl<void, 23>(this, clr, str);
	}
};
