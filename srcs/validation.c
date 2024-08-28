/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:15:37 by yoshin            #+#    #+#             */
/*   Updated: 2024/08/28 23:15:48 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/validation.h"
#include <unistd.h>

int	is_valid_meta(char **meta)
{
	char	*m;
	int		len;
	int		lines;
	int		idx;

	m = *meta;
	len = ft_strlen(m);
	if (len < 4)
		return (0);
	if (!('0' <= *m && *m <= '9'))
		return (0);
	lines = 0;
	idx = 0;
	while ('0' <= *m && *m <= '9')
	{
		lines = (lines * 10) + (*m - '0');
		m++;
		idx++;
	}
	if (lines == 0)
		return (0);
	if (idx != (len - 3))
		return (0);
	if (!(32 <= *m && *m <= 47)
		&& !(58 <= *m && *m <= 126))
		return (0);
	m++;
	if (!(32 <= *m && *m <= 47)
		&& !(58 <= *m && *m <= 126))
		return (0);
	m++;
	if (!(32 <= *m && *m <= 47)
		&& !(58 <= *m && *m <= 126))
		return (0);
	if (*(m + 1) != '\0'
		|| *(m - 2) == *(m - 1)
		|| *(m - 2) == *m
		|| *(m - 1) == *m)
		return (0);
	return (1);
}
