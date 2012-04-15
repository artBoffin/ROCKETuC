/* 
 * This file is part of the ROCKETuC firmware project
 *
 * Copyright (C) 2011 Stefan Wendler <sw@kaltpost.de>
 *
 * The ROCKETuC firmware is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ROCKETuC firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the ROCKETuC firmware; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.  
 */

#ifndef __CONIO_H_
#define __CONIO_H_

/**
 * Print a character to the console.
 *
 * @param[in] c		character to print
 */
void cio_printc(char c);

/**
 * Print a string to the console.
 *
 * @param[in] *line	string to print	
 */
void cio_print(char *line);

/**
 * Print an integer to the console.
 *
 * @param[in] n		number to print	
 */
void cio_printi(int n);

/**
 * Print a number in binary to the console.
 *
 * @param[in] n		number to print	
 * @param[in] size	number of bits to use
 */
void cio_printb(int n, int size);

/**
 * Print a formated string. The following formt specifiers could
 * be used in the format string:
 * <pre>
 * String			%s
 * Char          	%c
 * Integer       	%i
 * Unsigned      	%u
 * Long          	%l
 * unsigned long 	%n
 * heX          	%x
 * </pre>
 * @param[in] *format	the format string
 * @param[in] ...		the values to put into the format string
 */
void cio_printf(char *format, ...);

/**
 * Read a character form the console.
 *
 * @return	character read from the console
 */
char cio_getc();

#endif
