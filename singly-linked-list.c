#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;



headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	if(h != NULL)
		freeList(h);

	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}




int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}


int insertNode(headNode* h, int key) {
        listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로 넣을 노드 동적할당으로 생성  
        listNode* head = h->first; // 제일 첫번째 노드를 가리키는 헤드 노드
	listNode* prenode=NULL; // 이전 노드 위치 기억 포인터 변수
	int cnt=1; //반복문 체크 변수 
	
	node->key = key; // 입력된 키값을 생성한 노드에 넣는다
	
	if (h->first == NULL) // 첫노드가 비었으면 ( 리스트가 비었으면) 
	{
		 h->first=node; // 입력받은 노드를 맨앞  노드로 삽입
		 node->link=NULL; // 노드 꼬리 초기화 
        }
	
	else //노드가 비어있지 않으면 
	{
		if(head->link == NULL)  //노드가 유일할때
		{ 
			if(key < head->key) //헤드의 키값이 새로들어온 키값보다 크면
			{
				node->link=head; //헤드 노드 앞에 새로운 노드를 연결
				h->first=node; // 맨앞을 새로운노드로 초기화 
			} 
			
			else // 입력받은 키값이 헤드노드의 키값보다 클경우 
			{
				head->link=node; //헤드 링크 뒤에 새로운 노드 연결 
			}
		
		 return 0; 
		}
	
	while(head != NULL){ //노드가 여러개일때 
	   
	        if(head->key > key) //헤드가 가리키는 키값이 입력받는 키값보다 크면 
			{
				  node->link=head; // 새로운 노드를 헤드앞에 연결 
				  
				  switch(cnt){  
				    case 1:	//첫 바퀴인경우 (새로만든 노드가 맨앞일때) 
				  	   h->first = node;
				  	   return 1;
				  	   
				    default: //첫바퀴 가 아니면 (새노드가 맨앞이 아니면) 
				   	   prenode->link=node;
				   	   return 1;
				   }
				   
			} 
			
			prenode=head; // 이전 노드를 현재노드로 지정 
			head=head->link; // 다음노드 가리키도록 
			
			cnt ++;
	} //헤드노드가 가리키는게 없을때까지 반복	 
	
	if(head==NULL) // 맨뒤 삽입경우 
	{
		prenode->link=node; // 이전노드 뒤에 새로 만든 노드 연결 
		node->link=NULL; // 마지막 꼬리 초기화 
	}
	
    }
    
    return 0;
}

int insertLast(headNode* h, int key) {

	return 0;
}



int deleteFirst(headNode* h) {


	return 0;
}


int deleteNode(headNode* h, int key) {

	return 0;

}


int deleteLast(headNode* h) {

	return 0;
}


int invertList(headNode* h) {

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

