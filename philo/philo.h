/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keaton <keaton@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:55:12 by keaton            #+#    #+#             */
/*   Updated: 2022/07/21 21:21:07 by keaton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_dead{
	pthread_mutex_t	deadlock;
	pthread_mutex_t	report;
	int				flag;
}				t_dead;

typedef struct s_pinfo{
	t_dead			*dead;
	pthread_t		id;
	int				*info;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*deadlock;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	mt_lock;
	int				ph_nbr;
	struct timeval	last_meal;
	struct timeval	start_time;
	int				meals;
}				t_pinfo;

int		ft_atoi(const char *str);
int		**ft_fill_info(char **argv, int **info);
int		ft_usleep(int delay);
t_pinfo	*ft_free_idp(int *i, t_dead *d, t_pinfo **p);
void	ft_destroy_spoons(pthread_mutex_t **spoons, t_pinfo *pinfo);
void	ft_lets_eat(t_pinfo	*pinfo, pthread_mutex_t **spoons);
void	ft_report(const char *words, t_pinfo *pinfo);
t_pinfo	*ft_init_values(t_pinfo **pinfo, pthread_mutex_t **spoons, char **argv);
int		ft_philo_died(t_pinfo *pinfo);
void	ft_init_times(t_pinfo *pinfo);
void	*ft_philo(void *pinfo);
void	ft_eat_odd(t_pinfo *pinfo);
void	ft_eat_even(t_pinfo *pinfo);

#endif
