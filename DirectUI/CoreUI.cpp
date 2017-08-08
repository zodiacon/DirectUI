#include "pch.h"
#include "CoreUI.h"
#include "Window.h"

using namespace DirectUI;
using namespace DX;

DEFINE_DP_WITH_FLAGS(UIElement, Visibility, VisibilityType, VisibilityType::Visible, PropertyMetadataFlags::AffectsRender | PropertyMetadataFlags::AffectsLayout);
DEFINE_DP_WITH_FLAGS(UIElement, IsEnabled, bool, true, PropertyMetadataFlags::AffectsRender);

DEFINE_DP_WITH_FLAGS(UIElement, Background, Ref<Brush>, nullptr, PropertyMetadataFlags::AffectsRender);
DEFINE_DP_WITH_FLAGS(UIElement, Width, float, D2D1::FloatMax(), PropertyMetadataFlags::AffectsLayout);
DEFINE_DP_WITH_FLAGS(UIElement, Height, float, D2D1::FloatMax(), PropertyMetadataFlags::AffectsLayout);
DEFINE_DP_WITH_FLAGS(UIElement, HorizontalAlignment, HorizontalAlignmentType, HorizontalAlignmentType::Stretch, PropertyMetadataFlags::AffectsLayout);
DEFINE_DP_WITH_FLAGS(UIElement, VerticalAlignment, VerticalAlignmentType, VerticalAlignmentType::Stretch, PropertyMetadataFlags::AffectsLayout);
DEFINE_DP(UIElement, UserData, PVOID, nullptr);

DEFINE_DP_WITH_FLAGS(UIElement, Margin, Thickness, Thickness(), PropertyMetadataFlags::AffectsLayout);

DEFINE_DP_WITH_FLAGS(Control, Padding, Thickness, Thickness(), PropertyMetadataFlags::AffectsLayout);

DEFINE_DP_WITH_FLAGS(ContentControl, Content, Ref<UIElement>, nullptr, PropertyMetadataFlags::AffectsRender | PropertyMetadataFlags::AffectsLayout);

void UIElement::Draw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) {
	_bounds = bounds;

	if (Visibility() != VisibilityType::Visible)
		return;

	auto background = Background();
	if (background)
		dc.FillRectangle(bounds, background->GetBrush(dc));

	OnDraw(dc, bounds);
}

UIElement* UIElement::HitTest(const DX::Point2F& point) {
	if (!IsEnabled() || Visibility() != VisibilityType::Visible)
		return nullptr;
	return HitTestCore(point);
}

void UIElement::Invalidate() {
	if(GetWindow())
		GetWindow()->Invalidate(GetBounds());
}

void UIElement::InvalidateLayout(bool invalid) {
    if (GetWindow())
        GetWindow()->InvalidateLayout(invalid);
}

void ContentControl::OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) {
	auto content = Content();
	if (content)
		content->Draw(dc, bounds);
}

