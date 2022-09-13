/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:10:54 by sneyt             #+#    #+#             */
/*   Updated: 2022/09/13 16:36:03 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	death_checker(t_philosopher *philo)
{
	if (!philo->eating && get_timestamp() > philo->time_till_death)
	{
		log_message(philo, philo->time_till_death, "died");
		pthread_mutex_unlock(&philo->controller->death_mutex);
	//	philo->controller->death = 1;
		//pthread_mutex_lock(&philo->controller->write_mutex);
		return (1);
	}
	return (0);
}

int	drop_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->controller->fork_mutexes[philo->left_fork]);
	philo->controller->forks[philo->left_fork] = 0;
	pthread_mutex_unlock(&philo->controller->fork_mutexes[philo->left_fork]);
	pthread_mutex_lock(&philo->controller->fork_mutexes[philo->right_fork]);
	philo->controller->forks[philo->right_fork] = 0;
	pthread_mutex_unlock(&philo->controller->fork_mutexes[philo->right_fork]);
	log_message(philo, philo->last_meal + philo->controller->tto_eat, "sleeping");
	ft_usleep(philo->controller->tto_sleep);
	if (death_checker(philo))
		return (1);
	log_message(philo, philo->last_meal + philo->controller->tto_eat + philo->controller->tto_sleep, "thinking");
	return (0);
}

int	allocate_forks(t_philosopher *philo)
{
	int	i;
	unsigned int fork;

	i = 0;
	while (i < 2)
	{
		if (death_checker(philo))
			return (1);
		if (i == 0)
			fork = philo->left_fork;
		else
			fork = philo->right_fork;
		pthread_mutex_lock(&philo->controller->fork_mutexes[fork]);
		if (!philo->controller->forks[fork])
		{
			log_message(philo, get_timestamp(), "taking_fork");
			philo->controller->forks[fork] = 1;
			i++;
		}
		pthread_mutex_unlock(&philo->controller->fork_mutexes[fork]);
	}
	return (0);
}

int	eating(t_philosopher *philo)
{
	philo->eating = 1;
	philo->last_meal = get_timestamp();
	log_message(philo, philo->last_meal, "eating");
	ft_usleep(philo->controller->tto_eat);
	philo->time_till_death = philo->last_meal + philo->controller->tto_die;
	philo->eating = 0;
	philo->meals += 1;
	if (philo->controller->num_of_meals > 0 && philo->meals >= philo->controller->num_of_meals)
	{
		log_message(philo, philo->last_meal, "done");
		pthread_mutex_lock(&philo->controller->fork_mutexes[philo->left_fork]);
		philo->controller->forks[philo->left_fork] = 0;
		pthread_mutex_unlock(&philo->controller->fork_mutexes[philo->left_fork]);
		pthread_mutex_lock(&philo->controller->fork_mutexes[philo->right_fork]);
		philo->controller->forks[philo->right_fork] = 0;
		pthread_mutex_unlock(&philo->controller->fork_mutexes[philo->right_fork]);
		philo->controller->finished++;
		if (philo->controller->finished >= philo->controller->size)
		{
		//	pthread_mutex_lock(&philo->controller->write_mutex);
			pthread_mutex_unlock(&philo->controller->death_mutex);
		}
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philosopher *philo;

	philo = (t_philosopher *)arg;
	philo->last_meal = get_timestamp();
//	printf("%u >>> Hello from inside the thread %d\n",philo->last_meal, philo->philo_id);
	philo->time_till_death = philo->last_meal + philo->controller->tto_die;
	//printf("%u \n", philo->time_till_death);
	while (1)
	{
		if (allocate_forks(philo) || eating(philo) || drop_forks(philo))
			break ;
	}
	return (NULL);
}

int	launch(t_controller *controller)
{
	unsigned int	i;
	pthread_t th;

	i = 0;
	pthread_mutex_lock(&controller->death_mutex);
	controller->start = get_timestamp();
	while (i < controller->size)
	{
		if (pthread_create(&th, NULL, &routine, (void *)&controller->table[i]) != 0)
			return (error_msg("Failed to create thread"));
		pthread_detach(th);
		if (controller->size % 2)
			ft_usleep(500);
		i++;
	}
	return (0);
}

