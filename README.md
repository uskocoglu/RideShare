# RideShare

NOTE: This program works only for One Band (e.g. 2 threads for A, 2 threads for B)

```
Ridesharing func(){
    Sem1wait
    Looking for a car
    Sem1post
    Barrier1
    Sem2wait
    Found a spot in a car
    Sem2post
    Barrier2
    Sem3wait
    Captain of the car
    Sem3post
}
```


In this programming assignment, I used 3 pthreads semaphores and 2 pthreads barriers. In the first step each thread prints that they are looking for a car to ride. The first semaphore is used here to provide that each thread is announcing this statement sequentially so that an order is ensured. After this step, the threads are stopped using a barrier which has a limit of 4 threads. After 4 threads came, the threads are starting the race together to find a spot in the car. In order to prevent the race condition, another semaphore is used. After each thread found a spot in the car, they are stopped using another barrier. When all threads came to this barrier, they are all released to become the captain of the car. In order to prevent the race condition, the last semaphore is used and only the thread which acquired the semaphore first will be the captain and driving the car. There is no deadlock situation and my implementation is correct because the main thread waits for all child threads to finish and also the output format of the fan threads is also correct.
