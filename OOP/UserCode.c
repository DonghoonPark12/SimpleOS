#include "stack.h"

/*
    #define newStackWithValidator(buf, pValidator)   {0, sizeof(buf)/sizeof(int), (buf), pValidator}
    
    bool validateRange(Validator *pThis, int val){
      Range *pRange = (Range *)(pThis->pData);
      return pRange->min <= val && val <= pRange->max;
    }
    
    typedef struct Validator {
      bool (*const funtionPtr) (struct Validator *pThis, int val);
      void *const pData;
    } Validator;

*/

int main(){
    int buf[16];
    Validator v = {validateRange, &{0,9}}; // Funtion addr, Data addr
    Stack st = newStackWithValidator(buf, &v); 
    push(&st, 123);
 
    return 0;
}
