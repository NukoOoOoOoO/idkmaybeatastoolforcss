#pragma once

class CVerifiedUserCmd
{
public:
    CUserCmd m_cmd;
    CRC32_t m_crc{};
};

struct IInput_t
{
private:
    std::byte pad1[0x8C]{}; //0x0000
public:
    bool m_fCameraIntercerptingMouse; //0x008C 
    bool m_fCameraInThirdPerson; //0x008D 
private:
    std::byte pad2[0x16]{}; //0x008E
public:
    Angle_t m_angPreviousViewAngles; //0x00A4 
    float m_flLastForwardMove; //0x00B0 
private:
    std::byte pad3[0x10]{}; //0x00B4
public:
    CUserCmd* m_pCommands; //0x00C4 
    CVerifiedUserCmd* m_pVerifiedCommands; //0x00C8 
};
