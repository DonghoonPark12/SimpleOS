#include "stack.h"

/*
    #define newStackWithValidator(buf, pValidator)   {0, sizeof(buf)/sizeof(int), (buf), pValidator}
    
*/

int main(){
    int buf[16];
    Validator v = {validateRange, &{0,9}}; // Funtion addr, Data addr
    Stack st = newStackWithValidator(buf, &v); 
    push(&st, 123);
 
    return 0;
}
