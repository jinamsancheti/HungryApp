#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

#define MLC (RESTAURANT *)malloc(sizeof(RESTAURANT))
#define N 20

/*--------------------------------------------------------------------------------------*/

typedef struct Node1
{
	char name[N] ;
	char type[N] ;
	char area[2*N];
	char speciality[2*N];
	int noOfSeats;
	char facilities[10*N];
	char menu[10*N];
	struct Node1 * left ;
	struct Node1 * right ;
}RESTAURANT;

/*--------------------------------------------------------------------------------------*/

void insertNodeArea(RESTAURANT* head ,RESTAURANT * temp);
RESTAURANT * createTree();
void preorder(RESTAURANT * head);

/*--------------------------------------------------------------------------------------*/

RESTAURANT * createTree()
{
	FILE* ptr = fopen("D:\\COMPUTER PROGRAMMING\\DS PROJECTS\\RestaurantsList.txt", "r");
	char buffer[400] ;
	RESTAURANT* first , * temp ;
	int head = 1 ;
	while(fgets(buffer,400,ptr))
	{
		int ct = 0 ;
		char *tok = strtok(buffer,",") ;
		temp = MLC ;
		temp -> right = NULL ;
		temp -> left = NULL ; 
		while( tok != NULL )
		{
			if( ct == 0 )
				strcpy( temp->name , tok );
			else if( ct == 1 )
				strcpy( temp->type , tok );
			else if( ct == 2 )
				strcpy( temp->area , tok );
			else if( ct == 3 )
				strcpy( temp->speciality , tok );
			else if( ct == 4 )
				temp->noOfSeats = atoi(tok);
			else if( ct == 5 )
				strcpy( temp->facilities , tok );
			else if( ct == 6 )
				strcpy( temp->menu , tok );
			ct++ ;
			tok = strtok(NULL,",");
		};
		if(head == 1)
		{
			first = MLC ;
			strcpy(first->name, temp->name);
			strcpy(first->facilities, temp->facilities);
			strcpy(first->menu, temp->menu);
			first->noOfSeats = temp->noOfSeats;
			strcpy(first->area, temp->area);
			strcpy(first->type, temp->type);
			strcpy(first->speciality, temp->speciality);
			first->left = NULL ;
			first->right = NULL ;
		}
		else
		{
			insertNodeArea(first, temp);
		}
		head = 0 ;
	};
	fclose(ptr);
	return first ;
}

/*--------------------------------------------------------------------------------------*/

void insertNodeArea(RESTAURANT* root ,RESTAURANT * temp)
{
	if( (strcmp(root -> area , temp -> area)) > 0 )
	{
		if (root->left == NULL)
			root->left = temp;
		else
			insertNodeArea(root -> left , temp);
	}
	else
	{
		if (root->right == NULL)
			root->right = temp;
		else
			insertNodeArea(root -> right , temp);
	}
}

/*--------------------------------------------------------------------------------------*/

void preorder(RESTAURANT * head)
{
	if(head == NULL)
	{
	    return;
	}
	printf("%s\n",head-> area);
	preorder(head -> left);
	preorder(head -> right);
}

/*--------------------------------------------------------------------------------------*/

int main()
{
	RESTAURANT * first = createTree();
	preorder(first);
	return 0 ;
}

/*--------------------------------------------------------------------------------------*/


