#pragma once
#include <properties/property.h>

namespace props{
	/**
	 * @class ReadProp
	 * @tparam T being the underlying data type
	 * @brief A readonly proxy by reference
	 */
	template <class T>
	class ReadProp{
		USING_PROPS_TYPES(T, public)

		protected:
			/**
			 * @var ref
			 * @brief A reference to the guarded data
			 */
			ref_type ref;

			/**
			 * @var getter
			 * @brief The getter used to access the underlying data from outside
			 */
			getter_type getter = props::get<value_type>;

		public:
			/**
			 * @brief Construct a property from a reference and a getter
			 * @param ref being a reference to the guarded data
			 * @param get being the getter to use
			 */
			ReadProp(ref_type ref, getter_type get = props::get<value_type>) : ref{ref}, getter{get}{
			}

			/**
			 * @brief Retrieve the guarded data through the provided getter
			 * @return a const reference to the guarded data
			 */
			operator const_ref_type(){
				return this->getter(this->ref);
			}

			ReadProp& operator=(const_ref_type newValue) = delete;
	};
}