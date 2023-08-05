#include "stdafx.h"

#include "main_menu.h"
#include "imgui_codeeditor.h"

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

int Plum::PluginItem_file::FileLoad(int _start, int _end) {

	std::ifstream ifs(this->file_path);

	if (ifs.fail()) {
		//std::cerr << "Failed to open file." << std::endl;
		return -1;
	}
	
	if (_start >= _end) return -2;

	this->code.clear();

	this->start = _start;
	this->end = _end;
	int count = 0;
	string tmp_code = "";

	this->isLoad = false;

	while (getline(ifs, tmp_code)) {
		//std::cout << "#" << code << std::endl;

		count++;

		if (_start > count) continue;
		else if (_end < count) break;

		this->code.push_back(tmp_code);
		//this->code = tmp_code.c_str();

		if (ifs.eof()) {
			this->end = count;
			break;
		}

	}
	this->isLoad = true;

	ifs.close();
	return 0;
}

void Plum::PluginItem_file::CodeWindow() {

	std::string window_name = "Code : " + this->file_path.filename().string();
		
	if (ImGui::Begin(window_name.c_str())) {

		int line_count = 0;
		for (auto& code_line : this->code) {
			line_count++;

			string line_text = std::to_string(line_count);
			line_text = std::string(std::max(0, 6 - (int)line_text.size()), ' ') + line_text;

			ImGui::TextColored(ImVec4(1, 1, 0, 1), line_text.c_str());
			ImGui::SameLine();
			ImGui::Text(code_line.c_str());
		}

	}
	ImGui::End();
}
