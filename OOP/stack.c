#include <stdbool.h>
#include "Common.h"
#include "stack.h"

/*
* 단순 인터페이스 역할, Valiadator를 깨우면서, val를 체크.
* pVal이 가리키는 functionPrt에는 일절 관여하지 않는다.
*/
bool Interface(Validator *pVal, int val){
  if(!pVal)
    return true; //스택안에 유효성 검사 기능이 없다면, 항상 참.
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
  if(!Interface(pST->pValidator, val) || isStackFiil(p)) 
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
