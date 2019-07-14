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
		USING_PROPS_TYPES(T, public)

		protected:
			ref_type ref;
			getter_type getter = props::get;
			setter_type setter = props::set;

		public:
			Prop(ref_type ref, getter_type get = props::get, setter_type set = props::set)
			: ref{ref}, getter{get}, setter{set} {
			}

			operator const_ref_type(){
				return this->getter(this->ref);
			}

			virtual Prop& operator=(const_ref_type newValue){
				this->setter(this->ref, newValue);
				return *this;
			}
	};
}