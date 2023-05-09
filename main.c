/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfaramel <vfaramel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 04:06:41 by vfaramel          #+#    #+#             */
/*   Updated: 2023/05/09 12:07:44 by vfaramel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*eat_sleep_die(void *arg)
{
	t_philo			*philo;
	struct timeval	current_time;
	long			start_time;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->settings->threads_created == philo->settings->num_of_philo)
			break ;
	}
	philo->last_eat = philo->settings->start_time.tv_usec;
	start_time = (philo->settings->start_time.tv_sec * 1000) + philo->settings->start_time.tv_usec / 1000;
	if (philo->num % 2 == 1)
		ft_usleep(50);
	while (1)
	{
		gettimeofday(&current_time, NULL);
		pthread_mutex_lock(philo->fork_1);
		printf("%ld %d has taken a fork\n", ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - start_time, philo->num);
		gettimeofday(&current_time, NULL);
		pthread_mutex_lock(philo->fork_2);
		printf("%ld %d has taken a fork\n", ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - start_time, philo->num);
		gettimeofday(&current_time, NULL);
		philo->last_eat = current_time.tv_usec;
		printf("%ld %d is eating\n", ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - start_time, philo->num);
		ft_usleep(philo->settings->time_to_eat);
		pthread_mutex_unlock(philo->fork_1);
		pthread_mutex_unlock(philo->fork_2);
		gettimeofday(&current_time, NULL);
		printf("%ld %d is sleeping\n", ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - start_time, philo->num);
		ft_usleep(philo->settings->time_to_sleep);
		gettimeofday(&current_time, NULL);
		printf("%ld %d is thinking\n", ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - start_time, philo->num);
	}
}

void	assign_forks(pthread_mutex_t *forks, t_philo *philosophers, t_settings *settings)
{
	int	i;

	i = 0;
	while (i < settings->num_of_philo)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < settings->num_of_philo)
	{
		philosophers[i].num = i + 1;
		philosophers[i].fork_1 = &forks[i];
		if (i != settings->num_of_philo - 1)
			philosophers[i].fork_2 = &forks[i + 1];
		philosophers[i++].settings = settings;
	}
	philosophers[i - 1].fork_2 = &forks[0];
}

void	start_threads(t_settings *settings,
pthread_t *threads, t_philo *philosophers)
{
	int	i;

	pthread_create(&threads[settings->num_of_philo],
		NULL, monitor, (void *)philosophers);
	i = -1;
	while (++i < settings->num_of_philo)
	{
		pthread_create(&threads[i], NULL, eat_sleep_die,
			(void *)&philosophers[i]);
		gettimeofday(&settings->start_time, NULL);
		settings->threads_created++;
	}
	pthread_join(threads[settings->num_of_philo], 0);
}

int	main(int argc, char **argv)
{
	t_settings		*settings;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philosophers;

	if (argc < 5 || 6 < argc)
		return (0);
	settings = malloc(sizeof(t_settings));
	get_settings(argc, argv, settings);
	forks = malloc((settings->num_of_philo) * sizeof(pthread_mutex_t));
	philosophers = malloc(settings->num_of_philo * sizeof(t_philo));
	threads = malloc((1 + settings->num_of_philo) * sizeof(pthread_t));
	assign_forks(forks, philosophers, settings);
	start_threads(settings, threads, philosophers);
	free(forks);
	free(philosophers);
	quit(settings);
}
