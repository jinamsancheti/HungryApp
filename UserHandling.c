#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

#define N 20
#define MLC1 (USER *)malloc(sizeof(USER))

/*--------------------------------------------------------------------------------------*/

typedef struct Node3
{
	int user_id ;
	char name[N/2];
	char area[N];
	long long int phone_no;
	char prevOrder[N*4];
	int height ;
	struct Node3 * left ;
	struct Node3 * right ;
}USER;

USER * userRoot = NULL;
/*--------------------------------------------------------------------------------------*/
int userNodeHeight( USER * temp );
void createUserTree();
int max1(int a, int b);
USER *insertUserNode(USER * userRoot ,USER *node);
USER * userRotateRight(USER * temp);
USER * userRotateLeft(USER * temp);
void preorderUser(USER * head);
void inorderUser(USER * head);
int userBalanceFactor(USER * temp);
USER * searchUser(long long pno);
USER * findUser(USER * node, long long pno);
void newUser();
int noOfUsers();
/*--------------------------------------------------------------------------------------*/
void createUserTree()
{
	FILE* ptr = fopen("D:\\COMPUTER PROGRAMMING\\DS PROJECTS\\UsersList.txt", "r+");
	char buffer[400] ;
	USER * temp ;
	int head = 1 , i; 
	//char k[10];
	while(fgets(buffer,200,ptr))
	{
		int ct = 0 ;
		char *tok ;
		tok = strtok(buffer,",") ;
		temp = MLC1 ;
		temp->right = NULL ;
		temp->left = NULL ; 
		temp->height = 1 ;
		char *ptr;
		while( tok != NULL )
		{
			fflush(stdin);
			switch(ct)
			{
				case 0: 
					temp->user_id = atoi(tok); 
					break;
				case 1:
					strcpy( temp->name , tok );
					break;
				case 2:
					strcpy( temp->area , tok );
					break;
				case 3:
					temp->phone_no = atoll(tok);
					break;
				case 4:
					strcpy( temp->prevOrder , tok );
					break;
				default: ct = 0 ;
			}
			ct++ ;
			tok = strtok(NULL,",");
		};
		userRoot = insertUserNode(userRoot,temp);
	};
	fclose(ptr);
}
/*--------------------------------------------------------------------------------------*/
USER *insertUserNode(USER * node ,USER *temp)
{
	/* 1. Perform the normal BST insertion */
	if (node == NULL)
		return temp ;

	if (temp->phone_no < node->phone_no)
		node->left = insertUserNode(node->left,temp);
	else if (temp->phone_no > node->phone_no)
		node->right = insertUserNode(node->right, temp);
	else // Equal keys are not allowed in BST
		return node;

	/* 2. Update height of this ancestor node */
	node->height = 1 + max1(userNodeHeight(node->left), userNodeHeight(node->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalanced */
	int balance = userBalanceFactor(node);

	// If this node becomes unbalanced, then
	// there are 4 cases

	// Left Left Case
	if (balance > 1 && temp->phone_no < node->left->phone_no)
		return userRotateRight(node);

	// Right Right Case
	if (balance < -1 && temp->phone_no > node->right->phone_no)
		return userRotateLeft(node);

	// Left Right Case
	if (balance > 1 && temp->phone_no > node->left->phone_no)
	{	
		node->left = userRotateLeft(node->left);
		return userRotateRight(node);
	}

	// Right Left Case	
	if (balance < -1 && temp->phone_no < node->right->phone_no)
	{
		node->right = userRotateRight(node->right);
		return userRotateLeft(node);
	}

	/* return the (unchanged) node pointer */
	return node;
}
/*--------------------------------------------------------------------------------------*/
int userBalanceFactor(USER * temp)
{
	if (temp == NULL)
		return 0;
	return userNodeHeight(temp->left) - userNodeHeight(temp->right);
}
/*--------------------------------------------------------------------------------------*/
int userNodeHeight( USER * temp )
{
	if (temp == NULL)	
		return 0;
	return temp->height;
}
/*--------------------------------------------------------------------------------------*/
int max1(int a, int b)
{
	return a > b ? a : b ;
}
/*--------------------------------------------------------------------------------------*/
USER *userRotateRight(USER *y)
{
	USER *x = y->left;
	USER *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max1(userNodeHeight(y->left), userNodeHeight(y->right)) + 1;
	x->height = max1(userNodeHeight(x->left), userNodeHeight(x->right)) + 1;

	// Return new root
	return x;
}
/*--------------------------------------------------------------------------------------*/
USER *userRotateLeft(USER *x)
{
	USER *y = x->right;
	USER *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	// Update heights
	x->height = max1(userNodeHeight(x->left), userNodeHeight(x->right)) + 1;
	y->height = max1(userNodeHeight(y->left), userNodeHeight(y->right)) + 1;

	// Return new root
	return y;
}
/*--------------------------------------------------------------------------------------*/
USER * searchUser(long long pno)
{
	createUserTree();
	return findUser(userRoot,pno);
	//return ans ;
}
/*--------------------------------------------------------------------------------------*/
USER * findUser(USER * node, long long pno)
{
	if(node == NULL || node->phone_no == pno)
		return node ;
	
	if(node->phone_no < pno)
		return findUser(node->right, pno);

	return findUser(node->left, pno);
}
/*--------------------------------------------------------------------------------------*/
void preorderUser(USER * head)
{
	if(head == NULL)
	{
		return;
	}
	printf("%lld\t",head->phone_no);
	preorderUser(head -> left);
	preorderUser(head -> right);
}
/*--------------------------------------------------------------------------------------*/
void inorderUser(USER * head)
{
	if(head == NULL)
	{
		return;
	}
	inorderUser(head -> left);
	printf("%lld\t",head->phone_no);
	inorderUser(head -> right);
}
/*--------------------------------------------------------------------------------------*/
void newUser()
{
	char data[N*2];
	long long phn ;
	int uid ;
	FILE* ptr = fopen("D:\\COMPUTER PROGRAMMING\\DS PROJECTS\\UsersList.txt", "a+");
	uid = 10000 + noOfUsers();
	fprintf(ptr,"\n%d,",uid);
	printf("\n\t\t\tEnter Your Name : ");
	fflush(stdin);
	scanf("%[^\n]%*c",data);
	fprintf(ptr,"%s,",data);
	printf("\n\t\t\tEnter Your Area : ");
	fflush(stdin);
	scanf("%[^\n]%*c",data);
	fprintf(ptr,"%s,",data);
	printf("\n\t\t\tEnter Your Phone Number : ");
	scanf("%lld",&phn);
	fprintf(ptr,"%lld",phn);
	//fprintf(ptr,"%c","N");
	fclose(ptr);
}
/*--------------------------------------------------------------------------------------*/
int noOfUsers()
{
	FILE* ptr = fopen("D:\\COMPUTER PROGRAMMING\\DS PROJECTS\\UsersList.txt", "r");
	//char buffer[400] ;
	int ct = 0 ; 
	char ch = getc(ptr);
	while(ch != EOF)
	{
		if(ch == '\n')
			ct++ ;
		ch = getc(ptr);
	};
	fclose(ptr);
	return ct ;
}
/*--------------------------------------------------------------------------------------*/
// int main()
// {	
// 	createUserTree();
// 	preorderUser(root);
// 	printf("\n");
// 	inorderUser(root);
// 	return 0 ;
// }
/*--------------------------------------------------------------------------------------*/
