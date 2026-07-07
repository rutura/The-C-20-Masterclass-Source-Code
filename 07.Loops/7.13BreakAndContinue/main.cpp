#include <iostream>


int main(){


    /*
    // break and continue : for loops
    const size_t COUNT{20};


    for(size_t i{0} ; i < COUNT ; ++i ){

        if(i==5)
            continue;

        if(i == 11)
            break; // Breaks out of the loop
        std::cout << "i : " << i << std::endl;
    }
    std::cout << "Loop done!" << std::endl;
    */


   // break and continue : while loop
    /*
   size_t i{0};

   while (i < 20){

       if(i==5){
            ++i;
            continue;
       }

     if(i==11)
        break;


        std::cout << "i : " << i << std::endl;
        ++i;

   }
   std::cout << "Loop done!" << std::endl;
   */


  //break and continue : do while loop
  size_t i{0};

  do{
      if(i==5){
            ++i;
            continue;
       }

     if(i==11)
        break;


        std::cout << "i : " << i << std::endl;
        ++i;

  }while(i <20);
  
    return 0;
}