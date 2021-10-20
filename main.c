#include "includes/philo.h"

void	status(t_table *table, int id_philo, char *string)
{
	pthread_mutex_lock(&table->std_o);
	printf("%ld %d %s\n", curr_time() - table->t_start, id_philo, string);
	pthread_mutex_unlock(&table->std_o);
}

void	create_threads_mutex(t_table *table, t_philo *philos)
{
	int i;
    pthread_t death;

	i = 0;
	pthread_mutex_init(&table->std_o, NULL);
	while (i < table->n_philos)
	{
		table->forks[i].used = 0; 
		pthread_mutex_init(&table->forks[i++].fork, NULL);
	}
	i = 0;
	while (i < table->n_philos)
	{
		philos[i].table = table;
		philos[i].last_t_ate = curr_time();
		philos[i].id_philo = i + 1;
		philos[i].n_ate = 0;
		pthread_create(&philos[i].philo, NULL, &routine, &philos[i]);
		i++;
		usleep(1000);
	}
	pthread_create(&death, NULL, &check_death, table);
	i = 0;
	while (i < table->n_philos)
		pthread_join(philos[i++].philo, NULL);
	pthread_join(death, NULL);
}

int		main(int ac, char **av)
{
	t_table table;
	t_philo	*philos;
	int i;

	if (ac == 5 || ac == 6)
	{
		i = 0;
		if (!init_store_options(&table, av))
			ft_error("Error: Wrong args.\n");
		philos = malloc(sizeof(t_philo) * table.n_philos);
		table.forks = malloc(sizeof(t_fork) * table.n_philos);
		table.philos = philos;
		create_threads_mutex(&table, philos);
		pthread_mutex_destroy(&table.std_o);
		while (i < table.n_philos)
			pthread_mutex_destroy(&table.forks[i++].fork);
	}
	else
		ft_error("Error: Wrong args.\n");
	return (0);
}