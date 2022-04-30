#include<iostream>
#include<windows.h>
#include<conio.h>
#include <bits/stdc++.h>
//height and width  of the game
int height=25;
int width=100;
clock_t start, ending;
// declare variables
int gameover=0,counter,gameover2=0,choice,counter2;
int lflag=0,rflag=0,uflag=0,dflag=0;
int lflag2=0,rflag2=0,uflag2=0,dflag2=0;
short fcount;

using namespace std;
class Snake
{

	int x,y,x2,y2; //declare the positions of the snakes
	int fx,fy;    //declare the position of the fruit
	char playername[50],playername2[50]; //declare name of the players

	struct node  //declare a struct node with prev and next for doubly linked list
	{
		int nx,ny;
		struct node *next;
		struct node *prev;
	};

	struct node *head=NULL; //declare head of doubly linked list of snake 1
	struct node *tail=NULL;
	struct node *head2=NULL; //declare head of doubly linked list of snake 2
	struct node *tail2=NULL;

	void gotoxy(int x,int y) // function to go to position x and y in the screen
	// the center is in the top left of the screen
	{
		COORD pos={x,y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
	}

	void nameandscore() //function to write the score of the players
	{
		gotoxy(101,0); // go to the top right of the screen
		textcolour(10);
		cout<<"     Scoreboard";
		textcolour(6);
		gotoxy(101,2);
		cout<<playername<<"'s SCORE = "<<counter*100; //write the score of player 1 (counter is number of fruits he ate)
		if(choice==2)
		{
			gotoxy(101,4);
			cout<<playername2<<"'s SCORE = "<<counter2*100;
			gotoxy(101,6);
			cout<<"Remained Fruit :";  // print remained fruits in the multiplayer mode
			gotoxy(117,6);
			cout<<"  ";
			gotoxy(117,6);
			cout<<fcount;
		}
	}



	void textcolour(int k) //determine the color of text
	{
		HANDLE hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole,k);
	}

	public:

	void window() //make the frame of the game
	{
		if(choice==1)
		textcolour(4);
		else
		textcolour(1);
			for(int i=0;i<=width;i++)
		{
			gotoxy(i,0);
			cout<<"Û";
			gotoxy(i,height);
			cout<<"Û";
		}

		for(int i=0;i<=height;i++)
		{
			gotoxy(0,i);
			cout<<"Û";
			gotoxy(width,i);
			cout<<"Û";
		}
	}


	void setup() //initialize the game before it starts
	{
		counter=0; //number of fruits player 1 ate
		gameover=0; //flag to know if player 1 has lost
		window(); //add the frame
		resetflag(); //set all direction flag to zero
		nameandscore(); //print the scoreboard
		// add snake 1 in the middle of the screen
		head=new node;
		tail = head;
		head->nx=width/2;
		head->ny=height/2;
		head->next=NULL;
		head->prev=NULL;
		//adjust position of snake 1 to the middle of the screen
		x=width/2;
		y=height/2;
		//add the fruit in a random place on the screen and avoid adding it on the borders
		label1:
		fx=rand()%width;
		if(fx==0||fx==width)
		goto label1;
		label2:
		fy=rand()%height;
		if(fy==0||fy==height)
		goto label2;
	}

	void setup2()
	{
		resetflag2();
		gameover2=0;
		counter2=0;
		fcount=25; //number of fruits
		 // add snake 2 next to the first snake
		head2=new node;
		tail2 = head2;
		head2->nx=width/2+5;
		head2->ny=height/2+5;
		head2->next=NULL;
		head2->prev=NULL;
		x2=width/2+5;
		y2=height/2+5;

	}

	void drawlist(struct node *h,int k) //draw the snake on the screen
	{
		textcolour(k);
		struct node *ptr;
		ptr=h;
		while(ptr!=NULL)
		{
			gotoxy(ptr->nx,ptr->ny);
			cout<<"Û";
			ptr=ptr->next;
		}
	}


	void destroylist(struct node *h) //remove the snake from the screen
	{
		struct node *ptr;
		ptr=h;
		while(ptr!=NULL)
		{
			gotoxy(ptr->nx,ptr->ny);
			cout<<" ";
			ptr=ptr->next;
		}
	}



	void draw() //control the drawing of the snakes and food on the screen
	{

		drawlist(head,2);
		drawlist(head2,5);
		gotoxy(fx,fy);
		textcolour(4);
		cout<<"@";
		Sleep(70);
		destroylist(head);
		destroylist(head2);
	}

	void resetflag() //reset direction flags of snake 1
	{
		uflag=0;
		dflag=0;
		lflag=0;
		rflag=0;
	}

		void resetflag2()  //reset direction flags of snake 2
	{
		uflag2=0;
		dflag2=0;
		lflag2=0;
		rflag2=0;
	}

	void play() //get the direction of next move from keyboard
	{
		int h;
		char ch;
		if(kbhit()) //check if any key is pressed
		{

			ch=getch(); //get the ASCII code of the pressed button
			h=ch;
			//check the button pressed and set its direction flag to 1
			switch(h)
			{
				case 72:if(dflag!=1){resetflag();uflag=1;}
				break;
				case 80:if(uflag!=1){resetflag();dflag=1;}
				break;
				case 75:if(rflag!=1){resetflag();lflag=1;}
				break;
				case 77:if(lflag!=1){resetflag();rflag=1;}
				break;

				case 119:if(dflag2!=1){resetflag2();uflag2=1;}
				break;
				case 115:if(uflag2!=1){resetflag2();dflag2=1;}
				break;
				case 97:if(rflag2!=1){resetflag2();lflag2=1;}
				break;
				case 100:if(lflag2!=1){resetflag2();rflag2=1;}
				break;

				default:break;
			}
		}
	}

	void box(int m1,int n1,int m2,int n2) //draw a box for the welcome screen
	{
			for(int i=m1;i<=m2;i++)
		{
			gotoxy(i,n1);
			cout<<"//";
			gotoxy(i,n2);
			cout<<"//";
		}

		for(int i=n1;i<=n2;i++)
		{
			gotoxy(m1,i);
			cout<<"//";
			gotoxy(m2,i);
			cout<<"//";
		}
	}

	void welcome() //draw the welcome screen
	{
		textcolour(5);
		box(width/2-width/4,height/2-height/4,width/2+width/4,height/2+height/4);
		textcolour(10);
		gotoxy(width/2-13,height/2-8);
		cout<<"*** WELCOME TO SNAKE GAME *** ";
		textcolour(9);
		gotoxy(width/2-16,height/2-3);
		cout<<"Press 1 For Single player \n";
		gotoxy(width/2-16,height/2-1);
		cout<<"Press 2 For Multiplayer \n";
		gotoxy(width/2-16,height/2);
		cin>>choice; //get the mode of the game (Multi or Single)
		system("cls");
	}



	void welcome1() //draw the welcome screen for the Single player mode
	{
		textcolour(5);
		box(width/2-width/4,height/2-height/4,width/2+width/4,height/2+height/4);
		textcolour(6);
		gotoxy(width/2-18,height/2-3);
		cout<<"WELCOME TO SNAKE GAME SINGLE PLAYER MODE ";
		textcolour(8);
		gotoxy(width/2-13,height/2);
		cout<<"Enter Your Name : ";
		cin>>playername; //get player 1 name
		system("cls");
	}

	void welcome2()   //draw the welcome screen for the Multiplayer mode
	{
		textcolour(5);
		box(width/2-width/4,height/2-height/4,width/2+width/4,height/2+height/4);
		textcolour(6);
		gotoxy(width/2-18,height/2-3);
		cout<<"WELCOME TO SNAKE GAME MULTIPLAYER MODE ";
		textcolour(8);
		gotoxy(width/2-13,height/2);
		cout<<"Enter Player1 Name : ";
		gotoxy(width/2-13,height/2+2);
		cout<<"Enter Player2 Name : ";
		gotoxy(width/2+7,height/2);
		cin>>playername; //get player 1 name
		gotoxy(width/2+7,height/2+2);
		cin>>playername2; //get player 2 name
		system("cls");
	}




		char end() //check who won and draw the end screen
	{
		char c;
		gotoxy(width/2-5,height/2-4);
		cout<<"GAME OVER \n";
		textcolour(5);
		box(width/2-width/4,height/2-height/4,width/2+width/4,height/2+height/4);

		textcolour(1);
		gotoxy(width/2-15,height/2-2);
		cout<<playername<<" You Scored : "<<counter*100; //print score of player 1
		if(choice==2)
		{
			gotoxy(width/2-15,height/2);
			cout<<playername2<<" You Scored : "<<counter2*100; //print score of player 2
			textcolour(4);
			if(gameover!=0) //check if player 1 lost
			{
				gotoxy(width/2-15,height/2+2);
				cout<<playername<<" has lost !";
			}
			else
			{
				gotoxy(width/2-15,height/2+2);
				cout<<playername2 <<" has lost !";
			}
			if(fcount==0) //check if there is no fruits left
			{
				textcolour(4);
				gotoxy(width/2-15,height/2+2);
				if(counter>counter2) //check if player 1 ate more than player 2
				{
					cout<<playername<<" has WON !";
				}
				else
				{
					cout<<playername2<<" has WON !";
				}
			}
		}
		textcolour(6);
		gotoxy(width/2-15,height/2+4);
		cout<<"Want To Play Again ? (Y/N) : ";
		cin>>c; //get the answer of the user(Yes or No) to return it
		system("cls");
		return c;

	}



	void run() //change the position of the head depending on direction flag
	{
		if(uflag==1) //if the up direction flag is 1 we will decrement y of snake 1
		y--;
		else if(dflag==1) //if the down direction flag is 1 we will increment y of snake 1
		y++;
		else if(lflag==1) //if the left direction flag is 1 we will decrement x of snake 1
		x--;
		else if(rflag==1) //if the right direction flag is 1 we will increment x of snake 1
		x++;


			if(uflag2==1) //if the up direction flag is 1 we will decrement y of snake 2
		y2--;
		else if(dflag2==1) //if the down direction flag is 1 we will increment y of snake 2
		y2++;
		else if(lflag2==1) //if the left direction flag is 1 we will decrement x of snake 2
		x2--;
		else if(rflag2==1) //if the right direction flag is 1 we will increment x of snake 2
		x2++;

	}

	void dolist(struct node *h,struct node* t,int pp,int qq) //change the position of the snakes
	{
		struct node *ptr,*prev;
        ptr =t;
        prev = t->prev;
        if(t->prev==NULL) {
        prev = h;}
		while(prev!=h)
		{
			ptr->nx=prev->nx;
			ptr->ny=prev->ny;
			prev=prev->prev;
			ptr=ptr->prev;
		}
		ptr->nx=prev->nx;
		ptr->ny=prev->ny;
		prev->nx=pp;
		prev->ny=qq;
	}




	void drawagain() // draw snake 1 in the other side of the screen when it hits the borders in multiplayer mode
	{
		if(x==width)
		{
			x=1;
		}
		if(x==0)
		{
			x=width-1;
		}
		if(y==0)
		{
			y=height-1;
		}
		if(y==height)
		{
			y=1;
		}
	}


	void drawagain2() // draw snake 2 in the other side of the screen when it hits the borders in multiplayer mode
	{
		if(x2==width)
		{
			x2=1;
		}
		if(x2==0)
		{
			x2=width-1;
		}
		if(y2==0)
		{
			y2=height-1;
		}
		if(y2==height)
		{
			y2=1;
		}
	}

	void generatefruit() // add the fruit in a random position
	{
			label1:
			fx=rand()%width;
			if(fx==0||fx==width)
			goto label1;
			label2:
			fy=rand()%height;
			if(fy==0||fy==height)
			goto label2;
	}

	void checkfcount() // check if there is no fruits left
	{
		if(fcount==0)
		{
			gameover=1;
			gameover2=1;
		}
	}

	void checkup() // set the rules to end the game for snake 1
	{
		if(choice==1) // check if the snake hits the borders in single player mode
		{
			if(x==width||x==0)
			gameover=1;
			if(y==height||y==0)
			gameover=1;
		}
		drawagain(); // multiplayer mode

        // check if the snake 1 hits itself
		struct node *h;
		h=head->next;
		while(h!=NULL)
		{
			if(x==h->nx&&y==h->ny)
			{
				gameover=1;
				break;
			}
			h=h->next;
		}

		if(x==fx&&y==fy) // check if snake 1 ate the fruit
		{
			if(choice==2)
			{
				fcount--; // decrement the number of fruits in multiplayer mode
				checkfcount();
			}

			// make a new node to increment the length of the snake after eating a fruit
			struct node *t,*ptr,*prev;
			t=new node;
			t->next=NULL;
			t->prev=NULL;
				ptr=tail;
				ptr->next=t;
				t->prev=ptr;
				tail=ptr->next;
				generatefruit();
			counter++; // increment the number of fruits the snake 1 ate
			nameandscore(); // change the scoreboard
		}
			dolist(head,tail,x,y);
		}


		void checkup2() // set the rules to end the game for snake 2
	{
		drawagain2();

		// check if the snake 2 hits itself
		struct node *h;
		h=head2->next;
		while(h!=NULL)
		{
			if(x2==h->nx&&y2==h->ny)
			{
				gameover2=1;
				break;
			}
			h=h->next;
		}

		// check if snake 2 ate the fruit
		if(x2==fx&&y2==fy)
		{
			fcount--;
			checkfcount();
			struct node *t,*ptr;
			t=new node;
			t->next=NULL;
			t->prev=NULL;
				ptr=tail2;
				ptr->next=t;
				t->prev=ptr;
				tail2 = t;
				generatefruit();
				counter2++; // increment the number of fruits the snake 2 ate
				nameandscore(); // change the scoreboard
		}
			dolist(head2,tail2,x2,y2);
		}


	void game1() // start the game in single player mode
	{

	    int i=0;
		char ch;
		welcome1();
		do{
            start = clock();
			setup();
			window();
			while(!gameover)
			{
				draw();
				play();
				run();
				checkup();

				if(i==0)
                {
                  ending = clock();
                  i++;

                }
			}
			ch=end();
			}while(ch=='y'||ch=='Y'); // check if the player wants to play again
    double time_taken = double(ending - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}

	void game2() // start the game in multiplayer mode
	{
	    int i=0;
		char ch;
		welcome2();
		do{
            start = clock();
			setup2();
			setup();
			window();
		while(gameover!=1&&gameover2!=1)
			{
				draw();
				play();
				run();
				checkup();
				checkup2();
				if(i==0)
                {
                  ending = clock();
                  i++;
                }
			}ch=end();
		}while(ch=='y'||ch=='Y'); // check if the player wants to play again
		    double time_taken = double(ending - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
	}
};
int main()
{


	Snake s;
	s.welcome();
	if(choice==1) // single player mode
	{
		s.game1();
	}
	if(choice==2) // multiplayer mode
	{
		s.game2();
	}
	system("exit");
}
