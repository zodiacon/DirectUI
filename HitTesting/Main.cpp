#include "..\DirectUI\DirectUI.h"

using namespace DirectUI;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int) {
	Application app;
	app.Initialize();

    bool yellow = false;

	Window mainWindow(L"Hit Testing Demo");
	mainWindow.ClearColor(Colors::Lime());

    DX::Color old[10];
	auto canvas = Create<CanvasLayout>();
	for (int i = 0; i < 10; i++) {
		auto grid = Create<UniformGridLayout>();
		float c = i / 10.0f;
		grid->Width(100).Height(100).Background(Create<SolidColorBrush>(DX::Color(c, c, c))).Width(100).Height(100);;
		auto tb = Create<TextBlock>();
		const wchar_t text[] = { (const wchar_t)(i + L'0'), L'\0' };
		tb->Foreground(Create<SolidColorBrush>(Colors::Red())).TextAlignment(TextAlignmentType::Center).Text(text).FontSize(30);
		grid->AddEventHandler<MouseEventArgs>(UIElement::MouseDownEvent, [&yellow](auto& source, const auto& args) -> bool {
			source.Background(yellow ? Brushes::Blue() : Brushes::Yellow());
            yellow = !yellow;
			return true;
		});
		grid->AddChild(tb);

		canvas->X(grid, i * 50.0f + 20);
		canvas->Y(grid, i * 50.0f + 20);
		canvas->AddChild(grid);
	}

	mainWindow.Content(canvas);

	return app.Run();
}