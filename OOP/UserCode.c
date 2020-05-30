#include "stack.h"

int main(){
    int buf[16];
    Range range = {0,9};
    Validator v = rangeValidatoe(&range);
    Stack st = newStackWithValidator(buf, &v);
    push(&st, 123);
 
    return 0;
}
