/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 08:34:19 by sneyt             #+#    #+#             */
/*   Updated: 2022/09/13 16:02:52 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_args(t_controller *controller, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (error_msg("Wrong number of arguments"));
	if (ft_atoiv2(argv[1], &controller->size) || controller->size == 0
		|| ft_atoiv2(argv[2], &controller->tto_die) || controller->tto_die == 0
		|| ft_atoiv2(argv[3], &controller->tto_eat) || controller->tto_eat == 0
		|| ft_atoiv2(argv[4], &controller->tto_sleep)
	   	|| controller->tto_sleep == 0)
		return (error_msg("Wrong arguments"));
	if (argc == 6 && (ft_atoiv2(argv[5], &controller->num_of_meals)
		|| controller->num_of_meals == 0))
		return (error_msg("Wrong argumentss"));
	else if (argc == 5)
		controller->num_of_meals = -1;
	controller->finished = 0;
	//controller->death = 0;
	return (0);
}

int	init_philo(t_controller *controller)
{
	unsigned int	i;

	controller->table = malloc(sizeof(t_philosopher) * controller->size);
	controller->forks = malloc(sizeof(int) * controller->size);
	if (!controller->table || !controller->forks)
		return (error_msg("Malloc failed"));
	i = 0;
	while (i < controller->size)
	{
		controller->forks[i] = 0;
		controller->table[i].philo_id = i;
		controller->table[i].eating = 0;
		controller->table[i].left_fork = i;
		controller->table[i].right_fork = (i + 1) % controller->size;
		controller->table[i].controller = controller;
		controller->table[i].meals = 0;
		i++;
	}
	return (0);
}

int	init_mutex(t_controller *controller)
{
	unsigned int i;

	controller->fork_mutexes = malloc(sizeof(pthread_mutex_t) * controller->size);
	if (!controller->fork_mutexes)
		return (error_msg("Mutex malloc failed"));
	i = 0;
	while (i < controller->size)
	{
		pthread_mutex_init(&controller->fork_mutexes[i], NULL);
		i++;
	}
	pthread_mutex_init(&controller->write_mutex, NULL);
	pthread_mutex_init(&controller->death_mutex, NULL);
	return (0);
}
