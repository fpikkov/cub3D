/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_uchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:38:50 by fpikkov           #+#    #+#             */
/*   Updated: 2025/04/28 13:38:54 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static bool	iterate_arg(int c)
{
	if ((c >= 9 && c <= 13) || c == ' ' || c == '+' || c == '-')
		return (true);
	return (false);
}

uint8_t	arg_to_uchar(const char *str, bool *failure)
{
	int16_t	nbr;

	nbr = 0;
	while (iterate_arg(*str))
		str++;
	while (*str >= '0' && *str <= '9' && !(nbr > UCHAR_MAX))
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	if (nbr > UCHAR_MAX)
	{
		print_error(IMG_COLOR_LIMIT, false);
		*failure = true;
		return ((uint8_t)255);
	}
	return ((uint8_t)nbr);
}

/**
 * @brief Prints warning once when a letter or
 * a sign is found in the color data
 */
bool	color_warning(int c)
{
	static bool	printed_alpha = false;
	static bool	printed_neg = false;

	if (printed_alpha || printed_neg)
		return (true);
	if (!printed_alpha && ft_isalpha(c))
	{
		print_error(IMG_COLOR_CHARACTERS, false);
		printed_alpha = true;
		return (true);
	}
	if (!printed_neg && (c == '-' || c == '+'))
	{
		print_error(IMG_COLOR_SIGNEDNESS, false);
		printed_neg = true;
		return (true);
	}
	return (false);
}
