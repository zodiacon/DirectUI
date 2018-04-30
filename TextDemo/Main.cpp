#include "..\DirectUI\DirectUI.h"

using namespace DirectUI;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int) {
	Application app;
	app.Initialize();

	Window mainWindow(L"Text Demo");
	mainWindow.ClearColor(Colors::LightGray());

	auto tb = Create<TextBlock>();
	tb->Text(L"Hello, TextBlock!")->Foreground(Brushes::Black())->FontSize(30);

	mainWindow.Content(tb);

	return app.Run();
}