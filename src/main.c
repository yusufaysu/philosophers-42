/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:18:11 by yaysu             #+#    #+#             */
/*   Updated: 2022/09/08 15:49:02 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	cehck_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && j != '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	free_mutex(t_data *data, int var)
{
	int	i;

	i = -1;
	if (var == -1)
		init_mutex(data);
	while (++i < data->philo_count)
		pthread_mutex_destroy(&data->fork[i].mutex);
	pthread_mutex_destroy(&data->m_meal);
	pthread_mutex_destroy(&data->m_write);
	pthread_mutex_destroy(&data->m_dead);
	pthread_mutex_destroy(&data->m_fork);
	pthread_mutex_destroy(&data->m_win);
	pthread_mutex_destroy(&data->m_t_eat);
	free(data->philo);
	free(data->fork);
}

void	wait_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		pthread_join(data->philo[i].thread, NULL);
	free_mutex(data, 0);
}

void	start_thread(t_data *data)
{
	int		i;
	void	*func;

	i = -1;
	if (data->philo_count == 1)
		func = thread_1;
	else
		func = thread;
	data->start_time = get_time();
	while (++i < data->philo_count)
	{
		data->philo[i].last_meal = data->start_time;
		pthread_create(&data->philo[i].thread, NULL, func, &data->philo[i]);
	}
	if (func == thread)
		death_checker(data);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;

	if (argc < 5 || argc > 6)
		return (print_error("Error: Argument error.", 1));
	if (cehck_arg(argv) == 1)
		return (print_error("Error: Argument error.", 1));
	i = init_data(&data, argc, argv);
	if (i == 0 || i == -1)
	{
		free_mutex(&data, i);
		return (0);
	}
	start_thread(&data);
	wait_threads(&data);
	return (0);
}
