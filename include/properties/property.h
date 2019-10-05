#pragma once

#include <functional>
#include <utility>
#include <properties/utils.h>

namespace props{
	/**
	 * @class props::property
	 * @tparam T being the type of the underlying data
	 * @brief A guarded property that is accessed through getters and setters only
	 */
	template <class T>
	class property{
		USING_PROPS_TYPES(T, public)
		PROPS_OPERATORS(property)

		protected:
			/**
			 * @var data
			 * @brief The data that is accessed through getters and setters
			 */
			value_type data;

			/**
			 * @var getter
			 * @brief The getter used to retrieve data
			 */
			getter_type getter = props::get<value_type>;

			/**
			 * @var setter
			 * @brief The setter used to alter data
			 */
			setter_type setter = props::set<value_type>;

		public:
			/**
			 * @brief Construct from data and getters/setters
			 * @tparam U being the type of the data to construct from
			 * @param data being the data to construct from
			 * @param get being the getter to use
			 * @param set being the setter to use
			 */
			template <class U>
			property(U&& data, getter_type get = props::get<value_type>, setter_type set = props::set<value_type>)
			: data{std::forward<U>(data)}, getter{get}, setter{set} {
			}

			/**
			 * @brief Get the data from the property
			 * @return a const reference to the underlying data
			 */
			operator const_ref_type(){
				return this->getter(
					std::ref(this->data)
				);
			}

			/**
			 * @brief Set the data using the property
			 * @param newValue being the value to assign
			 * @return a reference to this property
			 */
			virtual property& operator=(const_ref_type newValue){
				this->setter(
					std::ref(this->data),
					newValue
				);

				return *this;
			}
	};
}
