#pragma once

#include <imgui.h>

#include "main_menu.h"

namespace ImGui {
	bool InputTextCodeEditor(const char* label, Plum::PluginItem_file& buf_orig, ImGuiInputTextFlags flags = 0, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
}
