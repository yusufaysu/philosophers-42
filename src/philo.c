/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 13:29:37 by yaysu             #+#    #+#             */
/*   Updated: 2022/09/02 14:57:20 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	release_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->taken_by = 0;
	pthread_mutex_unlock(&fork->mutex);
}

int	take_fork(t_philo *philo, t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (!fork->taken_by)
	{
		print(philo->data, philo->id, "has taken a fork.");
		fork->taken_by = philo->id;
	}
	if (fork->taken_by == philo->id)
	{
		pthread_mutex_unlock(&fork->mutex);
		return (1);
	}
	pthread_mutex_unlock(&fork->mutex);
	return (0);
}

void	eat(t_philo *philo)
{
	while (1)
	{
		if (take_fork(philo, &philo->data->fork[philo->left]))
			break ;
		usleep(100);
	}
	while (1)
	{
		if (take_fork(philo, &philo->data->fork[philo->right]))
			break ;
		usleep(100);
	}
	pthread_mutex_lock(&philo->data->m_meal);
	print(philo->data, philo->id, "is eating.");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->m_meal);
	smart_sleep(philo->data->eat_time, philo->data);
	pthread_mutex_lock(&philo->data->m_t_eat);
	philo->times_eat++;
	pthread_mutex_unlock(&philo->data->m_t_eat);
	release_fork(&philo->data->fork[philo->left]);
	release_fork(&philo->data->fork[philo->right]);
}

void	*thread_1(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	print(philo->data, philo->id, "has taken a fork.");
	usleep(philo->data->die_time * 1000);
	print(philo->data, philo->id, "died.");
	return (NULL);
}

void	*thread(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	if (philo->id % 2 == 0)
		usleep(1500);
	while (!check_died(philo->data))
	{
		eat(philo);
		if (check_win(philo->data))
			break ;
		print(philo->data, philo->id, "is sleeping.");
		smart_sleep(philo->data->sleep_time, philo->data);
		print(philo->data, philo->id, "is thinking.");
	}
	return (NULL);
}
