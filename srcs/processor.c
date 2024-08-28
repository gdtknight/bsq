/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoshin <yoshin@student.42gyeongsan.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 23:33:16 by yoshin            #+#    #+#             */
/*   Updated: 2024/08/28 23:09:35 by yoshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/processor.h"

/*
 * symbols[0] : empty
 * symbols[1] : obstacle
 * symbols[2] : full
 */
int	processing(char *filename)
{
	int		map_info_fd;
	char	*meta;
	char	*symbol;
	int		*result;
	int		max_row;

	meta = 0;
	symbol = 0;
	result = 0;
	map_info_fd = open(filename, O_RDONLY);
	if (!read_meta(map_info_fd, &meta)
		|| !is_valid_meta(&meta)
		|| !parse_meta_info(&meta, &symbol, &max_row)
		|| !find_max(map_info_fd, &result, &symbol, max_row))
	{
		close(map_info_fd);
		if (meta != NULL)
			free(meta);
		if (symbol != NULL)
			free(symbol);
		if (result != NULL)
			free(result);
		return (0);
	}
	close(map_info_fd);

	map_info_fd = open(filename, O_RDONLY);
	print_result(map_info_fd, &result, &symbol);
	close(map_info_fd);
	if (meta != NULL)
		free(meta);
	if (symbol != NULL)
		free(symbol);
	if (result != NULL)
		free(result);
	return (1);
}

int	read_meta(int map_info_fd, char **meta)
{
	int		temp_fd;
	char	buf[1];
	char	*m;
	int		size;

	size = 0;
	temp_fd = open("tmp", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	while(read(map_info_fd, buf, 1) > 0 && buf[0] != '\n')
	{
		write(temp_fd, buf, 1);
		size++;
	}
	close(temp_fd);
	*meta = (char *)malloc(sizeof(char) * (size + 1));
	temp_fd = open("tmp", O_RDONLY);
	m = *meta;
	while (read(temp_fd, buf, 1) > 0)
		*m++ = buf[0];
	*m = '\0';
	close(temp_fd);
	return (1);
}

int	parse_meta_info(char **meta, char **symbol, int *max_row)
{
	int		idx;
	int		meta_len;

	meta_len = ft_strlen(*meta);
	idx = -1;
	(*max_row) = 0;
	while (++idx < meta_len - 3)
		(*max_row) = ((*max_row) * 10) + ((*meta)[idx] - '0');
	*symbol = (char *) malloc(sizeof(char) * 4);
	if (symbol == NULL)
		return (0);
	*(*symbol) = *((*meta) + (meta_len - 3));
	*((*symbol) + 1) = *((*meta) + (meta_len - 2));
	*((*symbol) + 2) = *((*meta) + (meta_len - 1));
	*((*symbol) + 3) = '\0';
	return (1);
}

int		find_max(int map_info_fd, int **result, char **symbol, int max_row)
{
	int		**dp;
	int		row;
	int		col;
	int		max_col;

	if (max_row == 0)
		return (0);
	dp = 0;
	(*result) = (int *) malloc(sizeof(int) * 3);
	if ((*result) == NULL)
		return (0);
	if (!initialize_dp(map_info_fd, &dp, &max_col, *symbol))
		return (0);
	if (max_row == 1)
	{
		col = -1;
		while (++col < max_col)
			if (dp[1][col] == 1)
			{
				(*result)[0] = 0;
				(*result)[1] = col;
				(*result)[2] = 1;
				return (1);
			}
	}
	row = -1;
	while (++row < max_row)
	{
		update_dp(&dp, result, row, max_col);
		if(!insert_dp(map_info_fd, &dp, max_col, *symbol))
			return (0);
	}
	return (1);
}

void	print_result(int fd, int **result, char **symbol)
{
	char	buf[1];
	int		row;
	int		col;

	row = 0;
	col = 0;
	// 첫째줄 건너뛰고
	while (read(fd, buf, 1) == 1 && buf[0] != '\n')
		;
	// 두번째줄부터 파일 1바이트씩 읽고 출력
	// 찾은 범위는 full character 로 바꿔서 화면 출력
	while (read(fd, buf, 1) == 1)
	{
		if (((*result)[0] - (*result)[2] < row && row <= (*result)[0])
			&& ((*result)[1] - (*result)[2] < col && col <= (*result)[1]))
			write(1, &((*symbol)[2]), 1);
		else
			write(1, buf, 1);
		col++;
		if (buf[0] == '\n')
		{
			row++;
			col = 0;
		}
	}
}
