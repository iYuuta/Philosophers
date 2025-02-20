#ifndef PHILOSOPHERS
#define PHILOSOPHERS

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "utils/utils.h"

typedef struct s_fork {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int in_use;
} t_fork;

typedef struct s_philo
{
    int             id;
    pthread_t       thread;
    t_fork          *right_fork;
    t_fork          *left_fork;
    struct s_philo  *next;
    struct s_philo  *prev;
}       t_philo;

#endif