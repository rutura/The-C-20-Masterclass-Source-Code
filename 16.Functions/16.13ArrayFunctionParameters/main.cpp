#include <fmt/format.h>


//double sum( double scores[], size_t count){
double sum (double* scores , size_t count){

    double score_sum{};

    /*fmt::println( "sizeof(scores)  : {}" , sizeof(scores) );
    fmt::println( "sizeof(int*) : {}" , sizeof (int *) );
   size_t arr_size = std::size(scores);*/

   for(size_t i{0} ; i < count ; ++i){
       score_sum += scores[i];
   }
    return score_sum;
}



int main(){
    double my_scores[]{10.5,34.3,4.8,6.5};
    //fmt::println( "sizeof(my_scores) : {}" , sizeof(my_scores) );
   

   double result = sum(my_scores,std::size(my_scores));
   fmt::println( "result : {}" , result );
 
    return 0;
}