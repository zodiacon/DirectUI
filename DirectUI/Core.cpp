#include "pch.h"
#include "Core.h"
#include "CoreUI.h"

using namespace DirectUI;

const UIElement* DependencyObject::GetParent() const {
    auto element = DynamicAs<UIElement>();
	return element ? element->GetParent() : nullptr;
}

