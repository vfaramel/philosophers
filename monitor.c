/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfaramel <vfaramel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 07:31:26 by vfaramel          #+#    #+#             */
/*   Updated: 2023/05/09 12:05:08 by vfaramel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(int time)
{
	struct timeval	start_time;
	struct timeval	last_time;
	// long			long_time;

	gettimeofday(&start_time, NULL);
	gettimeofday(&last_time, NULL);
	// long_time = (long)time / 1000;
	while (((last_time.tv_sec * 1000) + (last_time.tv_usec / 1000)) - ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000)) < time)
	{
		// printf("%ld %d\n", ((last_time.tv_sec * 1000) + (last_time.tv_usec / 1000)) - ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000)), time);
		usleep(100);
		gettimeofday(&last_time, NULL);
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
			if (current_time.tv_usec - (philosophers + i)->last_eat
				> settings->time_to_die * 1000)
			{
				printf("%ld %d died\n", ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000)) - ((settings->start_time.tv_sec * 1000) + (settings->start_time.tv_usec / 1000)),
					(philosophers + i)->num);
				pthread_exit(0);
			}
		}
	}
}

void	*monitor(void *arg)
{
	t_philo			*philosophers;
	t_settings		*settings;

	philosophers = (t_philo *)arg;
	settings = philosophers->settings;
	while (1)
	{
		if (settings->threads_created == settings->num_of_philo)
			break ;
	}
	ft_usleep(settings->time_to_die);
	check_death(settings, philosophers);
	return (NULL);
}
