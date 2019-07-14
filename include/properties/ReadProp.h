#pragma once
#include <properties/readonly.h>

namespace props{
	/**
	 * @class props::Guarded
	 * @tparam T being the underlying data type
	 * @brief A guarded proxy by reference
	 */
	template <class T>
	class ReadProp{
		public:
			using prop_type = readonly<T>;
			using value_type = typename prop_type::ref_type;
			using ref_type = typename prop_type::ref_type;
			using const_ref_type = typename prop_type::const_ref_type;

			using getter_type = typename prop_type::getter_type;

		public:
			static getter_type get;

		protected:
			value_type data;
			getter_type getter = get;

		public:
			ReadProp(value_type data, getter_type get = ReadProp::get)
					: data{data}, getter{get}{
			}

			operator const_ref_type(){
				return this->getter(this->data);
			}

			ReadProp& operator=(const_ref_type newValue) = delete;
	};
}

template <class T>
typename props::ReadProp<T>::getter_type props::ReadProp<T>::get = props::property<T>::get;