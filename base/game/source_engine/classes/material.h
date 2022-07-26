#pragma once

struct MaterialVar_t
{
	auto SetFloat( float v )
	{
		return Hikari::Memory->VirtualCall<void, 3>( this, v );
	}
};

struct Material_t
{
	auto GetName()
	{
		return Hikari::Memory->VirtualCall<const char*, 0>( this );
	}

	auto GetTextureGroupName()
	{
		return Hikari::Memory->VirtualCall<const char*, 1>( this );
	}

	auto FindVar( const char* name, bool* found, bool complain = true )
	{
		return Hikari::Memory->VirtualCall<MaterialVar_t*, 11>( this, name, found, complain );
	}

	auto IncrementReferenceCount()
	{
		return Hikari::Memory->VirtualCall<void, 12>( this );
	}

	auto AlphaModulate( float a )
	{
		return Hikari::Memory->VirtualCall<void, 27>( this, a );
	}

	auto ColorModulate( float r, float g, float b )
	{
		return Hikari::Memory->VirtualCall<void, 28>( this, r, g, b );
	}

	auto SetMaterialVarFlag(int flag, bool on)
	{
		return Hikari::Memory->VirtualCall<void, 29>(this, flag, on);
	}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
};
