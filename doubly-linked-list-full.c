
#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {//노드 구조체 생성
	int key;
	struct Node* llink;// 왼쪽 노드 연결 링크
	struct Node* rlink;//오른쪽 노드 연결 링크
} listNode;



typedef struct Head {//헤드 노드
	struct Node* first;//헤드노드는 첫노드 가리킴
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);//이중포인터로된 초기노드생성 함수

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);//리스트 해제 함수

int insertNode(headNode* h, int key);//노드 입력
int insertLast(headNode* h, int key);//마지막 노드 입력
int insertFirst(headNode* h, int key);//첫번째 노드 입력
int deleteNode(headNode* h, int key);//노드 삭제
int deleteLast(headNode* h);//마지막 노드 삭제
int deleteFirst(headNode* h);//첫 노드 삭제
int invertList(headNode* h);//노드의 역순을 만들어주는 함수

void printList(headNode* h);//노드 출력함수


int main()
{
	printf("[----- [lee hyeondo] [2019038085] -----]");

	char command;//커맨드 입력
	int key;
	headNode* headnode=NULL;

	do{//while의 조건에 따라 반복. 메뉴 출력
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//커멘드 입력

		switch(command) {//입력받은 커멘드가
		case 'z': case 'Z'://z라면
			initialize(&headnode);//헤드노드 생성
			break;
		case 'p': case 'P'://p라면
			printList(headnode);//입력받은 노드 출력
			break;
		case 'i': case 'I'://i라면
			printf("Your Key = ");
			scanf("%d", &key);//키 입력받고
			insertNode(headnode, key);//키를 노드에 추가
			break;
		case 'd': case 'D'://d라면
			printf("Your Key = ");
			scanf("%d", &key);//키 입력받고
			deleteNode(headnode, key);//노드삭제
			break;
		case 'n': case 'N'://n라면
			printf("Your Key = ");
			scanf("%d", &key);//키 입력 받고
			insertLast(headnode, key);//마지막 노드 입력
			break;
		case 'e': case 'E'://e라면
			deleteLast(headnode);//마지막 노드 삭제
			break;
		case 'f': case 'F'://f라면
			printf("Your Key = ");
			scanf("%d", &key);//키 입력받고
			insertFirst(headnode, key);//첫 노드 입력
			break;
		case 't': case 'T'://t라면
			deleteFirst(headnode);//첫 노드 삭제
			break;
		case 'r': case 'R'://r라면
			invertList(headnode);//입력받은 노드들 역순 재배치
			break;
		case 'q': case 'Q'://q라면
			freeList(headnode);//리스트 메모리 해제
			break;
		default://모두아니면 오류 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');//커멘드가 q가 아니면 다시 반복

	return 1;
}


int initialize(headNode** h) {//초기화 함수

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)//만약 헤드노드가 NULL이 아니면
		freeList(*h);//할당된 메모리 모두 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));// 동적할당
	(*h)->first = NULL;//첫 노드는 NULL
	return 1;
}

int freeList(headNode* h){//메모리 해제 함수
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;//노드 p에 첫번째 노드입력

	listNode* prev = NULL;//노드 prev생성 및 NULL로 초기화
	while(p != NULL) {//연결된 노드들 모두 NULL이 될때까지 반복
		prev = p;//prev에 p 입력
		p = p->rlink;//p는 다음노드
		free(prev);//prev 해제
	}
	free(h);//헤드 노드 메모리 해제
	return 0;
}


void printList(headNode* h) {//리스트 출력 함수
	int i = 0;
	listNode* p;//노드 생성

	printf("\n---PRINT\n");

	if(h == NULL) {//헤드노드가 NULL이면
		printf("Nothing to print....\n");// 프린트할게 없음을 출력
		return;
	}

	p = h->first;//p는 첫 노드

	while(p != NULL) {//p가 NULL이지 않은동안
		printf("[ [%d]=%d ] ", i, p->key);//키 값고 번호 출력
		p = p->rlink;//p 한칸이동
		i++;//순서출력하는 변수 하나 증가
	}

	printf("  items = %d\n", i);//최종갯수 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {//마지막 노드 추가 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드 동적할당
	node->key = key;//노드가 가리키는 key는 key
	node->rlink = NULL;//오른쪽 링크는 NULL
	node->llink = NULL;//왼쪽 링트는 NULL

	if (h->first == NULL)//만약 첫 노드가 0 이면
	{
		h->first = node;// 첫 노드에 노드 입력
		return 0;
	}

	listNode* n = h->first;//노드 n 첫노드로 초기화
	while(n->rlink != NULL) {//노드의 오른쪽링크가 0 이 아닌동안
		n = n->rlink;//노드는 다음노드 
	}
	n->rlink = node;//마지막 노드는 key를 가진 노드 입력
	node->llink = n;//노드에 전 노드는 n
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {//마지막 노드 삭제 함수

	if (h->first == NULL)//첫노드가 0 이면
	{
		printf("nothing to delete.\n");//삭제할게 없음을 출력
		return 0;
	}

	listNode* n = h->first;//노드 n 을 첫노드로 초기화
	listNode* trail = NULL;// trail노드 0으로 초기화

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {//첫 노드 다음 노드가 없으면
		h->first = NULL;//첫 노드는 0
		free(n);//노드 n 메모리 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {//마지막 노드까지 이동
		trail = n;//트레일 노드는 현재 노드
		n = n->rlink;//현재 노드는 다음 노드
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;//트레일노드의 다음노드는 0으로 삭제
	free(n);//n의 메모리 해제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {//첫 노드 입력 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드 동적할당
	node->key = key;//노드의 값은 키
	node->rlink = node->llink = NULL;//노드의 다음 노드와 전 노드는 0

	if(h->first == NULL)//첫 노드가 없으면
	{
		h->first = node;//첫노드는 입력받은 노드 입력
		return 1;
	}

	node->rlink = h->first;//노드의 다음 노드는 원래 첫노드 였던것
	node->llink = NULL;//노드의 왼쪽 노드는 0

	listNode *p = h->first;//노드 p는 첫 노드
	p->llink = node;//p의 전 노드는 노드
	h->first = node;//첫 노드에 입력받은 노드 입력

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {//첫번째 노드 삭제 함수

	if (h->first == NULL)//첫 노드가 0이면
	{
		printf("nothing to delete.\n");//삭제할 노드 없음을 출력
		return 0;
	}
	listNode* n = h->first;//노드 n을 첫노드로 초기화
	h->first = n->rlink;//첫 노드 한칸 이동

	free(n);//n의 메모리 해제

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {//노드 역순 재배치 함수


	if(h->first == NULL) {//만약 첫 노드가 0 이면
		printf("nothing to invert...\n");//역순으로 재배치할 노드 없음을 출력
		return 0;
	}
	listNode *n = h->first;//노드 n을 첫 노드로 초기화
	listNode *trail = NULL;//트레일 노드는 0
	listNode *middle = NULL;//미들 노드는 0

	while(n != NULL){//n이 0이 아닐때까지
		trail = middle;//트레일노드에 미들노드 입력
		middle = n;//미들노드에 현재 노드 입력
		n = n->rlink;//현재 노드에 다음노드 입력
		middle->rlink = trail;//미들노드의 다음 노드에 트레일 노드 입력
		middle->llink = n;//미들 노드에 전 노드에 현재 노드 입력
	}

	h->first = middle;//첫 노드에 미들노드 입력

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {//노드 입력 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));//노드 동적할당
	node->key = key;//노드의 키값 키로 입력
	node->llink = node->rlink = NULL;//노드의 왼쪽 링크와 오른쪽 링크 0

	if (h->first == NULL)//만약 첫 노드가 0이면
	{
		h->first = node;//첫노드에 입력받은 노드 입력
		return 0;
	}

	listNode* n = h->first;//노드 n 은 첫노드 입력

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {//끝까지 반복
		if(n->key >= key) {//현재 노드의 값이 입력받은 키보다 크면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {//n이 첫노드일 경우
				insertFirst(h, key);//첫 노드에 입력 
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;//노드의 다음 값을 n 입력
				node->llink = n->llink;//노드의 전 값에 n의 전노드 입력
				n->llink->rlink = node;//n의 전 링크에 다음링크는 노드
			}
			return 0;
		}

		n = n->rlink;//n은 다음 노드로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);//찾지 못한경우 마지막에 삽입
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {//노드 삭제 함수

	if (h->first == NULL)//첫 노드가 0이면
	{
		printf("nothing to delete.\n");//삭제할 노드가 없음을 출력
		return 1;
	}

	listNode* n = h->first;//노드 n을 첫 노드로 초기화

	while(n != NULL) {//끝까지 반복
		if(n->key == key) {//현재 키 값이 입력받은 키값이면
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);//첫번째 노드 삭제
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h);//마지막 노드 삭제
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;//n의 전링크를 n의 다음링크로 연결
				n->rlink->llink = n->llink;//n의 다음링크의 전 링크를 n의 전 링크로 연결
				free(n);//n의 메모리 초기화
			}
			return 1;
		}

		n = n->rlink;//n은 다음링크로 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);//찾지못함을 출력
	return 1;
}


