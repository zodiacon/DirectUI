#pragma once

#include "CoreUI.h"

namespace DirectUI {
	class Shape abstract : public UIElement {
		DECLARE_DP(Shape, StrokeWidth, float);
		DECLARE_DP(Shape, Stroke, Ref<Brush>);
		DECLARE_DP(Shape, Fill, Ref<Brush>);

	public:
		void Measure(const DX::SizeF& maximumSize) override;
		void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) override;

	protected:
		Shape() : UIElement() { }

		virtual DX::Direct2D::Geometry CalculateGeometry(const DX::RectF&) = 0;
		UIElement* HitTestCore(const DX::Point2F&) override;

	private:
		DX::Direct2D::Geometry _geometry;
	};

	class Rectangle final : public Shape {
	public:

	protected:
		DX::Direct2D::Geometry CalculateGeometry(const DX::RectF&) override;

	};

	class Ellipse final : public Shape {
	public:

	protected:
		DX::Direct2D::Geometry CalculateGeometry(const DX::RectF&) override;
	};

}

