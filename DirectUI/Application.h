#pragma once

#include "Core.h"

namespace DirectUI {
	class Window;

	static const wchar_t* DirectUIWindowClassName = L"DirectUIWindowClassName";

	class Application : public DependencyObject {
		friend class Window;

	public:
		Application();

		static Application* Current() {
			return _app;
		}

		bool Initialize();
		virtual int Run();

		DX::Direct2D::Factory1& D2DFactory() {
			return _d2dfactory;
		}

		DX::DirectWrite::Factory2& DWriteFactory() {
			return _dwriteFactory;
		}

        float GetDpi() const {
            return _dpi;
        }

	protected:
		virtual void OnInit();
		virtual void OnExit();

		virtual bool RegisterWindowClass();

		virtual LRESULT WindowProc(HWND, UINT, WPARAM, LPARAM);

		bool CreateDeviceContextAndSwapChain(HWND, DX::Direct2D::DeviceContext& dc, DX::Dxgi::SwapChain1& swapChain);

	private:
		static LRESULT CALLBACK TopLevelWindowProc(HWND, UINT, WPARAM, LPARAM);
		static void CreateDeviceSwapChainBitmap(const DX::Dxgi::SwapChain& swapChain, const DX::Direct2D::DeviceContext& target);
		static bool ResizeSwapChainBitmap(DX::Direct2D::DeviceContext& target);
		void RemoveWindow(HWND hWnd);

		void AddWindow(HWND hWnd, Window* window) {
			_windows[hWnd] = window;
		}

	private:
		std::map<HWND, Window*> _windows;
		DX::Direct3D::Device1 _d3dDevice;
		DX::Direct2D::Factory1 _d2dfactory;
		DX::Dxgi::SwapChain1 _swapChain;
		DX::DirectWrite::Factory2 _dwriteFactory;
        float _dpi;

		static Application* _app;
	};
}

