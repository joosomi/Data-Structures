//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 2 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void inOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the in-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting in-order traversal of the binary search tree is: ");
			inOrderTraversal(root); // You need to code this function
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

// only use push() or pop()
// a stack 사용

// 중위 순회: 왼쪽 서브트리 -> 루트 노드 방문 -> 오른쪽 서브 트리
void inOrderTraversal(BSTNode *root) 
{
	if (root == NULL) {
		return;
	}

//	newStack 동적 할당 
	Stack *newStack;	
	newStack = malloc(sizeof(Stack));

	if (newStack == NULL) {
		return;
	}
	//newStack 초기화
	newStack -> top = NULL;

	//루트 노드를 가리키는 cur 포인터 
	BSTNode *cur = root;

//현재 노드가 NULL이 아니거나 스택이 비어있지 않은 동안 반복한다.
	while (!isEmpty(newStack) || cur != NULL) {
		while(cur != NULL) {
			
			push(newStack, cur);
			cur = cur -> left;

			// printf("%d ", cur->item);
		}

		cur = pop(newStack);

		printf("%d ", cur->item);

		cur = cur -> right;
	}

	free(newStack);

}



// void inOrderTraversal(BSTNode *root)
// {
// 	if (root == NULL) {
// 		return;
// 	}

// 	Stack *newStack;
// 	newStack = malloc(sizeof(newStack));

// 	//newStack 동적 할당 실패시 => 함수 종료
// 	if (newStack == NULL ) {
// 		return;
// 	}

// 	newStack -> top = NULL;

// 	while(!isEmpty(newStack)) {
// 		BSTNode *Node = pop(&newStack);
// 		printf("%d ", Node->item);

// 		if (root->right != NULL) {
// 			push(&newStack, root ->right );
// 		}

// 		push(&newStack, root->item);


// 		if (root->left != NULL) {
// 			push(&newStack, root-> left);
// 		}		


// 	}

// 	free(newStack);

// }

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}

BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
