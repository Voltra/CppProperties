#include <iostream>
#include <properties/properties.hpp>

using namespace props;

const int& logGet(int& data){
	std::cout << "[GET] data: " << data << '\n';
	return static_cast<const int&>(data);
}

void logSet(int& oldValue, const int& newValue){
	std::cout << "[SET] old: " << oldValue << " new: " << newValue << '\n';
	oldValue = newValue;
}

class T{
	protected:
		int i = 0;

	public:
		Guarded<int> I;

		explicit T(int a = 0) : i{a}, I{this->i, logGet, logSet} {
		}
};

int main() {
	/*property<int> i{0, logGet, logSet};
	i = 14;
	return i;*/

	T t;
	t.I = 42;
	return t.I;
}