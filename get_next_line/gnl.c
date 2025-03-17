#include "get_next_line.h"

int ft_found_newline(char *str_buf)
{
	int i;

	if (!str_buf)
		return (0);
	i = 0;
	while (str_buf[i])
	{
		if (str_buf[i] == '\n')
			return (1); //* true
		i++;
	}
	return (0); //*false
}

char * ft_read_join(char **str_buf, int fd)
{
	int		bytes_read;
	char	*buf;
	char	*temp;

	while (!ft_found_newline(*str_buf)) //* while ww do not find '\n' in static dt
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1); //* we allocat buf
		if (!buf)
			return (free(*str_buf), *str_buf = NULL, NULL);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0) //* if read fail and return -1
			return (free(*str_buf), *str_buf = NULL, free(buf), NULL);
		temp = ft_strjoined(*str_buf, buf); //* we added to static dt 
		//* we use temp so we free the last joind and give str_buf the new one 
		if (!temp)
			return (free(*str_buf), *str_buf = NULL, free(buf), NULL);
		free(*str_buf); //* free the last value
		*str_buf = temp; //* give it the new value 
		free(buf);//* free the buf we are done with it 
		if (bytes_read == 0)
			break; //* when we get to EOF 
	} 
	return (*str_buf);

}
char *get_next_line(int fd)
{
	static char *str_buf;
	char        *line;
	char        *temp;

	//! Part1: check for boundaries and leftovers
	//* in case we have (1) and str_buf still have something we free it and return NULL 
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024) //*1
	{
		if (str_buf)
		{
			free(str_buf);
			str_buf = NULL;
		}
		return (NULL);
	}
	//! Part2: read and add the buff read to static dt
	//* in case (2): ft_readandjoin fail we free static dt and we return NULL
	str_buf = ft_read_join(&str_buf, fd);
	if (!str_buf || !*str_buf) //* str_buf is NULL or str_buf is empty //*2
		return (free(str_buf), str_buf = NULL, NULL);
	//! Part3: extract line 
	line = ft_get_line(&str_buf);
	if (!line) //* in case lene extraction failed
		return (free(str_buf), str_buf = NULL, NULL);
	//! Part4: extract the rest after newline
	temp = ft_strdup(str_buf + ft_len_to_new_line(str_buf)); //* give the rest after '\n' to temp
	if (!temp)
		return (free(str_buf), free(line), str_buf = NULL, NULL);
	//! Part5: free the static dt to give it the rest 
	free(str_buf); //* free static dt, we gave the buf to line 
	//! Part6: give the rest to static dt 
	str_buf = temp; //* give the rest to str_buf for next time 
	//! Part7: return the line 
	return (line);
}