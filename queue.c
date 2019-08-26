#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define number_size 100

struct target
{
	int number;
	struct target* next;	
};

struct queue
{
	struct target* head;
	int num;
	struct target* (*pop)(struct queue* temp);
	void (*push)(struct queue* temp, struct target* target_temp);
	void (*clear_queue)(struct queue* temp);
};

void clear_queue(struct queue* temp)
{
	struct target* target_temp = NULL;
	for(int i = 0; i < temp->num; i++){
		target_temp = temp->pop(temp);
		free(target_temp);
	}
}

struct target* pop(struct queue* temp)
{
	if(temp->num == 0)
		return NULL;
	struct target* target_temp = temp->head;
	temp->head = temp->head->next;
	temp->num--;
	return target_temp;
}

void push(struct queue* temp, struct target* target_temp)
{
	if(temp->head == NULL){
		temp->head = target_temp;
		temp->num++;
		return;
	}
	struct target* node = temp->head;
	while(node->next != NULL) node = node->next;
	node->next = target_temp;
	temp->num++;
}

int main()
{
	struct queue* main_queue;
	main_queue = (struct queue*)calloc(1, sizeof(struct queue));

	main_queue->head = NULL;
	main_queue->num = 0;
	main_queue->pop = pop;
	main_queue->push = push;
	main_queue->clear_queue = clear_queue;

	srand((unsigned int)time(0));
	printf("Queue start\n");
	
	for(int i = 0; i < number_size; i++){
		struct target* node = NULL;
		node = (struct target*)calloc(1, sizeof(struct target));
		node->number = rand() % 1000;
		printf("%d ", node->number);
		main_queue->push(main_queue, node);
	}
	printf("\n");

	printf("Pops..\n");

	for(int i = 0; i < number_size; i++){
		struct target* node = NULL;
		node= main_queue->pop(main_queue);
		printf("%d ", node->number);
		free(node);
	}
	printf("\n");
	
	main_queue->clear_queue(main_queue);
	return 0;
}
