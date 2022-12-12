#include <iostream>
#include <windows.h>
#include <conio.h>
#include <chrono>
#include <thread>

#define usleep(usec) std::this_thread::sleep_for(std::chrono::microseconds(usec))

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}



class snakeController
{
	public:
		int xPosition=25;
		int yPosition=12;
		int snakeLengt=1;
		int xyDirection=2; //1=up, -1=down, 2=rigth, -2=left
		int frameCounter=0;
		int cGetch;
		int boardTab[52][52]; //0=empty, 1=snake, 2=food, 3=border 
		bool isAlive=true;

		void snakeDirection()
		{
			switch(cGetch=_getch())
			{
				case 72: //up arrow key
					xyDirection=1;
					break;

				case 80: //down arrow key
					xyDirection=-1;
					break;

				case 77: //rigth arrow key
					xyDirection=2;
					break;

				case 75: //left arrow key
					xyDirection=-2;
					break;

				default:
					break;

			}

		}	

		void drawSnake(int x, int y)
		{
			gotoxy(xPosition, yPosition);
			std::cout<<'.';
			xPosition+=x;
			yPosition+=y;
			gotoxy(xPosition, yPosition);
			std::cout<<'%';
			
		}

		void snakeMovement()
		{
			if(!frameCounter)
			{

				switch(xyDirection)
				{
					case 1:
						drawSnake(0, -1);
						break;

					case -1:
						drawSnake(0, 1);
						break;

					case 2:
						drawSnake(2, 0);
						break;

					case -2:
						drawSnake(-2, 0);
						break;	

				}
			}
		}
};

void drawBoard()
{
	snakeController snakeObj;

	for(int i=0; i<52; i++)
		std::cout<<'~';
	std::cout<<std::endl;

	for(int i=0; i<25; i++)
	{
		std::cout<<'~';
		snakeObj.boardTab[i][0]=3;
		for(int j=0; j<25; j++)
		{
			std::cout<<'.'<<' ';
			snakeObj.boardTab[j*2+1][i*2+1]=0;
		}
		std::cout<<'~'<<std::endl;
	}	
		for(int i=0; i<52; i++)
		std::cout<<'~';
}


int main()
{
	snakeController snakeObj;
	drawBoard();

	while(snakeObj.isAlive)
	{
		if(snakeObj.frameCounter<3)
			snakeObj.frameCounter++;
		else
			snakeObj.frameCounter=0;

		if(kbhit())
			{
			snakeObj.cGetch=_getch();
			snakeObj.snakeDirection();
			}

		snakeObj.snakeMovement();

		usleep(1000*62);
	}
}
