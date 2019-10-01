#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include"numbers.h"

int gi_Xposition = 0,gi_Yposition = 0,gi_BUTTON = 0;

/*///////////////////////////////////////////////////////////////////////////

	Function name : initializegraph()

	Description   : This function initialises the graph mode
					and also clears the device
	Output 		  : returns  on success
					else prints error message and exits from the program

///////////////////////////////////////////////////////////////////////////*/

int Initialize()
{
	int gdriver=DETECT,gmode;
	int errorcode;;
	initgraph(&gdriver,&gmode,"c://tc//bgi");

	errorcode = graphresult();

	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		return 1;		  /* return with error code */
	}

	cleardevice();

	if(InitMouse() == 0)
	{
		closegraph();
		printf("\nMouse driver is not present");
		getch();
		return 1;
	}
	return 0;
}

void main()
{
	int iKey = 0;

	if(Initialize() != 0)
		exit(0);

	InitMenu();

	RestrictMousePointer(TOP,LEFT,BOTTOM,RIGHT);

	while(1)
	{
		fflush(0);

		iKey = GetKey();

		switch(iKey)   // #define the numbers
		{
			case 14:               //Ctrl-N
					New();
					break;
			case 15:
					Open();       //Ctrl-O
					break;
			case 19:
					Save();       //Ctrl-S
					break;
			case 45:              //Alt-S
					if(Exit() == 0)
						continue;
					break;
			default:
					break;
		}

		if(iKey == EXIT)
		{
			if(Exit() == 0)
				break;
		}

		if(iKey == -1)
			break;
	}
}
