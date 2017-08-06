#pragma once

#include "CoreUI.h"

namespace DirectUI {
	class ButtonBase abstract : public ContentControl {
	};

	class Button : public ButtonBase {
	public:
		void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) override;
	};
}
