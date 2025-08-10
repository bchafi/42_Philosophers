/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 23:03:54 by bchafi            #+#    #+#             */
/*   Updated: 2025/08/10 14:27:47 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void f(){system("leaks philo");}

long get_time_in_ms()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void cpu_sleep(long duration_ms, int someone_died)
{
    long start = get_time_in_ms();
    while ((get_time_in_ms() - start) < duration_ms)
    {
        if(someone_died)
            return;
        usleep(100);
    }

}

void print_action(t_philo *philo, char *msg)
{
    long time;
    int died;
    // atexit(f);
    if (!msg)
    {
        write(2, "Warning: NULL message passed to print_action!\n", 47);
        return ;
    }
    time = get_time_in_ms() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->death_lock);
    died = philo->data->someone_died;
    pthread_mutex_unlock(&philo->data->death_lock);

    pthread_mutex_lock(&philo->data->print_lock);
    if (!died || (msg[0] == 'd' && !strncmp(msg, "died", 4)))
        printf("%ld %d %s\n", time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->print_lock);
}

void think(t_philo *philo)
{
    print_action(philo, "is thinking");
}

void take_forks(t_philo *philo)
{

        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken a fork");
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken a fork");
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->meal_lock);
    philo->last_meal = get_time_in_ms();
    pthread_mutex_unlock(&philo->meal_lock);

    print_action(philo, "is eating");
    long start = get_time_in_ms();
    while (get_time_in_ms() - start < philo->data->time_to_eat)
    {
        pthread_mutex_lock(&philo->data->death_lock);
        int died = philo->data->someone_died;
        pthread_mutex_unlock(&philo->data->death_lock);
        if (died)
            return;
        usleep(100);
    }
    pthread_mutex_lock(&philo->meal_lock);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_lock);
}

void put_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void sleep_philo(t_philo *philo)
{
    print_action(philo, "is sleeping");
    long start = get_time_in_ms();
    while (get_time_in_ms() - start < philo->data->time_to_sleep)
    {
        pthread_mutex_lock(&philo->data->death_lock);
        int died = philo->data->someone_died;
        pthread_mutex_unlock(&philo->data->death_lock);
        if (died)
            return;
        usleep(100);
    }
}

void *monitor_routine(void *data_ptr)
{
    t_data *data = (t_data *)data_ptr;
    int i, all_full;

    while (1)
    {
        i = 0;
        all_full = 1;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(&data->philos[i].meal_lock);
            long time_since_meal = get_time_in_ms() - data->philos[i].last_meal;
            int meals = data->philos[i].meals_eaten;
            pthread_mutex_unlock(&data->philos[i].meal_lock);
            pthread_mutex_lock(&data->death_lock);
            if (data->someone_died)
            {
                pthread_mutex_unlock(&data->death_lock);
                return NULL;
            }
            if (time_since_meal > data->time_to_die)
            {
                data->someone_died = 1;
                pthread_mutex_unlock(&data->death_lock);
                print_action(&data->philos[i], "died");
                return NULL;
            }
            pthread_mutex_unlock(&data->death_lock);
            if (data->meals_required != -1 && meals < data->meals_required)
                all_full = 0;
            i++;
        }
        if (data->meals_required != -1 && all_full)
        {
            pthread_mutex_lock(&data->death_lock);
            data->someone_died = 1;
            pthread_mutex_unlock(&data->death_lock);
            return NULL;
        }
        usleep(1000);
    }
    return NULL;
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->data->num_philos == 1)
    {
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken a fork");
        long start = get_time_in_ms();
        while (get_time_in_ms() - start < philo->data->time_to_die)
        {
            pthread_mutex_lock(&philo->data->death_lock);
            int died = philo->data->someone_died;
            pthread_mutex_unlock(&philo->data->death_lock);
            if (died)
                break;
            usleep(100);
        }
        pthread_mutex_unlock(philo->right_fork);
        return (NULL);
    }
    if (philo->id % 2 != 0)
    {
        long start = get_time_in_ms();
        while (get_time_in_ms() - start < 1)
        {
            pthread_mutex_lock(&philo->data->death_lock);
            int died = philo->data->someone_died;
            pthread_mutex_unlock(&philo->data->death_lock);
            if (died)
                break;
            usleep(100);
        }
    }
        usleep(200);
    while (1)
    {
        pthread_mutex_lock(&philo->data->death_lock);
        int died = philo->data->someone_died;
        pthread_mutex_unlock(&philo->data->death_lock);
        if (died)
            break;

        take_forks(philo);
        eat(philo);
        put_forks(philo);
        sleep_philo(philo);
        think(philo);
    }
    return (NULL);
}

int create_threads(t_data *data)
{
    int i = 0;
    while (i < data->num_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, &data->philos[i]))
        {
            while (--i > 0)
                pthread_join(data->philos[i].thread, NULL);
            write(2, "Failed to create thread for philosopher\n", 41);
            return (0);
        }
        i++;
    }
    return (1);
}

int main(int ac, char **av)
{
    t_data  *d_dataP;
    int     i;
    pthread_t monitor;

    d_dataP = malloc(sizeof(t_data));
    if (!d_dataP)
        return (0);
    ft_memset(d_dataP, 0, sizeof(t_data));
    av = initializer(ac, av, d_dataP);
    if (!av)
        return (free(d_dataP), 1);
    d_dataP->start_time = get_time_in_ms();
    i = -1;
    while (++i < d_dataP->num_philos)
        d_dataP->philos[i].last_meal = d_dataP->start_time;
    if (!create_threads(d_dataP))
        return (free_to_exit(av, d_dataP), 0);

    if (pthread_create(&monitor, NULL, monitor_routine, d_dataP))
    {
        pthread_join(monitor, NULL);
        return (free_to_exit(av, d_dataP), 0);
    }
    i = 0;
    while (i < d_dataP->num_philos)
    {
        pthread_join(d_dataP->philos[i].thread, NULL);
        i++;
    }
    pthread_join(monitor, NULL);
    free_to_exit(av, d_dataP);
    return 0;
}