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

    template<typename T>
    static Ref<T> Create(std::initializer_list<Ref<UIElement>> list) {
        return std::make_shared<T>(list);
    }

	class UIElement;

    enum class BindingMode {
        Default,
        OneWay,
        TwoWay,
        OneTime
    };

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

        template<typename TObject>
        const TObject* DynamicAs() const {
            return dynamic_cast<const TObject* const>(this);
        }
        
        const UIElement* GetParent() const;

		virtual void Invalidate() {}
        virtual void InvalidateLayout(bool = true) { }

        Window* GetWindow() const {
            return _window;
        }

		virtual void SetWindow(Window* window) {
			_window = window;
		}

        template<typename T>
        void BindTo(DependencyProperty<T>& targetDP, DependencyObject& source, DependencyProperty<T>& sourceDP, BindingMode mode = BindingMode::Default) {
            targetDP.BindTo(*this, source, sourceDP, mode);
        }

    protected:
        DependencyObject() {
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
	};
	DEFINE_ENUM_FLAG_OPERATORS(PropertyMetadataFlags);

	template<typename T>
	class DependencyProperty {
	public:
        using PropertyChangedHandler = std::function<void(DependencyObject&, DependencyProperty<T>&, const T&, const T&)>;

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
				InvokeHandlers(object, *this, oldValue, value);

				// check if render is affected
				if ((_flags & (PropertyMetadataFlags::AffectsLayout)) == PropertyMetadataFlags::AffectsLayout) {
					object.InvalidateLayout();
				}
                else if ((_flags & (PropertyMetadataFlags::AffectsRender)) == PropertyMetadataFlags::AffectsRender) {
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
					return GetValue(*parent);
			}
			return _defaultValue;
		}

        void BindTo(DependencyObject& target, DependencyObject& source, DependencyProperty<T>& sourceDP, BindingMode mode = BindingMode::Default) {
            sourceDP.RegisterPropertyChangedHandler(&source, [&target, this](auto& object, auto&, const T&, const T& newValue) {
                target.SetValue(*this, newValue);
            });
         }

		void RegisterPropertyChangedHandler(DependencyObject* object, PropertyChangedHandler handler) {
			_handlers[object].push_back(handler);
		}

        void RegisterPropertyChangedHandler(DependencyObject& object, PropertyChangedHandler handler) {
            _handlers[&object].push_back(handler);
        }

		void InvokeHandlers(DependencyObject& object, DependencyProperty& dp, const T& oldValue, const T& newValue) {
            auto it = _handlers.find(&object);
            if (it == _handlers.end())
                return;

			for (auto& handler : it->second)
				handler(object, dp, oldValue, newValue);
		}

	private:
		T _defaultValue;
		std::map<const DependencyObject*, T> _values;
		std::string _name;
		PropertyMetadataFlags _flags;
		std::map<DependencyObject*, std::vector<PropertyChangedHandler>> _handlers;
	};

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


