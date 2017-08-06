#include "pch.h"
#include "Core.h"
#include "CoreUI.h"

using namespace DirectUI;

UIElement* DependencyObject::GetParent() const {
	if(IsUIElement())
		return reinterpret_cast<const UIElement*>(this)->GetParent();
	return nullptr;
}

Window* DependencyObject::GetWindow() const {
	return _window;
}
