module;
#include <random>
export module math;

import <iostream>;


namespace math {
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
}


namespace math {
	// Function to generate a random 2D Point with x and y coordinates in the specified ranges
	export Point generateRandomPoint() {
		// Create random number generator engines for x and y
		std::random_device rd;
		std::mt19937 genXY(rd());

		// Define distributions for x and y coordinates
		std::uniform_real_distribution<double> distXY(0, 99);

		return Point(distXY(genXY), distXY(genXY));
	}
}