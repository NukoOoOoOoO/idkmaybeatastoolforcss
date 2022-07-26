#pragma once

struct IModelRender_t
{
	auto ForceMaterialOverride(Material_t* material, int type)
	{
		return Hikari::Memory->VirtualCall<void, 1>(this, material, type);
	}
};