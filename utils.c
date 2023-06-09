/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfaramel <vfaramel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 04:11:14 by vfaramel          #+#    #+#             */
/*   Updated: 2023/05/11 05:22:13 by vfaramel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	quit(t_settings *settings)
{
	free(settings);
	exit (0);
}

int	ft_isdigit(char *s)

{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] < '0' || '9' < s[i])
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	tot;
	int	n;

	tot = 0;
	i = 0;
	n = 1;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			n *= -1;
		i++;
	}
	while (48 <= str[i] && str[i] <= 57)
	{
		tot = str[i] - 48 + (tot * 10);
		i++;
	}
	return (tot * n);
}

void	get_settings(int argc, char **argv, t_settings *settings)
{
	int				i;
	pthread_mutex_t	settings_mutex;

	i = 0;
	while (++i < argc)
	{
		if (!ft_isdigit(argv[i]))
			quit(settings);
	}
	pthread_mutex_init(&settings_mutex, NULL);
	settings->num_of_philo = ft_atoi(argv[1]);
	settings->time_to_die = ft_atoi(argv[2]);
	settings->time_to_eat = ft_atoi(argv[3]);
	settings->time_to_sleep = ft_atoi(argv[4]);
	settings->max_meals = -1;
	if (argc == 6)
		settings->max_meals = ft_atoi(argv[5]);
	settings->max_meals_count = 0;
	settings->settings_mutex = &settings_mutex;
}
