module;

#include <iostream>
#include <random>

export module more_on_modules_05;

namespace more_on_modules_05{

    //The point class is not eexported.
    //A class to represent a Point in 2D space with x and y coordinates together with getters and setters
	class Point {
	private:
		double x;
		double y;
	public:
		Point(double x, double y) {
			this->x = x;
			this->y = y;
		}

		//An outuput stream operator to print the point
		friend std::ostream& operator<<(std::ostream& os, const Point& p) {
			os << "(" << p.x << ", " << p.y << ")";
			return os;
		}
		double getX() { return x; }
		double getY() { return y; }
		void setX(double x) { this->x = x; }
		void setY(double y) { this->y = y; }
	};


    //The function using returning Point is exported, even though Point itself is not exported.
	export Point generate_random_point() {
		// Create random number generator engines for x and y
		std::random_device rd;
		std::mt19937 genXY(rd());

		// Define distributions for x and y coordinates
		std::uniform_real_distribution<double> distXY(0, 99);

		return Point(distXY(genXY), distXY(genXY));     //When a Point object is returned, it will be reachable, but not visible.
	}

}   //namespace more_on_modules_05