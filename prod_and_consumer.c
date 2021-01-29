#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<dos.h>
#include<unistd.h>

int buffer[100];
int IN=0, OUT=0;
int N=5;

sem_t mutex;
sem_t empty;
sem_t full;

void *producer(void *arg1)
{
int item;
while(1)
{
item=produce_item();
sem_wait(&empty);
sem_wait(&mutex);
insert_item(item);
sem_post(&mutex);
sem_post(&full);
}
}

void *consumer(void *arg2)
{
int item;
while(1)
{
sem_wait(&full);
sem_wait(&mutex);
item=remove_item();
sem_post(&mutex);
sem_post(&empty);
consume_item(item);
}
}


int insert_item(int item)
{
buffer[IN]=item;
printf("\nProducer is inserting item %d at location %d\n", item, IN);
IN=(IN+1)%N;
system("pause");
printf("\nproducer inserted item %d ....", item);
}

int remove_item()
{
int item;
item=buffer[OUT];
printf("\nConsumer removing item %d from location %d\n", item, OUT);
OUT=(OUT+1)%N;
system("pause");
printf("\nConsumer removed item %d ....", item);
return(item);
}
int produce_item()
{
system("pause");
int itemx= rand();
printf("\nProduced Item %d\n", itemx);
return itemx;

}
int consume_item(int item)
{
printf("\nConsuming Item %d\n", item);
system("pause");
printf("\nConsumer has finished consuming item %d", item);
return item;
}
int main()
{
pthread_t producerthread;
pthread_t consumerthread;
sem_init(&mutex, 0, 1);
sem_init(&empty, 0, N);
sem_init(&full, 0, 0);
pthread_create(&producerthread, NULL, producer, NULL);
pthread_create(&consumerthread, NULL, consumer, NULL);
pthread_join(producerthread, NULL);
pthread_join(consumerthread, NULL);
sem_destroy(&mutex);
sem_destroy(&empty);
sem_destroy(&full);
return 0;
}

