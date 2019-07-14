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
		USING_PROPS_TYPES(T, public)

		protected:
			ref_type ref;
			setter_type setter = props::set;

		public:
			WriteProp(ref_type ref, setter_type set = props::set) : ref{ref}, setter{set} {
			}

			operator const_ref_type() = delete;

			virtual WriteProp& operator=(const_ref_type newValue){
				this->setter(this->ref, newValue);
				return *this;
			}
	};
}