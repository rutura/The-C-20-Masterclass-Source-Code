#include "need_for_exceptions.h"
namespace need_for_exceptions {
/*  Function throws const char* exception when par_b is zero  */
void process_parameters(int par_a, int par_b)
{

  // Do some processing
  if (par_b == 0) throw "Potential division by 0 detected";

  int result = par_a / par_b;

  // Some other processing.
}
}