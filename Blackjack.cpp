//Document name: Blackjack.cpp
//This is a game nemed Blackjack.
//author:huangyaowei
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

bool IfContinue();											//To ask player if he wants to continue to play game .
bool IfHit();												//To ask player if he wants to get another card.
void shuffle();                                             //To shuffle the card at the beginning.
double SendCard()	;										//To send a card to player or computer by random . 
double PlayerStage()	;									//It's the player's stage to get the card.
bool ComputerStage(double playercount);						//It's the computer's stage to get the card.

double card[4][13];                                         //card[][] is array store the card's information.									

int main()													
{
	srand(time(NULL));
	shuffle();
	double playercount;
	playercount=PlayerStage();
	if(playercount>0)										//To do the game at the first time.
	{
		if(ComputerStage(playercount))
		{
			if(playercount==21)
			{
				cout<<"level the score "<<endl;
			}
			else cout<<"Computer wins \n"<<endl;
		}
		else  cout<<"Player wins \n"<<endl;
	}
	else  cout<<"Computer wins \n"<<endl;
	while(IfContinue())										//Ask if to continue the game.
	{
		shuffle();
		double playercount;
		playercount=PlayerStage();
		if(playercount>0)
		{
			if(ComputerStage(playercount))
			{
				if(playercount==21)
				{
					cout<<"level the score \n"<<endl;
				}
				else cout<<"Computer wins \n"<<endl;
			}
			else  cout<<"Player wins \n"<<endl;
		}
		else  cout<<"Computer wins \n"<<endl;
	}
	system("pause");
	return 0 ;
}

bool IfContinue()											//To ask player if he wants to continue to play game . 
{
	bool flag=true ;
	char answer ;
	while(flag)
	{
		flag=false;
		cout<<"Do you want to continue? (y/n)";
		cin>>answer ;
		try{
			if(answer!='y' && answer!='n')
				throw 1;
		}
		catch(int input)
		{
			cout<<"ERROR INPUT "<<answer<<endl;
			flag=true;
		}
		
	}
	if (answer=='y')  return true ;
	if(answer=='n')   return false;
}

bool IfHit()												//To ask player if he wants to get another card.
{
	bool flag=true ;
	char answer ;
	while(flag)
	{
		flag=false;
		cout<<"\nDo you want another card? (y/n)";
		cin>>answer ;
		try{
			if(answer!='y' && answer!='n')
				throw 1;
		}
		catch(int input)
		{
			cout<<"ERROR INPUT "<<answer<<endl;
			flag=true;
		}
		
	}
	if (answer=='y')  return true ;
	if(answer=='n')   return false;
}



void shuffle()                                              //To shuffle the card at the beginning.
{
	int i ,k ; 
	for(i=0;i<4;++i){
		for(k=0;k<13;++k){
			if(k<10) card[i][k]=double(k+1);
			else  card[i][k]=0.5;
		}
	}
}



double SendCard()												//To send a card to player or computer by random . 
{
	bool flag=true;
	int suit ,point;											//The card information.	
	double count=0 ;

	while (flag)
	{
		suit= rand() * 4 / (RAND_MAX + 1);
		point=rand() * 13 / (RAND_MAX + 1);
		if (fabs(card[suit][point])>1e-8){
			flag=false;
		}
	}
	switch(suit){
	case 0 : cout<<"hearts" ;break;
	case 1 : cout<<"diamonds" ;break;
	case 2 : cout<<"spades";break;
	case 3 : cout<<"clubs";break;
	}
	switch(point){
	case 0 : cout<<"A ";break;
	case 10 : cout<<"J ";break;
	case 11 : cout<<"Q ";break;
	case 12 : cout<<"K ";break;
	default : cout<<point+1<<" ";
	}
	count=card[suit][point];
	card[suit][point]=0.0;
	return count ;
}


double PlayerStage()										//It's the player's stage to get the card.
{
	int i ;
	double playercount=0.0 ;								//To record the player's current number.
	cout<<"Player's stage. "<<endl;
	cout<<"Player gets the card ";
	for(i=0;i<2;++i){										//Send two cards at first.
			playercount+=SendCard();
	}
	cout<<"\n"<<"All score:  "<<playercount<<endl;
	while(playercount<=21)
	{
		if (IfHit())										//Ask if want more cards.
		{
			playercount+=SendCard();
			cout<<"\n"<<"All score:  "<<playercount<<endl;
		}
		else  return playercount;
	}
	return -1.0;
}

bool ComputerStage(double playercount)						//It's the computer's stage to get the card.
{
	int i ;
	double computercount=0.0;								//To record the computer's current number.	
	cout<<"Computer's stage. "<<endl;
	cout<<"Computer gets the card ";
										
	for(i=0;i<2;++i){
		computercount+=SendCard();
	}
	while(computercount<=21)
	{
		if(computercount>playercount) {
			cout<<"\n"<<"All score:  "<<computercount<<endl;
			return true;
		}
		if(computercount<=playercount){
			cout<<"\n Get another card.  ";
			computercount+=SendCard();
		}
		if(computercount==21) {
			cout<<"\n"<<"All score:  "<<computercount<<endl;
			return true;
		}
	}
	cout<<"\n"<<"All score:  "<<computercount<<endl;
	return false;
}
