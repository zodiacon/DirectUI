#include "pch.h"
#include "Window.h"
#include "Application.h"
#include "Colors.h"
#include "Buttons.h"

using namespace DirectUI;
using namespace DX;

Window* Window::_current = nullptr;

DEFINE_DP_WITH_FLAGS(Window, ClearColor, Color, Colors::BlueViolet(), PropertyMetadataFlags::AffectsRender);

Window::Window(const wchar_t* title) {
	_hWnd = ::CreateWindowW(DirectUIWindowClassName, title, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, ::GetModuleHandle(nullptr), nullptr);

	if (!_hWnd)
		throw std::exception("Failed to create window");

	SetWindow(this);
	Application::Current()->AddWindow(_hWnd, this);

	ContentProperty.RegisterPropertyChangedHandler(this, [this](auto&, auto&, auto& oldContent, auto& newContent) {
		if (oldContent) {
//			oldContent->SetParent(nullptr);
			oldContent->SetWindow(nullptr);
		}
		if (newContent) {
//			newContent->SetParent(this);
			newContent->SetWindow(this);
		}
	});
}

bool Window::ResizeSwapChainBitmap()
{
	_dc.SetTarget();

	if (S_OK == _swapChain.ResizeBuffers()) {
		Application::CreateDeviceSwapChainBitmap(_swapChain, _dc);
		return true;
	}
	else
	{
		ReleaseDevice();
		return false;
	}
}

void Window::ReleaseDevice() {
	_dc.Reset();
	_swapChain.Reset();
}

LRESULT Window::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) {
	using namespace std;

	switch (message) {
	case WM_PAINT:
		PAINTSTRUCT ps;
		::BeginPaint(_hWnd, &ps);
		Render();
		::EndPaint(_hWnd, &ps);
		break;

	case WM_DISPLAYCHANGE:
		Render();
		break;

	case WM_DESTROY:
		Application::Current()->RemoveWindow(_hWnd);

		break;

    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_LBUTTONDOWN:
        DispatchMouseEvent(UIElement::MouseDownEvent, wParam, lParam);
        return 0;

    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    case WM_LBUTTONUP:
        DispatchMouseEvent(UIElement::MouseUpEvent, wParam, lParam);
        return 0;

    case WM_MOUSEMOVE:
        DispatchMouseEvent(UIElement::MouseMoveEvent, wParam, lParam);
        return 0;

    case WM_LBUTTONDBLCLK:
        DispatchMouseEvent(UIElement::MouseDoubleClickEvent, wParam, lParam);
        return 0;

	case WM_SIZE:
		if (SIZE_MINIMIZED != wParam) {
			if (ResizeSwapChainBitmap()) {
				Render();
			}
		}
		break;
	}

	return ::DefWindowProc(_hWnd, message, wParam, lParam);
}

void Window::DispatchMouseEvent(RoutedEvent<MouseEventArgs>& event, WPARAM wParam, LPARAM lParam) {
    auto args = GetMouseEventArgs(wParam, lParam);
    auto source = std::get<0>(args);
    event.RaiseEvent(*source, std::get<1>(args));
}

std::tuple<UIElement*, MouseEventArgs> Window::GetMouseEventArgs(WPARAM wParam, LPARAM lParam) {
	MouseEventArgs args;
	args.Button = static_cast<MouseButton>(wParam & static_cast<WPARAM>(MouseButton::AllButtons));
    args.Keys = static_cast<MouseKeys>(wParam & static_cast<WPARAM>(MouseKeys::AllKeys));
	int x = GET_X_LPARAM(lParam), y = GET_Y_LPARAM(lParam);
    float dpi = Application::Current()->GetDpi();

    Point2F point(x * 96 / dpi, y * 96 / dpi);
    args.Position = point;

	UIElement* source = this;
	auto content = Content();
	if (content) {
		source = content->HitTest(point);
	}
	if (source == nullptr)
		source = this;

	return std::make_tuple(source, args);
}

void Window::Render() {
	using namespace DX;

	if (!_dc) {
		bool success = Application::Current()->CreateDeviceContextAndSwapChain(_hWnd, _dc, _swapChain);
		ASSERT(success);
	}

	_current = this;

    if (_isLayoutInvalid) {
        auto content = Content();
        if (content)
            content->Measure(_dc.GetSize());
        _isLayoutInvalid = false;
    }

	_dc.BeginDraw();
	_dc.Clear(ClearColor());
	Draw(_dc);
	_dc.EndDraw();

	_current = nullptr;

	_swapChain.Present();
}

void Window::Invalidate() {
    ::InvalidateRect(_hWnd, nullptr, FALSE);
}

void Window::Invalidate(const DX::RectF & rect) {
    if (rect.IsEmpty())
        return;

	RECT rc = { (int)rect.Left, (int)rect.Top, (int)rect.Right, (int)rect.Bottom };
	::InvalidateRect(_hWnd, &rc, FALSE);
}

void Window::InvalidateLayout(bool invalid) {
    _isLayoutInvalid = invalid;
    Invalidate();
}

void Window::Draw(Direct2D::DeviceContext& dc) {
	auto size = dc.GetSize();
	auto& content = Content();
	if (content)
		content->Draw(dc, RectF(0, 0, size.Width, size.Height));
}
