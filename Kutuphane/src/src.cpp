#include "mainHeader.h"

int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

	std::ofstream fileF;
	fileF.open("Database.txt");
	fileF << "Final\n";
	fileF.close();

	ClassBook book1(1, "Name");

	MainWindow win;

	if (!win.Create(L"Main Window", WS_OVERLAPPEDWINDOW)) {
		return 0;
	}

	ShowWindow(win.Window(), nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
 }