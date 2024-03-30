#include <fmt/format.h>

const double adjustment{0.724};

namespace No_Adjust
{
    double add(double x, double y){
        return x + y;
    }     
} // namespace name

namespace Adjust
{
    double add(double x, double y){
        return x+ y - adjustment;
    }  
} // namespace Adjust

namespace No_Adjust
{
    double mult(double x, double y); // Declarations
    double div(double x, double y);
    
} // namespace No_Adjust

namespace Adjust
{
    double mult(double x, double y); // Declarations
    double div(double x, double y);    
} // namespace Adjust





int main(){

   double result = No_Adjust::div(12,3);
   fmt::println( "result : {}" , result );
    return 0;
}


namespace No_Adjust
{
    double mult(double x, double y){
        return x * y;
    }
    double div(double x, double y){
        return x / y;
    }
    
} // namespace No_Adjust

namespace Adjust
{
    double mult(double x, double y){
        return x * y - adjustment;
    }
    double div(double x, double y){
        return x / y - adjustment;
    }    
} // namespace Adjust