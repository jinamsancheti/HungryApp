#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
/*--------------------------------------------------------------------------------------*/
#define MLC2 (RESTAURANT *)malloc(sizeof(RESTAURANT))
#define N 20
/*--------------------------------------------------------------------------------------*/
typedef struct restaurant
{
	char name[N] ;
	char type[N] ;
	char area[2*N];
	char speciality[2*N];
	int noOfSeats;
	char facilities[10*N];
	char menu[10*N];
	int value_type ;
	struct restaurant * left ;
	struct restaurant * right ;
	struct restaurant * next ;
	int height ;
}RESTAURANT;
RESTAURANT * restaurantRoot = NULL;
int choice;	
/*--------------------------------------------------------------------------------------*/
void createRestaurantTree();
RESTAURANT * insertRestaurantNode(RESTAURANT* node ,RESTAURANT * temp);
int restaurantBalanceFactor(RESTAURANT * temp);
int NodeHeight( RESTAURANT * temp );
int max2(int a, int b);
RESTAURANT *restaurantRotateRight(RESTAURANT *y);
RESTAURANT *restaurantRotateLeft(RESTAURANT *x);
RESTAURANT * displayRestaurant();
RESTAURANT * searchRestaurant(char str[N]);
RESTAURANT * findRestaurant(RESTAURANT * node,char str[N]);
void preorderRestaurant(RESTAURANT * node);
void inorderRestaurant(RESTAURANT * head);
/*--------------------------------------------------------------------------------------*/
void createRestaurantTree()
{
	FILE* ptr = fopen("D:\\COMPUTER PROGRAMMING\\DS PROJECTS\\RestaurantsList.txt", "a+");
	char buffer[400] ;
	RESTAURANT * temp ;	
	int head = 1 , i; 
	char k[10];
	while(fgets(buffer,200,ptr))
	{
		int ct = 0 ;
		char *tok ;
		tok = strtok(buffer,",") ;
		temp = MLC2 ;
		temp->right = NULL ;
		temp->left = NULL ; 
		temp->next = NULL ;
		temp->height = 1 ;
		char * ptr ;
		while( tok != NULL )
		{
			//printf("%s\t",tok);
			fflush(stdin);
			switch(ct)
			{
				case 0: 
					strcpy(temp->name, tok); 
					break;
				case 1:
					strcpy( temp->type, tok );
					break;
				case 2:
					strcpy( temp->area , tok );
					break;
				case 3:
					strcpy( temp->speciality , tok );
					break;
				case 4:
					temp->noOfSeats = atoi(tok) ;
					break;
				case 5:
					strcpy( temp->facilities, tok );
					break;
				case 6:
					strcpy( temp->menu, tok );
					break;
				case 7:
					temp->value_type = atoi(tok);
					break;
				default: ct = 0 ;
					break ;
			}
			ct++ ;
			tok = strtok(NULL,",");
		};
		restaurantRoot = insertRestaurantNode(restaurantRoot,temp);
	};
	fclose(ptr);
}
/*--------------------------------------------------------------------------------------*/
RESTAURANT * insertRestaurantNode(RESTAURANT* node ,RESTAURANT * temp)
{
	int balance;
	switch (choice)
	{
		case 1: if (node == NULL)
					return temp ;
				if ( (strcmpi(node->speciality , temp->speciality)) > 0 )
					node->left = insertRestaurantNode(node->left,temp);
				else if ( (strcmpi(node->speciality , temp->speciality)) < 0 )
					node->right = insertRestaurantNode(node->right, temp);
				else
					node->next = insertRestaurantNode(node->next,temp);

				node->height = 1 + max2(NodeHeight(node->left), NodeHeight(node->right));

				balance = restaurantBalanceFactor(node);
				if (balance > 1 && ( (strcmpi(node->left->speciality , temp->speciality)) > 0 ))
					return restaurantRotateRight(node);
				if (balance < -1 && ( (strcmpi(node->right->speciality , temp->speciality)) < 0 ))
					return restaurantRotateLeft(node);
				if (balance > 1 && ( (strcmpi(node->left->speciality , temp->speciality)) < 0 ))
				{	
					node->left = restaurantRotateLeft(node->left);
					return restaurantRotateRight(node);
				}
				if (balance < -1 && ( (strcmpi(node->right->speciality , temp->speciality)) > 0 ))
				{
					node->right = restaurantRotateRight(node->right);
					return restaurantRotateLeft(node);
				}
				return node;
				break;
		case 2: if (node == NULL)
					return temp ;
				if ( (strcmpi(node->area , temp->area)) > 0 )
					node->left = insertRestaurantNode(node->left,temp);
				else if ( (strcmpi(node->area , temp->area)) < 0 )
					node->right = insertRestaurantNode(node->right, temp);
				else
					node->next = insertRestaurantNode(node->next,temp);

				node->height = 1 + max2(NodeHeight(node->left), NodeHeight(node->right));

				balance = restaurantBalanceFactor(node);
				if (balance > 1 && ( (strcmpi(node->left->area , temp->area)) > 0 ))
					return restaurantRotateRight(node);
				if (balance < -1 && ( (strcmpi(node->right->area , temp->area)) < 0 ))
					return restaurantRotateLeft(node);
				if (balance > 1 && ( (strcmpi(node->left->area , temp->area)) < 0 ))
				{	
					node->left = restaurantRotateLeft(node->left);
					return restaurantRotateRight(node);
				}
				if (balance < -1 && ( (strcmpi(node->right->area , temp->area)) > 0 ))
				{
					node->right = restaurantRotateRight(node->right);
					return restaurantRotateLeft(node);
				}
				return node;
				break;
		case 3: if (node == NULL)
					return temp ;
				if ( (strcmpi(node->type , temp->type)) > 0 )
					node->left = insertRestaurantNode(node->left,temp);
				else if ( (strcmpi(node->type , temp->type)) < 0 )
					node->right = insertRestaurantNode(node->right, temp);
				else
					node->next = insertRestaurantNode(node->next,temp);

				node->height = 1 + max2(NodeHeight(node->left), NodeHeight(node->right));

				balance = restaurantBalanceFactor(node);
				if (balance > 1 && ( (strcmpi(node->left->type , temp->type)) > 0 ))
					return restaurantRotateRight(node);
				if (balance < -1 && ( (strcmpi(node->right->type , temp->type)) < 0 ))
					return restaurantRotateLeft(node);
				if (balance > 1 && ( (strcmpi(node->left->type , temp->type)) < 0 ))
				{	
					node->left = restaurantRotateLeft(node->left);
					return restaurantRotateRight(node);
				}
				if (balance < -1 && ( (strcmpi(node->right->type , temp->type)) > 0 ))
				{
					node->right = restaurantRotateRight(node->right);
					return restaurantRotateLeft(node);
				}
				return node;
				break;
		default:return node ;
				break;
	}
}
/*--------------------------------------------------------------------------------------*/
int restaurantBalanceFactor(RESTAURANT * temp)
{
	if (temp == NULL)
		return 0;
	return NodeHeight(temp->left) - NodeHeight(temp->right);
}
/*--------------------------------------------------------------------------------------*/
int NodeHeight( RESTAURANT * temp )
{
	if (temp == NULL)	
		return 0;
	return temp->height;
}
/*--------------------------------------------------------------------------------------*/
int max2(int a, int b)
{
	return a > b ? a : b ;
}
/*--------------------------------------------------------------------------------------*/
RESTAURANT *restaurantRotateRight(RESTAURANT *y)
{
	RESTAURANT *x = y->left;
	RESTAURANT *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max2(NodeHeight(y->left), NodeHeight(y->right)) + 1;
	x->height = max2(NodeHeight(x->left), NodeHeight(x->right)) + 1;

	// Return new root
	return x;
}
/*--------------------------------------------------------------------------------------*/
RESTAURANT *restaurantRotateLeft(RESTAURANT *x)
{
	RESTAURANT *y = x->right;
	RESTAURANT *T2 = y->left;

	// Perform rotation	
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max2(NodeHeight(x->left), NodeHeight(x->right)) + 1;
	y->height = max2(NodeHeight(y->left), NodeHeight(y->right)) + 1;

	// Return new root
	return y;
}
/*--------------------------------------------------------------------------------------*/
RESTAURANT * displayRestaurant()
{
	int s;
	char str[N];
	RESTAURANT * ele ;
	int p ;
	createRestaurantTree();
	switch (choice)
	{
		case 1: printf("\n\t\tSelect The Type Of Food\n");
				printf("\n\t\t\tPress 1:\t Italian\n");
				printf("\n\t\t\tPress 2:\t Continental\n");
				printf("\n\t\t\tPress 3:\t South-Indian\n");
				printf("\n\t\t\tPress 4:\t Mexican\n");
				printf("\n\t\t\tPress 5:\t North-Indian\n\t\t\t");
				scanf("%d",&s);
				switch (s)
				{
					case 1: strcpy(str,"Italian");
							break;	
					case 2: strcpy(str,"Continental");
							break;	
					case 3: strcpy(str,"SouthIndian");
							break;	
					case 4: strcpy(str,"Mexican");
							break;	
					case 5: strcpy(str,"NorthIndian");
							break;	
					default:
							break;	
				}
				ele = searchRestaurant(str);
				//printf("%s",ele->name);
				printf("\n\t\t\t\tNAME\t\t\tMENU\n");
				p = 1;
				while(ele != NULL)
				{
					printf("\n\t\t\t%d:\t%s\t\t%s\n",p,ele->name,ele->menu);
					p++ ;
					ele = ele->next ;
				};
				break;
		case 2: printf("\n\t\tSelect The Area\n");
				printf("\n\t\t\tPress 1:\t IT PARK\n");
				printf("\n\t\t\tPress 2:\t AMBAZARI\n");
				printf("\n\t\t\tPress 3:\t SITABULDI\n");
				printf("\n\t\t\tPress 4:\t SADAR\n");
				printf("\n\t\t\tPress 5:\t ITWARI\n\t\t\t");
				scanf("%d",&s);
				switch (s)
				{
					case 1: strcpy(str,"IT PARK");
							break;	
					case 2: strcpy(str,"AMBAZARI");
							break;	
					case 3: strcpy(str,"SITABULDI");
							break;	
					case 4: strcpy(str,"SADAR");
							break;	
					case 5: strcpy(str,"ITWARI");
							break;	
					default:
							break;	
				}
				ele = searchRestaurant(str);
				printf("\n\t\t\t\tNAME\t\t\tMENU\n");
				p = 1 ;
				while(ele != NULL)
				{
					printf("\n\t\t\t%d:\t%s\t\t%s\n",p,ele->name,ele->menu);
					p++ ;
					ele = ele->next ;
				};
				break;
		case 3: printf("\n\t\tSelect The Type\n");
				printf("\n\t\t\tPress 1:\t Cafe\n");
				printf("\n\t\t\tPress 2:\t Restaurant\n");
				printf("\n\t\t\tPress 3:\t Pub\n\t\t\t");
				printf("\n\t\t\tPress 4:\t Food Court\n\t\t\t");
				scanf("%d",&s);
				switch (s)
				{
					case 1: strcpy(str,"Cafe");
							break;	
					case 2: strcpy(str,"Restaurant");
							break;	
					case 3: strcpy(str,"Pub");
							break;	
					case 4: strcpy(str,"Food Court");
							break;	
					default:
							break;	
				}
				ele = searchRestaurant(str);
				printf("\n\t\t\t\tNAME\t\t\tMENU\n");
				p = 1 ;
				while(ele != NULL)
				{
					printf("\n\t\t\t%d:\t%s\t\t%s\n",p,ele->name,ele->menu);
					p++ ;
					ele = ele->next ;
				};
				break;
		default: ele = NULL ;
			break;
	}
	return ele;
}
/*--------------------------------------------------------------------------------------*/
RESTAURANT * searchRestaurant(char str[N])
{
	//printf("\nCheck 1\n");
	RESTAURANT * ans = findRestaurant(restaurantRoot,str);
	return ans ;
}
/*--------------------------------------------------------------------------------------*/
RESTAURANT * findRestaurant(RESTAURANT * node,char str[N])
{
	//printf("\nCheck 2\n");
	switch (choice)
	{
		case 1: if(node == NULL || (strcmpi(node->speciality,str) == 0)) 
					return node ;
				
				if((strcmpi(node->speciality,str) < 0))
					return findRestaurant(node->right, str);

				return findRestaurant(node->left,str);
				break;
		case 2: if(node == NULL || (strcmpi(node->area,str) == 0)) 
					return node ;
				
				if((strcmpi(node->area,str) < 0))
					return findRestaurant(node->right, str);

				return findRestaurant(node->left,str);
				break;
		case 3: if(node == NULL || (strcmpi(node->type,str) == 0)) 
					return node ;
				
				if((strcmpi(node->type,str) < 0))
					return findRestaurant(node->right, str);

				return findRestaurant(node->left,str);
				break;
		default:
			break;
	}
}
/*--------------------------------------------------------------------------------------*/
void preorderRestaurant(RESTAURANT * node)
{
	if(node == NULL)
	{
		return;
	}
	printf("%s\t",node->name);
	preorderRestaurant(node -> left);
	preorderRestaurant(node -> right);
}
/*--------------------------------------------------------------------------------------*/
void inorderRestaurant(RESTAURANT * head)
{
	if(head == NULL)
	{
		return;
	}
	inorderRestaurant(head -> left);
	printf("%s\t",head->name);
	inorderRestaurant(head -> right);
}
/*--------------------------------------------------------------------------------------*/
// int main()
// {
// 	//RESTAURANT * first;
// 	choice = 3 ;
// 	createRestaurantTree();
// 	preorderRestaurant(restaurantRoot);
// 	return 0 ;
// }

/*--------------------------------------------------------------------------------------*/
