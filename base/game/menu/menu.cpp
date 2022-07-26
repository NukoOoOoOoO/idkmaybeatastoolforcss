#include "../../framework.h"
#include "../game.h"
#include "menu.h"
#include "../../thirdparty/imgui/imgui.h"
#include "../config.h"
#include "../../thirdparty/imgui/imgui_stdlib.h"
#include "fonts.h"

namespace Game::Menu
{

	void Render()
	{
		if ( !menuOpen )
			return;

		/*auto screenSize = ImGui::GetWindowSize();
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(-1, -1));
		ImGui::SetNextWindowSizeConstraints(ImVec2(screenSize.x, screenSize.y), ImVec2(screenSize.x, screenSize.y));
		ImGui::SetNextWindowPos({ 0,0 });*/

		constexpr auto menuSize = ImVec2{916, 646};
		ImGui::SetNextWindowSize( menuSize );

		if ( ImGui::Begin( "ligma", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar ) )
		{
			
		}
		ImGui::End();
	}
}
