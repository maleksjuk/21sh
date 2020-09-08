/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floats_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 20:27:45 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/01 20:50:18 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		f_minus(t_printf **p, long double *num, char *str, int tab[4])
{
	int	help;

	help = tab[0] + (*p)->precision;
	if ((*p)->precision > 0 || (((*p)->hash) && (*p)->precision == 0))
		help++;
	if ((*num < 0 || 1 / (*num) == 1 / -0.0) && ++help)
	{
		str[tab[2]++] = '-';
		(*num) *= -1;
	}
	else if ((*p)->plus && num >= 0 && ++help)
		str[tab[2]++] = '+';
	else if ((*p)->space && num >= 0 && ++help)
		str[tab[2]++] = ' ';
	ft_left_part(num, &str, &tab[2], p);
	tab[2] += simvol_out(p, help, ' ', &str[help]);
	return (tab[2]);
}

int		f_zero(t_printf **p, long double *num, char *str, int tab[4])
{
	int	help;

	help = tab[0] + (*p)->precision + tab[3];
	if ((*num < 0 || 1 / (*num) == 1 / -0.0) && tab[3] == 0)
		help++;
	if (*num < 0 || 1 / (*num) == 1 / -0.0)
	{
		str[tab[2]++] = '-';
		(*num) *= -1;
	}
	else if ((*p)->plus && num >= 0)
		str[tab[2]++] = '+';
	else if ((*p)->space)
		str[tab[2]++] = ' ';
	if ((*p)->precision > 0 || (((*p)->hash) && (*p)->precision == 0))
		help++;
	if ((*p)->hash)
		str[tab[2]++] = '0';
	tab[2] += simvol_out(p, help, '0', &str[tab[2]]);
	return (tab[2]);
}

int		f_def(t_printf **p, long double *num, char *str, int tab[4])
{
	int	help;

	help = tab[0] + (*p)->precision + tab[3];
	if ((*p)->precision > 0)
		help++;
	if ((*num < 0 || 1 / (*num) == 1 / -0.0) && tab[3] == 0)
		help++;
	tab[2] += simvol_out(p, help, ' ', &str[tab[2]]);
	if (*num < 0 || 1 / (*num) == 1 / -0.0)
	{
		str[tab[2]++] = '-';
		(*num) *= -1;
	}
	else if ((*p)->plus && num >= 0)
		str[tab[2]++] = '+';
	else if ((*p)->space && num >= 0)
		str[tab[2]++] = ' ';
	return (tab[2]);
}

void	ft_dbl_big(t_printf **p)
{
	if (((*p)->plus))
		(*p)->str_val = ft_strdup("+1797693134862315708145274237317043567980"
		"7056752584499659891747680315726078002853876058955863276687817154"
		"0458953514382464234321326889464182768467546703537516986049910576"
		"5512820762454900903893289440758685084551339423045832369032229481"
		"6580855933212334827479782620414472316873817718091929988125040402"
		"6184124858368.000000\0");
	else if (((*p)->space))
		(*p)->str_val = ft_strdup(" 1797693134862315708145274237317043567980"
		"7056752584499659891747680315726078002853876058955863276687817154"
		"0458953514382464234321326889464182768467546703537516986049910576"
		"5512820762454900903893289440758685084551339423045832369032229481"
		"6580855933212334827479782620414472316873817718091929988125040402"
		"6184124858368.000000\0");
	else
		(*p)->str_val = ft_strdup("1797693134862315708145274237317043567980"
		"7056752584499659891747680315726078002853876058955863276687817154"
		"0458953514382464234321326889464182768467546703537516986049910576"
		"5512820762454900903893289440758685084551339423045832369032229481"
		"6580855933212334827479782620414472316873817718091929988125040402"
		"6184124858368.000000\0");
}

int		ft_flags(t_printf **p, long double *num, char *str, int tab[4])
{
	if ((*p)->minus)
		return (f_minus(p, num, str, tab));
	else if ((*p)->zero)
		return (f_zero(p, num, str, tab));
	else
		return (f_def(p, num, str, tab));
}
