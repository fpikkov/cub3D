/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flashlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpikkov <fpikkov@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:29:29 by fpikkov           #+#    #+#             */
/*   Updated: 2025/04/09 11:29:30 by fpikkov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	reset_flashlight(t_torch *torch)
{
	torch->one->enabled = false;
	torch->two->enabled = false;
	torch->three->enabled = false;
	torch->four->enabled = false;
	torch->five->enabled = false;
}

/**
 * @brief Selects the corrrect flashlight sprite to draw based on battery level
 */
void	flashlight_state(t_torch *torch)
{
	if (!torch->enabled)
		return ;
	reset_flashlight(torch);
	if (torch->battery == 0)
		flashlight_switch(torch);
	else if (torch->battery == 1)
		torch->one->enabled = true;
	else if (torch->battery == 2)
		torch->two->enabled = true;
	else if (torch->battery == 3)
		torch->three->enabled = true;
	else if (torch->battery == 4)
		torch->four->enabled = true;
	else if (torch->battery == BATTERY_MAX)
		torch->five->enabled = true;
}

/**
 * @brief Battery recharges twice as fast as it drains
 */
void	flashlight_battery(t_torch *torch)
{
	static int	counter = 0;

	counter++;
	if (!torch->enabled)
		counter++;
	if (counter < BATTERY_LIFE)
		return ;
	if (torch->enabled)
	{
		if (torch->battery > 0)
			torch->battery--;
		flashlight_state(torch);
	}
	else if (!torch->enabled && torch->battery < 5)
		torch->battery++;
	counter = 0;
}

/**
 * @brief Turns the flashlight on/off
 */
void	flashlight_switch(t_torch *torch)
{
	torch->enabled = !torch->enabled;
	torch->dark->enabled = !torch->dark->enabled;
	torch->light->enabled = !torch->light->enabled;
	torch->off->enabled = !torch->off->enabled;
	flashlight_state(torch);
}
