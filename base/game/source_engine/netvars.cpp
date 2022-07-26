#include "../../framework.h"
#include "../game.h"
#include "netvars.h"

// #define DUMP_NETVAR

#ifdef DUMP_NETVAR
#include <fstream>
#endif

namespace Game
{
    #ifdef DUMP_NETVAR
    std::ofstream _file;
    #endif


    Netvar_t::Netvar_t()
    {
        #ifdef DUMP_NETVAR
        _file.open( "client_netvar.txt" );
        #endif

        for ( auto ptr = Interfaces->Client->GetAllClasses(); ptr; ptr = ptr->m_pNext )
        {
            if ( ptr->m_pRecvTable )
            {
                Dump( ptr->m_pNetworkName, ptr->m_pRecvTable );
            }
        }

        if ( auto datamap = Addresses::GetDataDescMap.Cast<Datamap_t * (*)()>()(); datamap )
        {
            while ( datamap )
            {
                DumpDatamap( datamap->data_class_name, datamap );
                datamap = datamap->base_map;
            }
        }

        if ( auto datamap = Addresses::GetPredDataMap.Cast<Datamap_t * (*)()>()(); datamap )
        {
            while ( datamap )
            {
                DumpDatamap( datamap->data_class_name, datamap );
                datamap = datamap->base_map;
            }
        }

#ifdef DUMP_NETVAR
        _file.close();

        _file.open("server_netvar.txt");
#endif

        for ( auto ptr = Interfaces->ServerDLL->GetAllClasses(); ptr; ptr = ptr->pNext )
        {
            if ( ptr->pTable )
            {
                DumpServer( ptr->szNetworkName, ptr->pTable );
            }
        }
        
        if ( auto datamap = Modules::Server->FindPattern( "55 8B EC 51 89 4D FC B8 ? ? ? ? 8B E5 5D C3 8A 81" ).Cast<Datamap_t*(*)()>()(); datamap )
        {
            while ( datamap )
            {
                DumpServerDatamap( datamap->data_class_name, datamap );
                datamap = datamap->base_map;
            }
        }

        #ifdef DUMP_NETVAR
        _file.close();
        #endif
    }

    std::ptrdiff_t& Netvar_t::Get( const fnv::hash key )
    {
        if ( !this->_netProps.contains( key ) )
            throw std::runtime_error( "Unable to find netprop" );

        return this->_netProps[key];
    }

    void Netvar_t::Dump( const char* network_name, const RecvTable* table, const ptrdiff_t offset )
    {
        for ( auto i = 0; i < table->m_nProps; i++ )
        {
            const auto& prop = table->m_pProps[i];

            if ( std::isdigit( prop.m_pVarName[0] ) || prop.m_pVarName[0] == 'b' && prop.m_pVarName[4] == 'c' )
            {
                continue;
            }

            if ( prop.m_RecvType == 6 && prop.m_pDataTable && prop.m_pDataTable->m_pNetTableName[0] == 'D' )
            {
                Dump( network_name, prop.m_pDataTable, prop.m_Offset + offset );
            }

            std::string proper_name( network_name );
            proper_name = "C_" + (proper_name[0] == 'C' ? proper_name.substr( 1 ) : network_name) + "->" + prop.m_pVarName;

            if ( const auto hash = fnv::hash_runtime( proper_name.c_str() ); !this->_netProps[hash] )
            {
                this->_netProps[hash] = prop.m_Offset + offset;

                #ifdef DUMP_NETVAR
                _file << std::format( "{} ==> {:#04X}", proper_name, prop.m_Offset + offset ).c_str() << std::endl;
                #endif
            }
        }
    }

    void Netvar_t::DumpDatamap( const char* field_name, const Datamap_t* map, const ptrdiff_t offset, bool embedded )
    {
        for ( auto i = 0; i < map->data_num_fields; i++ )
        {
            const auto& field = map->data_desc[i];
            if ( field.name == nullptr )
                continue;

            if ( field.type == fieldtype_t::FIELD_EMBEDDED )
                DumpDatamap( field_name, field.td, field.offset[TD_OFFSET_NORMAL] + offset, true );

            char netprop_name[256];
            strcpy_s( netprop_name, field_name );
            strcat_s( netprop_name, ("->") );
            strcat_s( netprop_name, field.name );

            // Hikari::Logger->Info( std::format( "{}->{} ==> {:#04X}", field_name, field.name, field.offset[ TD_OFFSET_NORMAL ] + offset ) );

            if ( const auto hash = fnv::hash_runtime( netprop_name ); !this->_netProps[hash] )
            {
                this->_netProps[hash] = field.offset[TD_OFFSET_NORMAL] + offset;
                #ifdef DUMP_NETVAR
                _file << std::format( "{}->{} ==> {:#04X}", field_name, field.name, field.offset[ TD_OFFSET_NORMAL ] + offset ) << std::endl;
                #endif
            }
        }
    }

    void Netvar_t::DumpServer( const char* network_name, const SendTable* table, ptrdiff_t offset )
    {
        for ( auto i = 0; i < table->iTotalProps; i++ )
        {
            const auto prop = &table->pProps[i];

            if ( std::isdigit( prop->szVarName[0] ) || prop->szVarName[0] == 'b' && prop->szVarName[4] == 'c' )
            {
                continue;
            }

            std::string proper_name( network_name );
            proper_name = "C_" + (proper_name[0] == 'C' ? proper_name.substr( 1 ) : network_name) + "->" + prop->szVarName;

            if ( prop->pDataTable )
            {
                DumpServer( network_name, prop->pDataTable, prop->iOffset );
            }
            else if ( const auto hash = fnv::hash_runtime( proper_name.c_str() ); !this->_serverNetProps[hash] )
            {
                this->_serverNetProps[hash] = prop->iOffset + offset;

#ifdef DUMP_NETVAR
                _file << std::format("{} ==> {:#04X}", proper_name, prop->iOffset + offset).c_str() << std::endl;
#endif
            }
        }
    }

    void Netvar_t::DumpServerDatamap( const char* field_name, const Datamap_t* map, ptrdiff_t offset, bool embedded )
    {
        for ( auto i = 0; i < map->data_num_fields; i++ )
        {
            const auto& field = map->data_desc[i];
            if ( field.name == nullptr )
                continue;

            if ( field.type == fieldtype_t::FIELD_EMBEDDED )
                DumpDatamap( field_name, field.td, field.offset[TD_OFFSET_NORMAL] + offset, true );

            std::string proper_name(field_name);
            proper_name = "C_" + (proper_name[0] == 'C' ? proper_name.substr(1) : field_name) + "->" + field.name;
            // Hikari::Logger->Info( std::format( "{}->{} ==> {:#04X}", field_name, field.name, field.offset[ TD_OFFSET_NORMAL ] + offset ) );

            if ( const auto hash = fnv::hash_runtime(proper_name.c_str()); !this->_serverNetProps[hash] )
            {
                this->_serverNetProps[hash] = field.offset[TD_OFFSET_NORMAL] + offset;
#ifdef DUMP_NETVAR
                _file << std::format("{} ==> {:#04X}", proper_name, field.offset[TD_OFFSET_NORMAL] + offset) << std::endl;
#endif
            }
        }
    }
}
