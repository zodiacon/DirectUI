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
		Left = MK_LBUTTON,
		Middle = MK_MBUTTON,
		Right = MK_RBUTTON,
		AllButtons = Left | Middle | Right
	};

    enum class MouseKeys { 
        Shift = 4,
        Control = 8,
        AllKeys = Shift | Control
    };
    DEFINE_ENUM_FLAG_OPERATORS(MouseKeys);

    struct EventArgs { };

	struct MouseEventArgs : EventArgs {
		MouseButton Button;
        MouseKeys Keys;
		DX::Point2F Position;
	};

	enum class VisibilityType {
		Visible,
		Hidden,
		Collapsed
	};

    template<typename TArgs = EventArgs>
	using EventHandler = std::function<bool(UIElement&, const TArgs&)>;

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
        enum EventType { 
            MouseDownEvent, MouseUpEvent, MouseMoveEvent
        };

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

        template<typename TArgs>
		UIElement& AddEventHandler(int type, const EventHandler<TArgs>& handler) {
            switch (type) {
            case MouseDownEvent:
            case MouseUpEvent:
            case MouseMoveEvent:
                _mouseEvents[type].push_back(handler);
                return *this;

            default:
                ASSERT(0);
            }
			return *this;
		}

		const DX::RectF& GetBounds() const {
			return _bounds;
		}

		void Invalidate() override;
        void InvalidateLayout(bool) override;

	protected:
		virtual void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) = 0;

		virtual UIElement* HitTestCore(const DX::Point2F& point) {
			return false;
		}

	protected:
        template<typename TArgs>
        void DispatchEvent(int type, std::map<int, std::vector<EventHandler<TArgs>>>& handlers, UIElement& source, const TArgs& args) {
            bool handled = false;
            auto it = handlers.find(type);
            if (it != handlers.end()) {
                auto& handlers = it->second;
                for (auto& handler : handlers)
                    if (handled = handler(source, args))
                        break;
            }

            if (!handled) {
                auto parent = GetParent();
                if (parent) {
                    parent->DispatchEvent(type, handlers, source, args);
                }
            }
        }

		// event dispatchers
        template<typename TSource>
		void OnMouseEvent(int type, TSource& source, const MouseEventArgs& args) {
            DispatchEvent(type, _mouseEvents, source, args);
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
        DX::RectF _bounds{};

		// events
        std::map<int, std::vector<EventHandler<MouseEventArgs>>> _mouseEvents;
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
