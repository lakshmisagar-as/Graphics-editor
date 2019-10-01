#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<math.h>
#include<graphics.h>
#include"numbers.h"
#define DRAW 1
#define NOTDRAW 0

extern int gi_Xposition,gi_Yposition,gi_BUTTON;
extern int gi_SelectedDrawStyle;
extern int gi_SelectedColor;
extern int gi_THICKNESS;
extern int gi_Empty;
int gi_EDIT = 0;
static int gi_PrevX = 0, gi_PrevY = 0;

struct node
{
	int x;
	int y;
	int col;
	int status;
	struct node *next;
};

typedef struct node *nodeptr;
struct node *Start = NULL;

void Insert(int x,int y)
{
	int col;
	nodeptr Newnode,temp;

	col = getpixel(x,y);

/*	if(Start == NULL)
	{
		Newnode = (nodeptr)malloc(sizeof(struct node));

		if(Newnode == NULL)
			return;

		Newnode->x = x;
		Newnode->y = y;
		Newnode->col = col;
		Newnode->status = 1;

		Newnode->next = NULL;
		Start = Newnode;
	}

	else
	{   */
		for(temp = Start;temp != NULL && temp->status != 0;temp = temp->next);

		if(temp == NULL)
		{
			Newnode = (nodeptr)malloc(sizeof(struct node));

			if(Newnode == NULL)
				return;

			Newnode->x = x;
			Newnode->y = y;
			Newnode->col = col;
			Newnode->status = 1;

			if(Start == NULL)
				Newnode->next = NULL;
			else
				Newnode->next = Start;

			Start = Newnode;
		}

		else
		{
			temp->x = x;
			temp->y = y;
			temp->col = col;
			temp->status = 1;
		}
//	}
}

void Restore(int flag)
{
	nodeptr Node;

	if(Start == NULL)
		return;

//	if(flag == DRAW)
//		HideMousePointer();

		for(Node=Start;Node!=NULL;Node = Node->next)
		{
			if(flag == DRAW)
			{
				putpixel(Node->x,Node->y,Node->col);
				Node->status = 0;
			}

//			Start = Node->next;
			if(flag == NOTDRAW)
				free(Node);
		}

		if(flag == NOTDRAW)
			Start = NULL;
//	if(flag == DRAW)
//		ShowMousePointer();
}

void FreeHand()
{
	int i,j;
	int temp_x2,temp_y2;

	GetMousePosition(&gi_Xposition,&gi_Yposition,&gi_BUTTON);

	if( gi_Yposition > (LEFT+2) && gi_PrevY > (LEFT+2) && gi_Yposition < (RIGHT-2) && gi_PrevY < (RIGHT-2) )
	{
		if( gi_Xposition > (TOP+2) && gi_Xposition < (BOTTOM-2) )
		{
			if(gi_PrevX == gi_Xposition && gi_PrevY == gi_Yposition)
				return;

			for(i=1;i<(gi_THICKNESS+1);i++)
			{
				line(gi_PrevX-i,gi_PrevY+i,gi_Xposition-i,gi_Yposition+i);
			}

			gi_EDIT = 1;
			gi_Empty = 1;
		}
	 }

	 gi_PrevX = gi_Xposition;
	 gi_PrevY = gi_Yposition;
}

void Eraser()
{

}

void Exchange(int *t1, int *t2)
{
	int temp;

	temp=*t1;
	*t1=*t2;
	*t2=temp;
}

int Sign(int m)
{
	if(m<0)
		return -1;
	else if(m>0)
		return 1;
	else
		return 0;
}

void put_pixel(int x, int y, int color )
{
	if(x > TOP && x < BOTTOM && y > LEFT+81 && y < RIGHT-17)
	{
		Insert(x,y);
		putpixel(x,y,color);
	}
}

void LineDraw(int x1,int y1,int x2,int y2 ,int color)
{
	int Temp_X,Temp_Y,deltaX,deltaY;
	int Inc_or_Dec_x,Inc_or_Dec_y;
	int i,delta,temp,ExchangeFlag = 0;

	Temp_X = x1;
	Temp_Y = y1;

	deltaX = abs(x1 - x2);
	deltaY = abs(y1 - y2);

	Inc_or_Dec_x = Sign(x2 - x1);
	Inc_or_Dec_y = Sign(y2 - y1);

	if(deltaY > deltaX)
	{
		Exchange( &deltaX , &deltaY );
		ExchangeFlag = 1;
	}

	delta = 2*deltaY - deltaX;

	for(i = 0;i <= deltaX;i++)
	{
		put_pixel(Temp_X,Temp_Y,color);

		if(ExchangeFlag == 1)
			Temp_Y = Temp_Y + Inc_or_Dec_y;
		else
			Temp_X = Temp_X + Inc_or_Dec_x;

		if(delta >= 0)
		{
			if(ExchangeFlag == 1)
				Temp_X = Temp_X + Inc_or_Dec_x;
			else
				Temp_Y = Temp_Y + Inc_or_Dec_y;

			delta = delta - 2*deltaX;
		}

		delta = delta + 2*deltaY;

	}
}

void RectDraw(int left,int top,int right,int bottom)
{
	int i;

	for( i=0;i<gi_THICKNESS;i++)
	{
		LineDraw( left-i ,bottom+i ,right+i ,bottom+i ,gi_SelectedColor );
		LineDraw( right+i ,bottom+i ,right+i ,top-i ,gi_SelectedColor);
		LineDraw( right+i ,top-i ,left-i ,top-i ,gi_SelectedColor);
		LineDraw( left-i ,bottom+i ,left-i ,top-i ,gi_SelectedColor );
	}

}

void PlotPoints(int xc,int yc,int x,int y,int Color )
{


	put_pixel( xc + x , yc + y , Color );
	put_pixel( xc + x , yc - y , Color );
	put_pixel( xc - x , yc + y , Color );
	put_pixel( xc - x , yc - y , Color );
	put_pixel( xc + y , yc + x , Color );
	put_pixel( xc + y , yc - x , Color );
	put_pixel( xc - y , yc + x , Color );
	put_pixel( xc - y , yc - x , Color );

}

void CircDraw(int x_cord , int y_cord , double radius,int Color)
{
	double x,y,delta;
	int deltaE = 3;
	int deltaSE = -2 * radius + 5;

	x = 0;
	y = radius;
	delta = 1 - radius;

	PlotPoints( x_cord , y_cord , x , y , Color );

	while( y > x )
	{
		if(delta < 0)
		{
			delta = delta + deltaE;
			deltaE = deltaE + 2;
			deltaSE = deltaSE + 2;
		}

		else
		{
			delta = delta + deltaSE;
			deltaE = deltaE + 2;
			deltaSE = deltaSE + 4;
			y--;
		}

		x++;
		PlotPoints(x_cord,y_cord,x,y,Color);
	}
}

int CalculateRadius(int x1,int y1,int x2,int y2)
{
	double temp,radius;

	temp = pow((x1 - x2),2) + pow((y1 - y2),2);
	radius = sqrt(temp);

	return(radius);

}


void TriDraw()
{

}

void RtriDraw()
{

}

void DiaDraw()
{

}

void DrawShapes()
{
	static int PrevX = 0, PrevY = 0;
	static double PrevRadius = 0;
	int flag = 1;
	int i;
	double Radius = 0;
	static int preX = 0, preY = 0;

	setcolor(gi_SelectedColor);

	gi_PrevX = gi_Xposition;
	gi_PrevY = gi_Yposition;

	Restore(NOTDRAW);

	while(gi_BUTTON == 1)
	{
		GetMousePosition(&gi_Xposition,&gi_Yposition,&gi_BUTTON);

		if(preX == gi_Xposition && preY == gi_Yposition)
			continue;

		HideMousePointer();

		ShowMousePixels();

		Restore(DRAW);

		switch(gi_SelectedDrawStyle)
		{
			case FREEHAND :
					FreeHand();
					break;

			case ERASER :
					Eraser();
					break;

			case LINEDRAW :
					if( gi_Yposition > (LEFT+2) && gi_Yposition < (RIGHT-2)  )
					{
						for(i=1;i<=gi_THICKNESS;i++)
						{
							LineDraw(gi_PrevX-i,gi_PrevY+i,gi_Xposition-i,gi_Yposition+i,gi_SelectedColor);

						}
					}

					gi_EDIT = 1;
					break;

			case RECTDRAW :
					RectDraw(gi_PrevX,gi_PrevY,gi_Xposition,gi_Yposition);
					gi_EDIT = 1;
					break;

			case CIRCDRAW :
					Radius = CalculateRadius(gi_PrevX,gi_PrevY,gi_Xposition,gi_Yposition);

					if(PrevRadius == Radius)
						break;

					if(flag == 0)
					{
						if(PrevX != gi_Xposition || PrevY != gi_Yposition)
							CircDraw(PrevX,PrevY,PrevRadius,WHITE);
					}

					CircDraw(gi_Xposition,gi_Yposition,Radius,gi_SelectedColor);

					PrevX = gi_Xposition;
					PrevY = gi_Yposition;
					PrevRadius = Radius;
					flag = 0;

					gi_EDIT = 1;
					break;

			case TRIDRAW  :
						TriDraw();
						break;
			case RTRIDRAW :
						RtriDraw();
						break;
			case DIADRAW  :
						DiaDraw();
						break;
			default		  :
						FreeHand();
						break;
		}

		ShowMousePointer();

		preX = gi_Xposition;
		preY = gi_Yposition;
	}
}

