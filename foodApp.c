#include<stdio.h>
#include<conio.h>
#include<string.h>
#include"UserHandling.c"
#include"restaurantTree.c"
#include"OrderList.h"
#define N 20
/*--------------------------------------------------------------------------------------*/
int welcomePage();
USER * userPage(int userStatus);
/*--------------------------------------------------------------------------------------*/
typedef struct Node2
{
	int id;
	char name[N];
	char area[N]; 
	long int phno;
	float commision;
	struct Node2 * left ;
	struct Node2 * right ;
}AGENT;
/*--------------------------------------------------------------------------------------*/
ORDER *O1 ;
/*--------------------------------------------------------------------------------------*/
int main()
{	
	int userStatus = welcomePage();
	USER* us; 
	us = userPage(userStatus);
	return 0 ;
}
/*--------------------------------------------------------------------------------------*/
int welcomePage()
{
	int ch;
	printf("\nWELCOME!!\n");
	printf("\n\tPress1: Login \n");
	printf("\n\tPress2: Create New Account \n\n\t\t");
	scanf("%d",&ch);
	return ch;
}
/*--------------------------------------------------------------------------------------*/
USER * userPage(int userStatus)
{
	USER * u;
	int action1;
	char ch , c;
	long long userPhno;
	char food[100];
	switch(userStatus)
	{
		case 1:
				printf("\n\tEnter Your Phone Number: ");
				scanf("%lld",&userPhno);
				u = searchUser(userPhno);
				if( u == NULL )
					printf("\n\t\tUSER NOT FOUND!!\n");
				else
				{
					printf("\n\t\tPress1: Order Food...\n");
					printf("\n\t\tPress2: See Your Previous Order...\n\t\t");
					printf("\n\t\tPress3: Edit Your Details...\n\t\t");
					scanf("%d",&action1);
					switch(action1)
					{
						case 1:
								printf("\n\n\t\tTo Search Restaurant:\n");
								printf("\n\t\t\tPress1: Speciality Wise \n");
								printf("\n\t\t\tPress2: Area Wise \n");
								printf("\n\t\t\tPress3: Restaurant Type Wise \n\t\t\t");
								scanf("%d",&choice);
								displayRestaurant();
								printf("\n\t\t\tEnter The List Of Items You Want Seperated By \'|\' :- \n\t\t\t\t");
								fflush(stdin);
								//printf("\nhi\n");
								gets(food);
								strcpy(u->prevOrder,food);
								FILE* ptr = fopen("D:\\COMPUTER PROGRAMMING\\DS PROJECTS\\UsersList.txt", "a+");
								fprintf(ptr,"%s,",food);
								fclose(ptr);
								break;
						case 2:
								if(u->prevOrder[1] != '\0' && u->prevOrder[0] != 'N')
									printf("\n\t\t\t\t%s",u->prevOrder);	
								else
									printf("\n\t\t\tThere Are No Previous Orders");
								break ;
						default: 
								printf("\n\nEnter Correct Choice !! \n");
					}
				}
				break;
		case 2:
				newUser();

				break ;
		default: 
				printf("\n\nEnter Correct Choice !! \n");
	}
	return u ;
}