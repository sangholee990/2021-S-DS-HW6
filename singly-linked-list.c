#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key; // 키값을 저장하는 int형 변수 
	struct Node* link; //노드를 가리키는 포인터 (노드) 
} listNode; 

typedef struct Head {
	struct Node* first; //제일 첫번째 노드를 가리키는 포인터 
}headNode;



headNode* initialize(headNode* h); //리스트를 초기화하는 함수 
int freeList(headNode* h);// 노드를 해제하는 함수 

int insertFirst(headNode* h, int key); // 리스트의 첫부분에 키값같는 노드를 추가하는 함수 
int insertNode(headNode* h, int key); // 키값을 입력받아 그 값보다 큰값을 갖는 노드 바로앞에 추가하는 함수 
int insertLast(headNode* h, int key); // 리스트 가장 마지막부분에 노드를 연결하는 함수 

int deleteFirst(headNode* h); // 가장 첫번째 노드를 제거하는 함수 
int deleteNode(headNode* h, int key); // 리스트에서 해당 키값을 갖는 노드를 제거 
int deleteLast(headNode* h); //제일 마지막 노드를 제거 
int invertList(headNode* h); // 리스트에 있는 노드를 리버스 시킴 

void printList(headNode* h); // 리스트 정보 출력 

int main()
{
	char command; // 사용자에게 명령을 받는 변수 선언 
	int key; // 키값 받는 변수 선언 
	headNode* headnode=NULL; //제일 첫번째 노드를 가리키는 포인터 선언 

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
			headnode = initialize(headnode); //헤드노드를 초기화한다 
			break;
		case 'p': case 'P':
			printList(headnode); //리스트 정보 출력 
			break;
		case 'i': case 'I':
			printf("Your Key = ");  
			scanf("%d", &key); 
			insertNode(headnode, key); //키를 입력받아  오름차순으로 삽입 
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); 
			deleteNode(headnode, key); //입력받아온 키값과 같은 키값을 갖는 노드를 삭제한다 
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); // 마지막 노드에 받은 키값을 넣는다 
			break;
		case 'e': case 'E':
			deleteLast(headnode); // 마지막에 있는 노드를 지운다 
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //가장 첫 노드에 노드 삽입 
			break;
		case 't': case 'T':
			deleteFirst(headnode); // 가장 첫번째 노드를 삭제한다 
			break;
		case 'r': case 'R':
			invertList(headnode); // 리스트에 있는 노드들을 역순으로 뒤집는다 
			break;
		case 'q': case 'Q':  
			freeList(headnode); // 메모리 반납후 프로그램 종료 
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
		freeList(h); //headnode가 비어있지않으면 할당된 메모리 모두 해제 

	headNode* temp = (headNode*)malloc(sizeof(headNode)); //headnode에 대한 메모리를 할당받아 리턴 
	temp->first = NULL; //headnode 초기화 
	return temp;
}

int freeList(headNode* h){
	
	listNode* p = h->first; //헤드 노드가 가리키는 곳을 P가 가리키게 

	listNode* prev = NULL; // 이전노드 기억하는  포인터 
	while(p != NULL) {
		prev = p; //이전 노드 저장 
		p = p->link; // p가 다음노드 가리킬수있게 
		free(prev); // 이전노드 반납 
	}
	free(h); // headnode 해제 
	return 0;
}




int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 할당 
	node->key = key; //새로 만든 노드에 키값 입력 

	node->link = h->first; // 새로만든 노드를 제일 첫번째 노드앞에 연결 
	h->first = node; //헤드 노드가 새로 만든 노드를 가리키게 

	return 0;
}

/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {
	
    listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로 넣을 노드 동적할당으로 생성  
    listNode* now = h->first; //제일 맨앞 노드를 가리키는 곳을 현재노드가 가리키게 
	listNode* prenode=NULL; // 이전 노드 위치 기억 포인터 변수
	node->link=NULL; //node 가 가리키는곳 초기화 
	int cnt=1; //반복문 체크 변수 
	
	node->key = key; // 입력된 키값을 생성한 노드에 넣는다
	
	if (h->first == NULL) // 첫노드가 비었으면 ( 리스트가 비었으면) 
	{
		 h->first=node; // 입력받은 노드를 맨앞  노드로 삽입
		 node->link=NULL; // 노드 꼬리 초기화 
    }
	
	else //노드가 비어있지 않으면 
	{
		if(now->link == NULL)  //노드가 유일할때
		{ 
			if(key < now->key) //현재노드의 키값이 새로들어온 키값보다 크면
			{
				node->link=now; //현재  노드 앞에 새로운 노드를 연결
				h->first=node; // 맨앞을 새로운노드로 초기화 
			} 
			
			else // 입력받은 키값이 현재노드의 키값보다 클경우 
			{
				now->link=node; //헤드 링크 뒤에 새로운 노드 연결 
			}
		
		 return 0; 
		}
	
	while(now != NULL){ //노드가 여러개일때 
	   
	        if(now->key > key) //현재노드가 가리키는 키값이 입력받는 키값보다 크면 
			{
				  node->link=now; // 새로운 노드를 헤드앞에 연결 
				  
				  switch(cnt){  
				    case 1:	//첫 바퀴인경우 (새로만든 노드가 맨앞일때) 
				  	   h->first = node;
				  	   return 1;
				  	   
				    default: //첫바퀴 가 아니면 (새노드가 맨앞이 아니면) 
				   	   prenode->link=node;
				   	   return 1;
				   }
				   
			} 
			
			prenode=now; // 이전 노드를 현재노드로 지정 
			now=now->link; // 다음노드 가리키도록 
			
			cnt ++;
	} //현재노드가 가리키는게 없을때까지 반복	 
	
	if(now==NULL) // 맨뒤 삽입 해야하는 경우 
	{
		prenode->link=node; // 이전노드 뒤에 새로 만든 노드 연결 
		node->link=NULL; // 마지막 꼬리 초기화 
	}
	
    }
    
    return 0;
} 
	

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
    
    listNode* node = (listNode*)malloc(sizeof(listNode)); // 뒤에 붙일 노드 동적 할당으로 생성
    listNode* now = h->first; //제일 맨앞 노드를 가리키는 곳을 현재 노드가 가리키게 
    node->link = NULL;
	node->key= key; //입력받은 키 넣어주기 
	
	if(h->first==NULL) //노드가 비었으면 
	{
		h->first=node; //제일 앞노드를 새로운 노드로 초기화 
	}
	
	while(now->link != NULL) // 현재노드가 빈곳을 가리키지 않으면 계속 반복 
	{
	      now=now->link;// 현재 노드를 한칸씩 다음 노드 가리키게 이동 
	   
	}
	
	now->link=node; //마지막 노드 뒤에 node노드 연결
    
    return 0;
}

//맨앞 노드 제거 함수 
int deleteFirst(headNode* h) {
    
    if(h->first ==NULL){
			printf("더 이상 삭제할 노드가 없습니다\n");
			return 1;
	    }
		else{
		    listNode* head = h->first; //제일 맨앞 노드를 가리키는 곳을 head가 가리키게  
		    h->first=head->link; //노드 맨앞을 가리키는 포인터를 현재 노드의 다음노드로 포인팅
			free(head); // 제일 첫번째 노드였던거 반납 
       }
	    
	return 1;
       
}
/**
 * list에서 key에 대한 노드 삭제
 */

int deleteNode(headNode* h, int key) {
	
	listNode* head = h->first; //맨 앞을 가리키는 곳을 head가 가리키게 
	listNode* prenode = NULL; // 이전 노드 포인터 변수 NULL로 초기화 
	
	if(h->first ==NULL) //리스트에 노드가 없으면
	{ 
	    printf("더 이상 삭제할 노드가 없습니다.");
	    return 1;
	}
	
	while(head != NULL) //현재노드가 가리키는 곳이 비지않을때 까지 
	{
	    if(head->key == key){ //입력키가 현재키와 같으면 
	    	 if(head==h->first){ //맨 앞 노드가 현재 노드와 같으면 
	    	 	     h->first=head->link; //현재노드가 맨앞노드 가리키게 
			 } 
			 else //같지 않으면 
			 {
			 	prenode->link = head->link;// 현재노드가 가리키던곳을 이전노드가 가리키는 곳으로 설정 
			 }
			 free(head); // 노드 반납
			 return 1; 
		}
		prenode = head; // head노드를 이전노드에 저장
		head= head->link;// 헤드노드  다음 노드로 이동 
		
	}
	
    
	return 0;
}


int deleteLast(headNode* h) {
    
    listNode* head = h->first; //이동하는 현재 노드를 맨앞으로 초기화 
    listNode* prenode = NULL; //이전 노드를 가리키는 포인터
    
    if(h->first==NULL)//리스트에 노드가 없으면
	{
		printf("더 이상 삭제할 노드가 없습니다");
		return 1; 
	 } 
	
    else// 노드가 한개이상 있을때
	{
		if((head->link==NULL)&&(prenode==NULL))// 노드가 유일할때
		{
			h->first=NULL; //맨앞 포인터 널 초기화 
			free(head);// 기존 노드 반납
		    return 1; 
		 }
		 
		 while(head->link != NULL)//노드 2개 이상일 경우
		 {
		 	prenode=head; //이전 노드를 현재 노드 위치로;
			head= head->link; //현재 노드 다음노드로 한칸 
		  } 
		  
		  prenode->link =NULL; // 제일 꼬리 초기화
		  free(head); // 맨 마지막 노드 반납 
	 } 
	 
    
	return 0;
}


int invertList(headNode* h) {
	
    listNode* head = h->first; //이동하는 현재 노드를 맨앞으로 초기화 
	listNode* tail;   
	listNode* mid=NULL;
	
	if(h->first ==NULL) // 노드가 없으면 
	{
	     printf("리스트에 남은 노드가 없습니다\n");
	     return 1;
	}
	
	while(head) //이동하는 현재노드가 NULL 까지 반복 
	{
		tail=mid; //tail노드를 mid 로
		mid=head; // mid노드를 head로 
		head=head->link; // head를 다음 노드위치로 한칸
		mid->link = tail;// mid의 포인터를 역방향으로 
	}
	
	h->first=mid; // 역순이 되므로 mid가 맨앞 노드 
	
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //리스트에 아무노드도 없으면 
		printf("Nothing to print....\n");  // 낫띵투 프린트 출력 
		return;
	}

	p = h->first; //p가 제일 첫번째 노드 가리키게 

	while(p != NULL) { //p가 빈곳을 가리킬때 까지 
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link; //p한칸 이동하면서 탐색 
		i++;
	}

	printf("  items = %d\n", i);
}

