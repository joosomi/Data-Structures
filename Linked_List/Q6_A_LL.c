//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 6 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
int moveMaxToFront(ListNode **ptrHead);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	int c, i, j;
	c = 1;

	LinkedList ll;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move the largest stored value to the front of the list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j=insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveMaxToFront(&(ll.head));  // You need to code this function
			printf("The resulting linked list after moving largest stored value to the front of the list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////

// LinkedList의 최댓값을 가지는 노드는 맨 앞으로 보내기 
// 30 20 40 70 50 -> 70 30 20 40 50  

// 최댓값을 갖는 이전 노드 maxNode 
// moveMaxToFront(&(ll.head));

int moveMaxToFront(ListNode **ptrHead)
{
	//최댓값을 갖는 이전 노드를 가리키는 포인터 
	ListNode  *maxNodePrev;
	maxNodePrev = NULL;
	//연결리스트를 순회할 임시 포인터
	ListNode *temp;
	temp = *ptrHead; 
	//최댓값을 가진 노드를 가리키는 포인터 
	ListNode *maxNode; 
	maxNode = *ptrHead;
	
	//빈 리스트이거나 하나의 노드만 존재하는 경우
	//최댓값 찾을 필요 없음
	if ((*ptrHead) == NULL || (*ptrHead)->next == NULL ) 
	{
		return ;
	}

	// 다음 노드에 값이 있을 때만
	//temp 포인터를 활용 - 연결 리스트 순회
	while(temp->next != NULL) {
		
		//다음 노드의 item이 
		//현재 최댓값 item 보다 크다면
		
		//최댓값을 가지는 이전 노드를 가리키는 maxNodePrev temp로 갱신 
		//최댓값 갱신 
		if (temp->next->item > maxNode->item) {
			maxNodePrev = temp;
			maxNode = temp -> next;
			
		}
		//다음 노드로 이동
		temp = temp->next; 
	}

	//최댓값을 가지는 이전 노드 maxNodePrev가 NULL이 아닌 경우
	//최댓값을 가진 노드를 맨 앞으로 이동

	if (maxNodePrev != NULL) {
		//최댓값 이전 노드와 최댓값 갖는 노드의 다음 노드 서로 연결 
		maxNodePrev -> next = maxNode -> next;
		//maxNode의 next가 현재의 헤드가 되어야 함
		//그리고 현재의 헤드를 maxNode로 갱신 - 최댓값을 맨 앞으로 이동시킨 결과가 나온다.
		maxNode -> next = *ptrHead;
		*ptrHead = maxNode;
		
	
	}
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}
