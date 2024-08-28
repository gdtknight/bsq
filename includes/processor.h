/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:33:57 by yoshin            #+#    #+#             */
/*   Updated: 2024/08/28 23:23:30 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSOR_H
# define PROCESSOR_H
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "validation.h"
# include "dp.h"
# include "utils.h"

int		processing(char *filename);
int		read_meta(int map_info_fd, char **meta);
int		parse_meta_info(char **meta, char **symbol, int *max_row);
int		find_max(int map_info_fd, int **result, char **symbol, int max_row);
void	print_result(int fd, int **result, char **symbol, int max_row);
#endif
