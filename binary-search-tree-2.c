/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("[----- [조은지]  [2021076020] -----]\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	for(;;){
	for(;node;node=node->left){
		push(node);
	}
	node=pop();

	if(!node) break;

	printf(" [%d]",node->key);
	node=node->right;
	}
}
/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)
{
	if(!ptr) return; //트리가 비어있을 때
	enQueue(ptr); //큐에 노드 삽입 

	for(;;){
		ptr=deQueue(); //ptr=queue[front]		
		if(ptr){
			printf(" [%d]", ptr->key);
			//왼쪽 childnode부터 큐에 삽입 
			if(ptr->left)
				enQueue(ptr->left); 
			if(ptr->right)
				enQueue(ptr->right);
		}
		else break;
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //삽입할 노드 생성
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) { //트리가 비어있음
		head->left = newNode; 
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; 

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	if(head==NULL ||head->left==NULL){
		printf("\n Nothing to delete\n");
		return -1;
	}

	Node* root =head->left;

	Node *parent=NULL;
	Node *ptr=root;

	while((ptr!=NULL)&&(ptr->key!=key)){
		if(ptr->key!=key){
			parent=ptr;

		if (ptr->key>key)
			ptr=ptr->left;
		else 
			ptr=ptr->right;
		}
	}

	if(ptr==NULL){
		printf("No node for key [%d]",key);
		return -1;
	}

	//삭제할 노드가 leaf node인 경우
	if(ptr->left==NULL&&ptr->right==NULL){
		if(parent !=NULL){ 
			if(parent->left==ptr) //부모노드와 삭제할 노드 연결 끊기
				parent->left=NULL;
			else
				parent->right=NULL;
		}
		else //삭제할 노드가 root node인 경우
			head->left=NULL; 
	
	free(ptr); //ptr 메모리 할당 해제
	return 1;
	}

	//삭제할 노드의 child가 1개인 경우
	if((ptr->left==NULL||ptr->right==NULL))	
	{
		Node *child; //child 저장
		if(ptr->left!=NULL)
			child=ptr->left;
		else
			child=ptr->right;
		
		if(parent!=NULL){ //부모노드와 ptr의 child 연결
			if(parent->left==ptr)
				parent->left=child;
			else
				parent->right=child;
		}
		else
			root=child; //삭제할 노드가 root 노드인 경우
			
		free(ptr); //ptr 메모리 할당 해제
		return 1;
	}

	//삭제할 노드의 child가 2개인 경우
	Node *candidate;
	parent=ptr;

	candidate=ptr->right;

	while(candidate->left!=NULL) 
	//candidate가 leaf node가 될 때 까지 (가장 작은 노드)
	{
		parent=candidate;
		candidate=candidate->left;
	}
	//삭제할 노드의 key값과 candidate key값 바꾸기
	if(parent->right==candidate) 
		parent->right=candidate->right;
	else
		parent->left=candidate->right;
	
	ptr->key=candidate->key; //작은 값으로 key 값 바꾸기

	free(candidate); //leaf node 삭제
	return 1;

}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{
	if(head->left == head){
		free(head);
		return 1;
	}
	Node* p = head->left;
	freeNode(p);
	free(head);
	return 1;
}



Node* pop()
{
	if (top<0) return NULL; //stack에 데이터 없음
	return stack[top--];
}

void push(Node* aNode)
{
	stack[++top]=aNode;
}



Node* deQueue()
{
	if(front==rear){ //큐에 데이터 없음
		return NULL;
	}
	front=(front+1)%MAX_QUEUE_SIZE; //front	증가
	return queue[front]; //앞에 있는 데이터부터 반환
}

void enQueue(Node* aNode)
{
	rear=(rear+1)%MAX_QUEUE_SIZE;
	if(front==rear) //큐에 데이터 없음
		return;
	
		queue[rear]=aNode;
}


void printStack(){
	int i=0;
	printf("--- stack ---\n");
	while (i<=top)
		printf("stack[%d] = %d\n",i, stack[i]->key);
}

