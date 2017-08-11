#include "pch.h"
#include "Layout.h"
#include "Application.h"

using namespace DirectUI;
using namespace DX;

// StackLayout

DEFINE_DP_WITH_FLAGS(StackLayout, Orientation, LayoutOrientation, LayoutOrientation::Vertical, PropertyMetadataFlags::AffectsLayout);

LayoutBase& LayoutBase::AddChild(Ref<UIElement> child) {
    ASSERT(child->GetParent() == nullptr);
    if (child->GetParent())
        throw std::exception("element can only have one parent");

    _children.push_back(child);
    child->SetParent(this);
    child->SetWindow(GetWindow());

    return *this;
}

Ref<UIElement> LayoutBase::GetChild(int index) const {
    if (index < 0 || index >= static_cast<int>(_children.size()))
        throw std::out_of_range("child index out of range");

    return _children[index];
}

LayoutBase& LayoutBase::RemoveChild(int index) {
    if (index < 0 || index >= static_cast<int>(_children.size()))
        throw std::out_of_range("child index out of range");
    GetChild(index)->SetParent(nullptr);
    GetChild(index)->SetWindow(nullptr);
    _children.erase(_children.begin() + index);
    return *this;
}

void LayoutBase::OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) {
    auto background = Background();
    if (background) {
        _geometry = Application::Current()->D2DFactory().CreateRectangleGeometry(bounds);
        dc.FillRectangle(bounds, background->GetBrush(dc));
    }
    else {
        _geometry.Reset();
    }
}

void LayoutBase::SetWindow(Window* window) {
    UIElement::SetWindow(window);

    for (auto& element : _children)
        element->SetWindow(window);
}

UIElement* LayoutBase::HitTestCore(const Point2F& point) {
    UIElement* source = nullptr;

    for (auto it = _children.rbegin(); it != _children.rend(); ++it) {
        if (source = (*it)->HitTest(point))
            break;
    }

    if (!source &&_geometry && _geometry.FillContainsPoint(point))
        source = this;

    return source;
}

// StackLayout

void StackLayout::OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) {
    LayoutBase::OnDraw(dc, bounds);

    if (Orientation() == LayoutOrientation::Horizontal) {
        float x = 0;
        for (auto& element : _children) {
            x += element->Margin().Left;
            const auto& size = element->GetDesiredSize();
            element->Draw(dc, DX::RectF(DX::Point2F(bounds.Left + x, bounds.Top), size.Width, size.Height));
            x += size.Width + element->Margin().Right;
        }
    }
    else {
        float y = 0;
        for (auto& element : _children) {
            y += element->Margin().Top;
            const auto& size = element->GetDesiredSize();
            element->Draw(dc, DX::RectF(DX::Point2F(bounds.Left, bounds.Top + y), size.Width, size.Height));
            y += size.Height + element->Margin().Bottom;
        }
    }
}

void StackLayout::Measure(const DX::SizeF& maximumSize) {
    SizeF size{};
    auto orientation = Orientation();

    float max = 0;
    for (auto& element : _children) {
        element->Measure(maximumSize);
        const auto& desiredSize = element->GetDesiredSize();
        const auto& margin = element->Margin();

        if (orientation == LayoutOrientation::Horizontal) {
            size.Width += desiredSize.Width + margin.Left + margin.Right;
            if (size.Height > max)
                max = size.Height;
        }
        else {
            size.Height += desiredSize.Height + margin.Top+ margin.Bottom;
            if (size.Height > max)
                max = size.Height;
        }
    }
    if (orientation == LayoutOrientation::Horizontal)
        SetDesiredSize(SizeF(size.Width, max));
    else
        SetDesiredSize(SizeF(max, size.Height));
}

// CanvasLayout

DEFINE_AP(CanvasLayout, X, float, 0.0f)
DEFINE_AP(CanvasLayout, Y, float, 0.0f)

void CanvasLayout::Measure(const DX::SizeF& maximumSize) {
    for (auto& element : _children) {
        element->Measure(maximumSize);
    }
    SetDesiredSize(maximumSize);
}

void CanvasLayout::OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) {
    for (auto& element : _children) {
        const auto& size = element->GetDesiredSize();
        element->Draw(dc, DX::RectF(Point2F(X(*element), Y(*element)), size.Width, size.Height));
    }
}

// UniformGridLayout

DEFINE_DP(UniformGridLayout, Rows, int, 1);
DEFINE_DP(UniformGridLayout, Columns, int, 1);

DEFINE_AP(UniformGridLayout, Row, int, 0);
DEFINE_AP(UniformGridLayout, Column, int, 0);

void UniformGridLayout::OnDraw(DX::Direct2D::DeviceContext& dc, const DX::RectF& bounds) {
    LayoutBase::OnDraw(dc, bounds);

    float width = bounds.Width() / ChildrenCount();
    float height = bounds.Height() / ChildrenCount();

    int rows = Rows(), columns = Columns();

    for (auto& element : _children) {
        int row = Row(*element), col = Column(*element);
        const auto& size = element->GetDesiredSize();
        element->Draw(dc, RectF(Point2F(bounds.Left + width * col, bounds.Top + height * row), size.Width, size.Height));
    }

}
void UniformGridLayout::Measure(const DX::SizeF& maximumSize) {
    int rows = Rows(), columns = Columns();
    float width = Width(), height = Height();
    if (width > maximumSize.Width)
        width = maximumSize.Width;
    if (height > maximumSize.Height)
        height = maximumSize.Height;

    float cellwidth = width / columns;
    float cellheight = height / rows;

    for (auto& element : _children) {
        element->Measure(SizeF(cellwidth, cellheight));
    }
    SetDesiredSize(SizeF(width, height));
}

