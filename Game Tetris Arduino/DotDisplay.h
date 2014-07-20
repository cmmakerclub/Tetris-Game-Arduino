#include "Arduino.h"


class DotDisplay {
   public:
      DotDisplay();
      void Initialize() ;
      void fn_display(boolean (*data)[32][16]);
      //void DispalyUpdate(boolean (*data)[32][16],boolean (*data2)[36][16],const boolean (*tetris)[7][4][4][4],byte *type,byte *rotate,short *posX,short *posY);

   private:      
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
};



