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
      if(!Interface(pST->pValidator, val) || isStackFiil(p))  // 앞서 본것 처럼 해당 스택의 Validator는 
          return false;                                       // 범위 검사 기능의 함수를 가리키는 포인터를 인자로 가지고 있다.
      p->pBuf[p->top++] = val;
      return true;
    }
    
    bool Interface(Validator *pVal, int val){                 // 인터페이스는 스택 생성시에 유효성 검사로 지정된 '특정 함수'를
      if(!pVal)                                               // 관심두지 않는다. 몰라도 된다(★)
        return true; //스택안에 유효성 검사 기능이 없다면, 항상 참.
      return pVal->functionPtr(pVal, val);                    // '그' 스택의, '그' Validator의, '그' 함수(★) <-- 인자로 호출하면서 자기 자신의 주소를 넘긴다(★)
    }                                                         // 이때 왜 Validator의 주소도(pVal) 같이 넘기는 지 궁금할 것이다.
*/                                                            // '그' Validator가 사용하는 min/max 값이 필요하기 때문이다(★)

int main(){
    int buf[16];
    Validator v = {validateRange, &{0,9}}; // Funtion addr, Data addr
    Stack st = {0, sizeof(buf)/sizeof(int), buf, &v}; // Stack Initilize
    push(&st, 123);
 
    return 0;
}
