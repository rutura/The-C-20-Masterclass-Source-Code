#include <cstdlib>
#include <ctime>
#include <fmt/format.h>

int main()
{

  std::srand(std::time(0));// Seed

  /*
  int random_num = std::rand();

  fmt::println("random_num : {}",random_num ); // 0 ~ RAND_MAX

  random_num = std::rand();
  fmt::println("random_num : {}", random_num ); // 0 ~ RAND_MAX
  */


  // Generate random numbers in a loop
  /*
  int random_num;

  for(size_t i {0} ; i < 20 ; ++i){
      random_num = std::rand();
      fmt::println("random_num {}: {}", i,  random_num ); // 0 ~ RAND_MAX
  }
  */


  // Generate a range between 0 and 10
  /*
  int random_num =  std::rand() % 11;                  // [ 0 ~10]

  for(size_t i {0} ; i < 20 ; ++i){
      random_num = std::rand() % 11;
      fmt::println("random_num {} : {} ", i,  random_num ); // 0 ~ RAND_MAX
  }
  */


  int random_num = std::rand() % 10 + 1;// [1~10]
  for (size_t i{ 0 }; i < 20; ++i) {
    random_num = std::rand() % 10 + 1;
    fmt::println("random_num {} : {}", i, random_num);// 0 ~ RAND_MAX
  }


  return 0;
}