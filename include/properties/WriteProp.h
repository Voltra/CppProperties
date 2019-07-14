#pragma once
#include <properties/property.h>

namespace props{
	/**
	 * @class props::Guarded
	 * @tparam T being the underlying data type
	 * @brief A guarded proxy by reference
	 */
	template <class T>
	class WriteProp{
		public:
			using prop_type = property<T>;
			using value_type = typename prop_type::ref_type;
			using ref_type = typename prop_type::ref_type;
			using const_ref_type = typename prop_type::const_ref_type;

			using setter_type = typename prop_type::setter_type;

		public:
			static setter_type set;

		protected:
			value_type data;
			setter_type setter = set;

		public:
			WriteProp(value_type data, setter_type set = WriteProp::set)
					: data{data}, setter{set} {
			}

			operator const_ref_type() = delete;

			virtual WriteProp& operator=(const_ref_type newValue){
				this->setter(this->data, newValue);
				return *this;
			}
	};
}

template <class T>
typename props::WriteProp<T>::setter_type props::WriteProp<T>::set = props::property<T>::set;