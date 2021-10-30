#include "../includes/philo.h"

void     *check_death(void *data)
{
    t_philo *philo = (t_philo *)data;

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

void		lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->id_philo - 1].fork);
    status(philo->table, philo->id_philo, "has taken a fork", 0);
    pthread_mutex_lock(&philo->table->forks[philo->id_philo % philo->table->n_philos].fork);
    status(philo->table, philo->id_philo, "has taken a fork", 1);
}

void		unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->id_philo - 1].fork);
    pthread_mutex_unlock(&philo->table->forks[philo->id_philo % philo->table->n_philos].fork);
}

void     ph_eat(t_philo  *philo)
{
    lock_forks(philo);
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
    pthread_t   death;

	philo = (t_philo *)data;
    pthread_create(&death, NULL, &check_death, philo);
    pthread_detach(death);
	while (philo->table->death)
	{
        ph_eat(philo);
        ph_sleep(philo);
        status(philo->table, philo->id_philo, "is thinking", 0);
	}
	return (NULL);
}