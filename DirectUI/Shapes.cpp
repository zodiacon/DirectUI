#include "pch.h"
#include "Shapes.h"
#include "Application.h"

using namespace DirectUI;
using namespace DX;

DEFINE_DP_WITH_FLAGS(Shape, Fill, Ref<Brush>, nullptr, PropertyMetadataFlags::AffectsRender);
DEFINE_DP_WITH_FLAGS(Shape, Stroke, Ref<Brush>, nullptr, PropertyMetadataFlags::AffectsRender);
DEFINE_DP_WITH_FLAGS(Shape, StrokeWidth, float, 1.0f, PropertyMetadataFlags::AffectsRender);

// Shape

void Shape::Measure(const SizeF& maximumSize) {
	SizeF size{};
	if (Width() != D2D1::FloatMax())
		size.Width = Width();
	if (Height() != D2D1::FloatMax())
		size.Height = Height();
	SetDesiredSize(size);
}

void Shape::OnDraw(Direct2D::DeviceContext& dc, const RectF& bounds) {
	auto fill = Fill();
	auto stroke = Stroke();
	_geometry = CalculateGeometry(bounds);

	if (fill)
		dc.FillGeometry(_geometry, fill->GetBrush(dc));
	if (stroke)
		dc.DrawGeometry(_geometry, stroke->GetBrush(dc), StrokeWidth());
}

UIElement* Shape::HitTestCore(const Point2F& point) {
	if (!_geometry)
		return nullptr;

	if (Fill() && _geometry.FillContainsPoint(point))
		return this;
	if (Stroke() && _geometry.StrokeContainsPoint(point, StrokeWidth()))
		return this;

	return nullptr;
}

// Rectangle

Direct2D::Geometry Rectangle::CalculateGeometry(const DX::RectF& bounds) {
	return Application::Current()->D2DFactory().CreateRectangleGeometry(bounds);
}

// Ellipse

Direct2D::Geometry Ellipse::CalculateGeometry(const DX::RectF& bounds) {
	auto radiusx = bounds.Width() / 2.0f, radiusy = bounds.Height() / 2.0f;
	Direct2D::Ellipse ellipse(Point2F(bounds.Left + radiusx, bounds.Top + radiusy), radiusx, radiusy);

	return Application::Current()->D2DFactory().CreateEllipseGeometry(ellipse);
}
