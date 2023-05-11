/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfaramel <vfaramel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 00:28:37 by vfaramel          #+#    #+#             */
/*   Updated: 2023/05/11 04:57:50 by vfaramel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks(t_philo *philo, long start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(philo->fork_1);
	printf("%ld %d has taken a fork\n", ((current_time.tv_sec * 1000)
			+ (current_time.tv_usec / 1000)) - start_time, philo->num);
	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(philo->fork_2);
	printf("%ld %d has taken a fork\n", ((current_time.tv_sec * 1000)
			+ (current_time.tv_usec / 1000)) - start_time, philo->num);
}

void	eat(t_philo *philo, long start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	pthread_mutex_lock(philo->this_philo_mutex);
	philo->last_meal = current_time.tv_usec;
	pthread_mutex_unlock(philo->this_philo_mutex);
	printf("%ld %d is eating\n", ((current_time.tv_sec * 1000)
			+ (current_time.tv_usec / 1000)) - start_time, philo->num);
	philo->tot_meals++;
	if (philo->tot_meals == philo->settings->max_meals)
	{
		pthread_mutex_unlock(philo->fork_1);
		pthread_mutex_unlock(philo->fork_2);
		pthread_mutex_lock(philo->settings->settings_mutex);
		philo->settings->max_meals_count++;
		pthread_mutex_unlock(philo->settings->settings_mutex);
		pthread_exit(0);
	}
	ft_usleep(philo->settings->time_to_eat);
}

void	rest(t_philo *philo, long start_time)
{
	struct timeval	current_time;

	pthread_mutex_unlock(philo->fork_1);
	pthread_mutex_unlock(philo->fork_2);
	gettimeofday(&current_time, NULL);
	printf("%ld %d is sleeping\n", ((current_time.tv_sec * 1000)
			+ (current_time.tv_usec / 1000)) - start_time, philo->num);
	ft_usleep(philo->settings->time_to_sleep);
	gettimeofday(&current_time, NULL);
	printf("%ld %d is thinking\n", ((current_time.tv_sec * 1000)
			+ (current_time.tv_usec / 1000)) - start_time, philo->num);
}

void	*eat_sleep_die(void *arg)
{
	t_philo			*philo;
	long			start_time;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->this_philo_mutex);
	pthread_mutex_unlock(philo->this_philo_mutex);
	philo->last_meal = philo->settings->start_time.tv_usec;
	start_time = (philo->settings->start_time.tv_sec * 1000)
		+ philo->settings->start_time.tv_usec / 1000;
	if (philo->num % 2 == 1)
		ft_usleep(50);
	while (1)
	{
		take_forks(philo, start_time);
		eat(philo, start_time);
		rest(philo, start_time);
	}
}
