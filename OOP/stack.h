#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

  
typedef struct{
  int top;
  const size_t size;              
  int *const pBuf;                // const pointer to int <---> int const* pBuf : pointer to const int. Same as (const int* pBuf)
  Validator *const pValidator;    // const pointer to Validate struct
} Stack;                          // [https://stackoverflow.com/questions/21476869/constant-pointer-vs-pointer-to-constant]

bool push(Stack *p, int val);
bool pop(Stack *p, int *pRet);

//#define newStack(buf)  {0, sizeof(buf)/sizeof(int), (buf)};

/*
* 기능 추가를 용이하게 만들기 위해 추가한 Validator
* 아래 Handle은 Validator로서 역할을 하며, 기능을 위한 인터페이스 역할을 한다.
*/
typedef struct Validator {
  bool (*const funtionPtr) (struct Validator *pThis, int val);
  void *const pData;
} Validator;
  
  
typedef struct{
  const int min;
  const int max;
} Range;
  
//#define newStackWithRangeCheck(buf, pRange)   {0, sizeof(buf)/sizeof(int), (buf), pRange}
#define newStackWithValidator(buf, pValidator)   {0, sizeof(buf)/sizeof(int), (buf), pValidator}
 
/*
* Validator 1 : Range Check
* Return true, if val is within the range.
*/
bool validateRange(Validator *pThis, int val){
  Range *pRange = (Range *)(pThis->pData);
  return pRange->min <= val && val <= pRange->max;
}

  
#ifdef __cplusplus
}
#endif

#endif
