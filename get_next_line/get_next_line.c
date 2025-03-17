#include "get_next_line.h"


size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}


size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t			len;
	size_t			i;

	len = ft_strlen(src);
	if (dstsize != 0)
	{
		i = 0;
		while (src[i] && i < dstsize - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (len);
}
char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*cpy;
	int		i;

	if (!s1)
		return (NULL);
	size = ft_strlen((char *)s1);
	cpy = malloc(sizeof(char) * (size + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[size] = '\0';
	return (cpy);
}
static char	*ft_filljoin(char *tofill, const char *str_buf, const char *buf)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str_buf[i])
	{
		tofill[i] = str_buf[i];
		i++;
	}
	j = 0;
	while (buf[j])
	{
		tofill[i] = buf[j];
		i++;
		j++;
	}
	tofill[i] = '\0';
	return (tofill);
}

char	*ft_strjoined(char const *str_buff, char const *buf)
{
	char	*strjn;
	size_t	len;

	if (!str_buff && !buf)
		return (NULL);
	if (!str_buff)
		return (ft_strdup(buf));
	if (!buf)
		return (ft_strdup(str_buff));
	len = ft_strlen(str_buff) + ft_strlen(buf);
	strjn = malloc((len + 1) * sizeof(char));
	if (!strjn)
		return (NULL);
	strjn = ft_filljoin(strjn, str_buff, buf);
	return (strjn);
}

int	ft_found_newline(char *str_buf)
{
	int	i;

	if (!str_buf)
		return (0);
	i = 0;
	while (str_buf[i])
	{
		if (str_buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_len_to_newline(char *str_buf)
{
	int	len;

	if (!str_buf)
		return (0);
	len = 0;
	while (str_buf[len] && str_buf[len] != '\n')
		len++;
	if (str_buf[len] == '\n')
		len++;
	return (len);
}

char	*ft_get_line(char **str_buf)
{
	int		len;
	char	*line;

	if (!*str_buf)
		return (NULL);
	len = ft_len_to_newline(*str_buf);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *str_buf, len + 1);
	return (line);
}

char	*ft_read_join(char **str_buff, int fd)
{
	int		bytes_read;
	char	*buf;
	char	*temp;

	while (!ft_found_newline (*str_buff))
	{
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buf)
			return (free(*str_buff), *str_buff = NULL, NULL);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(*str_buff), *str_buff = NULL, free(buf), NULL);
		buf[bytes_read] = '\0';
		temp = ft_strjoined(*str_buff, buf);
		if (!temp)
			return (free(*str_buff), *str_buff = NULL, free(buf), NULL);
		free(*str_buff);
		*str_buff = temp;
		free(buf);
		if (bytes_read == 0)
			break ;
	}
	return (*str_buff);
}

char	*get_next_line(int fd)
{
	static char	*str_buf;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
	{
		if (str_buf)
		{
			free(str_buf);
			str_buf = 0;
		}
		return (NULL);
	}
	str_buf = ft_read_join(&str_buf, fd);
	if (!str_buf || !*str_buf)
		return (free(str_buf), str_buf = NULL, NULL);
	line = ft_get_line(&str_buf);
	if (!line)
		return (free(str_buf), str_buf = NULL, NULL);
	temp = ft_strdup(str_buf + ft_len_to_newline(str_buf));
	if (!temp)
		return (free(str_buf), free(line), str_buf = NULL, NULL);
	free(str_buf);
	str_buf = temp;
	return (line);
}