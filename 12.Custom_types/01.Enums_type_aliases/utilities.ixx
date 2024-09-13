module;
#include <string_view>
#include <fmt/format.h>
//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

//Module purview
// Declare an enum type
// The default type associated with enum classes with C++ is int
// unsigned char : 0 ~ 255
enum class Month : char {
	 Jan = -1, 
	 January = Jan, 
	 Feb, 
	 Mar, Apr, May, Jun, Jul, Aug, Sep, Oct = 100, Nov, Dec };


//Old enums
enum Direction : unsigned char { TopLeft = 64, TopRight, Center, BottomLeft, BottomRight };

enum Tool { Pen, Marker, Eraser, Rectangle, Circle, PaintBucket };

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

std::string_view month_to_string(Month month)
{
  switch (month) {
    /*
    case Month::Jan : return "January";
    case Month::Feb : return "February";
    case Month::Mar : return "March";
    case Month::Apr : return "April";
    case Month::May : return "May";
    case Month::Jun : return "June";
    case Month::Jul : return "July";
    case Month::Aug : return "August";
    case Month::Sep : return "September";
    case Month::Oct : return "October";
    case Month::Nov : return "November";
    case Month::Dec : return "December";
    default : return "None";
    */
    using enum Month;
  case Jan:
    return "January";
  case Feb:
    return "February";
  case Mar:
    return "March";
  case Apr:
    return "April";
  case May:
    return "May";
  case Jun:
    return "June";
  case Jul:
    return "July";
  case Aug:
    return "August";
  case Sep:
    return "September";
  case Oct:
    return "October";
  case Nov:
    return "November";
  case Dec:
    return "December";
  default:
    return "None";
  }
}

export void enum_classes(){
	Month month{ Month::Nov };
	fmt::println("month : {}", static_cast<int>(month));
	fmt::println("sizeof(month) : {}", sizeof(month));
}

export void using_enum(){
	Month month{ Month::Apr };
	//auto result = 2 + month; Can't treat enum like a number.
	fmt::println("month : {}", month_to_string(month));
}

export void old_enums(){
	Direction direction{ Direction::TopLeft };
	Tool tool{ Tool::Pen };

	//auto result = 2 + tool; This compiles. BAD.

	//fmt::println("direction : {}", static_cast<unsigned int>(direction));
	//fmt::println( "tool : {}" , tool );
	//fmt::println( "(tool > direction) : {}" , (tool > direction);	//This comparison doesn't make sense.
}

export void type_aliases(){
	using HugeInt = unsigned long long int;// Recommended in modern C++
	// typedef unsigned long long int HugeInt; // Older C++ syntax for type aliases
	HugeInt huge_number{ 123378997 };

	fmt::println("sizeof(unsigned long long int ) : {}", sizeof(unsigned long long int));
	fmt::println("sizeof(HugeInt) : {}", sizeof(HugeInt));

	fmt::println("huge_number : {}", huge_number);
}