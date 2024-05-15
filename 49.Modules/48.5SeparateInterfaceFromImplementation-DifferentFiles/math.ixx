module;
// Global module fragment
#include <string>
#include <fmt/format.h>

export module math_stuff; // Module declaration
//Module preamble
// import <iostream>;

//Module purview
export{

	double add(double a, double b);

	void greet(const std::string& name);

	void print_name_length(const char* c_str_name);

	class Point {
		friend struct fmt::formatter<Point>;
	public:
		Point() = default;
		Point(double x, double y);
		/*friend std::ostream& operator << (std::ostream& out, const Point& point) {
			out << "Point [ x : " << point.m_x << ", y : " << point.m_y << "]";
			return out;
		}
		*/

	private:
		double m_x;
		double m_y;
	};
}

// Point fmt stream overload
template <>
struct fmt::formatter<Point>
{
	constexpr auto parse(format_parse_context& ctx){return ctx.begin(); }
	template<typename FormatContext>
	auto format(const Point& obj, FormatContext& ctx)
	{
		return format_to(ctx.out(), "Point [x: {}, y: {}]", obj.m_x, obj.m_y);
	}
};
