/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfaramel <vfaramel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 07:31:26 by vfaramel          #+#    #+#             */
/*   Updated: 2023/05/11 04:55:08 by vfaramel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(int time)
{
	struct timeval	start_time;
	struct timeval	current_time;

	gettimeofday(&start_time, NULL);
	gettimeofday(&current_time, NULL);
	while (((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000))
		- ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000)) < time)
	{
		usleep(100);
		gettimeofday(&current_time, NULL);
	}
}

void	check_death(t_settings *settings, t_philo *philosophers)
{
	int				i;
	struct timeval	current_time;

	while (1)
	{
		i = -1;
		while (++i < settings->num_of_philo)
		{
			gettimeofday(&current_time, NULL);
			pthread_mutex_lock((philosophers + i)->this_philo_mutex);
			if (current_time.tv_usec - (philosophers + i)->last_meal
				> settings->time_to_die * 1000)
			{
				printf("%ld %d died\n", ((current_time.tv_sec * 1000)
						+ (current_time.tv_usec / 1000))
					- ((settings->start_time.tv_sec * 1000)
						+ (settings->start_time.tv_usec / 1000)),
					(philosophers + i)->num);
				pthread_exit(0);
			}
			pthread_mutex_unlock((philosophers + i)->this_philo_mutex);
		}
		pthread_mutex_lock(settings->settings_mutex);
		if (settings->max_meals_count == settings->num_of_philo)
		{
			printf("philosophers have eaten enough\n");
			pthread_exit(0);
		}
		pthread_mutex_unlock(settings->settings_mutex);
	}
}

void	*monitor(void *arg)
{
	t_philo			*philosophers;
	t_settings		*settings;

	philosophers = (t_philo *)arg;
	settings = philosophers->settings;
	pthread_mutex_lock(settings->settings_mutex);
	pthread_mutex_unlock(settings->settings_mutex);
	ft_usleep(settings->time_to_die);
	check_death(settings, philosophers);
	return (NULL);
}
