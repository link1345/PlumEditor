#pragma once

namespace Plum {

	class MainMenu {
	public:
		void Main(bool &isMainWindow);
	};

	class Plugin {
	public :
		Plugin() {
			this->isMainWindow = false;
		}

		bool isMainWindow;

		void MainWindow();
	};
}
