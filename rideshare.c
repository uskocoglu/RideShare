#define _XOPEN_SOURCE 600   //included to use pthread barriers.
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>

/*
    Name: UTKU SELİM KOÇOĞLU
    Date: 06.12.2021
    Program: Ridesharing between 2 teams
*/

sem_t sem1, sem2, sem3;
pthread_barrier_t barrier1, barrier2;
int teamA = 0;
int teamB = 0;
int captain = 0;
int valid = 0;

void * rideSharing (void * arg){

    char * p = (char *) arg;

    sem_wait(&sem1);

    printf("Thread ID: %ld, Team: %s, I am looking for a car\n", pthread_self(), p); //looking for a car

    if(p == "A"){
        teamA++;
    }
    else{
        teamB++;
    }

    sem_post(&sem1);
    pthread_barrier_wait(&barrier1); 

    sem_wait(&sem2);
    if(teamA == 0 && teamB == 4){
        printf("Thread ID: %ld, Team: %s, I have found a spot in a car\n", pthread_self(), p); //found a spot in a car
        valid++;
    }
    else if(teamA == 4 && teamB == 0){
       printf("Thread ID: %ld, Team: %s, I have found a spot in a car\n", pthread_self(), p); //found a spot in a car
        valid++;
    }
    else if(teamA == 2 && teamB == 2){
        printf("Thread ID: %ld, Team: %s, I have found a spot in a car\n", pthread_self(), p); //found a spot in a car
        valid++;
    }
    else if (teamA == 1 && teamB == 3)
    {
        ;
    }
    else if (teamA == 3 && teamB == 1)
    {
        ;
    }
    sem_post(&sem2);
    pthread_barrier_wait(&barrier2);

    sem_wait(&sem3);

    if (captain == 0 && valid != 0){
        printf("Thread ID: %ld, Team: %s, I am the captain and driving the car\n", pthread_self(), p); //captain in the car
        captain++;
    }

    sem_post(&sem3);
    
    
    
}

int main(int argc, char **argv)
{   
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int i, k;

    if (a+b % 4 != 0 && a%2 != 0 && b%2 != 0){
        ;
    }
    else{
        pthread_t th[4];
        sem_init(&sem1, 0, 1);
        sem_init(&sem2, 0, 1);
        sem_init(&sem3, 0, 1);
        pthread_barrier_init(&barrier1, NULL, 4);
        pthread_barrier_init(&barrier2, NULL, 4);
        for (i = 0; i < a+b; i++)
        {
            if (i<a){
                pthread_create(&th[i], NULL, &rideSharing, "A");
            }
            else{
                pthread_create(&th[i], NULL, &rideSharing, "B");
            }

        }

        for (k = 0; k < a+b; k++)
        {
            pthread_join(th[k], NULL);
        }
        
        

    }
    pthread_barrier_destroy(&barrier1);
    pthread_barrier_destroy(&barrier2);

    printf("The main terminates.\n"); //the main terminates
    return 0;
}