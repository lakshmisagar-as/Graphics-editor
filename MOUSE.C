#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<graphics.h>
#include"numbers.h"

extern int gi_BUTTON,gi_Xposition,gi_Yposition;
union REGS  InReg , OutReg;

/*////////////////////////////////////////////////////////////////////////////

	Function name : InitMouse()

	Input 		  : InReg.x.ax = 0;

	Description   : This function initializes the mouse and
					also get the mouse status, returns the value of output AX

	Output		  : Output AX value = FFFFh if mouse support is available
					Output AX value = 0 if mouse support is not available

////////////////////////////////////////////////////////////////////////////*/

int InitMouse()
{
	InReg.x.ax = 0;
	int86( 0x33 , &InReg , &OutReg );

	return(OutReg.x.ax);
}

/*////////////////////////////////////////////////////////////////////////////

	Function name : ShowMousePointer()

	Inut		  : InReg.x.ax = 1;

	Description   : This function displays the mouse pointer on the screen

////////////////////////////////////////////////////////////////////////////*/

void ShowMousePointer()
{
	InReg.x.ax = 1;
	int86( 0x33 , &InReg, &OutReg );
}

/*////////////////////////////////////////////////////////////////////////////

	Function name : HideMousePointer()

	Input		  : InReg.x.ax = 2;

	Description	  : This function hides the mouse pointer from displaying
					on the screen

////////////////////////////////////////////////////////////////////////////*/

void HideMousePointer()
{
	InReg.x.ax = 2;
	int86( 0x33 , &InReg , &OutReg );
}

/*////////////////////////////////////////////////////////////////////////////

	Function name : GetMousePosition()

	Input 		  : InReg.x.ax = 3;

	Description   : This function gives the current position of mouse cursor
					and also the button status

	Output		  : X-coordinate = OutReg.x.cx;
					Y-coordinate = OutReg.x.dx;
					Button status= OutReg.x.bx;

////////////////////////////////////////////////////////////////////////////*/

void GetMousePosition()
{
	InReg.x.ax = 3;
	int86( 0x33 , &InReg , &OutReg );

	gi_BUTTON = OutReg.x.bx;
	gi_Xposition = OutReg.x.cx;
	gi_Yposition = OutReg.x.dx;
}

/*////////////////////////////////////////////////////////////////////////////

	Function name : RestrictMousePointer()

	Input		  : InReg.x.ax = 7  for horizontal range
					InReg.x.ax = 8  for vertical range

	Description   : This function restricts the mouse pointer area on the
					screen to a desired area which user wants

////////////////////////////////////////////////////////////////////////////*/

void RestrictMousePointer(int X1,int Y1,int X2,int Y2)
{
	InReg.x.ax = 7;
	InReg.x.cx = X1;
	InReg.x.dx = X2;
	int86( 0X33 , &InReg , &OutReg );

	InReg.x.ax = 8;
	InReg.x.cx = Y1;
	InReg.x.dx = Y2;
	int86( 0X33 , &InReg , &OutReg );
}

/*////////////////////////////////////////////////////////////////////////////

	Function name : ShowMousePixels()

	Description   : This function shows the the current mouse position in the
					status bar as (X,Y)

////////////////////////////////////////////////////////////////////////////*/

void ShowMousePixels()
{
	char chArray[50];
	int icol;
	static int iPrevX=0,iPrevY=0;

	icol = getcolor();

	if(iPrevX != gi_Xposition || iPrevY != gi_Yposition)
	{
		if( gi_Xposition>=TOP && gi_Xposition<=BOTTOM && gi_Yposition>=(LEFT+80) && gi_Yposition<(RIGHT-15))
		{
			setfillstyle(SOLID_FILL,LIGHTGRAY); // to erase the old position
			bar(85,463,140,476);

			setcolor(BLACK);
			sprintf(chArray,"%d,%d",(gi_Xposition-TOP),(gi_Yposition-(LEFT+80))); // printing the position
			outtextxy(85,467, chArray);
		}

		if( gi_Yposition > (RIGHT-15))
		{
			setfillstyle(SOLID_FILL,LIGHTGRAY);
			bar(85,463,140,476);
		}
		iPrevX = gi_Xposition;
		iPrevY = gi_Yposition;
	}
	setcolor(icol);
}
