#pragma once

#define	MASK_ALL					(0xFFFFFFFF)

struct CBaseEntity_t;

struct cplane_t
{
	Vector3D_t normal;
	float dist;
	BYTE type; // for fast side tests
	BYTE signbits; // signx + (signy<<1) + (signz<<1)
	BYTE pad[2];
};

struct Ray_t
{
	__declspec(align(16)) Vector3D_t m_Start;
	__declspec(align(16)) Vector3D_t m_Delta;
	__declspec(align(16)) Vector3D_t m_StartOffset;
	__declspec(align(16)) Vector3D_t m_Extents;
	const matrix3x4_t* m_pWorldAxisTransform = nullptr;
	//without your matrix3x4
	bool m_IsRay;
	bool m_IsSwept;

	void Init( const Vector3D_t& start, const Vector3D_t& end )
	{
		m_Delta = end - start;

		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents.x = m_Extents.y = m_Extents.z = 0.0f;

		m_IsRay = true;

		m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;

		m_Start = start;
	}

	void Init( const Vector3D_t& start, const Vector3D_t& end, const Vector3D_t& mins, const Vector3D_t& maxs )
	{
		m_Delta = end - start;

		m_pWorldAxisTransform = nullptr;
		m_IsSwept = (m_Delta.LengthSqr() != 0);

		m_Extents = maxs - mins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.LengthSqr() < 1e-6);

		m_StartOffset = maxs + mins;
		m_StartOffset *= 0.5f;
		m_Start = start + m_StartOffset;
		m_StartOffset *= -1.0f;
	}
};

class CBaseTrace
{
public:
	Vector3D_t startpos;
	Vector3D_t endpos;
	cplane_t plane;
	float fraction;
	int contents;
	unsigned short dispFlags;
	bool allsolid;
	bool startsolid;
};

struct csurface_t
{
	const char* name;
	short surfaceProps;
	unsigned short flags;
};

class CGameTrace : public CBaseTrace
{
public:
	// Returns true if hEnt points at the world entity.
	// If this returns true, then you can't use GetHitBoxIndex().
	bool DidHitWorld() const;

	// Returns true if we hit something and it wasn't the world.
	bool DidHitNonWorldEntity() const;

	// Gets the entity's network index if the trace has hit an entity.
	// If not, returns -1.
	int GetEntityIndex() const;

	// Returns true if there was any kind of impact at all
	bool DidHit() const;
public:
	float fractionleftsolid; // time we left a solid, only valid if we started in solid
	csurface_t surface; // surface hit (impact surface)

	int hitgroup; // 0 == generic, non-zero is specific body part
	short physicsbone; // physics bone hit by trace in studio

	#if defined( CLIENT_DLL )
	C_BaseEntity* m_pEnt;
	#else
	CBaseEntity_t* m_pEnt;
	#endif

	// NOTE: this member is overloaded.
	// If hEnt points at the world entity, then this is the static prop index.
	// Otherwise, this is the hitbox index.
	int hitbox; // box hit by trace in studio

	CGameTrace()
	{
	}

private:
	// No copy constructors allowed
	CGameTrace( const CGameTrace& vOther );
};


//-----------------------------------------------------------------------------
// Returns true if there was any kind of impact at all
//-----------------------------------------------------------------------------
inline bool CGameTrace::DidHit() const
{
	return fraction < 1 || allsolid || startsolid;
}


using trace_t = CGameTrace;

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity( CBaseEntity_t* pEntity, int contentsMask ) = 0;
	virtual TraceType_t GetTraceType() const = 0;
};

class CTraceFilter : public ITraceFilter
{
public:
	bool ShouldHitEntity( CBaseEntity_t* pEntityHandle, int contentsMask ) override
	{
		return !(pEntityHandle == pSkip);
	}

	TraceType_t GetTraceType() const override
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};

class CTraceFilterSkipTwoEntities : public ITraceFilter
{
public:
	CTraceFilterSkipTwoEntities( void* pPassEnt1, void* pPassEnt2 )
	{
		pSkip1 = pPassEnt1;
		pSkip2 = pPassEnt2;
	}

	bool ShouldHitEntity( CBaseEntity_t* pEntityHandle, int contentsMask ) override
	{
		return !(pEntityHandle == pSkip1 || pEntityHandle == pSkip2);
	}

	TraceType_t GetTraceType() const override
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip1;
	void* pSkip2;
};

class IEngineTrace_t
{
public:
	/*int	GetPointContents(const Vector3D_t& vecAbsPosition, IHandleEntity** ppEntity = NULL)
	{
		typedef int(__thiscall* fnGetPointContents)(void*, const Vector&, IHandleEntity**);
		return get_vfunc<fnGetPointContents>(this, 0)(this, vecAbsPosition, ppEntity);
	}*/

	/*void ClipRayToEntity(const Ray_t& ray, unsigned int fMask, IHandleEntity* pEnt, trace_t* pTrace)
	{
		typedef void(__thiscall* ClipRayToEntity_fn)(void*, const Ray_t& ray, unsigned int fMask, IHandleEntity* pEnt, trace_t* pTrace);
		get_vfunc<ClipRayToEntity_fn>(this, 2)(this, ray, fMask, pEnt, pTrace);
	}*/

	auto TraceRay( const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace )
	{
		return Hikari::Memory->VirtualCall<void, 4>( this, ray, fMask, pTraceFilter, pTrace );
	}
};
