#pragma once

namespace Game
{
	struct Config_t
	{
		struct Aimbot_t
		{
			bool enabled{};
			bool onKey{};
			int key{};
			float fov{};
			std::unordered_map<int, bool> hitboxes;
		};

		struct AntiAim_t
		{
			bool enabled{};
			int pitch{};
			int realYaw{};
			int fakeYaw{};
			float spinSpeed{};
		};

		struct Visual_t
		{
			struct Player_t
			{
				bool bbox{};
				bool health{};
				bool name{};
				bool weapon{};
				bool ammo{};
				bool flags{};
			};

			Player_t player;
		};

		Aimbot_t aimbot;
		AntiAim_t antiaim;
		Visual_t visual;
	};

	inline Config_t Config;
}
