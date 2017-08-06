#include "pch.h"
#include "Application.h"
#include "Window.h"

using namespace DirectUI;
using namespace std;

Application* Application::_app;

Application::Application() {
	if (_app)
		throw std::exception("only a single Application object must exist");
	_app = this;

}

bool Application::Initialize() {
	if (!RegisterWindowClass())
		return false;

	_d2dfactory = DX::Direct2D::CreateFactory();
	if (!_d2dfactory)
		return false;

	_dwriteFactory = DX::DirectWrite::CreateFactory();

	_d3dDevice = DX::Direct3D::CreateDevice();

	OnInit();
	return true;
}

bool Application::RegisterWindowClass() {
	WNDCLASS wc {};
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hInstance = ::GetModuleHandle(nullptr);
	wc.lpszClassName = DirectUIWindowClassName;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = TopLevelWindowProc;
	return ::RegisterClass(&wc) ? true : false;
}

void Application::CreateDeviceSwapChainBitmap(const DX::Dxgi::SwapChain& swapChain, const DX::Direct2D::DeviceContext& target) {
	using namespace DX::Direct2D;
	using namespace DX;

	auto props = BitmapProperties1(BitmapOptions::Target | BitmapOptions::CannotDraw,
		PixelFormat(Dxgi::Format::B8G8R8A8_UNORM, AlphaMode::Ignore));

	target.SetTarget(target.CreateBitmapFromDxgiSurface(swapChain, props));
}

void Application::RemoveWindow(HWND hWnd) {
	_windows.erase(hWnd);
	if (_windows.size() == 0)
		::PostQuitMessage(0);
}

bool Application::CreateDeviceContextAndSwapChain(HWND hWnd, DX::Direct2D::DeviceContext& dc, DX::Dxgi::SwapChain1& swapChain) {
	using namespace DX;

	dc = _d2dfactory.CreateDevice(_d3dDevice).CreateDeviceContext();
	ASSERT(dc);
	auto dxgi = _d3dDevice.GetDxgiFactory();

	Dxgi::SwapChainDescription1 description;
	description.SwapEffect = Dxgi::SwapEffect::Discard;

	swapChain = dxgi.CreateSwapChainForHwnd(_d3dDevice, hWnd, description);
	ASSERT(swapChain);
	CreateDeviceSwapChainBitmap(swapChain, dc);
	
	const auto dpi = _d2dfactory.GetDesktopDpi();
	dc.SetDpi(dpi, dpi);

	return true;
}

LRESULT Application::TopLevelWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return Current()->WindowProc(hWnd, message, wParam, lParam);
}

LRESULT Application::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	auto it = _windows.find(hWnd);
	if (it == _windows.end())
		return ::DefWindowProc(hWnd, message, wParam, lParam);

	return it->second->WindowProc(message, wParam, lParam);
}

void Application::OnInit() {
	::CoInitialize(nullptr);
}

void Application::OnExit() {
	::CoUninitialize();
}

int Application::Run() {
	MSG msg;
	while (auto result = GetMessage(&msg, 0, 0, 0)) {
		if (-1 != result) 
			DispatchMessage(&msg);
	}

	return 0;
}
