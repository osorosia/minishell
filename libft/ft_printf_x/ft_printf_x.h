/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 07:45:17 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/02 20:50:40 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_X_H
# define FT_PRINTF_X_H

// private`
char	*xspec_d(va_list ap);
char	*xspec_s(va_list ap);
char	*xspec(va_list ap, char c);

#endif
