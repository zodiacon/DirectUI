#pragma once

#include "CoreUI.h"

namespace DirectUI {
	class TextBlock final : public UIElement {
		DECLARE_DP(TextBlock, Foreground, Ref<Brush>);
		DECLARE_DP(TextBlock, Text, std::wstring);
		DECLARE_DP(TextBlock, Underline, bool);
		DECLARE_DP(TextBlock, Strikethrough, bool);
		DECLARE_DP(TextBlock, TextAlignment, TextAlignmentType);
		DECLARE_DP(TextBlock, ReadingDirection, ReadingDirectionType);

	public:
		void Measure(const DX::SizeF& maximumSize) override;
		void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) override;

	protected:
		UIElement* HitTestCore(const DX::Point2F& point) override;

	private:
		DX::DirectWrite::TextFormat _format;
		DX::DirectWrite::TextLayout _layout;
	};

}