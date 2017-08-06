#include "pch.h"
#include "Buttons.h"

using namespace DirectUI;
using namespace DX;
using namespace DX::Direct2D;

void Button::OnDraw(DeviceContext& dc, const RectF& bounds) {
	auto background = Background()->GetBrush(dc);

	dc.FillRectangle(bounds, background);
}
