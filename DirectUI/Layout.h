#pragma once

#include "CoreUI.h"

namespace DirectUI {
	class LayoutBase abstract : public UIElement {
	public:
		LayoutBase& AddChild(Ref<UIElement> element);
		template<typename Iterator>
		LayoutBase& AddChildren(Iterator begin, Iterator end);
		Ref<UIElement> GetChild(int index) const;
		LayoutBase& RemoveChild(Ref<UIElement> element);
		LayoutBase& RemoveChild(int index);

		int ChildrenCount() {
			return static_cast<int>(_children.size());
		}

        void SetWindow(Window* window) override;

		void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) override;

	protected:
        LayoutBase(std::initializer_list<Ref<UIElement>> elements = {}) : UIElement() {
            for (auto& element : elements)
                AddChild(element);
        }

		UIElement* HitTestCore(const DX::Point2F& point) override;

	protected:
		std::vector<Ref<UIElement>> _children;
		DX::Direct2D::Geometry _geometry;
	};

	enum class LayoutOrientation {
		Horizontal,
		Vertical
	};

	// StackLayout

	class StackLayout final : public LayoutBase {
		DECLARE_DP(StackLayout, Orientation, LayoutOrientation);

	public:
        StackLayout(std::initializer_list<Ref<UIElement>> controls = {}) : LayoutBase(controls) { }

		void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) override;
		void Measure(const DX::SizeF& maximumSize) override;
	};

	// CanvasLayout

	class CanvasLayout final : public LayoutBase {
	public:
		DECLARE_AP(X, float);
		DECLARE_AP(Y, float);

	public:
		void Measure(const DX::SizeF& maximumSize) override;

	protected:

		void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) override;
	};

	// UniformGridLayout

	class UniformGridLayout final : public LayoutBase {
		DECLARE_DP(UniformGridLayout, Rows, int);
		DECLARE_DP(UniformGridLayout, Columns, int);

		DECLARE_AP(Row, int);
		DECLARE_AP(Column, int);

	public:
		void Measure(const DX::SizeF& maximumSize) override;

	protected:
		void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) override;
	};
}
