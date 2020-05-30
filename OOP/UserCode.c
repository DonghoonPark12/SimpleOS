#include "stack.h"

/*
    bool validateRange(Validator *pThis, int val){
      Range *pRange = (Range *)(pThis->pData);
      return pRange->min <= val && val <= pRange->max;
    }
    
    typedef struct Validator {
      bool (*const funtionPtr) (struct Validator *pThis, int val);
      void *const pData;
    } Validator;

    typedef struct{
      int top;
      const size_t size;
      int* const pBuf;
      Validator *const pValidator;
    } Stack;
    
    bool push(IN Stack *pST, IN int val){
      if(!Interface(pST->pValidator, val) || isStackFiil(p)) 
          return false;
      p->pBuf[p->top++] = val;
      return true;
    }
*/

int main(){
    int buf[16];
    Validator v = {validateRange, &{0,9}}; // Funtion addr, Data addr
    Stack st = {0, sizeof(buf)/sizeof(int), buf, &v}; // Stack Initilize
    push(&st, 123);
 
    return 0;
}
