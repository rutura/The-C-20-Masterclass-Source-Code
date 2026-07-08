#include <print>
#include <vector>

// A prompt like "write a function that returns the average of a vector of
// ints" will often get you something that looks exactly like this: clean,
// confident, and plausible at a glance.
double average_v1(const std::vector<int>& values){
	int sum{};
	for (int v : values)
		sum += v;
	return sum / values.size();
}

// The bug: sum / values.size() is int / size_t, so it's integer division --
// average_v1({1, 2}) returns 1, not 1.5. Every course concept up to this
// chapter (types, implicit conversions, operator overloading, the STL) is
// what lets you actually see that bug instead of just trusting the output.
// This is exactly why this chapter comes last: judging AI-generated C++
// requires already knowing C++, not the other way around.
double average_v2(const std::vector<int>& values){
	int sum{};
	for (int v : values)
		sum += v;
	return static_cast<double>(sum) / values.size();
}

int main(){

	std::vector<int> scores{1, 2, 3, 4};

	std::println("average_v1 (buggy)   : {}", average_v1(scores));
	std::println("average_v2 (correct) : {}", average_v2(scores));

	return 0;
}
