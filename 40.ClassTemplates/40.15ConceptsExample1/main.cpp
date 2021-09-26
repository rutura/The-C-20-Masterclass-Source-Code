#include <iostream>
#include <concepts>
#include <vector>

template <typename T>
concept OutputStreamable = requires(std::ostream& o , T d){
	o << d;
};


template <OutputStreamable T>
std::ostream & operator << (std::ostream& out, const std::vector<T> & vec){
   	out << " [ ";
  	for(auto i : vec){
      	out << i  << " ";
   	 }
   	out << "]";
   	return out;
}


struct Point{
	double mx;
	double my;

	friend std::ostream& operator<<( std::ostream& o, const Point p){
		o << "Point [ x : " << p.mx << ", y : " << p.my << "]";
		return o;
	}
   
};


int main(){

    std::vector<int> numbers {1,2,3,4,5};
    std::cout << "numbers : " << numbers << std::endl;

    std::vector<Point> points {{10,20} , {59,45}};
    std::cout << "points : " << points << std::endl;
   
    return 0;
}