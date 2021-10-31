/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_store.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 17:20:53 by obounri           #+#    #+#             */
/*   Updated: 2021/10/31 17:22:51 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_error(char *error)
{
	ft_putstr_fd(error, 2);
	exit(EXIT_FAILURE);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

void	store_arg(t_table *options, char *opt)
{
	if (options->n_philos == -1)
		options->n_philos = ft_atoi(opt);
	else if (options->t_die == -1)
		options->t_die = ft_atoi(opt);
	else if (options->t_eat == -1)
		options->t_eat = ft_atoi(opt);
	else if (options->t_sleep == -1)
		options->t_sleep = ft_atoi(opt);
	else if (options->n_must_eat == -1)
		options->n_must_eat = ft_atoi(opt);
}

int	init_store_options(t_table *options, char **av)
{
	int	i;

	i = 1;
	options->n_philos = -1;
	options->t_die = -1;
	options->t_eat = -1;
	options->t_sleep = -1;
	options->n_must_eat = -1;
	options->death = 1;
	while (av[i])
	{
		if (!ft_isnumber(av[i]))
			return (0);
		else
			store_arg(options, av[i]);
		i++;
	}
	options->t_start = curr_time();
	return (1);
}

long int	curr_time(void)
{
	struct timeval	time;
	long int		curr;

	gettimeofday(&time, NULL);
	curr = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (curr);
}
