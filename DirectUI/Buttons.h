#pragma once

#include "CoreUI.h"

namespace DirectUI {
	class ButtonBase abstract : public ContentControl {
        DECLARE_DP(ButtonBase, CornerRadius, DX::SizeF);

        DECLARE_EVENT(Click, EventArgs);

    public:
        void Measure(const DX::SizeF& size) override;

    protected:
        virtual void OnClick();

        ButtonBase();

        void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) override;
    };

	class Button : public ButtonBase {
	public:
        void OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) override;
	};

    class ToggleButton : public ButtonBase {
        DECLARE_DP(ToggleButton, IsChecked, bool);
    };
}
