// HelloWorld.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "HelloWorld.h"

using namespace DirectUI;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR lpCmdLine, int) {
	Application app;

	Window window1(L"Hello, World!");
	auto stack = Create<StackLayout>();
	stack->Background(Create<SolidColorBrush>(Colors::DarkCyan()));

	auto r1 = Create<DirectUI::Rectangle>();
	r1->Fill(Create<SolidColorBrush>(Colors::Yellow())).StrokeWidth(5).Width(200).Height(150).MouseDown([](auto& src, const auto& args) {
		auto button = args.Button;
		int zz = 9;
		return false;
	});

	stack->AddChild(r1);
	
	auto r2 = Create<DirectUI::Rectangle>();
	r2->Fill(Create<SolidColorBrush>(Colors::Red())).StrokeWidth(5).Width(100).Height(120);
	stack->AddChild(r2);

	auto r3 = Create<DirectUI::Ellipse>();
	r3->Fill(Create<SolidColorBrush>(Colors::LawnGreen())).StrokeWidth(10).Width(50).Height(50);
	auto b1 = Create<SolidColorBrush>(Colors::Orange());
	b1->Opacity(.6f);
	r3->Stroke(b1);
	stack->AddChild(r3);

	window1.Content(stack);
	window1.MouseDown([](auto& source, const auto& args) {
		int zz = 9;
		return true;
	});
	return app.Run();

}




