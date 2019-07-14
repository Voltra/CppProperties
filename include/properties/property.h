#pragma once

#include <functional>
#include <utility>

namespace props{
	/**
	 * @class props::property
	 * @tparam T being the type of the underlying data
	 * @brief A guarded property that is accessed through getters and setters only
	 */
	template <class T>
	class property{
		public:
			using value_type = T;
			using ref_type = T&;
			using const_ref_type = const T&;

			using getter_type = std::function<const_ref_type(ref_type)>;
			using setter_type = std::function<void(ref_type, const_ref_type)>;

		public:
			static getter_type get;
			static setter_type set;
			static setter_type noSet;

		protected:
			value_type data;
			getter_type getter = property::get;
			setter_type setter = property::set;

		public:
			template <class U>
			property(U&& data, getter_type get = property::get, setter_type set = property::set)
			: data{std::forward<U>(data)}, getter{get}, setter{set} {
			}

			operator const_ref_type(){
				return this->getter(
					std::ref(this->data)
				);
			}

			virtual property& operator=(const_ref_type newValue){
				this->setter(
					std::ref(this->data),
					newValue
				);

				return *this;
			}
	};
}

template <class T>
typename props::property<T>::getter_type props::property<T>::get = [](T& e) -> const T&{
	return e;
};

template <class T>
typename props::property<T>::setter_type props::property<T>::set = [](T& data, const T& newValue) -> void{
	data = newValue;
};

template <class T>
typename props::property<T>::setter_type props::property<T>::noSet = [](T& data, const T& newValue) -> void{
};
