/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:48:07 by yaysu             #+#    #+#             */
/*   Updated: 2022/09/06 13:57:12 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	init_gen_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->m_meal, NULL))
		return (print_error("Mutex initialization failed.", 1));
	if (pthread_mutex_init(&data->m_write, NULL))
		return (print_error("Mutex initialization failed.", 1));
	if (pthread_mutex_init(&data->m_dead, NULL))
		return (print_error("Mutex initialization failed.", 1));
	if (pthread_mutex_init(&data->m_fork, NULL))
		return (print_error("Mutex initialization failed.", 1));
	if (pthread_mutex_init(&data->m_win, NULL))
		return (print_error("Mutex initialization failed.", 1));
	if (pthread_mutex_init(&data->m_t_eat, NULL))
		return (print_error("Mutex initialization failed.", 1));
	return (1);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	data->fork = malloc(sizeof(t_fork) * data->philo_count);
	if (!data->fork)
		return (print_error("Malloc failed.", 1));
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(&data->fork[i].mutex, NULL))
			return (print_error("Mutex initialization failed.", 1));
		data->fork[i].taken_by = 0;
	}
	return (init_gen_mutex(data));
}

int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philo)
		return (print_error("Error: Memory allocation error.", 1));
	while (++i < data->philo_count)
	{
		data->philo[i].id = i + 1;
		data->philo[i].times_eat = 0;
		data->philo[i].right = i;
		data->philo[i].left = (i + 1) % data->philo_count;
		data->philo[i].last_meal = 0;
		data->philo[i].data = data;
	}
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	data->max_eat = -1;
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	data->died = 0;
	data->win = 0;
	if (data->philo_count < 1 || data->die_time < 0 || data->eat_time < 0
		|| data->sleep_time < 0 || (argc == 6 && data->max_eat < 1)
		|| data->sleep_time >= 2147483647 || data->die_time >= 2147483647
		|| data->eat_time >= 2147483647
		|| (argc == 6 && data->max_eat >= 2147483647))
		return (print_error("Error: Argument error.", -1));
	return (init_mutex(data) * init_philo(data));
}
