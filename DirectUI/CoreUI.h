#pragma once

#include "Core.h"
#include "Brushes.h"

#define DECLARE_CONVERT(target, source, name)	\
	target name(source value);

#define DEFINE_CONVERT(target, source, name)	\
	inline target name(source value) { return static_cast<target>(value); }

namespace DirectUI {
	struct Thickness {
		float Left, Top, Right, Bottom;

		Thickness(float left, float top, float right, float bottom)
			: Left(left), Top(top), Right(right), Bottom(bottom) { }
		Thickness(float uniform = 0) : Thickness(uniform, uniform, uniform, uniform) { }
		Thickness(float width, float height) : Thickness(width, height, width, height) { }
	};

	class Visual abstract : public DependencyObject {
	};

	enum class HorizontalAlignmentType {
		Left, Right, Center, Stretch
	};

	enum class VerticalAlignmentType {
		Top, Bottom, Center, Stretch
	};

	enum class MouseButton {
		None,
		Left = MK_RBUTTON,
		Middle = MK_MBUTTON,
		Right = MK_RBUTTON,
		AllButtons = Left | Middle | Right
	};

	struct MouseEventArgs {
		MouseButton Button;
		DX::Point2F Position;
	};

	enum class VisibilityType {
		Visible,
		Hidden,
		Collapsed
	};

	using MouseEventHandler = std::function<bool(UIElement&, const MouseEventArgs&)>;

	class UIElement abstract : public Visual {
		friend class Window;

		DECLARE_DP(UIElement, IsEnabled, bool);
		DECLARE_DP(UIElement, Visibility, VisibilityType);
		DECLARE_DP(UIElement, Margin, Thickness);
		DECLARE_DP(UIElement, Background, Ref<Brush>);
		DECLARE_DP(UIElement, Width, float);
		DECLARE_DP(UIElement, Height, float);
		DECLARE_DP(UIElement, HorizontalAlignment, HorizontalAlignmentType);
		DECLARE_DP(UIElement, VerticalAlignment, VerticalAlignmentType);
		DECLARE_DP(UIElement, UserData, PVOID);

	private:
		UIElement(const UIElement&) = delete;
		UIElement& operator=(const UIElement&) = delete;

	public:
		virtual bool IsUIElement() const {
			return true;
		}

		UIElement* GetParent() const {
			return _parent;
		}

		void Draw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds);
		virtual void Measure(const DX::SizeF& size) = 0;
		UIElement* HitTest(const DX::Point2F& point);

		const DX::SizeF& GetDesiredSize() const {
			return _desiredSize;
		}

		void SetParent(UIElement* parent) {
			ASSERT(_parent == nullptr);
			_parent = parent;
		}

		UIElement& MouseDown(const MouseEventHandler& handler) {
			_mouseDownHandlers.push_back(handler);
			return *this;
		}

		const DX::RectF& GetBounds() const {
			return _bounds;
		}

		void Invalidate() override;

	protected:
		virtual void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) = 0;

		virtual UIElement* HitTestCore(const DX::Point2F& point) {
			return false;
		}

	protected:
		// event dispatchers
		void OnMouseDown(UIElement& source, const MouseEventArgs& args) {
			bool handled = false;
			for (auto& handler : _mouseDownHandlers)
				if (handled = handler(source, args))
					break;

			UIElement* parent;
			if (!handled && (parent = GetParent())) {
				parent->OnMouseDown(source, args);
			}
		}

	protected:
		UIElement() : _parent(nullptr) {
		}

		void SetDesiredSize(const DX::SizeF& size) {
			_desiredSize = size;
		}

	private:
		DX::SizeF _desiredSize;
		UIElement* _parent;
		DX::RectF _bounds;

		// events
		std::vector<MouseEventHandler> _mouseDownHandlers, _mouseUpHandlers, _mouseMoveHandlers;
	};

	class Control abstract : public UIElement {
		DECLARE_DP(UIElement, Padding, Thickness);
		DECLARE_DP(UIElement, FontSize, float);
		DECLARE_DP(UIElement, FontFamily, std::string);
		DECLARE_DP(UIElement, FontWeight, DX::DirectWrite::FontWeight);
		DECLARE_DP(UIElement, FontStyle , DX::DirectWrite::FontStyle);
	};

	class ContentControl : public Control {
		DECLARE_DP(ContentControl, Content, Ref<UIElement>);

	protected:
		void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) override;
	};
}
