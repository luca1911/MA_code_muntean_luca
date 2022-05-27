
#include <stdio.h>
#include <stdlib.h>

const int buttonPin = 7;
int buttonState = 0;
int VRx = A0;
int VRy = A1;
int SW = 2;

int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

#include <SPI.h>
#include <TFT.h>
#define cs 10
#define dc 9
#define rst 8

TFT screen = TFT(cs, dc, rst);

int Board[9][9] =
{
    {-1, -1, -1, -1, -1, -1, -1, -1, -1},
    {-1, 1, 0, 0, 1, 0, 0, 1, -1},
    {-1, 0, 1, 0, 1, 0, 1, 0, -1},
    {-1, 0, 0, 1, 1, 1, 0, 0, -1},
    {-1, 1, 1, 1, -1, 1, 1, 1, -1},
    {-1, 0, 0, 1, 1, 1, 0, 0, -1},
    {-1, 0, 1, 0, 1, 0, 1, 0, -1},
    {-1, 1, 0, 0, 1, 0, 0, 1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1, -1}
};

int CurrentY = 1;
int CurrentX = 1;
int TurnCount = 0;
int WhitePcsHand = 9;
int BlackPcsHand = 9;
int WPcsBoard = 0;
int BPcsBoard = 0;
 int enter = 0;
 int win = 0;
    int PrevCurrentY;
    int PrevCurrentX;
    int prev;

void Game()
{
    while(WhitePcsHand != 0 || BlackPcsHand != 0)
    {
        Turn1();
    }
   
        Turn2();
    

}

void Turn2()
{
    
    int enter = 0;
    int PrevCurrentY;
    int PrevCurrentX;
    int prev;
    PrevCurrentY = CurrentY;
    PrevCurrentX = CurrentX;
    prev = Board[CurrentY][CurrentX];
    Board[CurrentY][CurrentX] = 9;
   screen.background(0,0,0);
    screen.stroke(0,255,0);
    screen.setTextSize(2);
    screen.text("SELECT PIECE",0,20);
    delay(1000);
    screen.background(0,0,0);
    if(win==1){
       screen.background(0,0,0);
    screen.stroke(0,255,0);
    screen.setTextSize(2);
    screen.text("GAME OVER",0,20);
    delay(100000);
    return;
    }
    Display();
    while(enter == 0)
    {

         xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  buttonState = digitalRead(buttonPin);
        if(mapX > 400)
        {
            MoveLeft();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Display();

        }
        else if(mapX < -400)
        {
            MoveRight();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Display();

        }
        else if(mapY > 400)
        {
            MoveUp();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Display();

        }
        else if( mapY < -400)
        {
            MoveDown();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Display();

        }
        else if(buttonState == 1)
        {
            if(TurnCount % 2 == 0)
            {
              if( WPcsBoard == 3){
                if(prev == 2)
                {
                    Board[CurrentY][CurrentX] = prev;
                    Move2(2);
                     TurnCount++;
              }
               else
                {
                    screen.background(0,0,0);
                    screen.stroke(0,255,0);
                    screen.setTextSize(2);
                    screen.text("ERROR",0,20);
                    delay(1000);
                    screen.background(0,0,0);
                    Board[CurrentY][CurrentX] = prev;
                    Turn2();
                }
              }
              else{
                if(prev == 2)
                {
                    Board[CurrentY][CurrentX] = prev;
                    Move(2);
                     


                }
                else
                {
                    screen.background(0,0,0);
                    screen.stroke(0,255,0);
                    screen.setTextSize(2);
                    screen.text("ERROR",0,20);
                    delay(1000);
                    screen.background(0,0,0);
                    Board[CurrentY][CurrentX] = prev;
                    Turn2();
                }
            }
            }

            else if(BPcsBoard == 3){
              if(prev == 3)
            {
                Board[CurrentY][CurrentX] = prev;
                Move2(3);
                 TurnCount++;
            }


            else
            {
                 screen.background(0,0,0);
                screen.stroke(0,255,0);
                screen.setTextSize(2);
                screen.text("ERROR",0,20);
                delay(1000);
                screen.background(0,0,0);
                Board[CurrentY][CurrentX] = prev;
                Turn2();
            }
            }
            else if(prev == 3)
            {
                Board[CurrentY][CurrentX] = prev;
                Move(3);
                 
            }


            else
            {
                 screen.background(0,0,0);
                screen.stroke(0,255,0);
                screen.setTextSize(2);
                screen.text("ERROR",0,20);
                delay(1000);
                screen.background(0,0,0);
                Board[CurrentY][CurrentX] = prev;
                Turn2();
            }
            
            enter = 1;
           

            Display();

        } delay(300);


    }
}

void Move2(int x){
  int enter = 0;
   int InitialX = CurrentX;
    int InitialY = CurrentY;
    int ival = Board[InitialY][InitialX];
    int PrevCurrentY;
    int PrevCurrentX;
    int prev;
    PrevCurrentY = CurrentY;
    PrevCurrentX = CurrentX;
    prev = Board[CurrentY][CurrentX];
    Board[CurrentY][CurrentX] = 9;
     screen.background(0,0,0);
    screen.stroke(0,255,0);
    screen.setTextSize(2);
    screen.text("SELECT POSITION",0,20);
    delay(1000);
    screen.background(0,0,0);
    Display();
    while(enter == 0)
    {
       xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  buttonState = digitalRead(buttonPin);

        
        if(mapX > 400)
        {
            MoveLeft();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Board[InitialY][InitialX] = ival;
            Display();
            

        }
        else if(mapX < -400)
        {
            MoveRight();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Board[InitialY][InitialX] = ival;
            Display();
            

        }
        else if(mapY > 400)
        {
            MoveUp();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Board[InitialY][InitialX] = ival;
            Display();
            

        }
        else if( mapY < -400)
        {
            MoveDown();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Board[InitialY][InitialX] = ival;
            Display();
            

        }
        else if(buttonState == 1)
        {
           
                if(prev == 1)
                {
                    Board[CurrentY][CurrentX] = x;
                    Board[InitialY][InitialX] = 1;
                    screen.background(0,0,0);
                    screen.stroke(0,255,0);
                    screen.setTextSize(2);
                    screen.text("MOVED",0,20);
                    delay(1000);
                    screen.background(0,0,0);
                    Display();
                    if(CheckForMill(x) == 1)
                    {
                        Remove();
                    }
                }
                else
                {
                     screen.background(0,0,0);
                    screen.stroke(0,255,0);
                    screen.setTextSize(2);
                    screen.text("ERROR",0,20);
                    delay(1000);
                    screen.background(0,0,0);
                    Board[CurrentY][CurrentX] = prev;
                    CurrentX = InitialX;
                    CurrentY = InitialY;
                    Move(x);

                }
           
            enter = 1;

        } delay(300);
    }
  }

void Move(int x)
{
    
    int enter = 0;
    int count = 0;
    int InitialX = CurrentX;
    int InitialY = CurrentY;
    int ival = Board[InitialY][InitialX];
    int PrevCurrentY;
    int PrevCurrentX;
    int prev;
    PrevCurrentY = CurrentY;
    PrevCurrentX = CurrentX;
    prev = Board[CurrentY][CurrentX];
    Board[CurrentY][CurrentX] = 9;
    screen.background(0,0,0);
    screen.stroke(0,255,0);
    screen.setTextSize(2);
    screen.text("SELECT POSITION",0,20);
    delay(1000);
    screen.background(0,0,0);

    Display();
    while(enter == 0)
    {
       xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  buttonState = digitalRead(buttonPin);

        
        if(mapX > 400)
        {
            MoveLeft();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Board[InitialY][InitialX] = ival;
            Display();
            count--;

        }
        else if(mapX < -400)
        {
            MoveRight();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Board[InitialY][InitialX] = ival;
            Display();
            count++;

        }
        else if(mapY > 400)
        {
            MoveUp();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Board[InitialY][InitialX] = ival;
            Display();
            count++;

        }
        else if( mapY < -400)
        {
            MoveDown();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Board[InitialY][InitialX] = ival;
            Display();
            count--;

        }
        else if(buttonState == 1)
        {
            if(count == 1 || count == -1)
            {
                if(prev == 1)
                {
                    Board[CurrentY][CurrentX] = x;
                    Board[InitialY][InitialX] = 1;
                    screen.background(0,0,0);
                    screen.stroke(0,255,0);
                    screen.setTextSize(2);
                    screen.text("MOVED",0,20);
                    delay(1000);
                    screen.background(0,0,0);
                    Display();
                    if(CheckForMill(x) == 1)
                    {
                        Remove();
                    }
                     TurnCount++;
                }
                else
                {
                     screen.background(0,0,0);
                    screen.stroke(0,255,0);
                    screen.setTextSize(2);
                    screen.text("ERROR",0,20);
                    delay(1000);
                    screen.background(0,0,0);
                    Board[CurrentY][CurrentX] = prev;
                    CurrentX = InitialX;
                    CurrentY = InitialY;
                    Move(x);

                }
            }
            else
            {
               screen.background(0,0,0);
                    screen.stroke(0,255,0);
                    screen.setTextSize(2);
                    screen.text("ERROR",0,20);
                    delay(1000);
                    screen.background(0,0,0);
                Board[CurrentY][CurrentX] = prev;
                CurrentX = InitialX;
                CurrentY = InitialY;
                Move(x);

            }
            enter = 1;

        } delay(300);
    }
}


 int CheckForMill(int x)
{
    int check = 0;
    int count1 = 0;
    int count2 = 0;
    int j = 1;

    if(CurrentX == 4 && CurrentY <= 3)
    {
        while(Board[j][CurrentX] != -1)
        {
            if(Board[j][CurrentX] == x)
            {
                count1++;
            }
            j++;
        }
        if(count1 == 3)
        {

            check = 1;
        }
        for(int i = 0; i<9; i++)
        {
            if(Board[CurrentY][i] == x)
            {
                count2++;
            }
        }
        if(count2 == 3)
        {
            check = 1;

        }
    }
    else if(CurrentX == 4 && CurrentY >= 5)
    {
        j = 5;
        while(Board[j][CurrentX] != -1)
        {
            if(Board[j][CurrentX] == x)
            {
                count1++;
            }
            j++;
        }
        if(count1 == 3)
        {
            check = 1;
        }
        for(int i = 0; i<9; i++)
        {
            if(Board[CurrentY][i] == x)
            {
                count2++;
            }
        }
        if(count2 == 3)
        {
            check = 1;
        }
    }
    else if(CurrentY == 4 && CurrentX <= 3)
    {
        while(Board[CurrentY][j] != -1)
        {
            if(Board[CurrentY][j] == x)
            {
                count1++;
            }
            j++;
        }
        if(count1 == 3)
        {
            check = 1;
        }
        for(int i = 0; i<9; i++)
        {
            if(Board[i][CurrentX] == x)
            {
                count2++;
            }

        }
        if(count2 == 3)
        {
            check = 1;
        }
    }
    else if(CurrentY == 4 && CurrentX >= 5)
    {
        j = 5;
        while(Board[CurrentY][j] != -1)
        {
            if(Board[CurrentY][j] == x)
            {
                count1++;
            }
            j++;
        }
        if(count1 == 3)
        {
            check = 1;
        }
        for(int i = 0; i<9; i++)
        {
            if(Board[i][CurrentX] == x)
            {
                count2++;
            }

        }
        if(count2 == 3)
        {
            check = 1;
        }
    }
    else
    {

        for(int i = 0; i<9; i++)
        {
            if(Board[CurrentY][i] == x)
            {
                count1++;
            }
        }
        if(count1 == 3)
        {
            check = 1;
        }

        for(int i = 0; i<9; i++)
        {
            if(Board[i][CurrentX] == x)
            {
                count2++;
            }

        }
        if(count2 == 3)
        {
            check = 1;
        }
    }

    return check;
}

void MoveRight()
{
    do
    {
        if(Board[CurrentY][CurrentX + 1] != -1)
        {
            CurrentX = CurrentX + 1;
        }
        else{break;}
    }
    while(Board[CurrentY][CurrentX] != 1 && Board[CurrentY][CurrentX] != 2 && Board[CurrentY][CurrentX] != 3 );
}

void MoveLeft()
{
    do
    {
        if(Board[CurrentY][CurrentX - 1] != -1)
        {
            CurrentX = CurrentX - 1;
        }
        else{break;}
    }
    while(Board[CurrentY][CurrentX] != 1 && Board[CurrentY][CurrentX] != 2 && Board[CurrentY][CurrentX] != 3 );
}

void MoveDown()
{
    do
    {
        if(Board[CurrentY + 1][CurrentX] != -1)
        {
            CurrentY = CurrentY + 1;
        }
        else{break;}
    }
    while(Board[CurrentY][CurrentX] != 1 && Board[CurrentY][CurrentX] != 2 && Board[CurrentY][CurrentX] != 3 );
}

void MoveUp()
{
    do
    {
        if(Board[CurrentY - 1][CurrentX] != -1)
        {
            CurrentY = CurrentY - 1;
        }
        else{break;}
    }
    while(Board[CurrentY][CurrentX] != 1 && Board[CurrentY][CurrentX] != 2 && Board[CurrentY][CurrentX] != 3 );
}


 void Turn1()
{
    
    int enter = 0;
    int PrevCurrentY;
    int PrevCurrentX;
    int prev;
    PrevCurrentY = CurrentY;
    PrevCurrentX = CurrentX;
    prev = Board[CurrentY][CurrentX];
    Board[CurrentY][CurrentX] = 9;
    screen.background(0,0,0);
    screen.stroke(0,255,0);
    screen.setTextSize(2);
    screen.text("NEW TURN",0,20);
    delay(1000);
    screen.background(0,0,0);

    Display();
    while(enter == 0)
    {
    
        xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  buttonState = digitalRead(buttonPin);
  
        if(mapX > 400 )
        {
            MoveLeft();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Display();

        }
        else if(mapX < -400 )
        {
            MoveRight();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Display();

        }
        else if( mapY > 400)
        {
            MoveUp();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Display();

        }
        else if( mapY < -400)
        {
            MoveDown();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Display();

        } else if(buttonState == 1)
        {
          if(TurnCount % 2 == 0)
            {
                if(prev != 2 && prev != 3)
                {
                    Board[CurrentY][CurrentX] = 2;
                    WhitePcsHand--;
                    WPcsBoard++;

                    if(CheckForMill(2) == 1)
                    {
                        Remove();

                    }
                   TurnCount++;
                }
                else
                {
                     screen.background(0,0,0);
                     screen.stroke(0,255,0);
                     screen.setTextSize(2);
                     screen.text("ERROR",0,20);
                     delay(1000);
                     screen.background(0,0,0);
                    Board[CurrentY][CurrentX] = prev;
                }
            }
            else
            {
                if(prev != 2 && prev != 3)
                {
                    Board[CurrentY][CurrentX] = 3;
                    BlackPcsHand--;
                    BPcsBoard++;

                    if(CheckForMill(3) == 1)
                    {
                        Remove();

                    }
                   TurnCount++;
                }
                else
                {
                   screen.background(0,0,0);
                     screen.stroke(0,255,0);
                     screen.setTextSize(2);
                     screen.text("ERROR",0,20);
                     delay(1000);
                     screen.background(0,0,0);
                    Board[CurrentY][CurrentX] = prev;
                }
            }
            enter = 1;
           

            Display();
            


        } delay(300);
    }
}

void Remove()
{
    screen.background(0,0,0);
    screen.stroke(0,255,0);
    screen.setTextSize(2);
    screen.text("MILL!",0,20);
    delay(1000);
    screen.background(0,0,0);
     screen.stroke(0,255,0);
    screen.setTextSize(2);
    screen.text("REMOVE",0,20);
    delay(1000);
    screen.background(0,0,0);
    char val;
    int e = 0;
    int PrevCurrentY;
    int PrevCurrentX;
    int prev;
    PrevCurrentY = CurrentY;
    PrevCurrentX = CurrentX;
    prev = Board[CurrentY][CurrentX];
    Board[CurrentY][CurrentX] = 9;
    Display();
     

    while(e == 0)
    {
      xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);
  buttonState = digitalRead(buttonPin);

        
        if(mapX > 400)
        {
            MoveLeft();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Display();

        }
        else if(mapX < -400)
        {
            MoveRight();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Display();

        }
        else if(mapY > 400)
        {
            MoveUp();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Display();

        }
        else if( mapY < -400)
        {
            MoveDown();
            Board[PrevCurrentY][PrevCurrentX] = prev;
            PrevCurrentY = CurrentY;
            PrevCurrentX = CurrentX;
            prev = Board[CurrentY][CurrentX];
            Board[CurrentY][CurrentX] = 9;
            Display();

        }
        else if(buttonState == 1)
        {
            Board[CurrentY][CurrentX] = prev;
            Display();

            if(TurnCount % 2 == 0)
            {

                if(CheckForMill(3) == 0)
                {
                    Board[CurrentY][CurrentX] = 1;
                     screen.background(0,0,0);
                    screen.stroke(0,255,0);
                     screen.setTextSize(2);
                     screen.text("REMOVED",0,20);
                    delay(1000);
                    screen.background(0,0,0);
                    BPcsBoard--;
                    if(BPcsBoard + BlackPcsHand == 2){win = 1;}

                }
                else
                {

                   screen.background(0,0,0);
                    screen.stroke(0,255,0);
                     screen.setTextSize(2);
                     screen.text("ERROR",0,20);
                    delay(1000);
                    screen.background(0,0,0);
                    Remove();
                }


            }
            else
            {
                if(CheckForMill(2) == 0)
                {
                    Board[CurrentY][CurrentX] = 1;
                    screen.background(0,0,0);
                    screen.stroke(0,255,0);
                     screen.setTextSize(2);
                     screen.text("REMOVED",0,20);
                    delay(1000);
                    screen.background(0,0,0);
                    WPcsBoard--;
                    if(WPcsBoard + WhitePcsHand == 2){win = 1;}
                }
                else
                {
                   screen.background(0,0,0);
                    screen.stroke(0,255,0);
                     screen.setTextSize(2);
                     screen.text("ERROR",0,20);
                    delay(1000);
                    screen.background(0,0,0);
                    Remove();
                }

            }

            e = 1;
        }delay(300);
    }
}
           
void Display(){
   screen.stroke(0,255,0); 
  if(Board[1][1] == 2){
     screen.fill(255,255,255);
  screen.circle(21,5,4);
  screen.noFill();
   }
   else if(Board[1][1] == 3){
     screen.fill(0,255,0);
    screen.circle(21,5,4);
  screen.noFill();
   }
   else if(Board[1][1] == 9){
      screen.fill(0,0,255);
    screen.circle(21,5,4);
  screen.noFill();
   }
   else{ screen.fill(0,0,0);
    screen.circle(21,5,4);
     screen.noFill();}
   
   if(Board[1][4] == 2){
     screen.fill(255,255,255);
  screen.circle(80,5,4);
  screen.noFill();
   }
   else if(Board[1][4] == 3){
     screen.fill(0,255,0);
    screen.circle(80,5,4);
  screen.noFill();
   }
   else if(Board[1][4] == 9){
      screen.fill(0,0,255);
    screen.circle(80,5,4);
  screen.noFill();
   }
   else{screen.fill(0,0,0);
   screen.circle(80,5,4);
    screen.noFill();}

    if(Board[1][7] == 2){
     screen.fill(255,255,255);
  screen.circle(139,5,4);
  screen.noFill();
   }
   else if(Board[1][7] == 3){
     screen.fill(0,255,0);
    screen.circle(139,5,4);
  screen.noFill();
   }
   else if(Board[1][7] == 9){
      screen.fill(0,0,255);
    screen.circle(139,5,4);
  screen.noFill();
   }
   else{screen.fill(0,0,0);
   screen.circle(139,5,4);
   screen.noFill();}
  
  
if(Board[2][2] == 2){
     screen.fill(255,255,255);
  screen.circle(41,25,4);;
  screen.noFill();
   }
   else if(Board[2][2] == 3){
     screen.fill(0,255,0);
    screen.circle(41,25,4);
  screen.noFill();
   }
   else if(Board[2][2] == 9){
      screen.fill(0,0,255);
    screen.circle(41,25,4);
  screen.noFill();
   }
   else{screen.fill(0,0,0);
   screen.circle(41,25,4);
    screen.noFill();}

   if(Board[2][4] == 2){
     screen.fill(255,255,255);
  screen.circle(80,25,4);
  screen.noFill();
   }
   else if(Board[2][4] == 3){
     screen.fill(0,255,0);
    screen.circle(80,25,4);
  screen.noFill();
   }
   else if(Board[2][4] == 9){
      screen.fill(0,0,255);
    screen.circle(80,25,4);
  screen.noFill();
   }
   else{screen.fill(0,0,0);
   screen.circle(80,25,4);
    screen.noFill();}
  
    if(Board[2][6] == 2){
     screen.fill(255,255,255);
  screen.circle(119,25,4);
  screen.noFill();
   }
   else if(Board[2][6] == 3){
     screen.fill(0,255,0);
    screen.circle(119,25,4);
  screen.noFill();
   }
   else if(Board[2][6] == 9){
      screen.fill(0,0,255);
    screen.circle(119,25,4);
  screen.noFill();
   }
   else{screen.fill(0,0,0);
   screen.circle(119,25,4);
    screen.noFill();}

    if(Board[3][3] == 2){
     screen.fill(255,255,255);
   screen.circle(61,45,4);
  screen.noFill();
   }
   else if(Board[3][3] == 3){
     screen.fill(0,255,0);
     screen.circle(61,45,4);
  screen.noFill();
   }
   else if(Board[3][3] == 9){
      screen.fill(0,0,255);
    screen.circle(61,45,4);
  screen.noFill();
   }
   else{ screen.fill(0,0,0);
   screen.circle(61,45,4);
    screen.noFill();}

    if(Board[3][4] == 2){
     screen.fill(255,255,255);
    screen.circle(80,45,4);
  screen.noFill();
   }
   else if(Board[3][4] == 3){
     screen.fill(0,255,0);
      screen.circle(80,45,4);
  screen.noFill();
   }
   else if(Board[3][4] == 9){
      screen.fill(0,0,255);
     screen.circle(80,45,4);
  screen.noFill();
   }
   else{ screen.fill(0,0,0);
   screen.circle(80,45,4);
   screen.noFill();}

    if(Board[3][5] == 2){
     screen.fill(255,255,255);
    screen.circle(99,45,4);
  screen.noFill();
   }
   else if(Board[3][5] == 3){
     screen.fill(0,255,0);
      screen.circle(99,45,4);
  screen.noFill();
   }
   else if(Board[3][5] == 9){
      screen.fill(0,0,255);
     screen.circle(99,45,4);
  screen.noFill();
   }
   else{  screen.fill(0,0,0);
   screen.circle(99,45,4);
   screen.noFill();}

   if(Board[4][1] == 2){
     screen.fill(255,255,255);
    screen.circle(21,64,4);
  screen.noFill();
   }
   else if(Board[4][1] == 3){
     screen.fill(0,255,0);
      screen.circle(21,64,4);
  screen.noFill();
   }
   else if(Board[4][1] == 9){
      screen.fill(0,0,255);
     screen.circle(21,64,4);
  screen.noFill();
   }
   else{  screen.fill(0,0,0);
   screen.circle(21,64,4);
   screen.noFill();}

   if(Board[4][2] == 2){
     screen.fill(255,255,255);
   screen.circle(41,64,4);
  screen.noFill();
   }
   else if(Board[4][2] == 3){
     screen.fill(0,255,0);
      screen.circle(41,64,4);
  screen.noFill();
   }
   else if(Board[4][2] == 9){
      screen.fill(0,0,255);
     screen.circle(41,64,4);
  screen.noFill();
   }
   else{ screen.fill(0,0,0);
   screen.circle(41,64,4);
   screen.noFill();}

    if(Board[4][3] == 2){
     screen.fill(255,255,255);
   screen.circle(61,64,4);
  screen.noFill();
   }
   else if(Board[4][3] == 3){
     screen.fill(0,255,0);
       screen.circle(61,64,4);
  screen.noFill();
   }
   else if(Board[4][3] == 9){
      screen.fill(0,0,255);
      screen.circle(61,64,4);
  screen.noFill();
   }
   else{  screen.fill(0,0,0);
   screen.circle(61,64,4);
    screen.noFill();}

    if(Board[4][5] == 2){
     screen.fill(255,255,255);
  screen.circle(99,64,4);
  screen.noFill();
   }
   else if(Board[4][5] == 3){
     screen.fill(0,255,0);
       screen.circle(99,64,4);
  screen.noFill();
   }
   else if(Board[4][5] == 9){
      screen.fill(0,0,255);
      screen.circle(99,64,4);
  screen.noFill();
   }
   else{ screen.fill(0,0,0);
   screen.circle(99,64,4);
    screen.noFill();}

   if(Board[4][6] == 2){
     screen.fill(255,255,255);
   screen.circle(119,64,4);
  screen.noFill();
   }
   else if(Board[4][6] == 3){
     screen.fill(0,255,0);
       screen.circle(119,64,4);
  screen.noFill();
   }
   else if(Board[4][6] == 9){
      screen.fill(0,0,255);
       screen.circle(119,64,4);
  screen.noFill();
   }
   else{  screen.fill(0,0,0);
   screen.circle(119,64,4);
   screen.noFill();}

    if(Board[4][7] == 2){
     screen.fill(255,255,255);
   screen.circle(139,64,4);
  screen.noFill();
   }
   else if(Board[4][7] == 3){
     screen.fill(0,255,0);
       screen.circle(139,64,4);
  screen.noFill();
   }
   else if(Board[4][7] == 9){
      screen.fill(0,0,255);
        screen.circle(139,64,4);
  screen.noFill();
   }
   else{  screen.fill(0,0,0);
   screen.circle(139,64,4);
   screen.noFill();}

    if(Board[5][3] == 2){
     screen.fill(255,255,255);
    screen.circle(61,83,4);
  screen.noFill();
   }
   else if(Board[5][3] == 3){
     screen.fill(0,255,0);
       screen.circle(61,83,4);
  screen.noFill();
   }
   else if(Board[5][3] == 9){
      screen.fill(0,0,255);
        screen.circle(61,83,4);
  screen.noFill();
   }
   else{  screen.fill(0,0,0);
   screen.circle(61,83,4);
   screen.noFill();}

    if(Board[5][4] == 2){
     screen.fill(255,255,255);
    screen.circle(80,83,4);
  screen.noFill();
   }
   else if(Board[5][4] == 3){
     screen.fill(0,255,0);
       screen.circle(80,83,4);
  screen.noFill();
   }
   else if(Board[5][4] == 9){
      screen.fill(0,0,255);
         screen.circle(80,83,4);
  screen.noFill();
   }
   else{ screen.fill(0,0,0);
   screen.circle(80,83,4);
    screen.noFill();}

    if(Board[5][5] == 2){
     screen.fill(255,255,255);
   screen.circle(99,83,4);
  screen.noFill();
   }
   else if(Board[5][5] == 3){
     screen.fill(0,255,0);
       screen.circle(99,83,4);
  screen.noFill();
   }
   else if(Board[5][5] == 9){
      screen.fill(0,0,255);
        screen.circle(99,83,4);
  screen.noFill();
   }
   else{ screen.fill(0,0,0);
   screen.circle(99,83,4);
    screen.noFill();}

    if(Board[6][2] == 2){
     screen.fill(255,255,255);
   screen.circle(41,103,4);
  screen.noFill();
   }
   else if(Board[6][2] == 3){
     screen.fill(0,255,0);
       screen.circle(41,103,4);
  screen.noFill();
   }
   else if(Board[6][2] == 9){
      screen.fill(0,0,255);
         screen.circle(41,103,4);
  screen.noFill();
   }
   else{ screen.fill(0,0,0);
   screen.circle(41,103,4);
   screen.noFill();}

    if(Board[6][4] == 2){
     screen.fill(255,255,255);
   screen.circle(80,103,4);
  screen.noFill();
   }
   else if(Board[6][4] == 3){
     screen.fill(0,255,0);
        screen.circle(80,103,4);
  screen.noFill();
   }
   else if(Board[6][4] == 9){
      screen.fill(0,0,255);
          screen.circle(80,103,4);
  screen.noFill();
   }
   else{  screen.fill(0,0,0);
   screen.circle(80,103,4);
   screen.noFill();}

   if(Board[6][4] == 2){
     screen.fill(255,255,255);
   screen.circle(80,103,4);
  screen.noFill();
   }
   else if(Board[6][4] == 3){
     screen.fill(0,255,0);
        screen.circle(80,103,4);
  screen.noFill();
   }
   else if(Board[6][4] == 9){
      screen.fill(0,0,255);
          screen.circle(80,103,4);
  screen.noFill();
   }
   else{  screen.fill(0,0,0);
   screen.circle(80,103,4);
    screen.noFill();}

    if(Board[6][6] == 2){
     screen.fill(255,255,255);
   screen.circle(119,103,4);
  screen.noFill();
   }
   else if(Board[6][6] == 3){
     screen.fill(0,255,0);
        screen.circle(119,103,4);
  screen.noFill();
   }
   else if(Board[6][6] == 9){
      screen.fill(0,0,255);
          screen.circle(119,103,4);
  screen.noFill();
   }
   else{ screen.fill(0,0,0);
   screen.circle(119,103,4);
   screen.noFill();}

    if(Board[7][1] == 2){
     screen.fill(255,255,255);
   screen.circle(21,123,4);
  screen.noFill();
   }
   else if(Board[7][1] == 3){
     screen.fill(0,255,0);
       screen.circle(21,123,4);
  screen.noFill();
   }
   else if(Board[7][1] == 9){
      screen.fill(0,0,255);
          screen.circle(21,123,4);
  screen.noFill();
   }
   else{ screen.fill(0,0,0);
   screen.circle(21,123,4);
    screen.noFill();}

    if(Board[7][4] == 2){
     screen.fill(255,255,255);
   screen.circle(80,123,4);
  screen.noFill();
   }
   else if(Board[7][4] == 3){
     screen.fill(0,255,0);
      screen.circle(80,123,4);
  screen.noFill();
   }
   else if(Board[7][4] == 9){
      screen.fill(0,0,255);
          screen.circle(80,123,4);
  screen.noFill();
   }
   else{screen.fill(0,0,0);
   screen.circle(80,123,4);
   screen.noFill();}

   if(Board[7][7] == 2){
     screen.fill(255,255,255);
   screen.circle(139,123,4);
  screen.noFill();
   }
   else if(Board[7][7] == 3){
     screen.fill(0,255,0);
      screen.circle(139,123,4);
  screen.noFill();
   }
   else if(Board[7][7] == 9){
      screen.fill(0,0,255);
          screen.circle(139,123,4);
  screen.noFill();
   }
   else{ screen.fill(0,0,0);
   screen.circle(139,123,4);
   screen.noFill();}

    screen.noFill();
  screen.stroke(0,255,0); 
  screen.rect(21,5,118,118);
  screen.rect(41,25,78,78);
  screen.rect(61,45,38,38);
  screen.line(80,5,80,45);
  screen.line(80,123,80,83);
  screen.line(21,64,61,64);
  screen.line(99,64,139,64);
 
}



void setup(){
  
  screen.begin();
  screen.background(0,0,0); 
   pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(buttonPin, INPUT); 

  
  
}
 
  


void loop(){
Game();
  
  }
  
