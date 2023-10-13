module;
export module math;

namespace math {
	export double add(double a, double b);
}

module: private;

namespace math {
	double add(double a, double b) {
		return a + b;
	}
}