#include "stdafx.h"
#include "..\DirectUI\DirectUI.h"
#include <thread>
#include <atomic>

using namespace DirectUI;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int) {
	Application app;
	app.Initialize();

	Window window1(L"Hello, World!");
	auto stack = Create<StackLayout>();
	stack->Background(Create<SolidColorBrush>(Colors::DarkCyan()));

	auto r1 = Create<DirectUI::Rectangle>();
	r1->Fill(Create<SolidColorBrush>(Colors::Yellow()))->StrokeWidth(5)->Width(200)->Height(150);

	stack->AddChild(r1);

	auto r2 = Create<DirectUI::Rectangle>();
	r2->Fill(Create<SolidColorBrush>(Colors::Red()))->StrokeWidth(5)->Width(100)->Height(120);
	stack->AddChild(r2);

	auto r3 = Create<DirectUI::Ellipse>();
	r3->Fill(Create<SolidColorBrush>(Colors::LawnGreen()))->StrokeWidth(10)->Width(50)->Height(50);
	auto b1 = Create<SolidColorBrush>(Colors::Orange());
	b1->Opacity(.6f);
	r3->Stroke(b1);
	stack->AddChild(r3);

	window1.Content(stack);

	auto b3 = Create<SolidColorBrush>(Colors::DarkCyan());
	auto b4 = Create<SolidColorBrush>(Colors::LightBlue());
	std::atomic<bool> done(false);

	auto t = std::thread([&done](auto r1, auto b3, auto b4) {
		while (!done) {
			r1->Fill(b3);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			r1->Fill(b4);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}, r1, b3, b4);

	auto rv = app.Run();
	done = true;
	t.join();
	return rv;
}




