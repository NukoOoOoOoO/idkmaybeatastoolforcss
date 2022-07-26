#pragma once
#define MAXSTUDIOBONES 128

#define BONE_USED_MASK				0x0007FF00
#define BONE_USED_BY_ANYTHING		0x0007FF00
#define BONE_USED_BY_HITBOX			0x00000100	// bone (or child) is used by a hit box
#define BONE_USED_BY_ATTACHMENT		0x00000200	// bone (or child) is used by an attachment point
#define BONE_USED_BY_VERTEX_MASK	0x0003FC00
#define BONE_USED_BY_VERTEX_LOD0	0x00000400	// bone (or child) is used by the toplevel model via skinned vertex
#define BONE_USED_BY_VERTEX_LOD1	0x00000800
#define BONE_USED_BY_VERTEX_LOD2	0x00001000
#define BONE_USED_BY_VERTEX_LOD3	0x00002000
#define BONE_USED_BY_VERTEX_LOD4	0x00004000
#define BONE_USED_BY_VERTEX_LOD5	0x00008000
#define BONE_USED_BY_VERTEX_LOD6	0x00010000
#define BONE_USED_BY_VERTEX_LOD7	0x00020000
#define BONE_USED_BY_BONE_MERGE		0x00040000	// bone is available for bone merge to occur against it

struct model_t;

struct mstudiobbox_t
{
    int bone;
    int group;
    Vector3D_t bbmin;
    Vector3D_t bbmax;
    int szhitboxnameindex;
    int pad00[3];
    float pillradius;
    int pad01[4];
};

struct mstudiohitboxset_t
{
    int sznameindex;

    char* const pszName( void ) const
    {
        return ((char*)this) + sznameindex;
    }

    int numhitboxes;
    int hitboxindex;

    mstudiobbox_t* pHitbox( int i ) const
    {
        return reinterpret_cast<mstudiobbox_t*>(((BYTE*)this) + hitboxindex) + i;
    };
};

struct mstudiobone_t
{
    int sznameindex;

    char* const GetName( void ) const
    {
        return ((char*)this) + sznameindex;
    }

    int parent;
    int bonecontroller[6];

    Vector3D_t pos;
    float quat[4];
    Vector3D_t rot;
    Vector3D_t posscale;
    Vector3D_t rotscale;

    matrix3x4_t poseToBone;
    float qAlignment[4];
    int flags;
    int proctype;
    int procindex; // procedural rule
    mutable int physicsbone; // index into physically simulated bone
    void* GetProcedure() const
    {
        if ( procindex == 0 )
            return nullptr;
        return (BYTE*)this + procindex;
    };
    int surfacepropidx; // index into string tablefor property name
    char* const GetSurfaceProps( void ) const
    {
        return ((char*)this) + surfacepropidx;
    }

    int contents; // See BSPFlags.h for the contents flags

    int unused[8]; // remove as appropriate
};

struct studiohdr_t
{
private:
    char pad00[12];
public:
    char name[64];
private:
    char pad01[80];
public:
    int numbones;
    int boneindex;
private:
    char pad02[12];
public:
    int hitboxsetindex;
private:
    char pad03[228];
public:
    mstudiobone_t* GetBone( int i ) const
    {
        return reinterpret_cast<mstudiobone_t*>((unsigned char*)this + boneindex) + i;
    }

    // Look up hitbox set by index
    mstudiohitboxset_t* pHitboxSet( int i ) const
    {
        return reinterpret_cast<mstudiohitboxset_t*>(((unsigned char*)this) + hitboxsetindex) + i;
    }

    // Calls through to hitbox to determine size of specified set
    mstudiobbox_t* pHitbox( int i, int set ) const
    {
        const mstudiohitboxset_t* s = pHitboxSet( set );
        if ( !s )
            return nullptr;

        return s->pHitbox( i );
    }

    // Calls through to set to get hitbox count for set
    int iHitboxCount( int set ) const
    {
        const mstudiohitboxset_t* s = pHitboxSet( set );
        if ( !s )
            return 0;

        return s->numhitboxes;
    }
};

struct DrawModelState_t
{
    studiohdr_t* _studioHdr;
    void* _studioHardwareData;
    void* _renderable;
    const matrix3x4_t* _modelToWorld;
    void* _decals;
    int _drawFlags;
    int _lod;
};

struct draw_model_info_t
{
    studiohdr_t* _studioHdr;
    void* _studioHardwareData;
    void* _decals;
    int _skin;
    int _body;
    int _hitboxSet;
    void* _renderable;
    int _lod;
    void* _pColorMeshes;
    bool _bStaticLighting;
    Vector3D_t _vecAmbientCube[6]; // ambient, and lights that aren't in locallight[]
    int _localLightCount;
    int _localLightDescs[4];
};
