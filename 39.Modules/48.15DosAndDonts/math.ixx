module;

export module math;

//Dont's do this.
/*
namespace {
	export int add(int a, int b) {return a + b;}
}

export static int  VERSION = 1;

struct Point {
	export int x;
	int y;
}

*/



//This is ok.
export {
	template <typename T> T add(T a, T b) { return a + b; }
}

export template <typename T> T sub(T a, T b) { return a - b; }

export template <typename T>
concept Multipliable = requires (T a, T b) {
	{a* b};
};

export int VERSION = 1;

export struct Point {
	int x;
	int y;
};
