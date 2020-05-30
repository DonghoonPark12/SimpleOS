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
      if(!Interface(pST->pValidator, val) || isStackFiil(p))  //앞서 본것 처럼 해당 스택의 Validator는 
          return false;                                       //범위 검사 기능의 함수를 가리키는 포인터를 인자로 가지고 있다.
      p->pBuf[p->top++] = val;
      return true;
    }
    
    bool Interface(Validator *pVal, int val){
      if(!pVal)
        return true; //스택안에 유효성 검사 기능이 없다면, 항상 참.
      return pVal->functionPtr(pVal, val);
    }
*/

int main(){
    int buf[16];
    Validator v = {validateRange, &{0,9}}; // Funtion addr, Data addr
    Stack st = {0, sizeof(buf)/sizeof(int), buf, &v}; // Stack Initilize
    push(&st, 123);
 
    return 0;
}
