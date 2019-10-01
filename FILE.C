#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include"numbers.h"

extern gi_Xposition,gi_Yposition,gi_BUTTON;
extern int gi_EDIT;
extern gi_PrevHighlighted;
static char Name[15] = {'\0'};
int gi_Empty = 0;
static int flag = 0;

/*////////////////////////////////////////////////////////////////////////////

	Function Name : save();

	Parameters    : x1,y1 - top left position of a area to save
					x2,y2 - bottom right position of a area
					str[15] - name of a file to save

	Descrpition   : This function saves the area which is specified by the
					co-ordinates as the name given as parameter

////////////////////////////////////////////////////////////////////////////*/

void save(int x1, int y1, int x2, int y2,char str[15])
{
	int i,j;
	int ch;
	FILE *fp;

	if( (fp = fopen(str,"wb")) == NULL)
	{
		return ;
	}

	for(i=x1;i<=x2;i++)
		for(j=y1;j<=y2;j++)
		{
			ch = getpixel(i,j);
			fputc(ch,fp);
		}
	fclose(fp);
}

/*////////////////////////////////////////////////////////////////////////////

	Function Name : restore();

	Parameters    : x1,y1 - top left position of a area to restore into paint area
					x2,y2 - right bottom position of a area
					str[15] - name of a file to restore

	Description   : This function restores the area of the file specified
					in the parameters to the paint area. It returns 1 on success
					 and 0 if restore is failed.

////////////////////////////////////////////////////////////////////////////*/

int restore(int x1, int y1, int x2, int y2,char str[15])
{
	char ch;
	int i,j;
	FILE *fp;

	if( (fp = fopen(str,"rb")) == NULL)
	{
		return 0;
	}

	for(i=x1;i<=x2;i++)
		for(j=y1;j<=y2;j++)
		{
			ch = fgetc(fp);
			if(ch != EOF)
				putpixel(i,j,ch);
		}
	fclose(fp);
	return 1;
}

void Window(char str[10])
{
	int i;

	HideMousePointer();

	save(199,159,439,319,"temp.pic");

	setfillstyle(SOLID_FILL,LIGHTRED);
	bar(200,160,438,318);
	setfillstyle(SOLID_FILL,WHITE);
	bar(210,175,428,310);

	setcolor(BLACK);
	outtextxy(300,165,str);

	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(263,270,313,287);
	setcolor(LIGHTGRAY);
	rectangle(261,268,315,289);
	setcolor(BLACK);
	outtextxy(270,275,"Enter");

	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(327,270,377,287);
	setcolor(LIGHTGRAY);
	rectangle(325,268,379,289);
	setcolor(BLACK);
	outtextxy(330,275,"Cancel");

	outtextxy(238,210,"Enter the File Name:");
	outtextxy(243,225,"(max 10 characters)");

	setfillstyle(SOLID_FILL,YELLOW);
	bar(245,242,390,258);

	outtextxy(350,247,".pic");

	ShowMousePointer();

	for(i=0;Name[i-1]!='\n';i++)
	{
		while(!kbhit())
		{
			GetMousePosition();

			if( (gi_Xposition >= ENTERX1 && gi_Xposition <= ENTERX2) && (gi_Yposition >= ENTERY1 && gi_Yposition <= ENTERY2) )
			{
				if(gi_PrevHighlighted != ENTER)
				{
					HighlightRect(gi_PrevHighlighted,LIGHTGRAY);
					HighlightRect(ENTER,LIGHTBLUE);
					gi_PrevHighlighted = ENTER;
				}
			}

			else if( (gi_Xposition >= CANCELX1 && gi_Xposition <= CANCELX2) && (gi_Yposition >= CANCELY1 && gi_Yposition <= CANCELY2) )
			{
				if(gi_PrevHighlighted != CANCEL)
				{
					HighlightRect(gi_PrevHighlighted,LIGHTGRAY);
					HighlightRect(CANCEL,LIGHTBLUE);
					gi_PrevHighlighted = CANCEL;
				}
			}

			else
			{
				HighlightRect(gi_PrevHighlighted,LIGHTGRAY);
				gi_PrevHighlighted = 35;
			}

			if(gi_BUTTON == 1)
			{
				if( (gi_Xposition >= ENTERX1 && gi_Xposition <= ENTERX2) && (gi_Yposition >= ENTERY1 && gi_Yposition <= ENTERY2) )
				{
					flag = 1;
					return;
				}
				else if( (gi_Xposition >= CANCELX1 && gi_Xposition <= CANCELX2) && (gi_Yposition >= CANCELY1 && gi_Yposition <= CANCELY2) )
				{
					flag = 2;
					goto down;
				}
			}
		}

		Name[i] = getch();

		if(Name[i] == 8)
		{
			setfillstyle(SOLID_FILL,YELLOW);
			bar(245,242,349,258);

			Name[i-1] = '\0';
			i = i-2;

			setcolor(BLACK);
			HideMousePointer();
			outtextxy(248,247,Name);
			ShowMousePointer();
		}

		else if(Name[i] == 13 || i>9)
		{
			Name[i] = '\0';
			flag = 1;
			break;
		}

		else if(Name[i] == 27)
		{
			flag = 2;
			break;
		}

		if( (Name[i] >= 65 && Name[i] <= 90) || (Name[i] >= 97 && Name[i] <= 122) || (Name[i] >= 48 && Name[i] <= 57) )
		{
			Name[i+1] = '\0';

			setcolor(BLACK);
			HideMousePointer();
			outtextxy(248,247,Name);
			ShowMousePointer();
		}

		else
		{
			Name[i] = '\0';
			i--;
		}
	}

	down:
		HideMousePointer();
		restore(199,159,439,319,"temp.pic");
}
/*////////////////////////////////////////////////////////////////////////////

	Function name : SaveAs();

	Description   : This function saves the paint area into the file and file
					name is given by user and file  name is limited to the
					10 characters of name and each file is end with .pic. Using
					this we can change name of a already saved file. This function
					opens a window in the center of the screen which asks users
					to enter the file name.If we press [Esc] key, the window
					closes and everything appears as left.

////////////////////////////////////////////////////////////////////////////*/

void SaveAs()
{
	int col;
	char Extn[5] = ".pic";

	col = getcolor();

	if(gi_Empty == 0)
		return;

	HighlightRect(SAVEAS,WHITE);
	gi_PrevHighlighted = 35;

	Window("Save As");

	strcat(Name,Extn);

	if(flag ==1)
	{
		if(restore(0,0,0,0,Name) == 0)
		{
			save(TOP,LEFT+80,BOTTOM,RIGHT-15,Name);
			flag = 3;
			gi_EDIT  = 0;
			setfillstyle(SOLID_FILL,LIGHTGRAY); // to erase the old position
			bar(250,463,500,476);
			setcolor(GREEN);
			outtextxy(255,465,"Successfully Saved");
		}

		else
		{
			HideMousePointer();

			setfillstyle(SOLID_FILL,LIGHTRED);
			bar(200,160,438,318);
			setfillstyle(SOLID_FILL,WHITE);
			bar(210,175,428,310);

			setcolor(BLACK);
			outtextxy(300,165,"Save As");

			setcolor(RED);
			outtextxy(247,215,"File already exists");
			outtextxy(225,240,"Do you want to overwrite?");

			setfillstyle(SOLID_FILL,LIGHTGRAY);
			bar(263,260,303,277);
			setcolor(LIGHTGRAY);
			rectangle(261,258,305,279);
			setcolor(BLACK);
			outtextxy(273,265,"YES");

			setfillstyle(SOLID_FILL,LIGHTGRAY);
			bar(327,260,367,277);
			setcolor(LIGHTGRAY);
			rectangle(325,258,369,279);
			setcolor(BLACK);
			outtextxy(340,265,"NO");

			ShowMousePointer();

			if(gi_BUTTON == 1)
			{
				GetMousePosition();
				while(gi_BUTTON == 1)
					GetMousePosition();
			}

			while(1)
			{
				GetMousePosition();

				if( (gi_Xposition >= YESX1 && gi_Xposition <= YESX2) && (gi_Yposition >= YESY1 && gi_Yposition <= YESY2) )
				{
					if(gi_PrevHighlighted != YES)
					{
						HighlightRect(gi_PrevHighlighted,LIGHTGRAY);
						HighlightRect(YES,LIGHTBLUE);
						gi_PrevHighlighted = YES;
					}
				}

				else if( (gi_Xposition >= NOX1 && gi_Xposition <= NOX2) && (gi_Yposition >= NOY1 && gi_Yposition <= NOY2) )
				{
					if(gi_PrevHighlighted != NO)
					{
						HighlightRect(gi_PrevHighlighted,LIGHTGRAY);
						HighlightRect(NO,LIGHTBLUE);
						gi_PrevHighlighted = NO;
					}
				}

				else
				{
					HighlightRect(gi_PrevHighlighted,LIGHTGRAY);
					gi_PrevHighlighted = 35;
				}

				if(gi_BUTTON == 1)
				{
					if( (gi_Xposition >= YESX1 && gi_Xposition <= YESX2) && (gi_Yposition >= YESY1 && gi_Yposition <= YESY2) )
					{
						save(TOP,LEFT+80,RIGHT,BOTTOM-15,Name);
						flag = 3;
						gi_EDIT = 0;

						setfillstyle(SOLID_FILL,LIGHTGRAY); // to erase the old position
						bar(250,463,500,476);
						setcolor(GREEN);
						outtextxy(255,465,"Successfully Saved");
						break;
					}

					else if( (gi_Xposition >= NOX1 && gi_Xposition <= NOX2) && (gi_Yposition >= NOY1 && gi_Yposition <= NOY2) )
					{
						flag = 2;
						break;
					}
				}
			}
		}

		HideMousePointer();
		restore(199,159,439,319,"temp.pic");
	}
	remove("temp.pic");

	ShowMousePointer();
	setcolor(col);
}

/*////////////////////////////////////////////////////////////////////////////

	Function Name : Open();

	Description   : This function opens the file using thwe file name which is
					given by the user. If the file doesnt exists, then it gives
					message as invalid file name. Else it opens the file and
					writes to the paint area. This function opens a window
					in the center of the screen which asks user to enter the
					file name. If we press [Esc] key, the window closes and
					everything appears as left.

////////////////////////////////////////////////////////////////////////////*/

void Open()
{
	int col;
	char Extn[5] = ".pic";

	col = getcolor();

	HighlightRect(OPEN,WHITE);
	gi_PrevHighlighted = 35;

	Window("Open");

	if(flag != 2)
	{
		strcat(Name,Extn);

		HideMousePointer();

		if(restore(TOP,LEFT+80,BOTTOM,RIGHT-15,Name) == 0)
		{
			setfillstyle(SOLID_FILL,LIGHTRED);
			bar(200,160,438,318);
			setfillstyle(SOLID_FILL,WHITE);
			bar(210,175,428,310);

			setcolor(BLACK);
			outtextxy(300,165,"OPEN");

			setcolor(RED);
			outtextxy(290,230,"ERROR!");
			outtextxy(250,240,"Invalid File Name!");
			outtextxy(215,300,"Press any key to continue...");

			getch();

			HideMousePointer();
			restore(199,159,439,319,"temp.pic");
		}
		gi_Empty = 1;
		flag = 3;
	}

	remove("temp.pic");

	ShowMousePointer();
	setcolor(col);
}

/*////////////////////////////////////////////////////////////////////////////

	Function Nmae : Save();

	Description   : This function saves the paint area into file, and the file
					name is given by the user. If the file is saved for the first
					time the window will appear which asks the to enter the file
					name. Afterwards each time it simply saves the changes to the
					opened file.

////////////////////////////////////////////////////////////////////////////*/

void Save()
{
	static int FrstSave = 1;

	HighlightRect(SAVE,WHITE);
	gi_PrevHighlighted = 35;

	if(gi_Empty == 1)
	{
		if(FrstSave == 1)
		{
			SaveAs();
			if(flag != 2)
			{
				FrstSave = 0;
				gi_EDIT = 0;
				setfillstyle(SOLID_FILL,LIGHTGRAY); // to erase the old position
				bar(250,463,500,476);
				setcolor(GREEN);
				outtextxy(255,465,"Successfully Saved");
			}
		}

		else
		{
			save(TOP,LEFT+80,BOTTOM,RIGHT-15,Name);
			HighlightRect(SAVE,WHITE);
			gi_EDIT = 0;
			flag = 3;
			setfillstyle(SOLID_FILL,LIGHTGRAY); // to erase the old position
			bar(250,463,500,476);
			setcolor(GREEN);
			outtextxy(255,465,"Successfully Saved");
		}
	}
}

void Window1(char str[10])
{
	HideMousePointer();

	save(199,159,439,319,"temp.pic");

	setfillstyle(SOLID_FILL,LIGHTRED);
	bar(200,160,438,318);
	setfillstyle(SOLID_FILL,WHITE);
	bar(210,175,428,310);

	setcolor(BLACK);
	outtextxy(300,165,str);

	setcolor(BLUE);
	outtextxy(240,215,"Do you want to save");
	outtextxy(278,230,"changes?");

	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(263,260,303,277);
	setcolor(LIGHTGRAY);
	rectangle(261,258,305,279);
	setcolor(BLACK);
	outtextxy(273,265,"YES");

	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(327,260,367,277);
	setcolor(LIGHTGRAY);
	rectangle(325,258,369,279);
	setcolor(BLACK);
	outtextxy(340,265,"NO");

	setfillstyle(SOLID_FILL,LIGHTGRAY);
	bar(288,285,342,303);
	setcolor(LIGHTGRAY);
	rectangle(286,283,344,305);
	setcolor(BLACK);
	outtextxy(292,290,"Cancel");

	ShowMousePointer();

	while(1)
	{
		GetMousePosition();

		if( (gi_Xposition >= YESX1 && gi_Xposition <= YESX2) && (gi_Yposition >= YESY1 && gi_Yposition <= YESY2) )
		{
			if(gi_PrevHighlighted != YES)
			{
				HighlightRect(gi_PrevHighlighted,LIGHTGRAY);
				HighlightRect(YES,LIGHTBLUE);
				gi_PrevHighlighted = YES;
			}
		}

		else if( (gi_Xposition >= NOX1 && gi_Xposition <= NOX2) && (gi_Yposition >= NOY1 && gi_Yposition <= NOY2) )
		{
			if(gi_PrevHighlighted != NO)
			{
				HighlightRect(gi_PrevHighlighted,LIGHTGRAY);
				HighlightRect(NO,LIGHTBLUE);
				gi_PrevHighlighted = NO;
			}
		}

		else if( (gi_Xposition >= CANX1 && gi_Xposition <= CANX2) && (gi_Yposition >= CANY1 && gi_Yposition <= CANY2) )
		{
			if(gi_PrevHighlighted != CAN)
			{
				HighlightRect(gi_PrevHighlighted,LIGHTGRAY);
				HighlightRect(CAN,LIGHTBLUE);
				gi_PrevHighlighted = CAN;
			}
		}

		else
		{
			HighlightRect(gi_PrevHighlighted,LIGHTGRAY);
			gi_PrevHighlighted = 35;
		}

		if(gi_BUTTON == 1)
		{
			if( (gi_Xposition >= YESX1 && gi_Xposition <= YESX2) && (gi_Yposition >= YESY1 && gi_Yposition <= YESY2) )
			{
				Save();
				flag = 3;
				gi_EDIT = 0;
				break;
			}

			else if( (gi_Xposition >= NOX1 && gi_Xposition <= NOX2) && (gi_Yposition >= NOY1 && gi_Yposition <= NOY2) )
			{
				flag = 3;
				gi_EDIT = 0;
				break;
			}

			else if( (gi_Xposition >= CANX1 && gi_Xposition <= CANX2) && (gi_Yposition >= CANY1 && gi_Yposition <= CANY2) )
			{
				HideMousePointer();
				restore(199,159,439,319,"temp.pic");
				break;
			}
		}
	}
	remove("temp.pic");
}
/*////////////////////////////////////////////////////////////////////////////

	Function Name : New();

	Description   : This function opens the new paint area i.e., which appears
					as when we open the paint for first time. But if we try to
					open a new file without saving the changes made with earlier
					file then a window will appear in the screen which asks
					users that if they want to earlier things or not.If we press
					Y/y the things are saved, else the they are disgarded. If
					we press [Esc] key, the window closes and everything appears
					as left.

////////////////////////////////////////////////////////////////////////////*/

void New()
{
	int col;

	col = getcolor();

	HighlightRect(NEW,WHITE);
	gi_PrevHighlighted = 35;

	if(gi_EDIT == 1)
	{
		HighlightRect(NEW,WHITE);
		gi_PrevHighlighted = 35;
		Window1("New");
	}

	if(flag == 3)
	{
		HideMousePointer();
		setfillstyle(SOLID_FILL,WHITE);
		bar(TOP,LEFT+80,BOTTOM,RIGHT-15);
		gi_Empty = 0;
	}

	ShowMousePointer();
	setcolor(col);
}

/*////////////////////////////////////////////////////////////////////////////

	Function Name : Exit();

	Description   : This function exits from program i.e., closes the paint.
					If the changes made or not saved, then a window will open
					on the screen which asks weather users wants to save or not.
					If we press Y/y the things are saved, else if press N/n
					the earlier things are disgarded. If we press [Esc] key,
					the window closes and everything appears as left.

////////////////////////////////////////////////////////////////////////////*/

int Exit()
{
	int col;

	col = getcolor();

	HighlightRect(EXIT,WHITE);
	gi_PrevHighlighted = 35;

	if(gi_EDIT == 1)
		Window1("Exit");

	if(flag == 3 || gi_EDIT == 0)
	{
		if(gi_BUTTON == 1)
		{
			GetMousePosition();
			while(gi_BUTTON == 1)
				GetMousePosition();
		}

		closegraph();
		return 0;
	}
	setcolor(col);

	return 1;
}