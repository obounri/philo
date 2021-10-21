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

    while (1)
    {
        i = 0;
        while (i < table->n_philos)
        {
            if (curr_time() - philos[i].last_t_ate > table->t_die)
            {
                table->death = 0;
                printf("philo %d last ate %ld ms ago\n", philos[i].id_philo, curr_time() - philos[i].last_t_ate);
                status(table, philos[i].id_philo, "died", 0);
                ft_exit(table);
            }
            if (philos[table->n_philos - 1].n_ate == table->n_must_eat)
            {
                table->death = 0;
                ft_exit(table);
            }
            i++;
        }
    }
    return (NULL);
}

void		lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->id_philo - 1].fork);
    pthread_mutex_lock(&philo->table->forks[philo->id_philo % philo->table->n_philos].fork);
}

void		unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->id_philo - 1].fork);
    pthread_mutex_unlock(&philo->table->forks[philo->id_philo % philo->table->n_philos].fork);
}

void     ph_eat(t_philo  *philo)
{
    lock_forks(philo);
    status(philo->table, philo->id_philo, "has taken a fork", 1);
    philo->last_t_ate = curr_time();
    usleep(philo->table->t_eat * 1000);
    philo->n_ate += 1;
    unlock_forks(philo);
}

void     ph_sleep(t_philo  *philo)
{
    status(philo->table, philo->id_philo, "is sleeping", 0);
    usleep(philo->table->t_sleep * 1000);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	while (philo->table->death)
	{
		if (philo->table->death)
            ph_eat(philo);
        if (philo->table->death)
		    ph_sleep(philo);
        if (philo->table->death)
		    status(philo->table, philo->id_philo, "is thinking", 0);
	}
	return (NULL);
}