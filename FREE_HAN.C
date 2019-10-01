#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>

extern int button,x,y;
extern enum MenuType SelectedMenu;

void free_hand()
{
	int px=1,py=1,flag=0;
	int col,ch;

	while(1)
	{
		get_mouse_pos(&button,&x,&y);
		if(x>69 &&  x<569 && y>80 && y<464)
		{
			col = selected_color();
			setcolor(col);
			if(button==1)
			{
				if(flag==0)
				{
					flag=1;
				}
				else
					line(px,py,x,y);
			}
			else if(flag!=0)
				flag=0;
			px=x;
			py=y;
		}
		else
			break;
	}
}

int selected_color()
{
	int x = 0,y = 0,button;

	get_mouse_pos(&button,&x,&y);

	if(x>=419 && y>=4 && x<=433 && y<=18)
	{
		setcolor(LIGHTCYAN);
		rectangle(419,4,433,18);
		if(button == 1)
			return(0);
	}

	setcolor(WHITE);
	rectangle(419,4,433,18);

	if(x>=436 && y>=4 && x<=450 && y<=18)
	{
		setcolor(LIGHTCYAN);
		rectangle(436,4,450,18);
		SelectedMenu = BLACKCOLOR ;
		if(button==1)
			return(1);
	}

	setcolor(WHITE);
	rectangle(436,4,450,18);

	if(x>=453 && y>=4 && x<=467 && y<=18 && button==1)
//		SelectedMenu = BLUECOLOR ;
		return(2);

	if(x>=470 && y>=4 && x<=484 && y<=18 && button==1)
		return(3);

	if(x>=419 && y>=21 && x<=433 && y<=35 && button==1)
		return(4);

	if(x>=436 && y>=21 && x<=450 && y<=35 && button==1)
		return(5);

	if(x>=453 && y>=21 &&  x<=467 && y<=35 && button==1)
		return(6);

	if(x>=470 && y>=21 && x<=484 && y<=35 && button==1)
		return(7);

	if(x>=419 && y>=38 && x<=433 && y<=52 && button==1)
		return(8);

	if(x>=436 && y>=38 && x<=450 && y<=52 && button==1)
		return(9);

	if(x>=453 && y>=38 &&  x<=467 && y<=52 && button==1)
		return(10);

	if(x>=470 && y>=38 && x<=484 && y<=52 && button==1)
		return(11);

	if(x>=419 && y>=55 && x<=433 && y<=69 && button==1)
		return(12);

	if(x>=436 && y>=55 && x<=450 && y<=69 && button==1)
		return(13);

	if(x>=453 && y>=55 &&  x<=467 && y<=69 && button==1)
		return(14);
}
