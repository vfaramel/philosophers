/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfaramel <vfaramel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 04:06:41 by vfaramel          #+#    #+#             */
/*   Updated: 2023/05/05 08:42:48 by vfaramel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*eat_sleep_die(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("%d\n", philo->num);
	usleep(philo->num * 1000000);
	printf("%d\n", philo->num);
	return (NULL);
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

int	main(int argc, char **argv)
{
	t_settings		*settings;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	t_philo			*philosophers;
	int				i;

	if (argc < 5 || 6 < argc)
		return (0);
	settings = malloc(5 * sizeof(int));
	get_settings(argc, argv, settings);
	forks = malloc(settings->num_of_philo * sizeof(pthread_mutex_t));
	philosophers = malloc(settings->num_of_philo * sizeof(t_philo));
	threads = malloc(settings->num_of_philo * sizeof(pthread_t));
	assign_forks(forks, philosophers, settings);
	i = -1;
	printf("ciao\n");
	while (++i < settings->num_of_philo)
		pthread_create(&threads[i], NULL, eat_sleep_die, (void *)&philosophers[i]);
	i = 0;
	while (i < settings->num_of_philo)
		pthread_join(threads[i++], NULL);
	free(forks);
	free(philosophers);
	quit(settings);
}
