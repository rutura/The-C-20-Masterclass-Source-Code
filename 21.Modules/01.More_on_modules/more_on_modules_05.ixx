/*
	. Visibility and reachability
*/
module;

#include <iostream>
#include <random>

export module more_on_modules_05;

namespace more_on_modules_05{

    //The point class is not eexported.
    //A class to represent a Point in 2D space with x and y coordinates together with getters and setters
	class Point {
	private:
		double x_;
		double y_;
	public:
		Point(double x, double y) {
			this->x_ = x;
			this->y_ = y;
		}

		//An output stream operator to print the point
		friend std::ostream& operator<<(std::ostream& os, const Point& p) {
			os << "(" << p.x_ << ", " << p.y_ << ")";
			return os;
		}
		double get_x() { return x_; }
		double get_y() { return y_; }
		void set_x(double x) { this->x_ = x; }
		void set_y(double y) { this->y_ = y; }
	};

	//The function returning Point is exported, even though Point itself is not exported.
	export Point generate_random_point() {
		// Create random number generator engines for x and y
		std::random_device random_device;
		std::mt19937 generator_xy(random_device());

		// Define distributions for x and y coordinates
		std::uniform_real_distribution<double> distribution_xy(0, 99);

		return Point(distribution_xy(generator_xy), distribution_xy(generator_xy));     //When a Point object is returned, it will be reachable, but not visible.
	}

}   //namespace more_on_modules_05