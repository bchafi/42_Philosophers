/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bader <bader@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:11:20 by bader             #+#    #+#             */
/*   Updated: 2025/04/09 13:51:23 by bader            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
long get_time_in_ms()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

t_data *init_data(t_data *data, char **args)
{
    if (!args)
    {
        free(data);
        data = NULL;
        ft_puterror_fd("Has No Argument !!");
    }

    data->meals_required = -1;
    data->num_philos = ft_atoi(args[0]);
    data->time_to_die = ft_atoi(args[1]);
    data->time_to_eat = ft_atoi(args[2]);
    data->time_to_sleep = ft_atoi(args[3]);

    if (args[4])
        data->meals_required = ft_atoi(args[4]);

    pthread_mutex_init(&data->print_lock, NULL);
    data->start_time = get_time_in_ms();
    data->someone_died = 0;
    return data;
}
t_data *init_philos(t_data *d_dataP)
{
    int i = 0;
    while (i < d_dataP->num_philos)
    {
        d_dataP->philos[i].id = i + 1;
        d_dataP->philos[i].left_fork = &d_dataP->forks[i];
        d_dataP->philos[i].right_fork = &d_dataP->forks[(i + 1) % d_dataP->num_philos];
        d_dataP->philos[i].meals_eaten = 0;
        d_dataP->philos[i].last_meal = get_time_in_ms();
        d_dataP->philos[i].data = d_dataP;
        pthread_mutex_init(&d_dataP->philos[i].meal_lock, NULL);
        i++;
    }
    return d_dataP;
}


char** half_main(int ac, char **av, t_data *d_dataP)
{
	int i;

	if (ac < 2)
	{
		printf("Argumenta Is Less Then Two Args!!");
		exit(1);
	}
	av = parcing(av);
	d_dataP = init_data(d_dataP, av);
	d_dataP->forks = malloc(sizeof(pthread_mutex_t) * d_dataP->num_philos);
	if (!d_dataP->forks)
	{
		free(d_dataP);
		exit(1);
	}
	i = 0;
	while (i < d_dataP->num_philos)
		pthread_mutex_init(&d_dataP->forks[i++], NULL);
	d_dataP->philos = malloc(sizeof(t_philo) * d_dataP->num_philos);
	if (!d_dataP->philos)
	{
		free(d_dataP);
		free(d_dataP->forks);
		exit(1);
	}
	init_philos(d_dataP);
	return (av);
}

void print_action(t_philo *philo, char *msg)
{
    if (!msg)
    {
        printf("Warning: NULL message passed to print_action!\n");
        return;
    }
    long time = get_time_in_ms() - philo->data->start_time;
    pthread_mutex_lock(&philo->data->print_lock);
    if (!philo->data->someone_died)
        printf("%ld %d %s\n", time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->print_lock);
}


void think(t_philo *philo)
{
    if (!philo->left_fork || !philo->right_fork)
        print_action(philo, "is thinking");
}

void take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken left fork");
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken right fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_action(philo, "has taken left fork");
        pthread_mutex_lock(philo->right_fork);
        print_action(philo, "has taken right fork");
    }
}

void eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time_in_ms();
	printf("%ld %d is eating\n", philo->last_meal - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(&philo->data->print_lock);

	usleep(philo->data->time_to_eat * 1000);
	philo->meals_eaten++;
}

void put_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void sleep_philo(t_philo *philo)
{
	print_action(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 == 0)
    {
        usleep(500);
    }

    while (!philo->data->someone_died)
    {
        // Check if the philosopher has died
        long time_since_last_meal = get_time_in_ms() - philo->last_meal;
        if (time_since_last_meal > philo->data->time_to_die)
        {
            philo->data->someone_died = 1;
            print_action(philo, "died");
            break;
        }

        if (philo->data->meals_required != -1 && philo->meals_eaten >= philo->data->meals_required)
        {
            print_action(philo, "has finished eating the required meals");
            break;
        }
		
        think(philo);
        take_forks(philo);
        eat(philo);
        put_forks(philo);
        sleep_philo(philo);
    }
    return NULL;
}


void create_threads(t_data *data)
{
    int i = 0;

    data->start_time = get_time_in_ms();
    while (i < data->num_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]) != 0)
            printf("Failed to create thread for philosopher %d\n", i + 1);
        i++;
    }
}

int main(int ac, char **av)
{
    t_data *d_dataP;
    int i;

    d_dataP = malloc(sizeof(t_data));
    if (!d_dataP)
        exit(1);
    memset(d_dataP, 0, sizeof(t_data));

    printf("Initialize arguments ...\n");
    av = half_main(ac, av, d_dataP);

    printf("Create threads ...\n");
    create_threads(d_dataP);

    // Wait for all philosopher threads to finish
    i = 0;
    while (i < d_dataP->num_philos)
    {
        pthread_join(d_dataP->philos[i++].thread, NULL);
    }

    printf("Cleaning up...\n");
    free_to_exit(av, d_dataP);
    return 0;
}

