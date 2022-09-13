/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaysu <yaysu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:26:31 by yaysu             #+#    #+#             */
/*   Updated: 2022/09/06 13:41:28 by yaysu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <time.h>

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	int					taken_by;
}						t_fork;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	int					times_eat;
	int					left;
	int					right;
	long int			last_meal;
	struct s_data		*data;
}						t_philo;

typedef struct s_data
{
	int					philo_count;
	int					die_time;
	int					eat_time;
	int					sleep_time;
	int					max_eat;
	int					died;
	int					win;
	long int			start_time;
	pthread_mutex_t		m_meal;
	pthread_mutex_t		m_dead;
	pthread_mutex_t		m_win;
	pthread_mutex_t		m_write;
	pthread_mutex_t		m_fork;
	pthread_mutex_t		m_t_eat;
	t_philo				*philo;
	t_fork				*fork;
}						t_data;

int				ft_atoi(char *str);
int				print_error(char *str, int i);
long int		get_time(void);
long int		now(t_philo *philo);
void			*thread(void *var);
void			*thread_1(void *var);
int				init_data(t_data *data, int argc, char **argv);
void			print(t_data *data, int id, char *str);
int				check_died(t_data *data);
int				check_win(t_data *data);
void			start_thread(t_data *data);
void			smart_sleep(long int time, t_data *data);
int				is_reached_max_eat(t_philo *philo);
void			win_checker(t_data *data);
void			death_checker(t_data *data);
int				init_mutex(t_data *data);

#endif