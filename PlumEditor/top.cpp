#include "stdafx.h"
#include "top.h"

namespace Plum {

	void Top::Main() {
		this->topMenu.Main(this->pluginWindow.isMainWindow);

		this->pluginWindow.MainWindow();
	}

}

