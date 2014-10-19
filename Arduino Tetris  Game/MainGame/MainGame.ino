#include "Tetris.h"
#include <TrueRandom.h>

DotDisplay dotDisplay;  // assign to pin 13
Hero hero;
unsigned long currentMillis = 0;

short GameFPS = 50;
short GameInterval = 1000/GameFPS;
float GameDeltaTime = 0;
long GameUpdatedMillis = 0;

short DisplayFPSNormal = 150;
short DisplayFPS = DisplayFPSNormal;
short DisplayInterval = 1000/DisplayFPS;
long DisplayUpdatedMillis = 0;

byte gameStep = 0;
void setup()
{

    Serial.begin(9600);
    dotDisplay.Initialize();
    //initKey();
}

void loop()
{
    GamepLoop();
}

void GamepLoop()
{
    currentMillis = millis();
    if(currentMillis - GameUpdatedMillis > GameInterval)
    {
        GameDeltaTime = (currentMillis - GameUpdatedMillis) / (float)1000;
        //Serial.println(GameMillCal,4);
        GameUpdatedMillis = currentMillis;
        checkKey();
        Update();
    }

    if(currentMillis - DisplayUpdatedMillis > DisplayInterval)
    {
        DisplayUpdatedMillis = currentMillis;
        UpdateDisplay();
    }
}
boolean loopcheck = true;
void Update()
{

    switch(gameStep)
    {
    case 0 : //Gen
        hero.type = (byte) TrueRandom.random(0,7);
        hero.heroRotate = (byte) TrueRandom.random(0,4);

        hero.posX = 6;
        hero.posY = 36;

        gameStep = 1;
        hero.DispalyUpdate(&aTrueDisplay,&aDotArea,&aTetris);

        break;

    case 1 ://Down
        hero.Update(&gameStep , &GameDeltaTime,&aTrueDisplay,&aDotArea,&aTetris);
        break;

    case 2 : //Clear Row
        loopcheck = true;
        while(loopcheck)
        {
            short row = -1;
            for(short j = 0 ; j < 32 ; j++)
            {
                byte full = 0;
                for(short i = 0 ; i < 16 ; i++)
                {
                    if(aDotArea[j][i] == 1)
                    {
                        full++;
                    }
                }

                if(full == 16)
                {
                    row = j;
                }
            }

            if(row != -1)
            {
                for(short i = 0 ; i < 16 ; i++)
                {
                    for(short j = row ; j < 32 - row - 1 ; j++)
                    {
                        aDotArea[j][i]  =  aDotArea[j+1][i];
                    }

                    for(short j = 32 - row  ; j < 32 ; j++)
                    {
                        aDotArea[j][i]  =  0;
                    }
                }
            }
            else
            {
                loopcheck = false;
            }
        }
        gameStep = 3;
        break;

    case 3 : // GameOver
        gameStep = 0;

        for(short i = 0 ; i < 16 ; i++)
        {
            for(short j = 32 ; j < 36 ; j++)
            {
                if(aDotArea [j][i] != 0)
                {
                    for(byte i = 0 ; i < 16 ; i++)
                    {
                        for(byte j = 0 ; j < 32 ; j++)
                        {
                            aTrueDisplay [j][i] = 1;
                        }
                    }
                    gameStep = 7;
                    break;
                    break;
                }
            }
        }
        break;

    case 4 : // Reset
        gameStep = 0;
        hero.SpeedLevel = hero.SpeedLevelNormal ;

        for(byte i = 0 ; i < 16 ; i++)
        {
            for(byte j = 0 ; j < 36 ; j++)
            {
                aDotArea [j][i] = 0;
            }
        }

        hero.Update(&gameStep , &GameDeltaTime,&aTrueDisplay,&aDotArea,&aTetris);
        break;

    case 5 :
        for(byte i = 0 ; i < 16 ; i++)
        {
            for(byte j = 0 ; j < 32 ; j++)
            {
                aTrueDisplay [j][i] = 0;
            }
        }
        gameStep = 6;
        break;

    case 6 :
        hero.GamePause(&gameStep , &GameDeltaTime,&aTrueDisplay,&aDotArea,&aTetris);
        break;

    case 7 :
        hero.GameReset(&gameStep , &GameDeltaTime,&aTrueDisplay,&aDotArea,&aTetris);
        break;
    }

    //=================================================

    if(hero.keyDownLightDown  )
    {
        if(hero.holdKeyLightDown )
        {
            DisplayFPS -= 20;
            if(DisplayFPS < 60)
            {
                DisplayFPS = 60;
            }
            DisplayInterval = 1000/DisplayFPS;
            Serial.println(DisplayFPS );
        }
        hero.holdKeyLightDown  = false;
    }
    else
    {
        hero.holdKeyLightDown  = true;
    }
    //=================================================

    if(hero.keyDownLightUp )
    {
        if(hero.holdKeyLightUp )
        {
            DisplayFPS += 20;
            if(DisplayFPS > 240)
            {
                DisplayFPS = 240;
            }
            DisplayInterval = 1000/DisplayFPS;
            Serial.println(DisplayFPS );
        }
        hero.holdKeyLightUp = false;
    }
    else
    {
        hero.holdKeyLightUp = true;
    }

}

void UpdateDisplay()
{
    //dotDisplay.DispalyUpdate(&aTrueDisplay,&aDotArea,&aTetris);

    dotDisplay.fn_display(&aTrueDisplay);
}
void initKey()
{
    //pinMode(4 ,INPUT_PULLUP);
    //pinMode(10 ,INPUT_PULLUP);
    pinMode(11 ,INPUT_PULLUP);
    pinMode(12 ,INPUT_PULLUP);
    pinMode(13 ,INPUT_PULLUP); //Up

    pinMode(14 ,OUTPUT);
    pinMode(15 ,OUTPUT);
    pinMode(16 ,OUTPUT);
    pinMode(17 ,OUTPUT);


}
void checkKey()
{
    //hero.keyDownSpace = !digitalRead(12);

    for(byte i = 0 ; i < 4 ; i++)
    {
        analogWrite(14, 255);
        analogWrite(15, 255);
        analogWrite(16, 255);
        analogWrite(17, 255);

        analogWrite(14 + i, 0);

        for(byte j = 0 ; j < 3 ; j++)
        {
            aKey[i][j] = !digitalRead(11 + j);
        }
    }

    hero.keyDownL1         = aKey[0][0] ;
    hero.keyDownSpace      = aKey[0][1] ;
    hero.keyDownR1         = aKey[0][2] ;

    hero.keyDownLeft       = aKey[1][0] ;
    hero.keyDownDown       = aKey[1][1] ;
    hero.keyDownRight      = aKey[1][2] ;

    hero.keyDownReset      = aKey[2][0] ;
    hero.keyDownPause      = aKey[2][1] ;
    hero.keyDownLightUp    = aKey[2][2] ;

    hero.keyDownLevelDown  = aKey[3][0] ;
    hero.keyDownLevelUp    = aKey[3][1] ;
    hero.keyDownLightDown  = aKey[3][2] ;

    /*
     for(byte i = 0 ; i < 4 ; i++)
    {
       for(byte j = 0 ; j < 3 ; j++)
       {
          if(aKey[i][j] == 1){Serial.print("Key : "); Serial.println((i*3)+j);}
       }
    }
    */

    /*
     Serial.print(!digitalRead(11));
     Serial.print(" ");
        Serial.print(!digitalRead(12));
     Serial.print(" ");
        Serial.print(!digitalRead(13));
     Serial.print(" ");
    Serial.println();
    */
    //hero.keyDownLeft = !digitalRead(12);
    //Serial.println(hero.keyDownLeft);

    //hero.keyDownRight = !digitalRead(12);
    //Serial.println(hero.keyDownRight);

}


