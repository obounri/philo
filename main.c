/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 17:10:41 by obounri           #+#    #+#             */
/*   Updated: 2021/10/31 17:38:20 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	status(t_table *table, int id_philo, char *string, int c)
{
	pthread_mutex_lock(&table->std_o);
	if (table->death)
	{
		printf("%ld %d %s\n", curr_time() - table->t_start, id_philo, string);
		if (c == 1)
			printf("%ld %d %s\n",
				curr_time() - table->t_start, id_philo, "is eating");
	}
	pthread_mutex_unlock(&table->std_o);
}

void	*eat_count(void *data)
{
	t_table	*table;
	t_philo	*philos;
	int		ate;
	int		i;

	table = (t_table *)data;
	philos = table->philos;
	ate = 0;
	while (ate != table->n_philos)
	{
		i = 0;
		ate = 0;
		while (i < table->n_philos)
		{
			if (philos[i].n_ate == table->n_must_eat)
				ate++;
			i++;
		}
	}
	pthread_mutex_unlock(&table->philo_dead);
	table->death = 0;
	return (NULL);
}

void	create_threads_mutex(t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->std_o, NULL);
	pthread_mutex_init(&table->philo_dead, NULL);
	pthread_mutex_lock(&table->philo_dead);
	while (i < table->n_philos)
		pthread_mutex_init(&table->forks[i++].fork, NULL);
	i = 0;
	while (i < table->n_philos)
	{
		philos[i].table = table;
		philos[i].id_philo = i + 1;
		philos[i].n_ate = 0;
		pthread_create(&philos[i].philo, NULL, &routine, &philos[i]);
		pthread_detach(philos[i].philo);
		i++;
		usleep(100);
	}
	if (table->n_must_eat > 0)
	{
		pthread_create(&table->count, NULL, &eat_count, table);
		pthread_detach(table->count);
	}
}

int	main(int ac, char **av)
{
	t_table	table;
	t_philo	*philos;
	int		i;

	if (ac == 5 || ac == 6)
	{
		i = 0;
		if (!init_store_options(&table, av))
			ft_error("Error: Wrong args.\n");
		philos = malloc(sizeof(t_philo) * table.n_philos);
		table.forks = malloc(sizeof(t_fork) * table.n_philos);
		table.philos = philos;
		create_threads_mutex(&table, philos);
		pthread_mutex_lock(&table.philo_dead);
		pthread_mutex_unlock(&table.philo_dead);
		pthread_mutex_destroy(&table.std_o);
		pthread_mutex_destroy(&table.philo_dead);
		while (i < table.n_philos)
			pthread_mutex_destroy(&table.forks[i++].fork);
	}
	else
		ft_error("Error: Wrong args.\n");
	return (0);
}
