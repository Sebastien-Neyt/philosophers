/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 08:15:56 by sneyt             #+#    #+#             */
/*   Updated: 2022/09/13 14:33:44 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_controller controller;
	
	if (init_args(&controller, argc, argv) || init_philo(&controller)
		|| init_mutex(&controller))
		return (1);
	if (launch(&controller))
		return (1);
	pthread_mutex_lock(&controller.death_mutex);
	pthread_mutex_unlock(&controller.death_mutex);
	exit(0);
}
