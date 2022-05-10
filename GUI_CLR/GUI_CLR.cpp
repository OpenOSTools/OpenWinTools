#include "pch.h"
#include <windows.h>
#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	if (Environment::OSVersion->Version->Major >= 6)
		SetProcessDPIAware();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

    System::Windows::Forms::Application::Run(gcnew GUICLR::MainForm);
    return 0;
}

