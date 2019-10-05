#pragma once
#include <properties/property.h>

namespace props{
	/**
	 * @class Prop
	 * @tparam T being the underlying data type
	 * @brief A guarded proxy by reference
	 */
	template <class T>
	class Prop{
		USING_PROPS_TYPES(T, public)
		PROPS_OPERATORS(Prop)

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
			getter_type getter = props::get;

			/**
			 * @var setter
			 * @brief The setter used to alter data
			 */
			setter_type setter = props::set;

		public:
			/**
			 * @brief Construct a property from a reference and a getter+setter
			 * @param ref being a reference to the guarded data
			 * @param get being the getter to use
			 * @param set being the setter to use
			 */
			Prop(ref_type ref, getter_type get = props::get, setter_type set = props::set)
			: ref{ref}, getter{get}, setter{set} {
			}

			/**
			 * @brief Retrieve the guarded data through the provided getter
			 * @return a const reference to the guarded data
			 */
			operator const_ref_type(){
				return this->getter(this->ref);
			}

			/**
			 * @brief Mutate the guarded data through the provided setter
			 * @param newValue being the value to assign
			 * @return a reference to this Prop
			 */
			virtual Prop& operator=(const_ref_type newValue){
				this->setter(this->ref, newValue);
				return *this;
			}
	};
}