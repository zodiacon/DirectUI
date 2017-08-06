#include "pch.h"
#include "Brushes.h"
#include "Colors.h"
#include "CoreUI.h"

using namespace DirectUI;

DEFINE_DP_WITH_FLAGS(Brush, Opacity, float, 1.0f, PropertyMetadataFlags::AffectsParentRender);

DEFINE_DP_WITH_FLAGS(SolidColorBrush, Color, DX::Color, Colors::White(), PropertyMetadataFlags::AffectsParentRender);

SolidColorBrush::SolidColorBrush(const DX::Color& color) {
	SetValue(ColorProperty, color, false);
}

DX::Direct2D::Brush& SolidColorBrush::GetBrush(DX::Direct2D::DeviceContext& dc) {
	if (!_brush)
		_brush = dc.CreateSolidColorBrush(Color());
	return _brush;
}

Ref<SolidColorBrush> Brushes::AliceBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::AliceBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::AntiqueWhite() {
	static auto brush = Create<SolidColorBrush>(Colors::AntiqueWhite());
	return brush;
}

Ref<SolidColorBrush> Brushes::Aqua() {
	static auto brush = Create<SolidColorBrush>(Colors::Aqua());
	return brush;
}

Ref<SolidColorBrush> Brushes::Aquamarine() {
	static auto brush = Create<SolidColorBrush>(Colors::Aquamarine());
	return brush;
}

Ref<SolidColorBrush> Brushes::Azure() {
	static auto brush = Create<SolidColorBrush>(Colors::Azure());
	return brush;
}

Ref<SolidColorBrush> Brushes::Beige() {
	static auto brush = Create<SolidColorBrush>(Colors::Beige());
	return brush;
}

Ref<SolidColorBrush> Brushes::Bisque() {
	static auto brush = Create<SolidColorBrush>(Colors::Bisque());
	return brush;
}

Ref<SolidColorBrush> Brushes::Black() {
	static auto brush = Create<SolidColorBrush>(Colors::Black());
	return brush;
}

Ref<SolidColorBrush> Brushes::BlanchedAlmond() {
	static auto brush = Create<SolidColorBrush>(Colors::BlanchedAlmond());
	return brush;
}

Ref<SolidColorBrush> Brushes::Blue() {
	static auto brush = Create<SolidColorBrush>(Colors::Blue());
	return brush;
}

Ref<SolidColorBrush> Brushes::BlueViolet() {
	static auto brush = Create<SolidColorBrush>(Colors::BlueViolet());
	return brush;
}

Ref<SolidColorBrush> Brushes::Brown() {
	static auto brush = Create<SolidColorBrush>(Colors::Brown());
	return brush;
}

Ref<SolidColorBrush> Brushes::BurlyWood() {
	static auto brush = Create<SolidColorBrush>(Colors::BurlyWood());
	return brush;
}

Ref<SolidColorBrush> Brushes::CadetBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::CadetBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::Chartreuse() {
	static auto brush = Create<SolidColorBrush>(Colors::Chartreuse());
	return brush;
}

Ref<SolidColorBrush> Brushes::Chocolate() {
	static auto brush = Create<SolidColorBrush>(Colors::Chocolate());
	return brush;
}

Ref<SolidColorBrush> Brushes::Coral() {
	static auto brush = Create<SolidColorBrush>(Colors::Coral());
	return brush;
}

Ref<SolidColorBrush> Brushes::CornflowerBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::CornflowerBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::Cornsilk() {
	static auto brush = Create<SolidColorBrush>(Colors::Cornsilk());
	return brush;
}

Ref<SolidColorBrush> Brushes::Crimson() {
	static auto brush = Create<SolidColorBrush>(Colors::Crimson());
	return brush;
}

Ref<SolidColorBrush> Brushes::Cyan() {
	static auto brush = Create<SolidColorBrush>(Colors::Cyan());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkCyan() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkCyan());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkGoldenrod() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkGoldenrod());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkGray() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkGray());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkKhaki() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkKhaki());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkMagenta() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkMagenta());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkOliveGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkOliveGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkOrange() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkOrange());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkOrchid() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkOrchid());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkRed() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkRed());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkSalmon() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkSalmon());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkSeaGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkSeaGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkSlateBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkSlateBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkSlateGray() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkSlateGray());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkTurquoise() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkTurquoise());
	return brush;
}

Ref<SolidColorBrush> Brushes::DarkViolet() {
	static auto brush = Create<SolidColorBrush>(Colors::DarkViolet());
	return brush;
}

Ref<SolidColorBrush> Brushes::DeepPink() {
	static auto brush = Create<SolidColorBrush>(Colors::DeepPink());
	return brush;
}

Ref<SolidColorBrush> Brushes::DeepSkyBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::DeepSkyBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::DimGray() {
	static auto brush = Create<SolidColorBrush>(Colors::DimGray());
	return brush;
}

Ref<SolidColorBrush> Brushes::DodgerBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::DodgerBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::Firebrick() {
	static auto brush = Create<SolidColorBrush>(Colors::Firebrick());
	return brush;
}

Ref<SolidColorBrush> Brushes::FloralWhite() {
	static auto brush = Create<SolidColorBrush>(Colors::FloralWhite());
	return brush;
}

Ref<SolidColorBrush> Brushes::ForestGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::ForestGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::Fuchsia() {
	static auto brush = Create<SolidColorBrush>(Colors::Fuchsia());
	return brush;
}

Ref<SolidColorBrush> Brushes::Gainsboro() {
	static auto brush = Create<SolidColorBrush>(Colors::Gainsboro());
	return brush;
}

Ref<SolidColorBrush> Brushes::GhostWhite() {
	static auto brush = Create<SolidColorBrush>(Colors::GhostWhite());
	return brush;
}

Ref<SolidColorBrush> Brushes::Gold() {
	static auto brush = Create<SolidColorBrush>(Colors::Gold());
	return brush;
}

Ref<SolidColorBrush> Brushes::Goldenrod() {
	static auto brush = Create<SolidColorBrush>(Colors::Goldenrod());
	return brush;
}

Ref<SolidColorBrush> Brushes::Gray() {
	static auto brush = Create<SolidColorBrush>(Colors::Gray());
	return brush;
}

Ref<SolidColorBrush> Brushes::Green() {
	static auto brush = Create<SolidColorBrush>(Colors::Green());
	return brush;
}

Ref<SolidColorBrush> Brushes::GreenYellow() {
	static auto brush = Create<SolidColorBrush>(Colors::GreenYellow());
	return brush;
}

Ref<SolidColorBrush> Brushes::Honeydew() {
	static auto brush = Create<SolidColorBrush>(Colors::Honeydew());
	return brush;
}

Ref<SolidColorBrush> Brushes::HotPink() {
	static auto brush = Create<SolidColorBrush>(Colors::HotPink());
	return brush;
}

Ref<SolidColorBrush> Brushes::IndianRed() {
	static auto brush = Create<SolidColorBrush>(Colors::IndianRed());
	return brush;
}

Ref<SolidColorBrush> Brushes::Indigo() {
	static auto brush = Create<SolidColorBrush>(Colors::Indigo());
	return brush;
}

Ref<SolidColorBrush> Brushes::Ivory() {
	static auto brush = Create<SolidColorBrush>(Colors::Ivory());
	return brush;
}

Ref<SolidColorBrush> Brushes::Khaki() {
	static auto brush = Create<SolidColorBrush>(Colors::Khaki());
	return brush;
}

Ref<SolidColorBrush> Brushes::Lavender() {
	static auto brush = Create<SolidColorBrush>(Colors::Lavender());
	return brush;
}

Ref<SolidColorBrush> Brushes::LavenderBlush() {
	static auto brush = Create<SolidColorBrush>(Colors::LavenderBlush());
	return brush;
}

Ref<SolidColorBrush> Brushes::LawnGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::LawnGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::LemonChiffon() {
	static auto brush = Create<SolidColorBrush>(Colors::LemonChiffon());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::LightBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightCoral() {
	static auto brush = Create<SolidColorBrush>(Colors::LightCoral());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightCyan() {
	static auto brush = Create<SolidColorBrush>(Colors::LightCyan());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightGoldenrodYellow() {
	static auto brush = Create<SolidColorBrush>(Colors::LightGoldenrodYellow());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightGray() {
	static auto brush = Create<SolidColorBrush>(Colors::LightGray());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::LightGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightPink() {
	static auto brush = Create<SolidColorBrush>(Colors::LightPink());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightSalmon() {
	static auto brush = Create<SolidColorBrush>(Colors::LightSalmon());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightSeaGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::LightSeaGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightSkyBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::LightSkyBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightSlateGray() {
	static auto brush = Create<SolidColorBrush>(Colors::LightSlateGray());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightSteelBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::LightSteelBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::LightYellow() {
	static auto brush = Create<SolidColorBrush>(Colors::LightYellow());
	return brush;
}

Ref<SolidColorBrush> Brushes::Lime() {
	static auto brush = Create<SolidColorBrush>(Colors::Lime());
	return brush;
}

Ref<SolidColorBrush> Brushes::LimeGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::LimeGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::Linen() {
	static auto brush = Create<SolidColorBrush>(Colors::Linen());
	return brush;
}

Ref<SolidColorBrush> Brushes::Magenta() {
	static auto brush = Create<SolidColorBrush>(Colors::Magenta());
	return brush;
}

Ref<SolidColorBrush> Brushes::Maroon() {
	static auto brush = Create<SolidColorBrush>(Colors::Maroon());
	return brush;
}

Ref<SolidColorBrush> Brushes::MediumAquamarine() {
	static auto brush = Create<SolidColorBrush>(Colors::MediumAquamarine());
	return brush;
}

Ref<SolidColorBrush> Brushes::MediumBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::MediumBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::MediumOrchid() {
	static auto brush = Create<SolidColorBrush>(Colors::MediumOrchid());
	return brush;
}

Ref<SolidColorBrush> Brushes::MediumPurple() {
	static auto brush = Create<SolidColorBrush>(Colors::MediumPurple());
	return brush;
}

Ref<SolidColorBrush> Brushes::MediumSeaGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::MediumSeaGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::MediumSlateBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::MediumSlateBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::MediumSpringGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::MediumSpringGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::MediumTurquoise() {
	static auto brush = Create<SolidColorBrush>(Colors::MediumTurquoise());
	return brush;
}

Ref<SolidColorBrush> Brushes::MediumVioletRed() {
	static auto brush = Create<SolidColorBrush>(Colors::MediumVioletRed());
	return brush;
}

Ref<SolidColorBrush> Brushes::MidnightBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::MidnightBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::MintCream() {
	static auto brush = Create<SolidColorBrush>(Colors::MintCream());
	return brush;
}

Ref<SolidColorBrush> Brushes::MistyRose() {
	static auto brush = Create<SolidColorBrush>(Colors::MistyRose());
	return brush;
}

Ref<SolidColorBrush> Brushes::Moccasin() {
	static auto brush = Create<SolidColorBrush>(Colors::Moccasin());
	return brush;
}

Ref<SolidColorBrush> Brushes::NavajoWhite() {
	static auto brush = Create<SolidColorBrush>(Colors::NavajoWhite());
	return brush;
}

Ref<SolidColorBrush> Brushes::Navy() {
	static auto brush = Create<SolidColorBrush>(Colors::Navy());
	return brush;
}

Ref<SolidColorBrush> Brushes::OldLace() {
	static auto brush = Create<SolidColorBrush>(Colors::OldLace());
	return brush;
}

Ref<SolidColorBrush> Brushes::Olive() {
	static auto brush = Create<SolidColorBrush>(Colors::Olive());
	return brush;
}

Ref<SolidColorBrush> Brushes::OliveDrab() {
	static auto brush = Create<SolidColorBrush>(Colors::OliveDrab());
	return brush;
}

Ref<SolidColorBrush> Brushes::Orange() {
	static auto brush = Create<SolidColorBrush>(Colors::Orange());
	return brush;
}

Ref<SolidColorBrush> Brushes::OrangeRed() {
	static auto brush = Create<SolidColorBrush>(Colors::OrangeRed());
	return brush;
}

Ref<SolidColorBrush> Brushes::Orchid() {
	static auto brush = Create<SolidColorBrush>(Colors::Orchid());
	return brush;
}

Ref<SolidColorBrush> Brushes::PaleGoldenrod() {
	static auto brush = Create<SolidColorBrush>(Colors::PaleGoldenrod());
	return brush;
}

Ref<SolidColorBrush> Brushes::PaleGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::PaleGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::PaleTurquoise() {
	static auto brush = Create<SolidColorBrush>(Colors::PaleTurquoise());
	return brush;
}

Ref<SolidColorBrush> Brushes::PaleVioletRed() {
	static auto brush = Create<SolidColorBrush>(Colors::PaleVioletRed());
	return brush;
}

Ref<SolidColorBrush> Brushes::PapayaWhip() {
	static auto brush = Create<SolidColorBrush>(Colors::PapayaWhip());
	return brush;
}

Ref<SolidColorBrush> Brushes::PeachPuff() {
	static auto brush = Create<SolidColorBrush>(Colors::PeachPuff());
	return brush;
}

Ref<SolidColorBrush> Brushes::Peru() {
	static auto brush = Create<SolidColorBrush>(Colors::Peru());
	return brush;
}

Ref<SolidColorBrush> Brushes::Pink() {
	static auto brush = Create<SolidColorBrush>(Colors::Pink());
	return brush;
}

Ref<SolidColorBrush> Brushes::Plum() {
	static auto brush = Create<SolidColorBrush>(Colors::Plum());
	return brush;
}

Ref<SolidColorBrush> Brushes::PowderBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::PowderBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::Purple() {
	static auto brush = Create<SolidColorBrush>(Colors::Purple());
	return brush;
}

Ref<SolidColorBrush> Brushes::Red() {
	static auto brush = Create<SolidColorBrush>(Colors::Red());
	return brush;
}

Ref<SolidColorBrush> Brushes::RosyBrown() {
	static auto brush = Create<SolidColorBrush>(Colors::RosyBrown());
	return brush;
}

Ref<SolidColorBrush> Brushes::RoyalBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::RoyalBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::SaddleBrown() {
	static auto brush = Create<SolidColorBrush>(Colors::SaddleBrown());
	return brush;
}

Ref<SolidColorBrush> Brushes::Salmon() {
	static auto brush = Create<SolidColorBrush>(Colors::Salmon());
	return brush;
}

Ref<SolidColorBrush> Brushes::SandyBrown() {
	static auto brush = Create<SolidColorBrush>(Colors::SandyBrown());
	return brush;
}

Ref<SolidColorBrush> Brushes::SeaGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::SeaGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::SeaShell() {
	static auto brush = Create<SolidColorBrush>(Colors::SeaShell());
	return brush;
}

Ref<SolidColorBrush> Brushes::Sienna() {
	static auto brush = Create<SolidColorBrush>(Colors::Sienna());
	return brush;
}

Ref<SolidColorBrush> Brushes::Silver() {
	static auto brush = Create<SolidColorBrush>(Colors::Silver());
	return brush;
}

Ref<SolidColorBrush> Brushes::SkyBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::SkyBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::SlateBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::SlateBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::SlateGray() {
	static auto brush = Create<SolidColorBrush>(Colors::SlateGray());
	return brush;
}

Ref<SolidColorBrush> Brushes::Snow() {
	static auto brush = Create<SolidColorBrush>(Colors::Snow());
	return brush;
}

Ref<SolidColorBrush> Brushes::SpringGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::SpringGreen());
	return brush;
}

Ref<SolidColorBrush> Brushes::SteelBlue() {
	static auto brush = Create<SolidColorBrush>(Colors::SteelBlue());
	return brush;
}

Ref<SolidColorBrush> Brushes::Tan() {
	static auto brush = Create<SolidColorBrush>(Colors::Tan());
	return brush;
}

Ref<SolidColorBrush> Brushes::Teal() {
	static auto brush = Create<SolidColorBrush>(Colors::Teal());
	return brush;
}

Ref<SolidColorBrush> Brushes::Thistle() {
	static auto brush = Create<SolidColorBrush>(Colors::Thistle());
	return brush;
}

Ref<SolidColorBrush> Brushes::Tomato() {
	static auto brush = Create<SolidColorBrush>(Colors::Tomato());
	return brush;
}

Ref<SolidColorBrush> Brushes::Transparent() {
	static auto brush = Create<SolidColorBrush>(Colors::Transparent());
	return brush;
}

Ref<SolidColorBrush> Brushes::Turquoise() {
	static auto brush = Create<SolidColorBrush>(Colors::Turquoise());
	return brush;
}

Ref<SolidColorBrush> Brushes::Violet() {
	static auto brush = Create<SolidColorBrush>(Colors::Violet());
	return brush;
}

Ref<SolidColorBrush> Brushes::Wheat() {
	static auto brush = Create<SolidColorBrush>(Colors::Wheat());
	return brush;
}

Ref<SolidColorBrush> Brushes::White() {
	static auto brush = Create<SolidColorBrush>(Colors::White());
	return brush;
}

Ref<SolidColorBrush> Brushes::WhiteSmoke() {
	static auto brush = Create<SolidColorBrush>(Colors::WhiteSmoke());
	return brush;
}

Ref<SolidColorBrush> Brushes::Yellow() {
	static auto brush = Create<SolidColorBrush>(Colors::Yellow());
	return brush;
}

Ref<SolidColorBrush> Brushes::YellowGreen() {
	static auto brush = Create<SolidColorBrush>(Colors::YellowGreen());
	return brush;
}

