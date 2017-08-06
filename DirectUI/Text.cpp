#include "pch.h"
#include "Text.h"
#include "Colors.h"
#include "Application.h"

using namespace DirectUI;

DEFINE_DP_WITH_FLAGS(TextBlock, FontSize, float, 12.0f, PropertyMetadataFlags::AffectsRender);
DEFINE_DP_WITH_FLAGS(TextBlock, FontFamily, std::wstring, L"Arial", PropertyMetadataFlags::AffectsRender);
DEFINE_DP_WITH_FLAGS(TextBlock, FontWeight, FontWeightType, FontWeightType::Normal, PropertyMetadataFlags::AffectsRender);
DEFINE_DP_WITH_FLAGS(TextBlock, FontStyle, FontStyleType, FontStyleType::Normal, PropertyMetadataFlags::AffectsRender);
DEFINE_DP_WITH_FLAGS(TextBlock, Foreground, Ref<Brush>, Brushes::Black(), PropertyMetadataFlags::AffectsRender);
DEFINE_DP_WITH_FLAGS(TextBlock, Text, std::wstring, L"", PropertyMetadataFlags::AffectsRender | PropertyMetadataFlags::AffectsLayout);
DEFINE_DP_WITH_FLAGS(TextBlock, Underline, bool, false, PropertyMetadataFlags::AffectsRender);
DEFINE_DP_WITH_FLAGS(TextBlock, Strikethrough, bool, false, PropertyMetadataFlags::AffectsRender);
DEFINE_DP_WITH_FLAGS(TextBlock, TextAlignment, TextAlignmentType, TextAlignmentType::Leading, PropertyMetadataFlags::AffectsRender);
DEFINE_DP_WITH_FLAGS(TextBlock, ReadingDirection, ReadingDirectionType, ReadingDirectionType::LeftToRight, PropertyMetadataFlags::AffectsRender);

DEFINE_CONVERT(DX::DirectWrite::TextAlignment, TextAlignmentType, ToDirectWrite);
DEFINE_CONVERT(DX::DirectWrite::FontWeight, FontWeightType, ToDirectWrite);
DEFINE_CONVERT(DX::DirectWrite::FontStyle, FontStyleType, ToDirectWrite);
DEFINE_CONVERT(DX::DirectWrite::ReadingDirection, ReadingDirectionType, ToDirectWrite);

void TextBlock::Measure(const DX::SizeF& maximumSize) {
	auto& factory = Application::Current()->DWriteFactory();

	if (!_format) {
		_format = factory.CreateTextFormat(FontFamily().c_str(), ToDirectWrite(FontWeight()), ToDirectWrite(FontStyle()), DX::DirectWrite::FontStretch::Normal, FontSize());
		_format.SetReadingDirection(ToDirectWrite(ReadingDirection()));
	}
	if (!_layout) {
		_layout = factory.CreateTextLayout(Text().c_str(), static_cast<int>(Text().size()), _format, maximumSize.Width, maximumSize.Height);
		_layout.SetTextAlignment(ToDirectWrite(TextAlignment()));
	}

	SetDesiredSize(DX::SizeF(_layout.GetMaxWidth(), _layout.GetMaxHeight()));
}

void TextBlock::OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) {
	auto foreground = Foreground();
	if(foreground)
		dc.DrawTextLayout(bounds.TopLeft(), _layout, foreground->GetBrush(dc));
}

UIElement* TextBlock::HitTestCore(const DX::Point2F& point) {
	if (!_layout)
		return nullptr;
	bool isTrailingHit, isInside;
	DX::DirectWrite::HitTestMetrics metrics;
	_layout.HitTestPoint(point.X, point.Y, &isTrailingHit, &isInside, metrics);
	return isInside ? this : nullptr;
}
