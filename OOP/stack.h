#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
  const int min;
  const int max;
} Range;
  
typedef struct{
  int top;
  const size_t size;
  int* const pBuf;
} Stack;

bool push(Stack *p, int val);
bool pop(Stack *p, int *pRet);

#define newStack(buf)  {0, sizeof(buf)/sizeof(int), (buf)};

#define newStackWithRangeCheck(buf, pRange)   {0, sizeof(buf)/sizeof(int), (buf), pRange}
  
#ifdef __cplusplus
}
#endif

#endif
