#pragma once

class KeyValues_t
{
private:
	int m_iKeyName;
	char* m_sValue;
	wchar_t* m_wsValue;

	union
	{
		int m_iValue;
		float m_flValue;
		void* m_pValue;
		uint8_t m_Color[4];
	};

	char m_iDataType;
	char m_bHasEscapeSequences;
	char m_bEvaluateConditionals;
	char unused[1];

	KeyValues_t* m_pPeer;
	KeyValues_t* m_pSub;
	KeyValues_t* m_pChain;

public:
	KeyValues_t() = default;
	explicit KeyValues_t( std::string name );
	bool LoadFromBuffer( const char* resource_name, const char* buffer, void* file_system = nullptr, const char* path_id = nullptr );
	void Initialize( char* name );
};
