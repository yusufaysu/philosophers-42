/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:56:18 by yaysu             #+#    #+#             */
/*   Updated: 2022/09/02 14:53:35 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print(t_data *data, int id, char *str)
{
	pthread_mutex_lock(&data->m_write);
	if (!check_died(data) && !check_win(data))
	{
		printf("%ld ms %d %s\n", get_time() - data->start_time, id, str);
	}
	pthread_mutex_unlock(&data->m_write);
}

int	check_died(t_data *data)
{
	pthread_mutex_lock(&data->m_dead);
	if (data->died)
	{
		pthread_mutex_unlock(&data->m_dead);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->m_dead);
		return (0);
	}
}

int	check_win(t_data *data)
{
	pthread_mutex_lock(&data->m_win);
	if (data->win)
	{
		pthread_mutex_unlock(&data->m_win);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->m_win);
		return (0);
	}
}

void	smart_sleep(long int time, t_data *data)
{
	long int	i;

	i = get_time();
	while (get_time() - i < time)
	{
		if (check_died(data) || check_win(data))
			break ;
		usleep(100);
	}
}

int	is_reached_max_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_t_eat);
	if (philo->times_eat >= philo->data->max_eat)
	{
		pthread_mutex_unlock(&philo->data->m_t_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->m_t_eat);
	return (0);
}
