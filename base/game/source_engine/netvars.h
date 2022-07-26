#pragma once

#include <unordered_map>

namespace Game
{
	struct Netvar_t
	{
		Netvar_t();

		std::ptrdiff_t& Get( fnv::hash key );

	private:
		void Dump( const char* network_name, const RecvTable* table, ptrdiff_t offset = 0 );
		void DumpDatamap(const char* field_name, const Datamap_t* map, ptrdiff_t offset = 0, bool embedded = false);

		void DumpServer(const char* network_name, const SendTable* table, ptrdiff_t offset = 0);
		void DumpServerDatamap(const char* field_name, const Datamap_t* map, ptrdiff_t offset = 0, bool embedded = false);

		std::unordered_map<fnv::hash, ptrdiff_t> _netProps;
		std::unordered_map<fnv::hash, ptrdiff_t> _serverNetProps;
	};

	inline std::unique_ptr<Netvar_t> Netvar;
}

#define NETVAR_CLIENT( func_type, func, netvar_name ) \
[[nodiscard]] std::add_lvalue_reference_t<func_type> func()\
{\
    static auto offset = Game::Netvar->Get(FNV(netvar_name));\
    return *(std::add_pointer_t<func_type>)(reinterpret_cast<std::uintptr_t>(this) + offset);\
}

#define NETVAR_OFFSET_CLIENT( func_type, func, netvar_name, off ) \
[[nodiscard]] std::add_lvalue_reference_t<func_type> func()\
{\
    static auto offset = Game::Netvar->Get(FNV(netvar_name));\
    return *(std::add_pointer_t<func_type>)(reinterpret_cast<std::uintptr_t>(this) + offset + off);\
}

#define OFFSET( func_type, func,  offset ) \
[[nodiscard]] std::add_lvalue_reference_t<func_type> func()\
{\
    return *(std::add_pointer_t<func_type>)(reinterpret_cast<std::uintptr_t>(this) + offset);\
}
