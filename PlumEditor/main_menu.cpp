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

	if(ImGui::Begin("Plugin List")) {

		for (auto& item : this->plugin_list) {
			if ( ImGui::CollapsingHeader(item.folder_path.filename().string().c_str()) )
			{
				for (auto& item_file : item.plugin_file) {

					bool item_Click = item_file.isWindowOpen;

					ImGui::Selectable( item_file.file_path.filename().string().c_str(), &item_Click);

					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
					{
						// Do stuff on Selectable() double click.                                                                                                                                                                                                                           
						item_file.isWindowOpen = !item_Click;
					}

					// 「今、開いた」場合、ロード処理を掛ける
					if (item_file.isWindowOpen && item_file.isWindowOpen != item_Click) {
						item_file.FileLoad(0,100);
					}

					// 「開いている」場合、表示する
					if (item_file.isWindowOpen ) {
						//ImGui::Text("hello!");

						item_file.CodeWindow();


					}
				}
			}
		}
	}
	ImGui::End();

}

/*
void Plum::Plugin::PluginWindow() {
	for (auto& item : this->plugin_list) {

		for (auto& item_file : item.plugin_file) {

			if (ImGui::Begin( item_file.file_path.filename().string().c_str() )) {

				

			}
			ImGui::End();

		}

	}
}
*/

int Plum::PluginItem_file::FileLoad(int start, int end) {

	this->code.clear();

	std::ifstream ifs(this->file_path);

	if (ifs.fail()) {
		//std::cerr << "Failed to open file." << std::endl;
		return -1;
	}

	if (start >= end) return -2;

	this->start = start;
	this->end = end;

	int count = 0;

	string tmp_code = "";

	while (getline(ifs, tmp_code)) {
		//std::cout << "#" << code << std::endl;

		count++;

		if (start > count) continue;
		else if (end < count) break;

		this->code.push_back(tmp_code);

		if (ifs.eof()) {
			this->end = count;
			break;
		}

	}

	ifs.close();

}

void Plum::PluginItem_file::CodeWindow() {

	std::string window_name = "Code : " + this->file_path.filename().string();

	if (ImGui::Begin(window_name.c_str())) {
		for (auto& code_line : this->code) {

			ImGui::Text(code_line.c_str());

		}
	}
	ImGui::End();
}
