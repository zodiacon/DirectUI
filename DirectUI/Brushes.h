#pragma once

#include "Core.h"

namespace DirectUI {
	class Brush abstract : public DeviceDependentResource {
	public:
		DECLARE_DP(Brush, Opacity, float);

		virtual DX::Direct2D::Brush& GetBrush(DX::Direct2D::DeviceContext& dc) = 0;
		DX::Direct2D::Brush& operator()(DX::Direct2D::DeviceContext& dc) {
			return GetBrush(dc);
		}

	protected:
	};

	class SolidColorBrush final : public Brush {
		DECLARE_DP(SolidColorBrush, Color, DX::Color);

	public:
		SolidColorBrush(const DX::Color& color);

		DX::Direct2D::Brush& GetBrush(DX::Direct2D::DeviceContext& dc);

	private:
		DX::Direct2D::SolidColorBrush _brush;
	};

	class GradientBrush abstract : public Brush {
	};

	class LinearGradientBrush sealed : public GradientBrush {
	};

	class RadialGradientBrush sealed : public GradientBrush {
	};

	class BitmapBrush sealed : public Brush {
	};

	class Brushes abstract final {
	public:
		static Ref<SolidColorBrush> AliceBlue();
		static Ref<SolidColorBrush> AntiqueWhite();
		static Ref<SolidColorBrush> Aqua();
		static Ref<SolidColorBrush> Aquamarine();
		static Ref<SolidColorBrush> Azure();
		static Ref<SolidColorBrush> Beige();
		static Ref<SolidColorBrush> Bisque();
		static Ref<SolidColorBrush> Black();
		static Ref<SolidColorBrush> BlanchedAlmond();
		static Ref<SolidColorBrush> Blue();
		static Ref<SolidColorBrush> BlueViolet();
		static Ref<SolidColorBrush> Brown();
		static Ref<SolidColorBrush> BurlyWood();
		static Ref<SolidColorBrush> CadetBlue();
		static Ref<SolidColorBrush> Chartreuse();
		static Ref<SolidColorBrush> Chocolate();
		static Ref<SolidColorBrush> Coral();
		static Ref<SolidColorBrush> CornflowerBlue();
		static Ref<SolidColorBrush> Cornsilk();
		static Ref<SolidColorBrush> Crimson();
		static Ref<SolidColorBrush> Cyan();
		static Ref<SolidColorBrush> DarkBlue();
		static Ref<SolidColorBrush> DarkCyan();
		static Ref<SolidColorBrush> DarkGoldenrod();
		static Ref<SolidColorBrush> DarkGray();
		static Ref<SolidColorBrush> DarkGreen();
		static Ref<SolidColorBrush> DarkKhaki();
		static Ref<SolidColorBrush> DarkMagenta();
		static Ref<SolidColorBrush> DarkOliveGreen();
		static Ref<SolidColorBrush> DarkOrange();
		static Ref<SolidColorBrush> DarkOrchid();
		static Ref<SolidColorBrush> DarkRed();
		static Ref<SolidColorBrush> DarkSalmon();
		static Ref<SolidColorBrush> DarkSeaGreen();
		static Ref<SolidColorBrush> DarkSlateBlue();
		static Ref<SolidColorBrush> DarkSlateGray();
		static Ref<SolidColorBrush> DarkTurquoise();
		static Ref<SolidColorBrush> DarkViolet();
		static Ref<SolidColorBrush> DeepPink();
		static Ref<SolidColorBrush> DeepSkyBlue();
		static Ref<SolidColorBrush> DimGray();
		static Ref<SolidColorBrush> DodgerBlue();
		static Ref<SolidColorBrush> Firebrick();
		static Ref<SolidColorBrush> FloralWhite();
		static Ref<SolidColorBrush> ForestGreen();
		static Ref<SolidColorBrush> Fuchsia();
		static Ref<SolidColorBrush> Gainsboro();
		static Ref<SolidColorBrush> GhostWhite();
		static Ref<SolidColorBrush> Gold();
		static Ref<SolidColorBrush> Goldenrod();
		static Ref<SolidColorBrush> Gray();
		static Ref<SolidColorBrush> Green();
		static Ref<SolidColorBrush> GreenYellow();
		static Ref<SolidColorBrush> Honeydew();
		static Ref<SolidColorBrush> HotPink();
		static Ref<SolidColorBrush> IndianRed();
		static Ref<SolidColorBrush> Indigo();
		static Ref<SolidColorBrush> Ivory();
		static Ref<SolidColorBrush> Khaki();
		static Ref<SolidColorBrush> Lavender();
		static Ref<SolidColorBrush> LavenderBlush();
		static Ref<SolidColorBrush> LawnGreen();
		static Ref<SolidColorBrush> LemonChiffon();
		static Ref<SolidColorBrush> LightBlue();
		static Ref<SolidColorBrush> LightCoral();
		static Ref<SolidColorBrush> LightCyan();
		static Ref<SolidColorBrush> LightGoldenrodYellow();
		static Ref<SolidColorBrush> LightGray();
		static Ref<SolidColorBrush> LightGreen();
		static Ref<SolidColorBrush> LightPink();
		static Ref<SolidColorBrush> LightSalmon();
		static Ref<SolidColorBrush> LightSeaGreen();
		static Ref<SolidColorBrush> LightSkyBlue();
		static Ref<SolidColorBrush> LightSlateGray();
		static Ref<SolidColorBrush> LightSteelBlue();
		static Ref<SolidColorBrush> LightYellow();
		static Ref<SolidColorBrush> Lime();
		static Ref<SolidColorBrush> LimeGreen();
		static Ref<SolidColorBrush> Linen();
		static Ref<SolidColorBrush> Magenta();
		static Ref<SolidColorBrush> Maroon();
		static Ref<SolidColorBrush> MediumAquamarine();
		static Ref<SolidColorBrush> MediumBlue();
		static Ref<SolidColorBrush> MediumOrchid();
		static Ref<SolidColorBrush> MediumPurple();
		static Ref<SolidColorBrush> MediumSeaGreen();
		static Ref<SolidColorBrush> MediumSlateBlue();
		static Ref<SolidColorBrush> MediumSpringGreen();
		static Ref<SolidColorBrush> MediumTurquoise();
		static Ref<SolidColorBrush> MediumVioletRed();
		static Ref<SolidColorBrush> MidnightBlue();
		static Ref<SolidColorBrush> MintCream();
		static Ref<SolidColorBrush> MistyRose();
		static Ref<SolidColorBrush> Moccasin();
		static Ref<SolidColorBrush> NavajoWhite();
		static Ref<SolidColorBrush> Navy();
		static Ref<SolidColorBrush> OldLace();
		static Ref<SolidColorBrush> Olive();
		static Ref<SolidColorBrush> OliveDrab();
		static Ref<SolidColorBrush> Orange();
		static Ref<SolidColorBrush> OrangeRed();
		static Ref<SolidColorBrush> Orchid();
		static Ref<SolidColorBrush> PaleGoldenrod();
		static Ref<SolidColorBrush> PaleGreen();
		static Ref<SolidColorBrush> PaleTurquoise();
		static Ref<SolidColorBrush> PaleVioletRed();
		static Ref<SolidColorBrush> PapayaWhip();
		static Ref<SolidColorBrush> PeachPuff();
		static Ref<SolidColorBrush> Peru();
		static Ref<SolidColorBrush> Pink();
		static Ref<SolidColorBrush> Plum();
		static Ref<SolidColorBrush> PowderBlue();
		static Ref<SolidColorBrush> Purple();
		static Ref<SolidColorBrush> Red();
		static Ref<SolidColorBrush> RosyBrown();
		static Ref<SolidColorBrush> RoyalBlue();
		static Ref<SolidColorBrush> SaddleBrown();
		static Ref<SolidColorBrush> Salmon();
		static Ref<SolidColorBrush> SandyBrown();
		static Ref<SolidColorBrush> SeaGreen();
		static Ref<SolidColorBrush> SeaShell();
		static Ref<SolidColorBrush> Sienna();
		static Ref<SolidColorBrush> Silver();
		static Ref<SolidColorBrush> SkyBlue();
		static Ref<SolidColorBrush> SlateBlue();
		static Ref<SolidColorBrush> SlateGray();
		static Ref<SolidColorBrush> Snow();
		static Ref<SolidColorBrush> SpringGreen();
		static Ref<SolidColorBrush> SteelBlue();
		static Ref<SolidColorBrush> Tan();
		static Ref<SolidColorBrush> Teal();
		static Ref<SolidColorBrush> Thistle();
		static Ref<SolidColorBrush> Tomato();
		static Ref<SolidColorBrush> Transparent();
		static Ref<SolidColorBrush> Turquoise();
		static Ref<SolidColorBrush> Violet();
		static Ref<SolidColorBrush> Wheat();
		static Ref<SolidColorBrush> White();
		static Ref<SolidColorBrush> WhiteSmoke();
		static Ref<SolidColorBrush> Yellow();
		static Ref<SolidColorBrush> YellowGreen();
	};

}

