#include "Philosophers.h"

void take_fork(t_fork *fork) {
    pthread_mutex_lock(&fork->mutex);
    while (fork->in_use){
        pthread_cond_wait(&fork->cond, &fork->mutex);  // Wait until fork is available
    }
    fork->in_use = 1;
    pthread_mutex_unlock(&fork->mutex);
}

void put_fork(t_fork *fork) {
    pthread_mutex_lock(&fork->mutex);
    fork->in_use = 0;
    pthread_cond_signal(&fork->cond);  // Notify waiting philosophers
    pthread_mutex_unlock(&fork->mutex);
}

void take_forks(t_philo *philo) {
    pthread_mutex_lock(&philo->left_fork->mutex);
    pthread_mutex_lock(&philo->right_fork->mutex);

    while (philo->left_fork->in_use || philo->right_fork->in_use) {
        pthread_cond_wait(&philo->left_fork->cond, &philo->left_fork->mutex);
        pthread_cond_wait(&philo->right_fork->cond, &philo->right_fork->mutex);
    }

    philo->left_fork->in_use = 1;
    philo->right_fork->in_use = 1;

    printf("Philosopher %d picked up both forks 🍴\n", philo->id);
    pthread_mutex_unlock(&philo->right_fork->mutex);
    pthread_mutex_unlock(&philo->left_fork->mutex);
}

void put_forks(t_philo *philo) {
    pthread_mutex_lock(&philo->left_fork->mutex);
    pthread_mutex_lock(&philo->right_fork->mutex);

    // Release both forks
    philo->left_fork->in_use = 0;
    philo->right_fork->in_use = 0;

    // Notify waiting philosophers
    pthread_cond_signal(&philo->left_fork->cond);
    pthread_cond_signal(&philo->right_fork->cond);

    printf("Philosopher %d put down both forks\n", philo->id);

    pthread_mutex_unlock(&philo->right_fork->mutex);
    pthread_mutex_unlock(&philo->left_fork->mutex);
}

void *philosopher_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;

    while (1) {
        take_forks(philo);

        // Eating
        printf("Philosopher %d is eating 🍝\n", philo->id);
        sleep(1);

        put_forks(philo);

        // Sleeping
        printf("Philosopher %d is sleeping 😴\n", philo->id);
        sleep(2);
    }
    return NULL;
}

int main(int ac, char **av) {
    if (ac != 2) {
        printf("Usage: %s <number_of_philosophers>\n", av[0]);
        return 1;
    }

    int n = atoi(av[1]);
    pthread_t threads[n];
    t_fork forks[n];
    t_philo philos[n];

    // Initialize forks (mutex + condition variable)
    for (int i = 0; i < n; i++) {
        pthread_mutex_init(&forks[i].mutex, NULL);
        pthread_cond_init(&forks[i].cond, NULL);
        forks[i].in_use = 0;
    }

    // Initialize philosophers
    for (int i = 0; i < n; i++) {
        philos[i].id = i + 1;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % n];  // Circular reference
        pthread_create(&threads[i], NULL, philosopher_routine, &philos[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < n; i++) {
        pthread_join(threads[i], NULL);
    }

    // Cleanup
    for (int i = 0; i < n; i++) {
        pthread_mutex_destroy(&forks[i].mutex);
        pthread_cond_destroy(&forks[i].cond);
    }

    return 0;
}