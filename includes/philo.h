/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 08:17:11 by sneyt             #+#    #+#             */
/*   Updated: 2022/09/13 16:13:27 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libs/libft/libft.h"
 

typedef struct s_philosopher {
	unsigned int	philo_id;
	unsigned int	right_fork;
	unsigned int	left_fork;
	unsigned int	eating;
	unsigned int meals;
	unsigned int last_meal;
	unsigned int time_till_death;
	struct s_controller *controller;
}	t_philosopher;

typedef struct s_controller {
	unsigned int	size;
	unsigned int	tto_eat;
	unsigned int	tto_sleep;
	unsigned int	tto_die;
	unsigned int	num_of_meals;
	unsigned int	start;
	t_philosopher *table;
	int	*forks;
	int	death;
	unsigned int	finished;
	pthread_mutex_t *fork_mutexes;
	pthread_mutex_t write_mutex;
	pthread_mutex_t	death_mutex;
}	t_controller;

int		init_args(t_controller *controller, int argc, char *argv[]);
int		init_philo(t_controller *controller);
int		init_mutex(t_controller *controller);
int		drop_forks(t_philosopher *philo);
void	ft_usleep(unsigned int ms);
int		death_checker(t_philosopher *philo);
void	log_message(t_philosopher *philo, unsigned int timestamp, char *action);
int		error_msg(char *message);
int		eating(t_philosopher *philo);
int		ft_atoiv2(char *str, unsigned int *dst);
int		ft_strcmp(char *s1, char *s2);
int		launch(t_controller *controller);
unsigned int		get_timestamp(void);
void	*routine(void *arg);
#endif
