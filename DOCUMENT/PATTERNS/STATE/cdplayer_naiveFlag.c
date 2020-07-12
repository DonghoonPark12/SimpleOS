typedef enum{
  STOP,
  PLAY_PAUSE
}EVENT;

/* Global Variable */
bool playFlag;
bool pauseFlag;
/* --------------- */

void initilize(){
  playFlag = false;
  pauseFalg = false;
}

void onEvent(EVENT e){
  switch(e){
    case STOP:
      if(playFlag == true || pauseFlag ==true)
        stopPlayer();
      break;
      
    case PLAY_PAUSE:
      if(playFlag == true)
        pausePlayer();
      else if(pauseFlag == true)
        resumePlayer();
      else
        startPlayer();
      break;
      
    defalut:
      break;
  }
}

void stopPlayer(){
  playFlag = false;
  pauseFlag = false;
}

void pausePlayer(){
  playFlag = false;
  pauseFlag = true;
}

void startPlyar(){
  playFlag = true;
  pauseFlag = false;
}

void resumePlayer(){
  startPlyar();
}
  
