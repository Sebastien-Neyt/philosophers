/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneyt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 08:45:07 by sneyt             #+#    #+#             */
/*   Updated: 2022/09/13 16:19:57 by sneyt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoiv2(char *str, unsigned int *dst)
{
	int	i;

	i = 0;
	if (!str[i])
		return (1);
	*dst = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		*dst = *dst * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (1);
	return (0);
}

void	log_message(t_philosopher *philo, unsigned int timestamp, char *action)
{
	//pthread_mutex_lock(&philo->controller->write_mutex);
	unsigned int start;

	start = philo->controller->start;
	if (!ft_strcmp(action, "taking_fork"))
		printf("%d %d has taken a fork\n", timestamp - start, philo->philo_id);
	if (!ft_strcmp(action, "died"))
		printf("%d %d died\n", timestamp - start, philo->philo_id);
	if (!ft_strcmp(action, "eating"))
		printf("%d %d is eating\n", timestamp - start, philo->philo_id);
	if (!ft_strcmp(action, "sleeping"))
		printf("%d %d is sleeping\n", timestamp - start, philo->philo_id);
	if (!ft_strcmp(action, "thinking"))
		printf("%d %d is thinking\n", timestamp - start, philo->philo_id);
	//pthread_mutex_unlock(&philo->controller->write_mutex);
}

void	ft_usleep(unsigned int ms)
{
	unsigned int	end;

	end = get_timestamp() + ms;
	while (get_timestamp() < end)
		usleep(ms / 1000);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

unsigned int	get_timestamp(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	//printf("%ld\n", tv.tv_sec);
	//printf("%d\n", tv.tv_usec);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
