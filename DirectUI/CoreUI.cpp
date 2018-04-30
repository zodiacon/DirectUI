#include "pch.h"
#include "CoreUI.h"
#include "Window.h"
#include "Application.h"

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

DEFINE_DP_WITH_FLAGS(UIElement, FontSize, float, 12.0f, PropertyMetadataFlags::AffectsRender | PropertyMetadataFlags::AffectsLayout | PropertyMetadataFlags::Inherit);
DEFINE_DP_WITH_FLAGS(UIElement, FontFamily, std::wstring, L"Arial", PropertyMetadataFlags::AffectsRender | PropertyMetadataFlags::Inherit);
DEFINE_DP_WITH_FLAGS(UIElement, FontWeight, DirectWrite::FontWeight, DirectWrite::FontWeight::Normal, PropertyMetadataFlags::AffectsRender);
DEFINE_DP_WITH_FLAGS(UIElement, FontStyle, DirectWrite::FontStyle, DirectWrite::FontStyle::Normal, PropertyMetadataFlags::AffectsRender);

DEFINE_DP_WITH_FLAGS(UIElement, Margin, Thickness, Thickness(), PropertyMetadataFlags::AffectsLayout);

DEFINE_DP_WITH_FLAGS(Control, Padding, Thickness, Thickness(), PropertyMetadataFlags::AffectsLayout);

DEFINE_DP_WITH_FLAGS(ContentControl, Content, Ref<UIElement>, nullptr, PropertyMetadataFlags::AffectsRender | PropertyMetadataFlags::AffectsLayout);

UIElement* UIElement::HitTestCore(const DX::Point2F& point) {
    if (_geometry.Get() == nullptr || Background() == nullptr)
        return nullptr;

    return _geometry.FillContainsPoint(point) ? this : nullptr;
}

void UIElement::Measure(const SizeF& maximumSize) {
    if (Visibility() == VisibilityType::Collapsed) {
        SetDesiredSize(SizeF(0, 0));
        return;
    }

    auto width = Width(), height = Height();
    SetDesiredSize(SizeF(width == D2D1::FloatMax() ? maximumSize.Width : width,
        height == D2D1::FloatMax() ? maximumSize.Height : height));
}

void UIElement::Draw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) {
	_bounds = bounds;

	if (Visibility() != VisibilityType::Visible || bounds.IsEmpty())
		return;

    _geometry = Application::Current()->D2DFactory().CreateRectangleGeometry(bounds);

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

DEFINE_EVENT(UIElement, MouseDown, MouseEventArgs, Bubbling);
DEFINE_EVENT(UIElement, MouseUp, MouseEventArgs, Bubbling);
DEFINE_EVENT(UIElement, MouseMove, MouseEventArgs, Bubbling);
DEFINE_EVENT(UIElement, MouseDoubleClick, MouseEventArgs, Bubbling);

// ContentControl

ContentControl::ContentControl() {
    ContentProperty.RegisterPropertyChangedHandler(*this, [this](auto&, auto&, const auto& oldValue, const auto& newValue) {
        if (oldValue)
            oldValue->SetParent(nullptr);
        if (newValue)
            newValue->SetParent(this);
    });
}

void ContentControl::OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) {
	auto content = Content();
    if (content) {
        auto padding = Padding();
        RectF contentBounds(bounds);
        contentBounds.MoveSize(padding.Left, padding.Top, padding.Right, padding.Bottom);

        content->Draw(dc, contentBounds);
    }
}
