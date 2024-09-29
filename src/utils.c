/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agtshiba <agtshiba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 16:16:50 by agtshiba          #+#    #+#             */
/*   Updated: 2024/09/24 17:12:58 by agtshiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (sign * result);
}


static size_t	calculate_size(long number)
{
	size_t	len;

	len = 0;
	if (number < 0)
	{
		number = number * (-1);
		len = 1;
	}
	if (number == 0)
		len = 1;
	else
	{
		while (number != 0)
		{
			len++;
			number = number / 10;
		}
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	size;
	long	nb;
	char	*str;
	int		is_negative;

	size = calculate_size((long) n);
	str = (char *) malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	nb = (long) n;
	is_negative = 0;
	if (nb < 0)
	{
		nb = nb * (-1);
		str[0] = '-';
		is_negative = 1;
	}
	str[size] = '\0';
	while (size > (size_t) is_negative)
	{
		str[size - 1] = nb % 10 + '0';
		nb = nb / 10;
		size--;
	}
	return (str);
}


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	return (str);
}

long long init_starttime()
{
	long long start_time;
	struct timeval tv;
	
	start_time = 0;
	gettimeofday(&tv, NULL);
	start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (start_time);
}

long long gettimestamp(t_table *table)
{
	struct timeval tv;
	long long start_time;

	start_time = table->start_time;

	gettimeofday(&tv, NULL);
	long long current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (current_time - start_time);
}

void print_starting_time(void)
{
	time_t raw_time;
	struct tm *time_info;
	char buffer[80];

	time(&raw_time);
	time_info = localtime(&raw_time);
	strftime(buffer, 80, "%H:%M:%S - %d/%m/%Y", time_info);
	printf("Le programme a commencé à : %s\n\n", buffer);
}


void print_finishing_time(void)
{
	time_t raw_time;
	struct tm *time_info;
	char buffer[80];

	time(&raw_time);
	time_info = localtime(&raw_time);
	strftime(buffer, 80, "%H:%M:%S - %d/%m/%Y", time_info);
	printf("Le programme a terminé à : %s\n", buffer);
}

long long 	time_diff(long long past, long long present)
{
	return (present - past);
}

void 	smart_sleep(long long time, t_table *table)
{
	long long i;

	i = gettimestamp(table);
	while (!(table->smbd_has_died))
	{
		if (time_diff(i, gettimestamp(table)) >= time)
			break;
		usleep(50);
	}


}