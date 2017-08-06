#pragma once

#include "CoreUI.h"

namespace DirectUI {
	enum class TextAlignmentType { 
		Leading = DX::DirectWrite::TextAlignment::Leading,
		Trailing = DX::DirectWrite::TextAlignment::Trailing,
		Center = DX::DirectWrite::TextAlignment::Center,
		Justified = DX::DirectWrite::TextAlignment::Justified,
	};

	enum class FontWeightType { 
		Thin =			DX::DirectWrite::FontWeight::Thin,
		ExtraLight =	DX::DirectWrite::FontWeight::ExtraLight,
		UltraLight =	DX::DirectWrite::FontWeight::UltraLight,
		Light =			DX::DirectWrite::FontWeight::Light,
		SemiLight =		DX::DirectWrite::FontWeight::SemiLight,
		Normal =		DX::DirectWrite::FontWeight::Normal,
		Regular =		DX::DirectWrite::FontWeight::Regular,
		Medium =		DX::DirectWrite::FontWeight::Medium,
		DemiBold =		DX::DirectWrite::FontWeight::DemiBold,
		SemiBold =		DX::DirectWrite::FontWeight::SemiBold,
		Bold =			DX::DirectWrite::FontWeight::Bold,
		ExtraBold =		DX::DirectWrite::FontWeight::ExtraBold,
		UltraBold =		DX::DirectWrite::FontWeight::UltraBold,
		Black =			DX::DirectWrite::FontWeight::Black,
		Heavy =			DX::DirectWrite::FontWeight::Heavy,
		ExtraBlack =	DX::DirectWrite::FontWeight::ExtraBlack,
		UltraBlack =	DX::DirectWrite::FontWeight::UltraBlack
	};
	
	enum class FontStyleType {
		Normal =	DX::DirectWrite::FontStyle::Normal,
		Italic =	DX::DirectWrite::FontStyle::Italic,
		Oblique =	DX::DirectWrite::FontStyle::Oblique,
	};

	enum class ReadingDirectionType {
		LeftToRight = DX::DirectWrite::ReadingDirection::LeftToRight,
		RightToLeft = DX::DirectWrite::ReadingDirection::RightToLeft,
	};

	class TextBlock final : public UIElement {
		DECLARE_DP(TextBlock, FontSize, float);
		DECLARE_DP(TextBlock, FontFamily, std::wstring);
		DECLARE_DP(TextBlock, FontWeight, FontWeightType);
		DECLARE_DP(TextBlock, FontStyle, FontStyleType);
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