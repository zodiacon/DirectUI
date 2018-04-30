#pragma once

#include "CoreUI.h"

namespace DirectUI {
	class TextBlock final : public UIElement {
		DECLARE_DP(TextBlock, Foreground, Ref<Brush>);
		DECLARE_DP2(TextBlock, Text, std::wstring);
		DECLARE_DP(TextBlock, Underline, bool);
		DECLARE_DP(TextBlock, Strikethrough, bool);
		DECLARE_DP(TextBlock, TextAlignment, DX::DirectWrite::TextAlignment);
		DECLARE_DP(TextBlock, ReadingDirection, DX::DirectWrite::ReadingDirection);

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