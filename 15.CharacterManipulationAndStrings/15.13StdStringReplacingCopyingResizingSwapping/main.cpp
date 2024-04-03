#include <fmt/format.h>
#include <string>

int main()
{

  // Replacing (1)
  // basic_string& replace( size_type pos, size_type count,const basic_string& str );
  // Replace the range [pos, pos + count] with str
  /*std::string str1 {"Finding Nemo"}; // Replace Finding with 'Searching For'
  std::string str1_2 {"Searcing For"};
  fmt::println( "str1 : {}" , str1 );

  fmt::println( "Replacing..." );
str1.replace(0,7,str1_2);

fmt::println( "str1 : {}" , str1 );*/

  // Replacing - (2)
  // basic_string& replace( size_type pos, size_type count,
  // const basic_string& str,
  // size_type pos2, size_type count2 = npos );
  // Replace in part of str, not its entirety
  /*
  std::string str2 {"Finding Nemo"};
std::string str3 {"The Horse was Found in the Fields Searching For Food"};

  fmt::println( "str2 : {}" , str2 );

  fmt::println( "Replacing..." );
str2.replace(0,7,str3,34,13);

fmt::println( "str2 : {}" , str2 );
*/

  // Copying
  // size_type copy( CharT* dest,size_type count,size_type pos = 0)
  // Copy a subsection of *this string to dest. Dest is pre-allocated
  //  The resulting character string is not null-terminated. Be careful
  /*
  std::string str4{"Climbing Kirimanjaro"};
  char txt4[15] {}; //Initialized with zero equivalent for characters which is '\0'
  fmt::println( "std::size(txt4) : {}" , std::size(txt4) );
  fmt::println( "txt4 : {}" , txt4 );

      fmt::println( "Copying..." );
  str4.copy(txt4,11,9);

      //Safe to print because the char array was initialized with '\0' s.
  fmt::println( "txt4 : {}" , txt4 );
  */


  // Resizing
  // std::resize(
  /*
  std::string str5{"Hello"};

  fmt::println( "null char : {}" , '\0' );
      fmt::println( "str5 : {}" , str5 );
  fmt::println( "str5.size() : {}" , str5.size() );
  fmt::println( "str5.capacity() : {}" , str5.capacity() );

      fmt::println( "Resizing..." );
  str5.resize(8); // This fills new char place holders with
                                              //null character by default, you can't print and see them

      fmt::println( "str5 : {}" , str5 );
  fmt::println( "str5.size() : {}" , str5.size() );
  fmt::println( "str5.capacity() : {}" , str5.capacity() );

      //Prove that they are indeed null characters
  fmt::println( "Printing through loop : " );
      for(size_t i{} ; i < str5.size() ; ++i){
              fmt::println( {}i , ":{}" , str5[i] );
      }


  //Resize and specify autofill character
  fmt::println( "Resize and specify autofill character : " );
  str5.resize(10,'*');
      fmt::println( "str5 : {}" , str5 );
  fmt::println( "str5.size() : {}" , str5.size() );
  fmt::println( "str5.capacity() : {}" , str5.capacity() );


  //Resize down
  fmt::println( "Resize down : " );
  str5.resize(5);
      fmt::println( "str5 : {}" , str5 );
  fmt::println( "str5.size() : {}" , str5.size() );
  fmt::println( "str5.capacity() : {}" , str5.capacity() );
  */


  // Swapping
  std::string str_a{ "This is a string stored in A" };
  std::string str_b{ "This is a string stored in B and it's really great to be able to do that." };

  // Before swap
  fmt::println("str_a : {}", str_a);
  fmt::println("str_b : {}", str_b);
  fmt::println("str_a.size() :{}", str_a.size());
  fmt::println("str_a.capaity() : {}", str_a.capacity());
  fmt::println("str_b.size() :{}", str_b.size());
  fmt::println("str_b.capaity() : {}", str_b.capacity());

  fmt::println("Swapping...");
  str_a.swap(str_b);

  // After swap
  fmt::println("str_a : {}", str_a);
  fmt::println("str_b : {}", str_b);
  fmt::println("str_a.size() :{}", str_a.size());
  fmt::println("str_a.capaity() : {}", str_a.capacity());
  fmt::println("str_b.size() :{}", str_b.size());
  fmt::println("str_b.capaity() : {}", str_b.capacity());


  return 0;
}