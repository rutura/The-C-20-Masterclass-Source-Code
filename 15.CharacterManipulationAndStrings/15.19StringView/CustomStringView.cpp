#include<iostream>
#include<cstring>
using namespace std;


class CustomStringView{
    //using constreference = const T &;
    using constpointer = const char *;

public:
    CustomStringView() = default;
    CustomStringView(string str){
        myptr = str.c_str();
        size = str.length();
    }

    CustomStringView(const char *str){
        myptr = str;
        size = strlen(str);
    }

    ~CustomStringView(){
        delete myptr;
        size = 0;
    }

    size_t length(){
        return size;
    }

    constpointer data(){
        return myptr;
    }


private:
    constpointer myptr{nullptr};
    size_t  size{0};
};

int main(){

    cout << "Welcome to CustomStringView" << endl;
    CustomStringView str(string{"Hello World"}); 
    cout << "Length of string: " << str.length() << endl;
    cout << "String Holded: " << str.data() << endl;


    const char *temp{"How are you"};
    CustomStringView array(temp);
    cout << "Length of string: " << array.length() << endl;
    cout << "String Holded: " << array.data() << endl;
    return 0;
}