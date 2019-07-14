#pragma once
#include <properties/property.h>

namespace props{
	/**
	 * @class props::Guarded
	 * @tparam T being the underlying data type
	 * @brief A guarded proxy by reference
	 */
	template <class T>
	class ReadProp{
		USING_PROPS_TYPES(T, public)

		protected:
			ref_type ref;
			getter_type getter = props::get;

		public:
			ReadProp(ref_type ref, getter_type get = props::get) : ref{ref}, getter{get}{
			}

			operator const_ref_type(){
				return this->getter(this->ref);
			}

			ReadProp& operator=(const_ref_type newValue) = delete;
	};
}