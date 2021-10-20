#include "../includes/philo.h"

void    ft_exit(t_table *table)
{
    table->death = 0;
    exit(0);
}   

void     *check_death(void *data)
{
    t_table *table = (t_table *)data;
    t_philo *philos = table->philos;
    int i;

    while (table->death)
    {
        i = 0;
        while (i < table->n_philos)
        {
            if (curr_time() - philos[i].last_t_ate > table->t_die)
            {
                table->death = 0;
                // pthread_mutex_unlock(&table->forks[philos[i].id_philo - 1].fork);
                // pthread_mutex_unlock(&table->forks[philos[i].id_philo % philos[i].table->n_philos].fork);  
                // printf("philo %d last ate %ld ms ago\n", philos[i].id_philo, curr_time() - philos[i].last_t_ate);
                status(table, philos[i].id_philo, "died");
                ft_exit(table);
            }
            if (philos[table->n_philos - 1].n_ate == table->n_must_eat)
                ft_exit(table);
            i++;
        }
    }
    return (NULL);
}

int		lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->id_philo - 1].fork);
    pthread_mutex_lock(&philo->table->forks[philo->id_philo % philo->table->n_philos].fork);
	return (1);
}

void		unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->id_philo - 1].fork);
    pthread_mutex_unlock(&philo->table->forks[philo->id_philo % philo->table->n_philos].fork);
}

int     ph_eat(t_philo  *philo)
{
    lock_forks(philo);
    status(philo->table, philo->id_philo, "has taken a fork");
    philo->last_t_ate = curr_time();
    status(philo->table, philo->id_philo, "is eating");
    usleep(philo->table->t_eat * 1000);
    philo->n_ate += 1;
    unlock_forks(philo);
    return (1);
}

int     ph_sleep(t_philo  *philo)
{
    status(philo->table, philo->id_philo, "is sleeping");
    usleep(philo->table->t_sleep * 1000);
    return (1);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	while (philo->table->death)
	{
		if (ph_eat(philo) == 0)
			break ;
		if (ph_sleep(philo) == 0)
			break ;
		status(philo->table, philo->id_philo, "is thinking");
	}
	return (NULL);
}