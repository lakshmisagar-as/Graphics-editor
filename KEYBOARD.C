#include<stdio.h>
#include<conio.h>
#include<dos.h>

int ascii,scan;

/* function to take input from keyboard without echo */
int getkey()
{
	union REGS  InReg , OutReg;

	InReg.h.ah = 8;

	int86(0x21, &InReg, &OutReg);
	ascii = OutReg.h.al;
	scan = 0 ;

	if( !ascii)
	{
		int86(0x21, &InReg, &OutReg);
		scan = OutReg.h.al;
	}
	if( ascii )
		return ascii;
	else
		return scan;
}

void main()
{
	int key=0;
	char c;
	clrscr();
	key=getkey();
	if(ascii)
	{
		c=key;
		if(key==9)
			printf("tab\n");
		else if(key==8)
			printf("backspace\n");
		else if(key==13)
			printf("enter\n");
		else
			printf("%c %d\n",c,key);
	}
	else
	{
		switch(key)
		{
			case 59:
				printf("F1\n");
				break;
			case 60:printf("F2\n");
				break;
			case 61:printf("F3\n");
				break;
			case 62:printf("F4\n");
				break;
			case 63:printf("F5\n");
				break;
			case 64:printf("F6\n");
				break;
			case 65:printf("F7\n");
				break;
			case 66:printf("F8\n");
				break;
			case 67:printf("F9\n");
				break;
			case 68:printf("F10\n");
				break;
			case 133:printf("F11\n");
				break;
			case 134:printf("F12\n");
				break;
			case 84:printf("(shift+F1)\n");
				break;
			case 85:printf("(shift+F2)\n");
				break;
			case 86:printf("(shift+F3)\n");
				break;
			case 87:printf("(shift+F4)\n");
				break;
			case 88:printf("(shift+F5)\n");
				break;
			case 89:printf("(shift+F6)\n");
				break;
			case 90:printf("(shift+F7)\n");
				break;
			case 91:printf("(shift+F8)\n");
				break;
			case 92:printf("(shift+F9)\n");
				break;
			case 93:printf("(shift+F10)\n");
				break;
			case 135:printf("(shift+F11)\n");
				break;
			case 136:printf("(shift+F12)\n");
				break;
			case 95:printf("(ctrlF2)\n");
				break;
			case 96:printf("(ctrl+F3)\n");
				break;
			case 102:printf("(ctrl+F9)\n");
				break;
			case 104:printf("(alt+F1)\n");
				break;
			case 105:printf("(alt+F2)\n");
				break;
			case 106:printf("(alt+F3)\n");
				break;
			case 107:printf("(alt+F4)\n");
				break;
			case 108:printf("(alt+F5)\n");
				break;
			case 109:printf("(alt+F6)\n");
				break;
			case 110:printf("(alt+F7)\n");
				break;
			case 111:printf("(alt+F8)\n");
				break;
			case 112:printf("(alt+F9)\n");
				break;
			case 113:printf("(alt+F10)\n");
				break;
			case 139:printf("(alt+F11)\n");
				break;
			case 82:printf("insert\n");
				break;
			case 83:printf("delete\n");
				break;
			case 73:printf("page up\n");
				break;
			case 81:printf("page down\n");
				break;
			case 71:printf("home\n");
				break;
			case 79:printf("end\n");
				break;
			case 77:printf("right arrow\n");
				break;
			case 75:printf("left arrow\n");
				break;
			case 72:printf("up arrow\n");
				break;
			case 80:printf("down arrow\n");
				break;
		}
	}
	getch();
}
