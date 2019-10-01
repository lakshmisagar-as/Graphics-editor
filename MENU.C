#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include"numbers.h"

/*//////////////////////////////////////////////////////////////////////////

	Function name : InitColorBoxes()

	Description   : This function creates the boxes which contains different
					colors, which are later used forselecting colors for drawing

//////////////////////////////////////////////////////////////////////////*/

void InitColorBoxes()
{
	int color;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	setcolor(BLACK);
	outtextxy(432,73,"Colors");

	x1 = BLACKX1;
	y1 = BLACKY1;
	x2 = BLACKX2;
	y2 = BLACKY2;

	for(color=0;color<16;color++)
	{
		setfillstyle(SOLID_FILL,color);
		bar(x1+2,y1+2,x2-2,y2-2);
		setcolor(WHITE);
		rectangle(x1,y1,x2,y2);
		x1 = x1+17;
		x2 = x2+17;
		if(x2 > 484)
		{
			y1 = y1+17;
			y2 = y2+17;
			x1 = 419;
			x2 = 433;
		}
	}
}

/*//////////////////////////////////////////////////////////////////////////

	Function name : InitShapesbox()

	Description   : This function creates the different shapes in the menu
					bar, which are later used for drawing

//////////////////////////////////////////////////////////////////////////*/

void InitShapesBox()
{
	/* displaying different shapes */
	setfillstyle(SOLID_FILL,WHITE);
	bar(290,6,360,65);
	setcolor(BLACK);
	outtextxy(304,71,"Shapes");

	PrintSelectedDrawStyle();          // for displaying selected shape in status bar //

	setcolor(DARKGRAY);
	rectangle(288,4,362,67);

//	rectangle(292,11,312,31);
	setcolor(LIGHTBLUE);
	line(295,14,309,28);

//	rectangle(315,11,335,31);
	rectangle(317,15,334,25);

//	rectangle(338,11,358,31);
	circle(348,21,7);

//	rectangle(292,36,312,56);
	line(302,39,294,53);
	line(294,53,310,53);
	line(302,39,310,53);

//	rectangle(315,36,335,56);
	line(318,39,318,53);
	line(318,39,332,53);
	line(318,53,332,53);

//	rectangle(338,36,358,56);
	line(348,39,341,46);
	line(348,39,355,46);
	line(341,46,348,53);
	line(355,46,348,53);
}


/*//////////////////////////////////////////////////////////////////////////

	Function name : InitMenu()

	Description   : This function initialize the menu bar and status bar

//////////////////////////////////////////////////////////////////////////*/

void InitMenu()
{
	setfillstyle(SOLID_FILL,WHITE);        //background
	bar(TOP,LEFT,BOTTOM,RIGHT);

	setfillstyle(SOLID_FILL,LIGHTGRAY);     //menu bar
	bar(TOP,LEFT,BOTTOM,LEFT+80);

	setfillstyle(SOLID_FILL,LIGHTGRAY);      //status bar
	bar(TOP,RIGHT-15,BOTTOM,RIGHT);

	setfillstyle(SOLID_FILL,LIGHTRED);
	bar(62,0,68,478);
	bar(570,0,576,478);
	bar(69,477,569,478);
	bar(69,0,569,1);

	setfillstyle(SOLID_FILL,DARKGRAY);
	bar(70,81,568,82);
	bar(70,461,568,462);
//	bar(70,81,70,462);
//	bar(568,81,568,462);

	InitColorBoxes();

	/* displaying box for selected color */
	setfillstyle(SOLID_FILL,BLACK);
	bar(375,15,405,50);

	setcolor(WHITE);
	rectangle(374,14,406,51);

	setcolor(BLACK);
	rectangle(373,13,407,52);
	outtextxy(374,59,"Color");

	/* displaying box for selecting pencil size  */
	setfillstyle(SOLID_FILL,WHITE);
	bar(230,15,275,61);

	setcolor(BLACK);
	rectangle(229,14,276,61);
	outtextxy(237,65,"Size");

	/* displaying different sizes */
	setcolor(WHITE);
	rectangle(233,17,272,26);
	rectangle(233,28,272,37);
	rectangle(233,39,272,48);
	rectangle(233,50,272,59);

	setfillstyle(SOLID_FILL,BLACK);
	bar(235,22,270,22);               /* thinckness = 1 */
	bar(235,32,270,33);               /* thinckness = 2 */
	bar(235,42,270,45);               /* thinckness = 4 */
	bar(235,52,270,57);               /* thinckness = 6 */

	InitShapesBox();

/* for file menu */
	setcolor(WHITE);
	rectangle(78,3,132,22);
	rectangle(78,28,132,47);
	rectangle(138,3,192,22);
	rectangle(138,28,202,47);
	rectangle(108,53,162,72);

	setcolor(BLACK);
	setfillstyle(SOLID_FILL,WHITE);
	bar(80,5,130,20);
	outtextxy(95,9,"New");

	setfillstyle(SOLID_FILL,WHITE);
	bar(80,30,130,45);
	outtextxy(90,34,"Open");

	setfillstyle(SOLID_FILL,WHITE);
	bar(140,5,190,20);
	outtextxy(150,9,"Save");

	setfillstyle(SOLID_FILL,WHITE);
	bar(140,30,200,45);
	outtextxy(142,34,"Save As");

	setfillstyle(SOLID_FILL,WHITE);
	bar(110,55,160,70);
	outtextxy(120,59,"Exit");

	setfillstyle(SOLID_FILL,WHITE);       /* box for pencil */
	bar(500,10,520,30);
	setcolor(WHITE);
	rectangle(498,8,522,32);

	setcolor(BLACK);
	line(503,24,514,13);
	line(505,27,516,16);
	line(503,24,505,27);
	line(514,13,516,16);
	line(503,24,502,28);
	line(505,27,502,28);
	line(511,15,514,18);
	line(509,17,511,19);

	setfillstyle(SOLID_FILL,YELLOW);
	floodfill(510,20,0);

	setfillstyle(SOLID_FILL,LIGHTBLUE);
	floodfill(512,18,0);

	setfillstyle(SOLID_FILL,BROWN);
	floodfill(514,16,0);

	setfillstyle(SOLID_FILL,WHITE);       /* box for eraser */
	bar(530,10,550,30);
	setcolor(WHITE);
	rectangle(528,8,552,32);

	setcolor(BLACK);
	line(535,21,543,13);
	line(537,25,545,17);
	line(535,21,537,25);
	line(543,13,545,17);
	line(545,17,545,20);
	line(537,25,537,28);
	line(545,20,537,28);
	line(535,21,533,24);
	line(533,24,537,28);

	setfillstyle(SOLID_FILL,LIGHTMAGENTA);
	floodfill(540,20,0);
	floodfill(541,22,0);

}

/*////////////////////////////////////////////////////////////////////////////

	Function Name : GetKey();

	Description   : This function leads to the HandleMouseEvents() function
					and also handles the file menus, if they are selected by
					the mouse. And also it handles the keyboard, and returns
					the key which is pressed in the keyboard as ascii or scan.

////////////////////////////////////////////////////////////////////////////*/

int GetKey()
{
	union REGS  InReg , OutReg;

	int iascii,iscan;
	int iFileMenu;

	iFileMenu = HandleMouseEvents();

	switch(iFileMenu)
	{
		case NEW:
				 New();
				 return 0;
		case OPEN:
				  Open();
				  return 0;
		case SAVE:
				  Save();
				  return 0;
		case SAVEAS:
				  SaveAs();
				  return 0;
		case EXIT:
				  if(Exit() == 0)
					return -1;
				  else
					return 0;
	}

	InReg.h.ah = 8;
	int86(0x21, &InReg, &OutReg);

	iascii = OutReg.h.al;
	iscan = 0 ;

	if( !iascii)
	{
		int86(0x21, &InReg, &OutReg);
		iscan = OutReg.h.al;
	}
	if( iascii )
		return iascii;
	else
		return iscan;
}



