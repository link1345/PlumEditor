#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <list>

#include <fstream>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;

namespace Plum {

	class MainMenu {
	public:
		void Main(bool &isMainWindow);
	};

	class PluginItem_file {
	public :
		PluginItem_file() {
			this->isWindowOpen = false;

			this->code = std::list<string>();

		}

		int FileLoad(int start , int end);

		/// @brief プラグインのファイル
		std::filesystem::path file_path;

		/// @brief プラグインのウィンドウ開いているか？
		bool isWindowOpen;

		std::list<string> code;

		int hasStart() {
			return this->start;
		}
		int hasEnd() {
			return this->end;
		}

		void CodeWindow();


	private:
		int start;
		int end;
	};

	class PluginItem {
	public :
		PluginItem() {
			plugin_file = std::list<PluginItem_file>();
		}

		/// @brief プラグインのフォルダ
		std::filesystem::path folder_path;

		/// @brief プラグインのファイル一覧
		std::list<PluginItem_file> plugin_file;

		// ここに何かconfigなどあったら追記する
	};

	class Plugin {
	public :
		Plugin() {
			this->isMainWindow = false;

			this->plugin_list = std::list<PluginItem>();

			this->init_plugin();
		}

		/// @brief プラグインの一覧初期化
		void init_plugin() {
			plugin_list.clear();

			for (const auto& pl_file : directory_iterator("./plugin/")) {

				if (!pl_file.is_directory()) continue;

				PluginItem item = PluginItem();
				item.folder_path = pl_file.path();

				for (const auto& file : directory_iterator(item.folder_path)) {
					PluginItem_file item_file = PluginItem_file();
					item_file.file_path = file;
					item.plugin_file.push_back( item_file );
				}

				plugin_list.push_back(item);
			}
		}

		/// @brief プラグインの一覧ウィンドウが開いているか？
		bool isMainWindow;

		/// @brief ウィンドウのプログラム
		void MainWindow();

		//void PluginWindow();

		/// @brief プラグインのリスト
		std::list<PluginItem> plugin_list;
	};
}
