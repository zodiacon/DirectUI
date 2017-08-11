#include "pch.h"
#include "Text.h"
#include "Colors.h"
#include "Application.h"

using namespace DirectUI;
using namespace DX;

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

    DX::SizeF size;
    
    _format = factory.CreateTextFormat(FontFamily().c_str(), ToDirectWrite(FontWeight()), ToDirectWrite(FontStyle()), DX::DirectWrite::FontStretch::Normal, FontSize());
    _format.SetReadingDirection(ToDirectWrite(ReadingDirection()));

    _layout = factory.CreateTextLayout(Text().c_str(), static_cast<int>(Text().size()), _format, maximumSize.Width, maximumSize.Height);
    _layout.SetTextAlignment(ToDirectWrite(TextAlignment()));
    auto metrics = _layout.GetMetrics();
    size.Width = metrics.Width;
    size.Height = metrics.Height;

    SetDesiredSize(size);
}

void TextBlock::OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) {
    auto background = Background();
    if (background) {
        dc.FillRectangle(bounds, background->GetBrush(dc));
    }
    auto foreground = Foreground();
    if (foreground)
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
