#include<stdio.h>
#include<dos.h>

int Xpress,Ypress;
int Xrel,Yrel;
int BUT;
union REGS  InReg , OutReg;

void GetMouseButtonPressData()
{
	InReg.x.ax=5;
	InReg.x.bx=0;

	int86( 0x33 , &InReg , &OutReg );
	Xpress = OutReg.x.cx;
	Ypress = OutReg.x.dx;
	BUT = OutReg.x.ax;
	gotoxy(10,10);
	printf("%d,%d,%d",Xpress,Ypress,BUT);
}

void GetMouseButtonReleaseData()
{
	InReg.x.ax=6;
	InReg.x.bx=0;

	int86( 0x33 , &InReg , &OutReg );
	Xrel = OutReg.x.cx;
	Yrel = OutReg.x.dx;
	BUT = OutReg.x.ax;

	gotoxy(20,20);
	printf("%d,%d,%d", Xrel,Yrel,BUT);
}

void main()
{
	clrscr();

	InReg.x.ax=1;
	int86(0x33, &InReg, &OutReg);

	while(!kbhit())
	{
		InReg.x.ax=3;
		int86(0x33, &InReg, &OutReg);
		gotoxy(1,1);
		printf("(%d,%d)",OutReg.x.cx,OutReg.x.dx);

		GetMouseButtonPressData();

		GetMouseButtonReleaseData();

	}

	getch();
}


