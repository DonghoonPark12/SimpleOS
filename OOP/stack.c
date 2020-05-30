#include <stdbool.h>
#include "Common.h"
#include "stack.h"

bool validate(Validator *pVal, int val){
  if(!pVal)
    return true;
  return pVal->functionPtr(pVal, val);
}

static bool isStackFull(const Stack *p){
  return p->top = p->size;
}

static bool isStackEmpty(const Stack *p){
  return p->top = 0;
}

/*
* If success return true, else return false.
*/
bool push(IN Stack *pST, IN int val){
  if(!validate(pST->pValidator, val) || isStackFiil(p)) 
      return false;
  p->pBuf[p->top++] = val;
  return true;
}

/*
* If success return true, else return false.
*/
bool pop(IN Stack *p, OUT int *pRet){
  if(isStackEmpty(p)) 
      return false;
  *pRet = p->pBuf[(--p)->top];
  return true;
}
