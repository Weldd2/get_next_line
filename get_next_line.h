/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:28:48 by antoinemura       #+#    #+#             */
/*   Updated: 2023/12/16 17:20:04 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char	*get_next_line(int fd);

#ifndef  BUFFER_SIZE 
# define BUFFER_SIZE 1
#endif

