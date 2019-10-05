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
		Prop<int> RW;
		ReadProp<int> R;
		WriteProp<int> W;

		explicit T(int a = 0) : i{a}, RW{this->i, logGet, logSet}, R{this->i, logGet}, W{this->i, logSet} {
		}
};

class Index{
	protected:
		int i = 0;
		int base1 = 0;

	public:
		Prop<int> index;
		ReadProp<int> indexPlusOne;

		explicit Index(int x = 0) :
			i{x},
			base1{x+1},
			index{this->i, get<int>, [&](int& self, const int& that){
				this->base1 = that + 1;
				self = that;
			}}, indexPlusOne{this->base1} {
		}
};

int main() {
	/*property<int> i{0, logGet, logSet};
	i = 14;
	return i;*/

	/*T t;
	t.W = 42;
	return t.R;*/

	Index i{0};
	i.index += 2;
	return i.indexPlusOne;
}