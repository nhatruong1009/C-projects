#include <stdarg.h>
#include <iostream>

double __stdcall avg(int num,...){
    va_list va;
    va_start(va,num);
    double total=0;
    for(int i =0;i<num;i++){
        total += va_arg(va,double);
    }
    va_end(va);
    return total/num;
}

// __cdecl: normal call
// __clrcall

double (__stdcall *func)(int,...) = &avg;

int main(){
    std::cout<<func<<"\n";
    std::cout<<avg<<"\n";
    std::cout<<&avg<<"\n";

    std::cout<<"\n"<<avg(5,1.0,2.0,3.0,4.0,5.0);

    return 0;
}