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
		public:
			using value_type = typename property<T>::value_type;
			using const_ref_type = typename property<T>::const_ref_type;
			using getter_type = typename property<T>::getter_type;

		public:
			using property<T>::operator const_ref_type;
			using property<T>::operator=;

			template <class U>
			readonly(U&& data, getter_type get = property<T>::get) : property<T>{std::forward<U>(data), get, property<T>::noSet} {
			}
	};

	/**
	 * @class props::preadonly
	 * @tparam T being the underlying data type
	 * @brief A guarded property which cannot be set
	 */
	template <class T>
	class preadonly{
		public:
			using prop_type = property<T>;
			using value_type = typename prop_type::value_type;
			using ref_type = typename prop_type::ref_type;
			using const_ref_type = typename prop_type::const_ref_type;

			using getter_type = typename prop_type::getter_type;
			using setter_type = typename prop_type::setter_type;

		protected:
			value_type data;
			getter_type getter = prop_type::get;

		public:
			template <class U>
			preadonly(U&& data, getter_type get = prop_type::get) : data{std::forward<U>(data)}, getter{get} {
			}

			operator const_ref_type(){
				return this->getter(
					std::ref(this->data)
				);
			}

			preadonly& operator=(const_ref_type) = delete;
	};
}