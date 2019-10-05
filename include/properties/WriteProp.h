#pragma once
#include <properties/property.h>

namespace props{
	/**
	 * @class WriteProp
	 * @tparam T being the underlying data type
	 * @brief A write-only proxy by reference
	 */
	template <class T>
	class WriteProp{
		USING_PROPS_TYPES(T, public)
		PROPS_OPERATORS(WriteProp)

		protected:
			/**
			 * @var ref
			 * @brief A reference to the guarded data
			 */
			ref_type ref;

			/**
			 * @var setter
			 * @brief The setter used to alter data
			 */
			setter_type setter = props::set<value_type>;

		public:
			/**
			 * @brief Construct a property from a reference and a setter
			 * @param ref being a reference to the guarded data
			 * @param set being the setter to use
			 */
			WriteProp(ref_type ref, setter_type set = props::set<value_type>) : ref{ref}, setter{set} {
			}

			operator const_ref_type() = delete;

			/**
			 * @brief Mutate the guarded data through the provided setter
			 * @param newValue being the value to assign
			 * @return a reference to this Prop
			 */
			virtual WriteProp& operator=(const_ref_type newValue){
				this->setter(this->ref, newValue);
				return *this;
			}
	};
}