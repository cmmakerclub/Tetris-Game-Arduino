#include "Hero.h"


Hero::Hero() {
       posX = 8;
       posY = 14;
       
       timeCount = 0;
       timeCMax = 0.5;
       
       SpeedMove  = 0.25;
       
       SpeedLevelNormal = 3;
       SpeedDown = 1;
       SpeedLevel = SpeedLevelNormal;
}

void Hero::Update(byte *gameStep,float *deltaTime,boolean (*data)[32][16],boolean (*dataDot)[36][16],const boolean (*tetris)[7][4][4][4])
{
 
        short x,y;

        timeCount += *deltaTime;
 
        //=======================================
        if(timeCount >= (timeCMax/SpeedLevel)/SpeedDown)
        {
          timeCount = 0;
          //posY--;
          //Serial.println(posY);
	
	  byte tcount = 0;
	 
          for(short i = 4 - 1; i >= 0 ; i--)
          {
            for(short j = 0 ; j < 4 ; j++) 
	    {
	      if((*tetris)[type][heroRotate][i][j] != 0)
	      {
                  x = j;
                  y = i;
                  
	        if(posY - y - 1 < 0)//
	        {
			tcount++;
		}
		else
		{
		  if((*dataDot)[posY - y - 1] [posX + x] != 0)
		  {
		    tcount++;
		    break;
		  }
		}
	      }
	    }
            
	    if(tcount != 0){ break;}
	  }
	  if(tcount == 0)
	  {
	    posY --;
	  }
	  else
	  {
	    for(short i = 0 ; i < 4 ; i++)
	    {
		for(short j = 0 ; j < 4 ; j++)
		{
		  if((*tetris)[type][heroRotate][i][j] != 0)
		  {	
                        x = j;
                        y = i;		
                        
			if(posY - y >= 0)
			{
				(*dataDot)[posY - y][posX + x] = 1;
			}
		  }
	      }	
	  }
	  			
	  *gameStep = 2;
	}
    DispalyUpdate((data),(dataDot),(tetris));

  }
  //=================================================   
  
  if(keyDownPause)
  {	
    if(holdKeyPause)
    {
      *gameStep = 5;
    }
    holdKeyPause = false;

  }else{
    timePauseCount += *deltaTime;
    if(timePauseCount >= 0.5)
    {
      holdKeyPause = true;
    }	
  }

//=================================================
 if(keyDownReset)
 {	
   if(holdKeyReset)
   {
     *gameStep = 4;
   }
   holdKeyReset = false;
  }else{
    holdKeyReset = true;	
  }
  //=================================================
  
 if(keyDownLevelDown)
 {	
   if(holdKeyLevelDown)
   {
     if(SpeedLevel>1){SpeedLevel--;}
   }
   holdKeyLevelDown = false;
  }else{
    holdKeyLevelDown = true;	
  }
  //=================================================
  
 if(keyDownLevelUp)
 {	
   if(holdKeyLevelUp)
   {
     if(SpeedLevel<20){SpeedLevel++;}
   }
   holdKeyLevelUp = false;
  }else{
    holdKeyLevelUp = true;	
  }
  
//=================================================

  if(keyDownL1)
  {
    if(holdKeyL1)
    {
      holdKeyL1 = false;
      
      buffLRotate = heroRotate - 1;
      if(buffLRotate < 0){buffLRotate = 4 - 1;}

      byte lrcount = 0 ;
      
      for(short i = 0 ; i < 4 ; i++)
      {		
        for(short j = 0 ; j < 4  ; j++)
        {				
          if((*tetris)[type][buffLRotate][j][i] != 0)
          {
            x = i;
            y = j;
            
            if(posX + x < 0 ||posX + x > 15)
            {
              lrcount ++;
            }
            else
            {
              if((*dataDot)[posY - y ][posX + x] != 0)
              {
              lrcount ++;
	      }
	    }
          }
	}
        if(lrcount != 0){break;}
      }			
      if(lrcount == 0){heroRotate = buffLRotate;}
      DispalyUpdate((data),(dataDot),(tetris));
    }
  }else{
    holdKeyL1 = true;
  }

  //=================================================

  if(keyDownR1)
  {
    if(holdKeyR1)
    {
	holdKeyR1 = false;
	
        buffRRotate = heroRotate + 1;
        if(buffRRotate >= 4){buffRRotate = 0;}
        
        byte rrcount = 0 ;
	for(short i = 0 ; i < 4 ; i++)
	{		
	  for(short j = 0 ; j < 4 ; j++)
	  {	

            			
	    if((*tetris)[type][buffRRotate][j][i] != 0)
	    {
              x = i;
              y = j;
	      if(posX + x < 0 || posX + x > 15)
              {
		rrcount ++;
	      }
              else
	      {
		if((*dataDot)[posY - y ][posX + x] != 0)
		{
	          rrcount ++;
		}
	      }
	    }				
	  }
          if(rrcount != 0){break;}
	}
			
	if(rrcount == 0){heroRotate = buffRRotate;}
	DispalyUpdate((data),(dataDot),(tetris));
	}
      }else{
    holdKeyR1 = true;
  }
  //=================================================
  if(keyDownLeft)
  {
    if(holdKeyLeft)
    {
      byte emply = 0;
      for(short i = 0 ; i < 4 ; i++)
      {
        byte ecount = 0 ;
        for(short j = 0 ; j < 4  ; j++)
	{			
	  if((*tetris)[type][heroRotate][j][i] != 0)
	  {
	    ecount++;
	  }
        }  
        if(ecount == 0){emply++;}else{break;}
      }
      /*
      Serial.println("E ");
      Serial.println(emply);
      */
      //console.log("E "+emply);
      //================================= 
      if(posX > 0 - emply)
      {	
        byte lcount = 0 ;
        for(short j = 0; j < 4 ; j++)
        {
          for(short i = 0 ; i < 4 ; i++)
          {
            if((*tetris)[type][heroRotate][j][i] != 0)
            {	
 	        x = j;
                 y = i;
              if((*dataDot)[posY - y][posX + x - 1]  != 0)
              {
                lcount++;
                break;
              }
            }
          }
        }
        
        if(lcount == 0)
        {
          posX --;
        }
        holdKeyLeft  = false;
        DispalyUpdate((data),(dataDot),(tetris));
      }
    }
    timeLMoveCount += *deltaTime;

    if(timeLMoveCount>= SpeedMove)
    {
      timeLMoveCount = 0;
      holdKeyLeft  = true;
    }
  }else{
    holdKeyLeft = true;
    timeLMoveCount = 0;
  }
  //=================================================
  if(keyDownRight)
  {
    if(holdKeyRight)
    {
      byte emply = 0;
      for(short i = 4 - 1; i >= 0  ; i--)
      {
        byte ecount = 0 ;
	for(short j = 0 ; j < 4  ; j++)
	{
	  if((*tetris)[type][heroRotate][j][i] != 0)
	  {
	    ecount++;
	  }
	}
	if(ecount == 0){emply++;}else{break;}            
      }
                       
      if(posX < 15 - (4 - 1) + emply)
      {	
	byte rcount = 0 ;
	for(short j = 0; j < 4 ; j++)
	{
	  for(short i = 4 - 1; i >= 0  ; i--)
	  {
	    if((*tetris)[type][heroRotate][j][i] != 0)
	    {
	      x = j;
              y = i;	
              if((*dataDot)[posY - y][posX + x + 1] != 0)
	      {
		rcount++;
                break;
	      }
	    }
          }
	}

	if(rcount == 0){
          posX ++;
	}
					
	holdKeyRight  = false;
	DispalyUpdate((data),(dataDot),(tetris));
      }
    }
			
    timeRMoveCount += *deltaTime;

    if(timeRMoveCount >= SpeedMove)
    {
      timeRMoveCount = 0;
      holdKeyRight = true;
    }
  }else{
    holdKeyRight = true;
    timeRMoveCount = 0;
  }

    //=================================================
    if(keyDownDown)
    {
	SpeedDown = 2;
    }else{
	SpeedDown = 1;
    }
    //=================================================
  if(keyDownSpace)
  {
    if(holdKeySpace)
    {
      if(posY <= 31){
      byte nearest = 40;

      for(short i = 4 - 1; i >= 0 ; i--)
      {
        short space = -1;
        for(short j = 4-1 ; j >= 0 ; j--) 
	{
  
  /*
      for(short i = 0; i < 4 ; i++)
      {
        
        //วัดระยะ ของ Tetris ว่าจุดใหนต่ำสุด
        for(short j = 4-1 ; j >= 0  ; j--)
        {
    */
    //Serial.print((*tetris)[type][heroRotate][j][i]);
		
        if((*tetris)[type][heroRotate][j][i]  != 0)
        {	
          space = j;
          /*
          Serial.print(x);
         Serial.print(" ");
         Serial.print(y);
         Serial.println();
          */
          break;
        }
        
      }
      // Serial.println();		
      byte far = 0;

      //วัดระยะห่างพื้น กับ Tetris
      for(short a = posY + space ; a > 0 ; a--)
      {
        if(posX + i >= 0 && posX + i <= 15)
        {
          if((*dataDot)[a - 1][posX + i] != 0)
          {
            if(space != -1)
            {
              far = a;
            }
            break;
          }
        }
      }  

         	
      //คำนวนว่า จุดพื้นใหนใกล้สุด
      short near = posY - space  -far;
      /*
           Serial.print(posY);
         Serial.print(" ");   
                    Serial.print(posX + i );
         Serial.print(" ");   
        Serial.print(space);
         Serial.print(" ");
         Serial.print(far);
                  Serial.print(" ");
         Serial.print(near);
          Serial.println();
        */
      if(nearest > near)
      {
        nearest = near; 
      }
    }    

     posY -= nearest;
     DispalyUpdate((data),(dataDot),(tetris));
				 
     timeCount = timeCMax;
  }
      }
  holdKeySpace = false;
  }else{
    holdKeySpace  = true;
  }
 

   //===========================================================
}
void Hero::DispalyUpdate(boolean (*data)[32][16],boolean (*data2)[36][16],const boolean (*tetris)[7][4][4][4])
{
  for(byte i = 0 ; i < 32 ; i++)
  {
    for(byte j = 0 ; j < 16 ; j++)
    {
      (*data)[i][j] = (*data2)[(35 - i) - 4][j];
      
    }
  }
  
   for(byte i = 0 ; i < 4 ; i++)
  {
    for(byte j = 0 ; j < 4 ; j++)
    {
      if((j + posX) >= 0 && (j + posX) < 16)
      {
        if((31 - posY) + i >= 0 && (31 - posY) + i <= 31)
	{
          if((*tetris)[type][heroRotate][i][j] != 0)
           {
              (*data)[(31 - posY) + i][( j + posX)] = (*tetris)[type][heroRotate][i][j];
           }
        }
      }
    }
  } 
}

void Hero::GamePause(byte *gameStep,float *deltaTime,boolean (*data)[32][16],boolean (*dataDot)[36][16],const boolean (*tetris)[7][4][4][4])
{
if(keyDownPause)
  {	
    if(holdKeyPause)
    {
      *gameStep = 1;
       DispalyUpdate((data),(dataDot),(tetris));
    }
    holdKeyPause = false;

  }else{
    //timePauseCount += *deltaTime;
    //if(timePauseCount >= 0.5)
    //{
      holdKeyPause = true;
    //}	
  }
}

void Hero::GameReset(byte *gameStep,float *deltaTime,boolean (*data)[32][16],boolean (*dataDot)[36][16],const boolean (*tetris)[7][4][4][4])
{
   if(keyDownReset)
 {	
   if(holdKeyReset)
   {
     *gameStep = 4;
     DispalyUpdate((data),(dataDot),(tetris));
   }
   holdKeyReset = false;
  }else{
    holdKeyReset = true;	
  }
}
/*
void Hero::DispalyUpdate(boolean (*data)[32][16],boolean (*data2)[36][16],const boolean (*tetris)[7][4][4][4])
{
  
}

 void Hero::fn_display(boolean (*data)[32][16]){
      
  }

  */      
