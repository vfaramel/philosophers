/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfaramel <vfaramel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 04:13:41 by vfaramel          #+#    #+#             */
/*   Updated: 2023/05/09 10:38:35 by vfaramel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_settings
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				threads_created;
	int				a_philo_died;
	struct timeval	start_time;
}	t_settings;

typedef struct s_philo
{
	pthread_mutex_t	*fork_1;
	pthread_mutex_t	*fork_2;
	int				num;
	int				last_eat;
	t_settings		*settings;
}	t_philo;

int		ft_atoi(const char *str);
int		ft_isdigit(char *s);
void	get_settings(int argc, char **argv, t_settings *settings);
void	quit(t_settings *settings);
void	*monitor(void *arg);
void	ft_usleep(int time);

#endif
