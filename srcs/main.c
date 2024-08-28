/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:30:53 by yoshin            #+#    #+#             */
/*   Updated: 2024/08/28 14:21:05 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	main(int argc, char **argv)
{
	int	idx;

	if (argc < 2)
		return (0);
	idx = 0;
	while (++idx < argc)
	{
		if(!processing(argv[idx]))
			write(1, "map error", 9);
		write(1, "\n", 1);
	}
	exit(0);
}
