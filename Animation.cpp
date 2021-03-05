#include<iostream>
#include<string>
#include<cmath>
#include<stdlib.h>
#include<unistd.h>
#include<windows.h>
#define MAX 40
#define g 9.8
#define h 1
using namespace std;

int counter=0;

float u=0,v,t,e;

void gotoxy(short x, short y)  //     x=col      y=row
{
	COORD pos ={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//Maintain function to maintain the line at the top.
void maintain_top(string s,int ind)
{
	gotoxy(0,0);
	cout<<"                    ";
	cout<<s.substr(0,ind);
}


//Maintain function to maintain the line at the bottom.
void maintain_bottom(string s,int ind)
{
	gotoxy(ind,MAX);
	cout<<"                    ";
	cout<<s.substr(ind,string::npos);
}

//To produce the downward animation.
void downward(string s,int drop_height,int ind)
{
	for(int i=drop_height;i<=MAX;i++)
	{
		//Finding the velocity after undergoing 1 m fall by the character
		//due to increase in velocity from u because of gravitational +ve accelerational g.
		v=sqrt(pow(u,2)+(2*g*h));

		//Finding the time taken to travel that 1 m after the which the velocity of the ball
		//will increase to v from u due to gravitational +ve accerleration g.
		t=(v-u)/g;

		system("cls");
		maintain_bottom(s,ind+1);
		maintain_top(s,ind);
		gotoxy(ind,i);
		cout<<"                    ";
		cout<<s[ind];

		//Changing the time form sec to microsecond, because usleep() fnc takes time in microsecond.
		usleep(t*pow(10,6));		//	Increase the value 67000, to make the downward animation faster.

		//For the next 1 m fall to calculate then v, the initial velocity would be the previous v, hence changing the value of u.
		u=v;
	}
}

//To produce the upward animation.
void upward(string s,int gain_height,int ind)
{
	//Due to inelastic collision, there will be energy loss, hence for the next maximum height it will reach will be less than intended.
	//e=v2/v1, where v2 is the velocity after collision and v1 is the velocity before collision.'
	//Hence, storing the inital velocity for the next upward motion in u.
	u=e*v;

	for(int i=MAX-1;i>=gain_height;i--)
	{
		//Finding the velocity after undergoing 1 m rise by the character
		//due to decrease in velocity from u because of gravitational -ve accelerational g.
		v=sqrt(pow(u,2)-(2*g*h));

		//Finding the time taken to travel that 1 m after the which the velocity of the ball
		//will decrease to v from u due to gravitational -ve accerleration g.
		t=(u-v)/g;
		system("cls");
		maintain_bottom(s,ind+1);
		maintain_top(s,ind);
		gotoxy(ind,i);
		cout<<"                    ";
		cout<<s[ind];

		//Changing the time form sec to microsecond, because usleep() fnc takes time in microsecond.
		usleep(t*pow(10,6));		//	Increase the value 68000, to make the upward animation faster.
		//For the next 1 m rise to calculate then v, the initial velocity would be the previous v, hence changing the value of u.
		u=v;
	}
}

//The bounce() fnc maintains the bounce animation of each character in the string.
void bounce(string s,int ind)
{


	//The array arr[] contains different co-effcient of restitution values of different materials.
	//arr[0] > arr[1] --->   higher energy loss in 2nd case, than 1st case, when collision with the base.
	//Don't make any value in the array >=1, because that will cause infinite loop,
	// since, then there will be either no energy loss or no gain in collision with the base
	//or there will be only energy gain in collision with the base.
	float arr[]={0.20,0.828,0.804,0.752,0.712,0.688,0.658,0.603,0.597};
	e=arr[counter%9];

	//e=sqrt(h1/h0), where, h1 will be the current height gain, h0 is the previous height gain.
	float high=pow(e,2)*MAX;

	while(high>1)
	{
		upward(s,MAX-ceil(high),ind);

		//Making the inital velocity before drop 0.
		u=0;

		downward(s,MAX-ceil(high),ind);

		//Changing the height gain after inelastic collision with the base.
		high=pow(e,2)*high;
	}

	counter++;
}

//Main function.
int main()
{
	string s;
	fflush(stdin);
	cout<<"                    ";

	//Taking the string from the user.
	getline(cin,s);

	for(int i=s.size()-1;i>=0;i--)
	{
		if(s[i]!=' ')
		{
			//Making inital speed 0, for the first drop of a character.
			u=0;

			//For initial fall.
			downward(s,1,i);

			//To maintain the bounce animation untill rest.
			bounce(s,i);
		}
	}
}
