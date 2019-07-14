#pragma once
#include <properties/property.h>

namespace props{
	/**
	 * @class props::Guarded
	 * @tparam T being the underlying data type
	 * @brief A guarded proxy by reference
	 */
	template <class T>
	class Prop{
		public:
			using prop_type = property<T>;
			using value_type = typename prop_type::ref_type;
			using ref_type = typename prop_type::ref_type;
			using const_ref_type = typename prop_type::const_ref_type;

			using getter_type = typename prop_type::getter_type;
			using setter_type = typename prop_type::setter_type;

		public:
			static getter_type get;
			static setter_type set;
			static setter_type noSet;

		protected:
			value_type data;
			getter_type getter = get;
			setter_type setter = set;

		public:
			Prop(value_type data, getter_type get = Prop::get, setter_type set = Prop::set)
			: data{data}, getter{get}, setter{set} {
			}

			operator const_ref_type(){
				return this->getter(this->data);
			}

			virtual Prop& operator=(const_ref_type newValue){
				this->setter(this->data, newValue);
				return *this;
			}
	};
}

template <class T>
typename props::Prop<T>::getter_type props::Prop<T>::get = props::property<T>::get;

template <class T>
typename props::Prop<T>::setter_type props::Prop<T>::set = props::property<T>::set;

template <class T>
typename props::Prop<T>::setter_type props::Prop<T>::noSet = props::property<T>::noSet;