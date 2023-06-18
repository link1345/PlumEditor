#include "main_menu.h"

#include <Siv3D.hpp>
#include <imgui.h>

void Plum::MainMenu::Main(bool& isMainWindow) {
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			Logger << U"File";
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("demo","CTRL+A")) {
			//Logger << U"demo";
			isMainWindow = true;
		}
		ImGui::EndMainMenuBar();
	}
}


void Plum::Plugin::MainWindow() {

	if (!this->isMainWindow) return;

	if(ImGui::Begin("test Plugin")) {

	}
	ImGui::End();

}
