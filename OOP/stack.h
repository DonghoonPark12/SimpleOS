#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
  int top;
  const size_t size;
  int* const pBuf;
  Handle *const pHandle;
} Stack;

bool push(Stack *p, int val);
bool pop(Stack *p, int *pRet);

#define newStack(buf)  {0, sizeof(buf)/sizeof(int), (buf)};

/*
* 기능 추가를 용이하게 만들기 위해 추가한 Validator
* 아래 Handle은 Validator로서 역할을 하며, 기능을 위한 인터페이스 역할을 한다.
*/
typedef struct Handle {
  bool (*const handle) (struct Handle *pThis, int val);
  void *const pData;
} Handle;
  
  
typedef struct{
  const int min;
  const int max;
} Range;
  
//#define newStackWithRangeCheck(buf, pRange)   {0, sizeof(buf)/sizeof(int), (buf), pRange}
#define newStackWithValidator(buf, pRange)   {0, sizeof(buf)/sizeof(int), (buf), pHandle}
 
/*
* Validator 1 : Range Check
* Return true, if val is within the range.
*/
bool validateRange(Handle *pThis, int val){
  Range *pRange = (Range *)(pThis->pData);
  return pRange->min <= val && val <= pRange->max;
}

  
#ifdef __cplusplus
}
#endif

#endif
