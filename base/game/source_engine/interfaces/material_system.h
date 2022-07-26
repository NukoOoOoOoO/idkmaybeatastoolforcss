#pragma once


struct IMaterialSystem_t
{
	auto CreateMaterial( const char* name, KeyValues_t* kv )
	{
		return Hikari::Memory->VirtualCall<Material_t*, 70>( this, name, kv );
	}

	auto FindMaterial( const char* name, const char* group, bool complain = true, const char* prefix = nullptr )
	{
		return Hikari::Memory->VirtualCall<Material_t*, 71>( this, name, group, complain, prefix );
	}

	auto FirstMaterial()
	{
		return Hikari::Memory->VirtualCall<uint16_t, 73>( this );
	}

	auto NextMaterial()
	{
		return Hikari::Memory->VirtualCall<uint16_t, 74>( this );
	}

	auto InvalidMaterial()
	{
		return Hikari::Memory->VirtualCall<uint16_t, 75>( this );
	}

	auto GetMaterial( uint16_t id )
	{
		return Hikari::Memory->VirtualCall<Material_t*, 76>( this, id );
	}

	auto FindTexture( const char* name, const char* group, bool complain = true, const char* prefix = nullptr )
	{
		return Hikari::Memory->VirtualCall<Texture_t*, 79>( this, name, group, complain, prefix );
	}

	auto CreateRenderTargetEx( const char* name, int w, int h, int size_mode, int format, int depth = 0x0, unsigned int texture_flags = 0x4 | 0x8, unsigned int render_target_flags = 0 )
	{
		return Hikari::Memory->VirtualCall<Texture_t, 85>( this, name, w, h, size_mode, format, depth, texture_flags, render_target_flags );
	}

	auto GetRenderContext()
	{
		return Hikari::Memory->VirtualCall<MaterialRenderContext_t*, 98>( this );
	}
};
