#pragma once

struct Texture_t
{
	int GetActualWidth()
	{
		return Hikari::Memory->VirtualCall<int, 3>( this );
	}

	int GetActualHeight()
	{
		return Hikari::Memory->VirtualCall<int, 4>( this );
	}

	void IncrementReferenceCount()
	{
		return Hikari::Memory->VirtualCall<void, 10>( this );
	}
};
