#pragma once

#include "CoreUI.h"

namespace DirectUI {
	class Window : public ContentControl {
		friend class Application;

		DECLARE_DP(Window, ClearColor, DX::Color);

	public:
		Window(const wchar_t* = nullptr);

		static Window* GetCurrent() {
			return _current;
		}

		virtual ~Window() {
			ReleaseDevice();
		}

		virtual void Render();
		void Measure(const DX::SizeF&) override { }

		void Invalidate(const DX::RectF& rect);

	protected:
		void Draw(DX::Direct2D::DeviceContext& dc);

		UIElement* HitTestCore(const DX::Point2F& point) override {
			return nullptr;
		}

		DX::Direct2D::DeviceContext& GetDeviceContext() {
			return _dc;
		}

		DX::Dxgi::SwapChain1& GetSwapChain() {
			return _swapChain;
		}

		bool ResizeSwapChainBitmap();
		void ReleaseDevice();

	private:
		LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

		std::tuple<UIElement*, MouseEventArgs> GetMouseEventArgs(WPARAM, LPARAM);

	private:
		HWND _hWnd;
		DX::Direct2D::DeviceContext _dc;
		DX::Dxgi::SwapChain1 _swapChain;
		static Window* _current;
	};

}
