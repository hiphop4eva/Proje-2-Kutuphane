#include "mainHeader.h"

int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

	MainWindow win;

	readDatabase();

	if (!win.Create(L"Main Window", WS_OVERLAPPEDWINDOW)) {
		return 1;
	}

	ShowWindow(win.Window(), nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
 }