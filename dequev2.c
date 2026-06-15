#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_QUEUE_SIZE 5
typedef int element;
typedef struct { // 큐 타입
	element  data[MAX_QUEUE_SIZE];
	int  front, rear;
} DequeType;
void error(char *message);
void init_deque(DequeType *q);
int is_full(DequeType *q);
int is_empty(DequeType *q);
void deque_print(DequeType *q);\
void add_rear(DequeType *q, element item);
bool add_front(DequeType *q, element val);
element delete_rear(DequeType *q);
element delete_front(DequeType *q);
element get_rear(DequeType *q);
element get_front(DequeType *q);

int main(void)
{
	DequeType queue;

	init_deque(&queue);
	for (int i = 0; i < 5; i++) {
		add_front(&queue, i);
		if(is_full(&queue)) { 
			deque_print(&queue);
			printf("큐가 포화상태입니다, 데이터 추가할 수 없습니다\n");
			
			printf("----------------------------------\n");
			printf("큐가 포화상태입니다, 데이터를 뒤에서부터 삭제 합니다\n");
			for (int i = 0; i < 3; i++) {

				delete_rear(&queue);
				deque_print(&queue);
			}
			printf("----------------------------------\n");
			break;
		}
		else deque_print(&queue);
	}
	printf("큐 뒷쪽에 값을 두 개 추가합니다.\n");
	printf("add rear() with the index of rear=%d, data=%d\n", queue.rear, 5);
	add_rear(&queue, 5);deque_print(&queue);
	printf("add rear() with the index of rear=%d, data=%d\n", queue.rear, 4);
	add_rear(&queue, 4);deque_print(&queue);
	printf("----------------------------------\n");
	while(!is_empty(&queue)){
		printf("Delete all remaining data from the rear of the queue\n");
		delete_rear(&queue);
		deque_print(&queue);
		
	}
	return 0;
}

// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	//exit(1);
	return;
}

// 초기화 
void init_deque(DequeType *q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(DequeType *q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(DequeType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
// 원형큐 출력 함수
void deque_print(DequeType *q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
	int test = is_empty(q);
	if (test) printf(" this deque is empty");
	if (!test) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear){
				
				break;
			}
		} while (i != q->front);
	}
	printf("\n");
}

bool add_front(DequeType *q, element val)
{
	if (is_full(q)){
		printf("큐가 포화상태입니다, 데이터 추가할 수 없습니다\n");
		return true;
	}
	else{
		printf("add front() with the index of front=%d, data=%d\n", q->front, val);
		q->data[q->front] = val;
		q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
		return false;
	}
}

// 삭제 함수
element delete_front(DequeType *q)
{
	if (is_empty(q)){
		printf("큐가 공백상태입니다, 데이터를 삭제 할 수 없습니다.\n");
		return -1;
	}
	else{

		q->front = (q->front + 1) % MAX_QUEUE_SIZE;
		return q->data[q->front];
	}
}
// 삽입 함수
void add_rear(DequeType *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}
element delete_rear(DequeType *q)
{
	int prev = q->rear;
	if (is_empty(q))
		error("큐가 공백상태입니다");
	printf("delete_rear() with the index of rear=%d, data=%d\n", q->rear, q->data[prev]);
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	
	return q->data[prev];
}


// 삭제 함수
element get_front(DequeType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}


element get_rear(DequeType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	return q->data[q->rear];
}
