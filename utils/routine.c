/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obounri <obounri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 17:13:56 by obounri           #+#    #+#             */
/*   Updated: 2021/10/31 17:16:14 by obounri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*check_death(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->last_t_ate = curr_time();
	while (1)
	{
		if (curr_time() - philo->last_t_ate > philo->table->t_die + 5)
		{
			status(philo->table, philo->id_philo, "died", 0);
			pthread_mutex_unlock(&philo->table->philo_dead);
			philo->table->death = 0;
			return (NULL);
		}
		usleep(philo->table->t_sleep + philo->table->t_eat);
	}
	return (NULL);
}

void	ph_eat(t_philo	*philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->id_philo - 1].fork);
	status(philo->table, philo->id_philo, "has taken a fork", 0);
	pthread_mutex_lock
		(&philo->table->forks[philo->id_philo % philo->table->n_philos].fork);
	status(philo->table, philo->id_philo, "has taken a fork", 1);
	philo->last_t_ate = curr_time();
	usleep(philo->table->t_eat * 1000);
	philo->n_ate += 1;
	pthread_mutex_unlock(&philo->table->forks[philo->id_philo - 1].fork);
	pthread_mutex_unlock
		(&philo->table->forks[philo->id_philo % philo->table->n_philos].fork);
}

void	*routine(void *data)
{
	t_philo		*philo;
	pthread_t	death;

	philo = (t_philo *)data;
	pthread_create(&death, NULL, &check_death, philo);
	pthread_detach(death);
	while (philo->table->death)
	{
		ph_eat(philo);
		status(philo->table, philo->id_philo, "is sleeping", 0);
		usleep(philo->table->t_sleep * 1000);
		status(philo->table, philo->id_philo, "is thinking", 0);
	}
	return (NULL);
}
