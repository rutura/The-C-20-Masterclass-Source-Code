module;

#include <string_view>
#include <fmt/format.h>

export module utilities; 

import handling_characters;
import handling_c_strings;
import handling_std_strings;
import escape_raw_string_literals;
import handling_string_view;

export void handling_characters_demo(){

	handling_characters::is_al_num();
	handling_characters::is_alphabetic();
	handling_characters::is_blank();
	handling_characters::is_upercase();
	handling_characters::is_digit();
	handling_characters::change_to_lowercase();

}

export void handling_c_strings_demo(){

	handling_c_strings::cstring_strlen();
	handling_c_strings::cstring_strcmp();
	handling_c_strings::cstring_strncmp();
	handling_c_strings::cstring_find_first_occurence_version_1();
	handling_c_strings::cstring_find_first_occurence_version_2();
	handling_c_strings::cstring_find_last_occurence();
	handling_c_strings::cstring_concatenation_version_1();
	handling_c_strings::cstring_concatenation_version_2();
	handling_c_strings::cstring_strncat();
	handling_c_strings::cstring_strcpy();
	handling_c_strings::cstring_strncpy();

}

export void handling_std_strings_demo(){
	handling_std_strings::std_string_declaration();
	handling_std_strings::std_string_concatenation();
	handling_std_strings::std_string_access_characters();
	handling_std_strings::std_string_size_and_capacity();
	handling_std_strings::std_string_modify();
}


export void escape_raw_string_literals_demo(){

	//escape_raw_string_literals::escape_sequences();
	escape_raw_string_literals::raw_string_litterals();

}


export void handling_string_view_demo(){
	//handling_string_view::string_view_the_problem();
	handling_string_view::string_view_the_solution();
	//handling_string_view::string_view_construction();
	//handling_string_view::std_string_view_visualizes_original_string();
	//handling_string_view::std_string_view_change_view_window();
	//handling_string_view::std_string_view_lifetime();
	//handling_string_view::std_string_view_data();
	//handling_string_view::std_string_view_non_null_terminated_strings();
	//handling_string_view::std_string_view_behaviors();



}