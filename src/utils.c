/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:17:24 by yaysu             #+#    #+#             */
/*   Updated: 2022/09/06 13:44:02 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(char *str)
{
	int		i;
	long	r;
	int		k;

	i = 0;
	r = 0;
	k = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = (r * 10) + (str[i] - 48);
		i++;
	}
	return (r * k);
}

int	print_error(char *str, int i)
{
	printf("%s\n", str);
	return (i);
}

long int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

void	win_checker(t_data *data)
{
	int	i;

	i = 0;
	while (data->max_eat != -1 && i < data->philo_count
		&& is_reached_max_eat(&data->philo[i]))
		i++;
	if (i == data->philo_count)
	{
		pthread_mutex_lock(&data->m_win);
		data->win = 1;
		pthread_mutex_unlock(&data->m_win);
		pthread_mutex_lock(&data->m_write);
		printf("Each philosopher ate at least %d time(s).\n", data->max_eat);
		pthread_mutex_unlock(&data->m_write);
	}
}

void	death_checker(t_data *data)
{
	int	i;

	while (!check_win(data))
	{
		i = -1;
		while (++i < data->philo_count && !check_died(data))
		{
			pthread_mutex_lock(&data->m_meal);
			if (get_time() - data->philo[i].last_meal > data->die_time)
			{
				pthread_mutex_lock(&data->m_dead);
				data->died = 1;
				pthread_mutex_unlock(&data->m_dead);
				pthread_mutex_lock(&data->m_write);
				printf("%ld %d %s\n", get_time() - data->start_time,
					data->philo[i].id, "died.");
				pthread_mutex_unlock(&data->m_write);
			}
			pthread_mutex_unlock(&data->m_meal);
			usleep(200);
		}
		if (check_died(data))
			break ;
		win_checker(data);
	}
}
