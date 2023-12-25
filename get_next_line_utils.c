/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line_utils.c							  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: antoinemura <antoinemura@student.42.fr>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/12/25 23:28:34 by antoinemura	   #+#	#+#			 */
/*   Updated: 2023/12/25 23:46:07 by antoinemura	  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*src_cpy;
	unsigned char	*dest_cpy;

	if (src == NULL && dest == NULL)
		return (NULL);
	src_cpy = (unsigned char *)src;
	dest_cpy = (unsigned char *)dest;
	while (n > 0)
	{
		*dest_cpy = *src_cpy;
		dest_cpy++;
		src_cpy++;
		n--;
	}
	return (dest);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	size_t	min_size;
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	if (old_size < new_size)
		min_size = old_size;
	else
		min_size = new_size;
	ft_memcpy(new_ptr, ptr, min_size);
	free(ptr);
	return (new_ptr);
}
