#include "intcontainer.h"
#include "doublecontainer.h"
#include "charcontainer.h"


int main(){

	DoubleContainer double_box1;
	double_box1.add(11.2);
	double_box1.add(33.5);
	
	fmt::println( "double_box1 : {}" , make_streamable(double_box1 ));
	
	IntContainer int_box1;
	int_box1.add(10);
	int_box1.add(20);
	
	fmt::println( "int_box1 : {}" , make_streamable(int_box1) );
	
	CharContainer char_box1;
	char_box1.add('H');
	char_box1.add('e');
	char_box1.add('l');
	char_box1.add('l');
	char_box1.add('o');
	
	fmt::println( "char_box1 : {}" , make_streamable(char_box1) );

    char_box1.remove_all('l');
	fmt::println( "char_box1 : {}" , make_streamable(char_box1) );
    

    return 0;
}