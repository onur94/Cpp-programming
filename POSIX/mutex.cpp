#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;
  
pthread_t pthread1, pthread2;
pthread_mutex_t lock;
  
void *thread_function(void *arg)
{
    char id = *(char *)arg;

    pthread_mutex_lock(&lock);
    cout << "Task-" << id << " has started" << endl;
    sleep(2);
    cout << "Task-" << id << " has finished" << endl;
    pthread_mutex_unlock(&lock);
    
    return NULL;
}
  
int main(void)
{
    if (pthread_mutex_init(&lock, NULL) != 0) {
        cout << "Mutex init has failed" << endl;
        return 1;
    }
  
    pthread_create(&pthread1, NULL, thread_function, (void *)"1");
    pthread_create(&pthread2, NULL, thread_function, (void *)"2");

    pthread_join(pthread1, NULL);
    pthread_join(pthread2, NULL);
    pthread_mutex_destroy(&lock);
  
    return 0;
}