#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
/*typedef struct message{
long mtype;
char buffer[messagesize];
}; */
sem_t empty;
sem_t full;
int t=4;
int buffersize[2]; 
int counter=0;
int i;
pthread_mutex_t my_mutex;
void*messages(void*argv){

counter=(int)argv;
for(i=0;i<5;i++){
pthread_mutex_lock(&my_mutex);
counter++;
printf("thread %d" ,i);
printf(": received a message \n");
sleep(t);
pthread_mutex_unlock(&my_mutex);
}
}
void*producer(void*argv){
//int m;
printf("Waiting to read buffer \n ");
sleep(3);
int temp=counter;
printf("Monitor thread reads the counter of value %d" ,temp);
printf("\n");
sem_wait(&empty);
buffersize[i]=counter;
//printf("reading to buffersize %d" , buffersize[i]);
//printf("\n");
//sleep(1);
i++;
counter=0;
sem_post(&full);
}
void*consumer(void*argv){
sleep(4);
i--;
printf("Waiting to write the buffer \n");
if(buffersize[i]==0)
printf("Nothing in the buffer \n");
else
sem_wait(&full);
printf("Mcollector threads writes buffersize value %d" ,buffersize[i]);
printf(" at index  %d \n" ,i);

sem_post(&empty);
}
void main(){
pthread_t producer_id;
pthread_t consumer_id;
pthread_t message_id;
sem_init(&empty, 1 , 1);
sem_init(&full , 1, 0);
pthread_attr_t attr;
pthread_attr_init(&attr);
pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);
pthread_create(&message_id,&attr,messages,NULL);
sleep(1);
pthread_create(&producer_id,&attr,producer,NULL);
pthread_create(&consumer_id,&attr,consumer,NULL);
pthread_join(message_id,NULL);
pthread_join (producer_id,NULL);
pthread_join(consumer_id,NULL);
}
