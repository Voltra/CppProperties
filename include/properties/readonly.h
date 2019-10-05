#pragma once
#include <properties/property.h>

namespace props{
	/**
	 * @class props::readonly
	 * @tparam T being the underlying data type
	 * @brief A guarded property whose setter has no effect
	 */
	template <class T>
	class readonly : protected property<T>{
		USING_PROPS_TYPES(T, public)

		public:
			using property<T>::operator const_ref_type;
			using property<T>::operator=;

			/**
			 * @brief Construct a readonly property via its data and a getter
			 * @tparam U being the type to construct from
			 * @param data being the data to construct from
			 * @param get being the getter
			 */
			template <class U>
			readonly(U&& data, getter_type get = props::get<value_type>) : property<T>{std::forward<U>(data), get, props::noSet<value_type>} {
			}
	};

	/**
	 * @class props::preadonly
	 * @tparam T being the underlying data type
	 * @brief A guarded property which cannot be set
	 */
	template <class T>
	class preadonly{
		USING_PROPS_TYPES(T, public)

		protected:
			/**
			 * @var data
			 * @brief The underlying data
			 */
			value_type data;

			/**
			 * @var getter
			 * @brief The getter used to access the underlying data from outside
			 */
			getter_type getter = props::get<value_type>;

		public:
			/**
			 * @brief Construct a pure readonly property from data and a getter
			 * @tparam U being the type to construct from
			 * @param data being the data to construct from
			 * @param get being the getter
			 */
			template <class U>
			preadonly(U&& data, getter_type get = props::get<value_type>) : data{std::forward<U>(data)}, getter{get} {
			}

			/**
			 * @brief Access the data from outside the preadonly
			 * @return a const reference to the underlying data
			 */
			operator const_ref_type(){
				return this->getter(
					std::ref(this->data)
				);
			}

			preadonly& operator=(const_ref_type) = delete;
	};
}