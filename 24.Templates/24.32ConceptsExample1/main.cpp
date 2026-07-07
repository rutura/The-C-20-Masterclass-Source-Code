#include <iostream>
#include <concepts>
#include "boxcontainer.h"

template <typename T>
concept OutputStreamable = requires(std::ostream& o , T d){
	o << d;
};


struct Point{
	double mx;
	double my;

	friend std::ostream& operator<<( std::ostream& o, const Point p){
		o << "Point [ x : " << p.mx << ", y : " << p.my << "]";
		return o;
	}

};


// OutputStreamable constrains T to only those types that can already be
// streamed with <<. BoxContainer<T> itself satisfies this - it defines its
// own operator<< (boxcontainer.h) - so a function built around this concept
// can accept a BoxContainer<Point> just as easily as a BoxContainer<int>.
template <OutputStreamable T>
void print_streamable(const T& value){
   	std::cout << value << std::endl;
}


int main(){

    BoxContainer<int> numbers;
    numbers.add(1);
    numbers.add(2);
    numbers.add(3);
    print_streamable(numbers);

    BoxContainer<Point> points;
    points.add({10,20});
    points.add({59,45});
    print_streamable(points);

    return 0;
}
