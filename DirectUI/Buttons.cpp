#include "pch.h"
#include "Buttons.h"

using namespace DirectUI;
using namespace DX;
using namespace DX::Direct2D;

// ButtonBase

DEFINE_DP(ButtonBase, CornerRadius, SizeF, SizeF(0, 0));

DEFINE_EVENT(ButtonBase, Click, EventArgs, Direct);

ButtonBase::ButtonBase() {
    MouseUpEvent.AddHandler(this, [this](auto& source, const auto& args) {
        OnClick();
        return true;
    });
}

void ButtonBase::Measure(const DX::SizeF& maximumSize) {
    auto content = Content();
    if (content) {
        content->Measure(maximumSize);
        auto size = content->GetDesiredSize();
        auto padding = Padding();
        size.Width += padding.Left + padding.Right;
        size.Height += padding.Top + padding.Bottom;

        SetDesiredSize(size);
    }
    else {
        UIElement::Measure(maximumSize);
    }
}

void ButtonBase::OnDraw(DeviceContext& dc, const RectF& bounds) {
    auto background = Background();
    if (background) {
        auto& radius = CornerRadius();
        if (radius.Width + radius.Height == 0)
            dc.FillRectangle(bounds, background->GetBrush(dc));
        else {
            RoundedRect rr(bounds, radius.Width, radius.Height);
            dc.FillRoundedRectangle(rr, background->GetBrush(dc));
        }
    }
    auto content = Content();
    if (content) {
        auto padding = Padding();
        RectF contentBounds(bounds);
        contentBounds.MoveSize(padding.Left, padding.Top, padding.Right, padding.Bottom);
        content->Draw(dc, contentBounds);
    }
}

void ButtonBase::OnClick() {
    ClickEvent.RaiseEvent(*this, EventArgs());
}

// Button

void Button::OnDraw(DeviceContext& dc, const RectF& bounds) {
    ButtonBase::OnDraw(dc, bounds);
}
