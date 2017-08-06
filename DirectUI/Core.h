#pragma once

namespace DirectUI {
	class UIElement;
	class Window;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T> class DependencyProperty;

	template<typename T, typename... Types>
	static Ref<T> Create(Types&&... args) {
		return std::make_shared<T>(std::forward<Types>(args)...);
	}

	class UIElement;

	class DependencyObject abstract {
	public:

		template<typename T, typename R = DependencyObject>
		R& SetValue(DependencyProperty<T>& dp, const T& value, bool checkForChange = true) {
			dp.SetValue(*this, value, checkForChange);
			return static_cast<R&>(*this);
		}

		template<typename T>
		const T& GetValue(const DependencyProperty<T>& dp) const {
			return dp.GetValue(*this);
		}

		template<typename TObject>
		TObject& As() const {
			return static_cast<TObject&>(*this);
		}

		UIElement* GetParent() const;

		virtual bool IsUIElement() const {
			return false;
		}

		virtual void Invalidate() {}
		Window* GetWindow() const;

		void SetWindow(Window* window) {
			_window = window;
		}

	private:
		Window* _window = nullptr;
	};

	enum class PropertyMetadataFlags {
		None = 0,
		AffectsRender = 1,
		AffectsLayout = 2,
		Inherit = 4,
		AffectsParentRender = 8,
		AffectsParentLayout = 16
	};
	DEFINE_ENUM_FLAG_OPERATORS(PropertyMetadataFlags);

	template<typename T>
	class DependencyProperty {
	public:
		using PropertyChangedHandler = std::function<void(DependencyObject&, const T&, const T&)>;

		DependencyProperty(const char* name, const T& defaultValue = T(), PropertyMetadataFlags flags = PropertyMetadataFlags::None)
			: _name(name), _defaultValue(defaultValue), _flags(flags) { }

		const std::string& GetName() const {
			return _name;
		}

		PropertyMetadataFlags GetFlags() const {
			return _flags;
		}

		const T& GetDefaultValue() const {
			return _defaultValue;
		}

		template<typename Type>
		Type& SetValue(Type& object, const T& value, bool checkForChange = true) {
			if (checkForChange) {
				const auto& oldValue = GetValue(object);
				_values[&object] = value;
				InvokeHandlers(object, oldValue, value);

				// check if render is affected
				if ((_flags & (PropertyMetadataFlags::AffectsRender | PropertyMetadataFlags::AffectsLayout)) == PropertyMetadataFlags::AffectsRender) {
					object.Invalidate();
				}
			}
			else {
				_values[&object] = value;
			}

			return object;
		}

		const T& GetValue(const DependencyObject& object) const {
			auto it = _values.find(&object);
			if (it != _values.end())
				return it->second;

			if ((_flags & PropertyMetadataFlags::Inherit) == PropertyMetadataFlags::Inherit) {
				auto parent = object.GetParent();
				if (parent)
					return GetValue(*reinterpret_cast<DependencyObject*>(parent));
			}
			return _defaultValue;
		}

		void RegisterPropertyChangedHandler(const PropertyChangedHandler& handler) {
			_handlers.push_back(handler);
		}

		void InvokeHandlers(DependencyObject& object, const T& oldValue, const T& newValue) {
			for (auto& handler : _handlers)
				handler(object, oldValue, newValue);
		}

		struct PropertyChangedData {
			PropertyChangedHandler Handler;
			DependencyObject* Instance;
		};

	private:
		T _defaultValue;
		std::map<const DependencyObject*, T> _values;
		std::string _name;
		PropertyMetadataFlags _flags;
		std::vector<PropertyChangedHandler> _handlers;
	};

	//template<typename T>
	//std::map<const DependencyObject*, T> DependencyProperty<T>::_values;

	class DeviceDependentResource abstract : public DependencyObject {
	protected:
		DeviceDependentResource() { }

	private:
	};
}

#define DECLARE_DP(class, name, type)	\
	public: static DependencyProperty<type> name##Property;	\
	class& name(const type& value) { return SetValue<type, class>(name##Property, value); }	\
	const type& name() const { return GetValue(name##Property); }

#define DECLARE_DP_REF(class, name, type)	\
	public: static DependencyProperty<type> name##Property;	\
	Ref<class>& name(const type& value) { return SetValue<type, class>(name##Property, value); }	\
	const type& name() const { return GetValue(name##Property); }

#define DEFINE_DP(class, name, type, defaultValue)	\
	DependencyProperty<type> class::name##Property(#name, defaultValue)

#define DEFINE_DP_WITH_FLAGS(class, name, type, defaultValue, flags)	\
	DependencyProperty<type> class::name##Property(#name, defaultValue, flags)

#define DECLARE_AP(name, type)	\
	static DependencyProperty<type> name##Property;	\
	static void name(UIElement& element, type value) {	\
		element.SetValue(name##Property, value);	\
	}	\
	static type name(UIElement& element) {	\
		return element.GetValue(name##Property);	\
	}	\
	static void name(Ref<UIElement> element, type value) { 	\
		element->SetValue(name##Property, value);	\
	}	

#define DEFINE_AP(class, name, type, defaultValue)	\
	DependencyProperty<type> class::name##Property(#name, defaultValue);


