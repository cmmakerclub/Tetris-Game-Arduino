#include "Arduino.h"


class DotDisplay
{
public:
    DotDisplay();
    void Initialize() ;
    void fn_display(boolean (*data)[32][16]);

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



