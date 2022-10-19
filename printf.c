#include "main.h"

void print_buffer(char buffer[], int *buff_inf);

/**
 * _printf - function that produces output according to a format.
 * @format: format.
 * Return: printed chars
 */
int _printf(const char *format, ...)
{
	int i, pri = 0, print_char = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_list(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
		       	if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1); */
			print_char++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i list);
			size = get_size(format, &i);
			++i;
			pri = handle_print(format, &i, list, buffer,
					flags, width, precision, size);
			if (pri == -1)
				return (-1);
			print_char += pri;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (print_char);
}

/**
 * printf_buffer - Prints the content of the buffer if it exists
 * @buffer: array of chars
 * @buff_ind: index of which to add next char, if it exists
 */
void printf_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
