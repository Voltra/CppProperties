#pragma once
#include <properties/property.h>
#include <properties/Prop.h>
#include <vector>
#include <functional>

namespace props{
	/**
	 * @class Watched
	 * @tparam T being the underlying data type
	 * @brief A watchable proxy by reference
	 */
	template <class T>
	class Watched : public Prop<T> {
		USING_PROPS_TYPES(T, public)
		PROPS_OPERATORS(Watched)

		public:
			/**
			 * @typedef listener_type
			 * @brief The type of a listener, being : (const& old, const& new) -> void
			 */
			using listener_type = std::function<void(const_ref_type, const_ref_type)>;

		protected:
			/**
			 * @var listeners
			 * @brief array of change listeners
			 */
			std::vector<listener_type> listeners;

		public:
			using Prop<T>::Prop;
			using Prop<T>::operator const_ref_type;

			/**
			 * @brief Listen to any changes made to the variable
			 * @tparam Listener being the type of the listener
			 * @param listener being the listener to add
			 * @return a reference to this watched property
			 */
			template <class Listener>
			Watched& onChange(Listener&& listener){
				this->listeners.push_back(std::forward<Listener>(listener));
				return *this;
			}

			Watched& operator=(const_ref_type newValue) override{
				for(auto&& listener : this->listeners){
					listener(
						static_cast<const_ref_type>(this->ref),
						newValue
					);
				}

				this->setter(this->ref, newValue);
				return *this;
			}
	};
}