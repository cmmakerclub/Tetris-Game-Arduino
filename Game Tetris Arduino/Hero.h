#include "Arduino.h"


class Hero {
   public:
      Hero();
      byte type;
      byte heroRotate;
      
      short posX;
      short posY;

      float timeCount;
      float timeCMax;
      
      boolean keyDownL1;
      boolean keyDownSpace;
      boolean keyDownR1;
      
      boolean keyDownLeft;
      boolean keyDownDown;
      boolean keyDownRight;
      
      boolean keyDownReset;
      boolean keyDownPause;
      boolean keyDownLightUp;  

      boolean keyDownLevelDown;
      boolean keyDownLevelUp;
      boolean keyDownLightDown;    
      
      //keyDownDown   
      boolean holdKeyL1;
      boolean holdKeySpace;
      boolean holdKeyR1;
      
      boolean holdKeyLeft;
      boolean holdKeyDown;
      boolean holdKeyRight;
      
      boolean holdKeyReset;
      boolean holdKeyPause;
      boolean holdKeyLightUp;  

      boolean holdKeyLevelDown;
      boolean holdKeyLevelUp;
      boolean holdKeyLightDown;  

      float timeRMoveCount;
      float timeLMoveCount;
      float timePauseCount;
      float SpeedMove;
      float SpeedDown;
      float SpeedLevel;
      
      short buffRRotate;
      short buffLRotate;
      
      float SpeedLevelNormal;
      void Update(byte *gameStep,float *deltaTime,boolean (*data)[32][16],boolean (*data2)[36][16],const boolean (*tetris)[7][4][4][4]);
      void DispalyUpdate(boolean (*data)[32][16],boolean (*data2)[36][16],const boolean (*tetris)[7][4][4][4]);
      
      void GamePause(byte *gameStep,float *deltaTime,boolean (*data)[32][16],boolean (*data2)[36][16],const boolean (*tetris)[7][4][4][4]);
      void GameReset(byte *gameStep,float *deltaTime,boolean (*data)[32][16],boolean (*data2)[36][16],const boolean (*tetris)[7][4][4][4]);
    /*
      void Initialize() ;
      void fn_display(boolean (*data)[32][16]);
      void DispalyUpdate(boolean (*data)[32][16],boolean (*data2)[36][16],const boolean (*tetris)[7][4][4][4]);
	  */
   private:    
	   /*
      byte led;
      byte led_set;
      byte sin1;
      byte sin2;
      byte sin3;
      byte clk;
      byte lat;
      byte str;
      boolean compare2; 
      boolean compare1; 
	  */
};



