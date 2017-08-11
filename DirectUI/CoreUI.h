#pragma once

#include "Core.h"
#include "Brushes.h"

#define DECLARE_CONVERT(target, source, name)	\
	target name(source value);

#define DEFINE_CONVERT(target, source, name)	\
	inline target name(source value) { return static_cast<target>(value); }

#define DECLARE_EVENT(name, args)  \
    static RoutedEvent<args> name##Event;

#define DEFINE_EVENT(class, name, args, strategy)  \
    RoutedEvent<args> class::name##Event(#name, RoutingStrategy::strategy);

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

    enum class TextAlignmentType {
        Leading = DX::DirectWrite::TextAlignment::Leading,
        Trailing = DX::DirectWrite::TextAlignment::Trailing,
        Center = DX::DirectWrite::TextAlignment::Center,
        Justified = DX::DirectWrite::TextAlignment::Justified,
    };

    enum class FontWeightType {
        Thin = DX::DirectWrite::FontWeight::Thin,
        ExtraLight = DX::DirectWrite::FontWeight::ExtraLight,
        UltraLight = DX::DirectWrite::FontWeight::UltraLight,
        Light = DX::DirectWrite::FontWeight::Light,
        SemiLight = DX::DirectWrite::FontWeight::SemiLight,
        Normal = DX::DirectWrite::FontWeight::Normal,
        Regular = DX::DirectWrite::FontWeight::Regular,
        Medium = DX::DirectWrite::FontWeight::Medium,
        DemiBold = DX::DirectWrite::FontWeight::DemiBold,
        SemiBold = DX::DirectWrite::FontWeight::SemiBold,
        Bold = DX::DirectWrite::FontWeight::Bold,
        ExtraBold = DX::DirectWrite::FontWeight::ExtraBold,
        UltraBold = DX::DirectWrite::FontWeight::UltraBold,
        Black = DX::DirectWrite::FontWeight::Black,
        Heavy = DX::DirectWrite::FontWeight::Heavy,
        ExtraBlack = DX::DirectWrite::FontWeight::ExtraBlack,
        UltraBlack = DX::DirectWrite::FontWeight::UltraBlack
    };

    enum class FontStyleType {
        Normal = DX::DirectWrite::FontStyle::Normal,
        Italic = DX::DirectWrite::FontStyle::Italic,
        Oblique = DX::DirectWrite::FontStyle::Oblique,
    };

    enum class ReadingDirectionType {
        LeftToRight = DX::DirectWrite::ReadingDirection::LeftToRight,
        RightToLeft = DX::DirectWrite::ReadingDirection::RightToLeft,
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

    enum class RoutingStrategy {
        Direct,
        Bubbling
    };

    template<typename TArgs = EventArgs>
    using EventHandler = std::function<bool(UIElement&, const TArgs&)>;

    template<typename TArgs>
    class RoutedEvent final {
    public:
        RoutedEvent(const std::string& name, RoutingStrategy strategy)
            : _name(name), _strategy(strategy) {
        }

        RoutingStrategy GetStrategy() const {
            return _strategy;
        }

        void AddHandler(UIElement& element, const EventHandler<TArgs>& handler) {
            _handlers[&element].push_back(handler);
        }

        void AddHandler(UIElement* element, const EventHandler<TArgs>& handler) {
            _handlers[element].push_back(handler);
        }

        void RemoveHandler(const EventHandler<TArgs>& handler) { }

        template<typename Type>
        void RaiseEvent(Type& source, const TArgs& args) { 
            auto it = _handlers.find(&source);
            if (it == _handlers.end())
                return;

            bool handled = false;
            for (auto& handler : it->second) {
                handled = handler(source, args);
                if (handled)
                    return;
            }
            if (GetStrategy() == RoutingStrategy::Direct)
                return;

        }

    private:
        RoutingStrategy _strategy;
        std::string _name;
        std::map<UIElement*, std::vector<EventHandler<TArgs>>> _handlers;
    };

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
        DECLARE_DP(UIElement, FontSize, float);
        DECLARE_DP(UIElement, FontFamily, std::wstring);
        DECLARE_DP(UIElement, FontWeight, FontWeightType);
        DECLARE_DP(UIElement, FontStyle, FontStyleType);

    private:
		UIElement(const UIElement&) = delete;
		UIElement& operator=(const UIElement&) = delete;

	public:
		void Draw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds);
        virtual void Measure(const DX::SizeF& size);
		UIElement* HitTest(const DX::Point2F& point);

		const DX::SizeF& GetDesiredSize() const {
			return _desiredSize;
		}

        UIElement* GetParent() const {
            return _parent;
        }
        
        void SetParent(UIElement* parent) {
			ASSERT(_parent == nullptr);
			_parent = parent;
		}

        template<typename TArgs = EventArgs>
        UIElement& AddEventHandler(RoutedEvent<TArgs>& event, const EventHandler<TArgs>& handler) {
            event.AddHandler(this, handler);
            return *this;
        }

        UIElement& AddEventHandler(RoutedEvent<EventArgs>& event, const EventHandler<EventArgs>& handler) {
            event.AddHandler(this, handler);
            return *this;
        }

		const DX::RectF& GetBounds() const {
			return _bounds;
		}

		void Invalidate() override;
        void InvalidateLayout(bool = true) override;

    public:
        // events
        DECLARE_EVENT(MouseDown, MouseEventArgs);
        DECLARE_EVENT(MouseUp, MouseEventArgs);
        DECLARE_EVENT(MouseMove, MouseEventArgs);
        DECLARE_EVENT(MouseDoubleClick, MouseEventArgs);

	protected:
		virtual void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) = 0;

        virtual UIElement* HitTestCore(const DX::Point2F& point);

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
        DX::Direct2D::Geometry _geometry;
    };

	class Control abstract : public UIElement {
		DECLARE_DP(Control, Padding, Thickness);

	};

	class ContentControl : public Control {
		DECLARE_DP(ContentControl, Content, Ref<UIElement>);

    public:
        ContentControl();

	protected:
		void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) override;
	};
}
