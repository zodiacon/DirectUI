#include "..\DirectUI\DirectUI.h"

using namespace DirectUI;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int) {
	Application app;
	app.Initialize();

	Window mainWindow(L"CanvasLayout Demo");
	mainWindow.ClearColor(Colors::Brown());

	auto canvas = Create<CanvasLayout>();
	auto e1 = Create<DirectUI::Ellipse>();
	e1->Fill(Create<SolidColorBrush>(Colors::Red()))->Width(100)->Height(100);
	canvas->X(e1, 50);
	canvas->Y(e1, 50);
	canvas->AddChild(e1);

	auto r1 = Create<DirectUI::Rectangle>();
	r1->Fill(Create<SolidColorBrush>(Colors::Cyan()))->Width(200)->Height(150);
	canvas->X(r1, 230);
	canvas->Y(r1, 350);
	canvas->AddChild(r1);

	mainWindow.Content(canvas);

	app.Run();

	return 0;
}
