module;
#include <string_view>
#include <fmt/format.h>

export module utilities;

import final_keyword;
import final_override_not_keywords;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void final_keyword_demo(){
	fmt::println("Can't inherit from a final class");
}

export void final_override_not_keywords_demo(){
	final_override_not_keywords::override();
}