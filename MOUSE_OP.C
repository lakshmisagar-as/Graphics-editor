#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include"numbers.h"

int gi_SelectedDrawStyle = FREEHAND;
int gi_SelectedColor = BLACK;
int gi_THICKNESS = 1;
int gi_PrevHighlighted = 35;

extern int gi_BUTTON,gi_Xposition,gi_Yposition;

/*////////////////////////////////////////////////////////////////////////////

	Function Name : CheckButtonPressArea();

	Parameters    : Xpos,Ypos - current position of the cursor

	Description   : This function finds on which area the mouse button is
					pressed. It returns the area on which the mouse button
					is pressed.

	Return value  : DRAWAREA(32), MENUAREA(33), STATUSAREA(34)

////////////////////////////////////////////////////////////////////////////*/

int CheckButtonPressArea(int iXpos, int iYpos)
{
	if( iXpos>=TOP && iXpos<=BOTTOM && iYpos>=(LEFT+80) && iYpos<(RIGHT-15))
	{
		return DRAWAREA;
	}

	if( iYpos<=(LEFT+80))
	{
		return MENUAREA;
	}

	if( iYpos>=(RIGHT-15))
	{
		return STATUSAREA;
	}

	return DRAWAREA;
}

/*////////////////////////////////////////////////////////////////////////////

	Function Name : FillingSelectedColorBox();

	Description   : It fills the box, which is present on menu bar to show the
					selected color. The default is black color.

////////////////////////////////////////////////////////////////////////////*/

void FillingSelectedColorBox()
{
	int i,j;
	for(i=375;i<=405;i++)
		for(j=15;j<=50;j++)
			putpixel(i,j,gi_SelectedColor);
}

/*////////////////////////////////////////////////////////////////////////////

	Function Name : PrintSelectedDrawStyle();

	Description   : This function prints the selected drawing style on the
					status bar. The default is Free hand style.

////////////////////////////////////////////////////////////////////////////*/

void PrintSelectedDrawStyle()
{
	static int PrevStyle = 10;

	if(PrevStyle == gi_SelectedDrawStyle)
		return;

	PrevStyle = gi_SelectedDrawStyle;

	setfillstyle(SOLID_FILL,LIGHTGRAY); // to erase the old position
	bar(250,463,500,476);

	setcolor(BLACK);

	switch(gi_SelectedDrawStyle)
	{
		case FREEHAND :
			outtextxy(255,466,"Free Hand");
			break;
		case LINEDRAW :
						outtextxy(255,466,"Line Draw");
						break;
		case RECTDRAW :
						outtextxy(255,466,"Rectangle Draw");
						break;
		case CIRCDRAW :
						outtextxy(255,466,"Circle Draw");
						break;
		case TRIDRAW  :
						outtextxy(255,466,"Triangle Draw");
						break;
		case RTRIDRAW :
						outtextxy(255,466,"Right angle Triangle Draw");
						break;
		case DIADRAW  :
						outtextxy(255,466,"Diamond Draw");
						break;
		case ERASER   :
						outtextxy(255,466,"Eraser");
						break;
		default       :
						outtextxy(255,466,"Free Hand Draw");
						break;
	}
}

/*////////////////////////////////////////////////////////////////////////////

	Function Name : CheckWhichMenuSelected();

	Parameters    : iXpos,iYpos - current position of the cursor
					FileMenu - It is required for selecting file menus

	Description   : This function check on which menu the mouse button selected
					and selects that menu for further operations. It incudes
					selecting the draw style, color, thickness for drawing,
					and also for file menus. If the File menus are selected
					the function will return appropriate values.

////////////////////////////////////////////////////////////////////////////*/

void CheckWhichMenuSelected(int iXpos, int iYpos, int *iFileMenu)
{
	int PrevColor = gi_SelectedColor;

	if( (iXpos >= LINEX1 && iXpos <= LINEX2) && (iYpos >= LINEY1 && iYpos <= LINEY2) )
		gi_SelectedDrawStyle = LINEDRAW;

	if( (iXpos >= RECTX1 && iXpos <= RECTX2) && (iYpos >= RECTY1 && iYpos <= RECTY2) )
		gi_SelectedDrawStyle = RECTDRAW;

	if( (iXpos >= CIRCX1 && iXpos <= CIRCX2) && (iYpos >= CIRCY1 && iYpos <= CIRCY2) )
		gi_SelectedDrawStyle = CIRCDRAW;

	if( (iXpos >= TRIX1 && iXpos <= TRIX2) && (iYpos >= TRIY1 && iYpos <= TRIY2) )
		gi_SelectedDrawStyle = TRIDRAW;

	if( (iXpos >= RTRIX1 && iXpos <= RTRIX2) && (iYpos >= RTRIY1 && iYpos <= RTRIY2) )
		gi_SelectedDrawStyle = RTRIDRAW;

	if( (iXpos >= DIAX1 && iXpos <= DIAX2) && (iYpos >= DIAY1 && iYpos <= DIAY2) )
		gi_SelectedDrawStyle = DIADRAW;

	if( (iXpos >= FREEHANDX1 && iXpos <= FREEHANDX2) && (iYpos >= FREEHANDY1 && iYpos <= FREEHANDY2) )
		gi_SelectedDrawStyle = FREEHAND;

	if( (iXpos >= ERASERX1 && iXpos <= ERASERX2) && (iYpos >= ERASERY1 && iYpos <= ERASERY2) )
		gi_SelectedDrawStyle = ERASER;

	PrintSelectedDrawStyle();


/* for selecting color */
	if( (iXpos >= BLACKX1 && iXpos <= BLACKX2) && (iYpos >= BLACKY1 && iYpos <= BLACKY2) )
		gi_SelectedColor = BLACK;

	if( (iXpos >= BLUEX1 && iXpos <= BLUEX2) && (iYpos >= BLUEY1 && iYpos <= BLUEY2) )
		gi_SelectedColor = BLUE;

	if( (iXpos >= GREENX1 && iXpos <= GREENX2) && (iYpos >= GREENY1 && iYpos <= GREENY2) )
		gi_SelectedColor = GREEN;

	if( (iXpos >= CYANX1 && iXpos <= CYANX2) && (iYpos >= CYANY1 && iYpos <= CYANY2) )
		gi_SelectedColor = CYAN;

	if( (iXpos >= REDX1 && iXpos <= REDX2) && (iYpos >= REDY1 && iYpos <= REDY2) )
		gi_SelectedColor = RED;

	if( (iXpos >= MAGENTAX1 && iXpos <= MAGENTAX2) && (iYpos >= MAGENTAY1 && iYpos <= MAGENTAY2) )
		gi_SelectedColor = MAGENTA;

	if( (iXpos >= BROWNX1 && iXpos <= BROWNX2) && (iYpos >= BROWNY1 && iYpos <= BROWNY2) )
		gi_SelectedColor = BROWN;

	if( (iXpos >= LIGHTGRAYX1 && iXpos <= LIGHTGRAYX2) && (iYpos >= LIGHTGRAYY1 && iYpos <= LIGHTGRAYY2) )
		gi_SelectedColor = LIGHTGRAY;

	if( (iXpos >= DARKGRAYX1 && iXpos <= DARKGRAYX2) && (iYpos >= DARKGRAYY1 && iYpos <= DARKGRAYY2) )
		gi_SelectedColor = DARKGRAY;

	if( (iXpos >= LIGHTBLUEX1 && iXpos <= LIGHTBLUEX2) && (iYpos >= LIGHTBLUEY1 && iYpos <= LIGHTBLUEY2) )
		gi_SelectedColor = LIGHTBLUE;

	if( (iXpos >= LIGHTGREENX1 && iXpos <= LIGHTGREENX2) && (iYpos >= LIGHTGREENY1 && iYpos <= LIGHTGREENY2) )
		gi_SelectedColor = LIGHTGREEN;

	if( (iXpos >= LIGHTCYANX1 && iXpos <= LIGHTCYANX2) && (iYpos >= LIGHTCYANY1 && iYpos <= LIGHTCYANY2) )
		gi_SelectedColor = LIGHTCYAN;

	if( (iXpos >= LIGHTREDX1 && iXpos <= LIGHTREDX2) && (iYpos >= LIGHTREDY1 && iYpos <= LIGHTREDY2) )
		gi_SelectedColor = LIGHTRED;

	if( (iXpos >= LIGHTMAGENTAX1 && iXpos <= LIGHTMAGENTAX2) && (iYpos >= LIGHTMAGENTAY1 && iYpos <= LIGHTMAGENTAY2) )
		gi_SelectedColor = LIGHTMAGENTA;

	if( (iXpos >= YELLOWX1 && iXpos <= YELLOWX2) && (iYpos >= YELLOWY1 && iYpos <= YELLOWY2) )
		gi_SelectedColor = YELLOW;

	if( (iXpos >= WHITEX1 && iXpos <= WHITEX2) && (iYpos >= WHITEY1 && iYpos <= WHITEY2) )
		gi_SelectedColor = WHITE;

	if(gi_SelectedColor != PrevColor)
		FillingSelectedColorBox();

/* for file menu */
// 80,5,130,20   //     new pos
	if( (iXpos >= 80 && iXpos <= 130) && (iYpos >= 5 && iYpos <= 20) )
		*iFileMenu = NEW;
// 80,30,130,45  //     open pos
	if( (iXpos >= 80 && iXpos <= 130) && (iYpos >= 30 && iYpos <= 45) )
		*iFileMenu = OPEN;
// 140,5,190,20  //    save pos
	if( (iXpos >= 140 && iXpos <= 190) && (iYpos >= 5 && iYpos <= 20) )
		*iFileMenu = SAVE;
// 140,30,200,45  // save as pos
	if( (iXpos >= 140 && iXpos <= 200) && (iYpos >= 30 && iYpos <= 45) )
		*iFileMenu = SAVEAS;
// 110,55,160,70  // exit pos
	if( (iXpos >= 110 && iXpos <= 160) && (iYpos >= 55 && iYpos <= 70) )
		*iFileMenu = EXIT;

/* for selecting thickness */
	if( (iXpos >= 233 && iXpos <= 272) && (iYpos >= 17 && iYpos <= 26) )
		gi_THICKNESS = 1;

	if( (iXpos >= 233 && iXpos <= 272) && (iYpos >= 28 && iYpos <= 37) )
		gi_THICKNESS = 2;

	if( (iXpos >= 233 && iXpos <= 272) && (iYpos >= 39 && iYpos <= 48) )
		gi_THICKNESS = 4;

	if( (iXpos >= 233 && iXpos <= 272) && (iYpos >= 50 && iYpos <= 59) )
		gi_THICKNESS = 6;
}

/*////////////////////////////////////////////////////////////////////////////

	Function Name : HighlightRect();

	Parameters    : box - which specifies on which menu box the action is to be taken
					color - it is used to either highlight or dehighlight the menu box

	Description   : This function Highlight menu box when the cursor is placed
					on that menu with lightred color and also dehighlight the
					menu box when the cursor is moved on from that box.

////////////////////////////////////////////////////////////////////////////*/

void HighlightRect(int ibox, int icolor)
{
	setcolor(icolor);

	switch(ibox)
	{
		case BLACK:
					HideMousePointer();
					rectangle(BLACKX1,BLACKY1,BLACKX2,BLACKY2);
					break;
		case BLUE:
					HideMousePointer();
					rectangle(BLUEX1,BLUEY1,BLUEX2,BLUEY2);
					break;
		case GREEN:
					HideMousePointer();
					rectangle(GREENX1,GREENY1,GREENX2,GREENY2);
					break;
		case CYAN:
					HideMousePointer();
					rectangle(CYANX1,CYANY1,CYANX2,CYANY2);
					break;
		case RED:
					HideMousePointer();
					rectangle(REDX1,REDY1,REDX2,REDY2);
					break;
		case MAGENTA:
					HideMousePointer();
					rectangle(MAGENTAX1,MAGENTAY1,MAGENTAX2,MAGENTAY2);
					break;
		case BROWN:
					HideMousePointer();
					rectangle(BROWNX1,BROWNY1,BROWNX2,BROWNY2);
					break;
		case LIGHTGRAY:
					HideMousePointer();
					rectangle(LIGHTGRAYX1,LIGHTGRAYY1,LIGHTGRAYX2,LIGHTGRAYY2);
					break;
		case DARKGRAY:
					HideMousePointer();
					rectangle(DARKGRAYX1,DARKGRAYY1,DARKGRAYX2,DARKGRAYY2);
					break;
		case LIGHTBLUE:
					HideMousePointer();
					rectangle(LIGHTBLUEX1,LIGHTBLUEY1,LIGHTBLUEX2,LIGHTBLUEY2);
					break;
		case LIGHTGREEN:
					HideMousePointer();
					rectangle(LIGHTGREENX1,LIGHTGREENY1,LIGHTGREENX2,LIGHTGREENY2);
					break;
		case LIGHTCYAN:
					HideMousePointer();
					rectangle(LIGHTCYANX1,LIGHTCYANY1,LIGHTCYANX2,LIGHTCYANY2);
					break;
		case LIGHTRED:
					HideMousePointer();
					rectangle(LIGHTREDX1,LIGHTREDY1,LIGHTREDX2,LIGHTREDY2);
					break;
		case LIGHTMAGENTA:
					HideMousePointer();
					rectangle(LIGHTMAGENTAX1,LIGHTMAGENTAY1,LIGHTMAGENTAX2,LIGHTMAGENTAY2);
					break;
		case YELLOW:
					HideMousePointer();
					rectangle(YELLOWX1,YELLOWY1,YELLOWX2,YELLOWY2);
					break;
		case WHITE:
					HideMousePointer();
					rectangle(WHITEX1,WHITEY1,WHITEX2,WHITEY2);
					break;
		case LINEDRAW:
					HideMousePointer();
					rectangle(LINEX1,LINEY1,LINEX2,LINEY2);
					break;
		case RECTDRAW:
					HideMousePointer();
					rectangle(RECTX1,RECTY1,RECTX2,RECTY2);
					break;
		case CIRCDRAW:
					HideMousePointer();
					rectangle(CIRCX1,CIRCY1,CIRCX2,CIRCY2);
					break;
		case TRIDRAW:
					HideMousePointer();
					rectangle(TRIX1,TRIY1,TRIX2,TRIY2);
					break;
		case RTRIDRAW:
					HideMousePointer();
					rectangle(RTRIX1,RTRIY1,RTRIX2,RTRIY2);
					break;
		case DIADRAW:
					HideMousePointer();
					rectangle(DIAX1,DIAY1,DIAX2,DIAY2);
					break;
		case SIZE1:
					HideMousePointer();
					rectangle(SIZE1X1,SIZE1Y1,SIZE1X2,SIZE1Y2);
					break;
		case SIZE2:
					HideMousePointer();
					rectangle(SIZE2X1,SIZE2Y1,SIZE2X2,SIZE2Y2);
					break;
		case SIZE4:
					HideMousePointer();
					rectangle(SIZE4X1,SIZE4Y1,SIZE4X2,SIZE4Y2);
					break;
		case SIZE6:
					HideMousePointer();
					rectangle(SIZE6X1,SIZE6Y1,SIZE6X2,SIZE6Y2);
					break;
		case NEW:
					HideMousePointer();
					rectangle(NEWX1,NEWY1,NEWX2,NEWY2);
					break;
		case OPEN:
					HideMousePointer();
					rectangle(OPENX1,OPENY1,OPENX2,OPENY2);
					break;
		case SAVE:
					HideMousePointer();
					rectangle(SAVEX1,SAVEY1,SAVEX2,SAVEY2);
					break;
		case SAVEAS:
					HideMousePointer();
					rectangle(SAVEASX1,SAVEASY1,SAVEASX2,SAVEASY2);
					break;
		case EXIT:
					HideMousePointer();
					rectangle(EXITX1,EXITY1,EXITX2,EXITY2);
					break;
		case ENTER:
					HideMousePointer();
					rectangle(ENTERX1,ENTERY1,ENTERX2,ENTERY2);
					break;
		case CANCEL:
					HideMousePointer();
					rectangle(CANCELX1,CANCELY1,CANCELX2,CANCELY2);
					break;
		case FREEHAND:
					HideMousePointer();
					rectangle(FREEHANDX1,FREEHANDY1,FREEHANDX2,FREEHANDY2);
					break;
		case ERASER:
					HideMousePointer();
					rectangle(ERASERX1,ERASERY1,ERASERX2,ERASERY2);
					break;
		case YES:
					HideMousePointer();
					rectangle(YESX1,YESY1,YESX2,YESY2);
					break;
		case NO:
					HideMousePointer();
					rectangle(NOX1,NOY1,NOX2,NOY2);
					break;
		case CAN:
					HideMousePointer();
					rectangle(CANX1,CANY1,CANX2,CANY2);
					break;
	}

	ShowMousePointer();
}

/*////////////////////////////////////////////////////////////////////////////

	Function Name : HighlightMenu();

	Parameters    : iXpos,iYpos - current position of the mouse cursor

	Description   : This function finds on which menu box the mouse cursor is
					placed and calls the HighlightRect() to highlight that
					menu box. It checks all the color boxes, shapes boxes,
					thickness boxes, and file menus

////////////////////////////////////////////////////////////////////////////*/

void HighlightMenu(iXpos , iYpos)
{
	int col;
	col = getcolor();

	if( (iXpos >= BLACKX1 && iXpos <= BLACKX2) && (iYpos >= BLACKY1 && iYpos <= BLACKY2) )
	{
		if(gi_PrevHighlighted == BLACK)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(BLACK,LIGHTRED);
		gi_PrevHighlighted = BLACK;
	}

	else if( (iXpos >= BLUEX1 && iXpos <= BLUEX2) && (iYpos >= BLUEY1 && iYpos <= BLUEY2) )
	{
		if(gi_PrevHighlighted == BLUE)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(BLUE,LIGHTRED);
		gi_PrevHighlighted = BLUE;
	}

	else if( (iXpos >= GREENX1 && iXpos <= GREENX2) && (iYpos >= GREENY1 && iYpos <= GREENY2) )
	{
		if(gi_PrevHighlighted == GREEN)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(GREEN,LIGHTRED);
		gi_PrevHighlighted = GREEN;
	}

	else if( (iXpos >= CYANX1 && iXpos <= CYANX2) && (iYpos >= CYANY1 && iYpos <= CYANY2) )
	{
		if(gi_PrevHighlighted == CYAN)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(CYAN,LIGHTRED);
		gi_PrevHighlighted = CYAN;
	}

	else if( (iXpos >= REDX1 && iXpos <= REDX2) && (iYpos >= REDY1 && iYpos <= REDY2) )
	{
		if(gi_PrevHighlighted == RED)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(RED,LIGHTRED);
		gi_PrevHighlighted = RED;
	}

	else if( (iXpos >= MAGENTAX1 && iXpos <= MAGENTAX2) && (iYpos >= MAGENTAY1 && iYpos <= MAGENTAY2) )
	{
		if(gi_PrevHighlighted == MAGENTA)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(MAGENTA,LIGHTRED);
		gi_PrevHighlighted = MAGENTA;
	}

	else if( (iXpos >= BROWNX1 && iXpos <= BROWNX2) && (iYpos >= BROWNY1 && iYpos <= BROWNY2) )
	{
		if(gi_PrevHighlighted == BROWN)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(BROWN,LIGHTRED);
		gi_PrevHighlighted = BROWN;
	}

	else if( (iXpos >= LIGHTGRAYX1 && iXpos <= LIGHTGRAYX2) && (iYpos >= LIGHTGRAYY1 && iYpos <= LIGHTGRAYY2) )
	{
		if(gi_PrevHighlighted == LIGHTGRAY)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(LIGHTGRAY,LIGHTRED);
		gi_PrevHighlighted = LIGHTGRAY;
	}

	else if( (iXpos >= DARKGRAYX1 && iXpos <= DARKGRAYX2) && (iYpos >= DARKGRAYY1 && iYpos <= DARKGRAYY2) )
	{
		if(gi_PrevHighlighted == DARKGRAY)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(DARKGRAY,LIGHTRED);
		gi_PrevHighlighted = DARKGRAY;
	}

	else if( (iXpos >= LIGHTBLUEX1 && iXpos <= LIGHTBLUEX2) && (iYpos >= LIGHTBLUEY1 && iYpos <= LIGHTBLUEY2) )
	{
		if(gi_PrevHighlighted == LIGHTBLUE)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(LIGHTBLUE,LIGHTRED);
		gi_PrevHighlighted = LIGHTBLUE;
	}

	else if( (iXpos >= LIGHTGREENX1 && iXpos <= LIGHTGREENX2) && (iYpos >= LIGHTGREENY1 && iYpos <= LIGHTGREENY2) )
	{
		if(gi_PrevHighlighted == LIGHTGREEN)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(LIGHTGREEN,LIGHTRED);
		gi_PrevHighlighted = LIGHTGREEN;
	}

	else if( (iXpos >= LIGHTCYANX1 && iXpos <= LIGHTCYANX2) && (iYpos >= LIGHTCYANY1 && iYpos <= LIGHTCYANY2) )
	{
		if(gi_PrevHighlighted == LIGHTCYAN)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(LIGHTCYAN,LIGHTRED);
		gi_PrevHighlighted = LIGHTCYAN;
	}

	else if( (iXpos >= LIGHTREDX1 && iXpos <= LIGHTREDX2) && (iYpos >= LIGHTREDY1 && iYpos <= LIGHTREDY2) )
	{
		if(gi_PrevHighlighted == LIGHTRED)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(LIGHTRED,LIGHTRED);
		gi_PrevHighlighted = LIGHTRED;
	}

	else if( (iXpos >= LIGHTMAGENTAX1 && iXpos <= LIGHTMAGENTAX2) && (iYpos >= LIGHTMAGENTAY1 && iYpos <= LIGHTMAGENTAY2) )
	{
		if(gi_PrevHighlighted == LIGHTMAGENTA)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(LIGHTMAGENTA,LIGHTRED);
		gi_PrevHighlighted = LIGHTMAGENTA;
	}

	else if( (iXpos >= YELLOWX1 && iXpos <= YELLOWX2) && (iYpos >= YELLOWY1 && iYpos <= YELLOWY2) )
	{
		if(gi_PrevHighlighted == YELLOW)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(YELLOW,LIGHTRED);
		gi_PrevHighlighted = YELLOW;
	}

	else if( (iXpos >= WHITEX1 && iXpos <= WHITEX2) && (iYpos >= WHITEY1 && iYpos <= WHITEY2) )
	{
		if(gi_PrevHighlighted == WHITE)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(WHITE,LIGHTRED);
		gi_PrevHighlighted = WHITE;
	}

	else if( (iXpos >=LINEX1 && iXpos <= LINEX2) && (iYpos >=LINEY1 && iYpos <= LINEY2) )
	{
		if(gi_PrevHighlighted == LINEDRAW)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(LINEDRAW,LIGHTRED);
		gi_PrevHighlighted = LINEDRAW;
	}

	else if( (iXpos >=RECTX1 && iXpos <= RECTX2) && (iYpos >=RECTY1 && iYpos <= RECTY2) )
	{
		if(gi_PrevHighlighted == RECTDRAW)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(RECTDRAW,LIGHTRED);
		gi_PrevHighlighted = RECTDRAW;
	}

	else if( (iXpos >=CIRCX1 && iXpos <= CIRCX2) && (iYpos >=CIRCY1 && iYpos <= CIRCY2) )
	{
		if(gi_PrevHighlighted == CIRCDRAW)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(CIRCDRAW,LIGHTRED);
		gi_PrevHighlighted = CIRCDRAW;
	}

	else if( (iXpos >=TRIX1 && iXpos <= TRIX2) && (iYpos >=TRIY1 && iYpos <= TRIY2) )
	{
		if(gi_PrevHighlighted == TRIDRAW)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(TRIDRAW,LIGHTRED);
		gi_PrevHighlighted = TRIDRAW;
	}

	else if( (iXpos >=RTRIX1 && iXpos <= RTRIX2) && (iYpos >=RTRIY1 && iYpos <= RTRIY2) )
	{
		if(gi_PrevHighlighted == RTRIDRAW)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(RTRIDRAW,LIGHTRED);
		gi_PrevHighlighted = RTRIDRAW;
	}

	else if( (iXpos >= DIAX1 && iXpos <= DIAX2) && (iYpos >= DIAY1 && iYpos <= DIAY2) )
	{
		if(gi_PrevHighlighted == DIADRAW)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(DIADRAW,LIGHTRED);
		gi_PrevHighlighted = DIADRAW;
	}

	else if( (iXpos >= SIZE1X1 && iXpos <= SIZE1X2) && (iYpos >= SIZE1Y1 && iYpos <= SIZE1Y2) )
	{
		if(gi_PrevHighlighted == SIZE1)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(SIZE1,LIGHTRED);
		gi_PrevHighlighted = SIZE1;
	}

	else if( (iXpos >= SIZE2X1 && iXpos <= SIZE2X2) && (iYpos >= SIZE2Y1 && iYpos <= SIZE2Y2) )
	{
		if(gi_PrevHighlighted == SIZE2)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(SIZE2,LIGHTRED);
		gi_PrevHighlighted = SIZE2;
	}

	else if( (iXpos >= SIZE4X1 && iXpos <= SIZE4X2) && (iYpos >= SIZE4Y1 && iYpos <= SIZE4Y2) )
	{
		if(gi_PrevHighlighted == SIZE4)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(SIZE4,LIGHTRED);
		gi_PrevHighlighted = SIZE4;
	}

	else if( (iXpos >= SIZE6X1 && iXpos <= SIZE6X2) && (iYpos >= SIZE6Y1 && iYpos <= SIZE6Y2) )
	{
		if(gi_PrevHighlighted == SIZE6)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(SIZE6,LIGHTRED);
		gi_PrevHighlighted = SIZE6;
	}

	else if( (iXpos >= NEWX1 && iXpos <= NEWX2) && (iYpos >= NEWY1 && iYpos <= NEWY2) )
	{
		if(gi_PrevHighlighted == NEW)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(NEW,LIGHTRED);
		gi_PrevHighlighted = NEW;
	}

	else if( (iXpos >= OPENX1 && iXpos <= OPENX2) && (iYpos >= OPENY1 && iYpos <= OPENY2) )
	{
		if(gi_PrevHighlighted == OPEN)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(OPEN,LIGHTRED);
		gi_PrevHighlighted = OPEN;
	}

	else if( (iXpos >= SAVEX1 && iXpos <= SAVEX2) && (iYpos >= SAVEY1 && iYpos <= SAVEY2) )
	{
		if(gi_PrevHighlighted == SAVE)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(SAVE,LIGHTRED);
		gi_PrevHighlighted = SAVE;
	}

	else if( (iXpos >= SAVEASX1 && iXpos <= SAVEASX2) && (iYpos >= SAVEASY1 && iYpos <= SAVEASY2) )
	{
		if(gi_PrevHighlighted == SAVEAS)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(SAVEAS,LIGHTRED);
		gi_PrevHighlighted = SAVEAS;
	}

	else if( (iXpos >= EXITX1 && iXpos <= EXITX2) && (iYpos >= EXITY1 && iYpos <= EXITY2) )
	{
		if(gi_PrevHighlighted == EXIT)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(EXIT,LIGHTRED);
		gi_PrevHighlighted = EXIT;
	}

	else if( (iXpos >= FREEHANDX1 && iXpos <= FREEHANDX2) && (iYpos >= FREEHANDY1 && iYpos <= FREEHANDY2) )
	{
		if(gi_PrevHighlighted == FREEHAND)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(FREEHAND,LIGHTRED);
		gi_PrevHighlighted = FREEHAND;
	}

	else if( (iXpos >= ERASERX1 && iXpos <= ERASERX2) && (iYpos >= ERASERY1 && iYpos <= ERASERY2) )
	{
		if(gi_PrevHighlighted == ERASER)
			return;

		HighlightRect(gi_PrevHighlighted,WHITE);
		HighlightRect(ERASER,LIGHTRED);
		gi_PrevHighlighted = ERASER;
	}

	else
	{
		HighlightRect(gi_PrevHighlighted,WHITE);
		gi_PrevHighlighted = 35;
	}

	setcolor(col);
}

/*////////////////////////////////////////////////////////////////////////////

	Function Name : HandleMouseEvents();

	Description   : This function handles all the mouse events and calls the
					required functions. If the mouse is pressed  on Draw area,
					the DrawShapes() function is called to draw and if mouse
					is pressed on Menu area, the CheckWhichMenuSelected()
					function is called to select the menus, and if mouse is
					pressed on status area no action is taken.

////////////////////////////////////////////////////////////////////////////*/

int HandleMouseEvents()
{
	int iFileMenu = 0;
	gi_BUTTON = 0;

	while( !kbhit()  && (gi_BUTTON & 1) !=1 )
	{
		ShowMousePointer();

		GetMousePosition();

		ShowMousePixels();

		if(gi_Yposition < 80)
			HighlightMenu(gi_Xposition , gi_Yposition);

		if(gi_BUTTON == 1)
		{
			int area = 0;
			area = CheckButtonPressArea(gi_Xposition, gi_Yposition);
			switch(area)
			{
				case DRAWAREA:
					DrawShapes();
					break;
				case MENUAREA:
					CheckWhichMenuSelected(gi_Xposition, gi_Yposition,&iFileMenu);
					if(iFileMenu > 0)
						return iFileMenu;

					break;
				case STATUSAREA:
					break;
			}
		}

		if(gi_BUTTON == 1)
		{
			GetMousePosition();
			while(gi_BUTTON == 1)
				GetMousePosition();
		}
	}
	return 0;
}

