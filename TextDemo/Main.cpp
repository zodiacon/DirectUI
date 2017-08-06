#include "..\DirectUI\DirectUI.h"

using namespace DirectUI;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int) {
	Application app;
	app.Initialize();

	Window mainWindow(L"Text Demo");
	mainWindow.ClearColor(Colors::LightGray());

	auto tb = Create<TextBlock>();
	tb->FontSize(30).Text(L"Hello, TextBlock!").Foreground(Brushes::Black());

	mainWindow.Content(tb);

	return app.Run();
}