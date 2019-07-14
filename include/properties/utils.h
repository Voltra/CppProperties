#pragma once
#include <functional>

namespace props{
	/**
	 * @brief traits type that stores type information about properties
	 * @tparam T being the underlying data type
	 */
	template <class T>
	struct property_traits{
		using value_type = T;
		using ref_type = T&;
		using const_ref_type = const T&;

		using getter_type = std::function<const_ref_type(ref_type)>;
		using setter_type = std::function<void(ref_type, const_ref_type)>;
	};

#define PROP typename property_traits<T>

	/**
	 * @brief Default getter that just transmits the data
	 * @tparam T being the underlying data type
	 * @param current being the current value of a property
	 * @return a const reference to a value of the same type
	 */
	template <class T>
	PROP::const_ref_type get(PROP::ref_type current){
		return static_cast<PROP::const_ref_type>(current);
	}



	/**
	 * @brief Default setter that just assigns the value
	 * @tparam T being the underlying data type
	 * @param oldValue being the current value in the property
	 * @param newValue being the assigned value
	 */
	template <class T>
	void set(PROP::ref_type oldValue, PROP::const_ref_type newValue){
		oldValue = newValue;
	}

	/**
	 * @brief Setter that accomplishes nothing
	 * @tparam T being the underlying data type
	 * @param oldValue being the current value in the property
	 * @param newValue being the assigned/ignored value
	 */
	template <class T>
	void noSet(PROP::ref_type oldValue, PROP::const_ref_type newValue){}

#undef PROP
}

/**
 * @def USING_PROPS_TYPES(T, visibility)
 * @brief "using" types from traits for a specific type using a specific visibility
 */
#define USING_PROPS_TYPES(T, visibility)\
	protected:\
		using trait = property_traits<T>;\
		\
	visibility:\
		using value_type = typename trait::value_type;\
		using ref_type = typename trait::ref_type;\
		using const_ref_type = typename trait::const_ref_type;\
		using getter_type = typename trait::getter_type;\
		using setter_type = typename trait::setter_type;
