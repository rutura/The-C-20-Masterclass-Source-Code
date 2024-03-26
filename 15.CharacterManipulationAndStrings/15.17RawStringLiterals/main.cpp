#include <fmt/format.h>
#include <string>

int main(){
    //The bad way to do things
    /*
    std::string todo_list {"\tClean the house\n\tWalk the dog\n\tDo laundry\n\tpick groceries"};
    std::string windows_path {"D:\\sandbox\\testProject\\hello.txt"};
	std::string linux_path {"/home/username/files/hello.txt"};
    std::string hint {" \"\\\\\" escapes a backslash character like \\."};
	
	fmt::println( "todo_list : " );
	fmt::println( "{}", todo_list );
	fmt::println( "windows_path : {}" , windows_path );
	fmt::println( "linux_path : {}" , linux_path );
	fmt::println( "hint : {}" , hint );
	*/

   //Use raw string literals
   /*std::string to_do_list {R"(  Clean the house
   Walk the dog
   Do laundry
   Pick groceries)"};

   fmt::println( "to_do_list : " );
   fmt::println( "{}", to_do_list );*/

  //Raw string literals with assignments
  /*std::string to_do_list =   R"(
	Clean the house
	Walk the dog
	Do Laundry
	Pick groceries
    )";

   fmt::println( "to_do_list : " );
   fmt::println( "{}", to_do_list );*/

  //Raw string literals with assignments
  /*const char* c_string {  R"(
	Clean the house
	Walk the dog
	Do Laundry
	Pick groceries
    )"} ;

   fmt::println( "to_do_list : " );
   fmt::println( "{}", c_string );*/

    /*//Fixing other escaped strings
    std::string windows_path1 {R"(D:\sandbox\testProject\hello.txt)"};
	std::string linux_path1 {R"(/home/username/files/hello.txt)"};
    std::string hint1 {R"("\\" escapes a backslash character like \.)"};	
	
	fmt::println( "windows_path1 : {}" , windows_path1 );
	fmt::println( "linux_path1 : {}" , linux_path1 );
	fmt::println( "hint1 : {}" , hint1 );*/

   //Problematic raw string literals
   std::string sentence {R"--(The message was "(Stay out of this!)")--"};

   fmt::println( "sentence : {}" , sentence );

    return 0;
}