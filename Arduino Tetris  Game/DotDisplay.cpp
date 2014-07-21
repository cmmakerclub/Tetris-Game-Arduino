#include "DotDisplay.h"

// LED() constructor
DotDisplay::DotDisplay()
{
    led  =13;
    led_set=1;

    sin1 = 2;
    sin2 = 3;
    sin3 = 4;
    clk  = 5;
    lat  = 6;
    str  = 7;

    compare2 = 0;
    compare1 = 0;
}
void DotDisplay::Initialize()
{
    pinMode(led, OUTPUT);
    pinMode(sin1, OUTPUT);
    pinMode(sin2, OUTPUT);
    pinMode(sin3, OUTPUT);
    pinMode(clk, OUTPUT);
    pinMode(lat, OUTPUT);
    pinMode(str, OUTPUT);

    digitalWrite(led,0);
    digitalWrite(sin1,0);
    digitalWrite(sin2,0);
    digitalWrite(sin3,0);
    digitalWrite(clk,0);
    digitalWrite(lat,0);
    digitalWrite(str,0);
}

void DotDisplay::fn_display(boolean (*data)[32][16])
{
    for(int y=0; y <16 ; y++ )
    {
        for(int x=0; x <16 ; x++ )
        {
            //write data
            digitalWrite(sin1,x==y);
            if(compare2 != (*data)[x][y])
            {
                compare2=(*data)[x][y];
                digitalWrite(sin3,compare2);
            };


            if(compare1 != (*data)[16+x][y])
            {
                compare1=(*data)[16+x][y];
                digitalWrite(sin2,compare1);
            };

            //shift clk
            digitalWrite(clk,1);
            digitalWrite(clk,0);
        }

        digitalWrite(lat,0);
        digitalWrite(lat,1);
    }
}


