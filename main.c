/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfaramel <vfaramel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 04:06:41 by vfaramel          #+#    #+#             */
/*   Updated: 2023/05/11 05:21:52 by vfaramel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	assign_forks(pthread_mutex_t *forks, t_philo *philosophers,
t_settings *settings)
{
	int	i;

	i = 0;
	while (i < settings->num_of_philo * 2)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < settings->num_of_philo)
	{
		philosophers[i].num = i + 1;
		philosophers[i].fork_1 = &forks[i];
		if (i != settings->num_of_philo - 1)
			philosophers[i].fork_2 = &forks[i + 1];
		philosophers[i].tot_meals = 0;
		philosophers[i].this_philo_mutex
			= &forks[i + settings->num_of_philo];
		philosophers[i++].settings = settings;
	}
	philosophers[i - 1].fork_2 = &forks[0];
}

void	start_threads(t_settings *settings,
pthread_t *threads, t_philo *philosophers)
{
	int	i;

	pthread_mutex_lock(settings->settings_mutex);
	pthread_create(&threads[settings->num_of_philo],
		NULL, monitor, (void *)philosophers);
	i = -1;
	while (++i < settings->num_of_philo)
	{
		pthread_mutex_lock((philosophers[i]).this_philo_mutex);
		pthread_create(&threads[i], NULL, eat_sleep_die,
			(void *)&philosophers[i]);
		gettimeofday(&settings->start_time, NULL);
	}
	i = -1;
	while (++i < settings->num_of_philo)
		pthread_mutex_unlock((philosophers[i]).this_philo_mutex);
	pthread_mutex_unlock(settings->settings_mutex);
	pthread_join(threads[settings->num_of_philo], 0);
	i = -1;
	while (++i < settings->num_of_philo)
		pthread_detach(threads[i]);
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
