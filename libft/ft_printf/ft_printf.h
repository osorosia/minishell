/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 07:45:17 by rnishimo          #+#    #+#             */
/*   Updated: 2022/07/01 07:45:21 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// private
long		spec_c(va_list ap, int fd);
long		spec_d(va_list ap, int fd);
long		spec_p(va_list ap, int fd);
long		spec_s(va_list ap, int fd);
long		spec_u(va_list ap, int fd);
long		spec_x(va_list ap, int fd);
long		spec_X(va_list ap, int fd);
long		print_spec(char c, va_list ap, int fd);

#endif
