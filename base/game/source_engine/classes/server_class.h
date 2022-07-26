#pragma once

class SendTable;
struct RecvProp;

using ArrayLengthSendProxy_fn = int(*)( const void*, int );
using SendVarProxy_fn = void(*)( const void*, const void*, const void*, void*, int, int );
using SendTableProxy_fn = void* (*)( const void*, const void*, const void*, void*, int );

typedef enum {
    DPT_Int = 0,
    DPT_Float,
    DPT_Vector,
    DPT_VectorXY,
    DPT_String,
    DPT_Array,
    DPT_DataTable,
    DPT_Int64,
    DPT_NUMSendPropTypes
} SendPropType;

class SendProp
{
public:
    RecvProp* pMatchingRecvProp; // This is temporary and only used while precalculating
    // data for the decoders.

    SendPropType iType;
    int iBits;
    float flLowValue;
    float flHighValue;

    SendProp* pArrayProp; // If this is an array, this is the property that defines each array element.
    ArrayLengthSendProxy_fn pArrayLengthProxy; // This callback returns the array length.

    int iElements; // Number of elements in the array (or 1 if it's not an array).
    int iElementStride; // Pointer distance between array elements.

    const char* szExcludeDTName; // If this is an exclude prop, then this is the name of the datatable to exclude a prop from.
    const char* szParentArrayPropName;

    int pad;

    const char* szVarName;
    float flHighLowMul;

    //private:

    int iFlags; // SPROP_ flags.

    SendVarProxy_fn pProxyfn; // NULL for DPT_DataTable.
    SendTableProxy_fn pDataTableProxyfn; // Valid for DPT_DataTable.

    SendTable* pDataTable;

    // SENDPROP_VECTORELEM makes this negative to start with so we can detect that and
    // set the SPROP_IS_VECTOR_ELEM flag.
    int iOffset;

    // Extra data bound to this property.
    const void* pExtraData;
};

class SendTable
{
public:
    SendProp* pProps;
    int iTotalProps;

    const char* szNetTableName; // The name matched between client and server.

    // The engine hooks the SendTable here.
    void* pPrecalc;
protected:
    bool bInitialized : 1;
    bool bHasBeenWritten : 1;
    bool bHasPropsEncodedAgainstCurrentTickCount : 1; // m_flSimulationTime and m_flAnimTime, e.g.
};

class ServerClass
{
public:
    const char* szNetworkName;
    SendTable* pTable;
    ServerClass* pNext;
    int iClassID; // Managed by the engine.

    // This is an index into the network string table (sv.GetInstanceBaselineTable()).
    int iInstanceBaselineIndex; // INVALID_STRING_INDEX if not initialized yet.
};
