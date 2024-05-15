#include <fmt/format.h>

int main()
{

  // Setw on numbers before you print them
  const size_t ROWS{ 12 };
  const size_t COLS{ 3 };


  /*
      fmt::println("Tabular data visualization with nested for loops : ");



      for (size_t row{0} ; row < ROWS ; ++ row){

              for (size_t col{0} ; col < COLS ; ++col){

                      fmt::println("( row {:>2}, col {:>2})", row, col);
              }
  }

  */


  // While loop
  /*
       fmt::println("Tabular data visualization with nested while loops : " << );

       //Remember to reset col to 0 after the inner loop is done for the next row
   // to use the right columns.
   size_t row {0};
   size_t col {0};

   while(row < ROWS){

       while(col < COLS){
                       fmt::println("( row {:>2}, col {:>2})", row, col);
           ++col;
       }
       col = 0 ;   // Reset col to 0 to allow printing from col 0 . col is in main
                   // function local scope now.
       ++row;
   }

   */


  fmt::println("Tabular data visualization with nested do while loops : ");

  size_t row = 0;
  size_t col = 0;

  do {// row

    do {
      fmt::println("( row {:>2}, col {:>2})", row, col);
      ++col;
    } while (col < COLS);

    col = 0;// Reset col to 0 to allow printing from col 0 . col is in main
            // function local scope now.
    ++row;
  } while (row < ROWS);


  return 0;
}