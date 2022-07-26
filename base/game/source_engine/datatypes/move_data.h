#pragma once

class Angle_t;
class Vector3D_t;

struct CMoveData
{
	bool m_bFirstRunOfFunctions;  // 0
	bool m_bGameCodeMovedPlayer;  // 2
	// bool m_bNoAirControl;         // 0
	void* m_nPlayerHandle;            // 4
	int m_nImpulseCommand;            // 8
	Angle_t m_vecViewAngles;           // 12, 16, 20
	Angle_t m_vecAbsViewAngles;        // 24, 28, 32
	int m_nButtons;                   // 36
	int m_nOldButtons;                // 40
	float m_flForwardMove;            // 44
	float m_flSideMove;               // 48
	float m_flUpMove;                 // 52
	float m_flMaxSpeed;               // 56
	float m_flClientMaxSpeed;         // 60
	Vector3D_t m_vecVelocity;             // 64, 68, 72
	Angle_t m_vecAngles;               // 76, 80, 84
	Angle_t m_vecOldAngles;            // 88, 92, 96
	float m_outStepHeight;            // 100
	Vector3D_t m_outWishVel;              // 104, 108, 112
	Vector3D_t m_outJumpVel;              // 116, 120, 124
	Vector3D_t m_vecConstraintCenter;     // 128, 132, 136
	float m_flConstraintRadius;       // 140
	float m_flConstraintWidth;        // 144
	float m_flConstraintSpeedFactor;  // 148
	bool m_bConstraintPastRadius;     // 154
	Vector3D_t m_vecAbsOrigin;            // 156
};