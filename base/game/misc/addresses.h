#pragma once

namespace Game::Addresses
{
    void Setup();

    // engine.dll
    inline Hikari::Address_t Paint;

    // client.dll
    inline Hikari::Address_t CalcView;
    inline Hikari::Address_t GetCSWepData;
    inline Hikari::Address_t GetActiveWeapon;
    inline Hikari::Address_t SetupBones;
    inline Hikari::Address_t GetDataDescMap;
    inline Hikari::Address_t GetPredDataMap;

    // matsurface.dll
    inline Hikari::Address_t StartDrawing;
    inline Hikari::Address_t FinishDrawing;

    inline Hikari::Address_t GetListenServerHost;
}