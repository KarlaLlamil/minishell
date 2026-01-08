/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crirodr2 <crirodr2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:24:11 by crirodr2          #+#    #+#             */
/*   Updated: 2025/11/20 12:21:26 by crirodr2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

char	*sepjoin(char const *s1, char const *s2, char sep);
char	**strict_split(char const *s, char c);
void	free_arr(char ***arr);

#endif
