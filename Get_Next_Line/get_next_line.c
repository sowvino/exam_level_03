    /* ************************************************************************** */
    /*                                                                            */
    /*                                                        :::      ::::::::   */
    /*   get_next_line.c                                    :+:      :+:    :+:   */
    /*                                                    +:+ +:+         +:+     */
    /*   By: selango <selango@student.42.fr>            #+#  +:+       +#+        */
    /*                                                +#+#+#+#+#+   +#+           */
    /*   Created: 2024-07-01 16:50:31 by selango           #+#    #+#             */
    /*   Updated: 2024-07-01 16:50:31 by selango          ###   ########.fr       */
    /*                                                                            */
    /* ************************************************************************** */

    #include <fcntl.h>
    #include <limits.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>

    #ifndef BUFFER_SIZE
    #define BUFFER_SIZE 10
    #endif

    size_t ft_strlen(const char *str)
    {
        size_t i;

        i = 0;
        while (str[i] != '\0')
            i++;
        return (i);
    }

    char *ft_strdup(const char *src)
    {
        char *new;
        int len;

        len = ft_strlen(src);
        new = (char *)malloc((len + 1) * sizeof(char));
        if (!new)
            return (0);
        while (len >= 0)
        {
            new[len] = src[len];
            len--;
        }
        return (new);
    }

    int ft_totlen(char *s1, char *s2)
    {
        int len1;
        int len2;
        int totlen;

        len1 = ft_strlen((char *)s1);
        len2 = ft_strlen((char *)s2);
        totlen = len1 + len2;
        return (totlen);
    }

    char *ft_strjoin(char const *s1, char const *s2)
    {
        int totlen;
        char *newstr;
        int i;
        int j;

        totlen = ft_totlen((char *)s1, (char *)s2);
        newstr = (char *)malloc((totlen + 1) * sizeof(char));
        if (newstr == NULL)
            return (NULL);
        i = 0;
        while (s1[i] != '\0')
        {
            newstr[i] = s1[i];
            i++;
        }
        j = 0;
        while (s2[j] != '\0')
        {
            newstr[i + j] = s2[j];
            j++;
        }
        newstr[i + j] = '\0';
        return (newstr);
    }

    char *ft_strchr(const char *s, int c)
    {
        char a;
        int i;

        a = (char)c;
        i = 0;
        while (s[i] != '\0')
        {
            if (s[i] == a)
            {
                return ((char *)&s[i]);
            }
            i++;
        }
        if (a == '\0')
        {
            return ((char *)&s[i]);
        }
        return (NULL);
    }

    char *ft_substr(const char *s, unsigned int start, size_t len)
    {
        char *substr;
        size_t i;
        size_t strlength;

        i = 0;
        if (s == NULL)
            return (NULL);
        strlength = ft_strlen((char *)s);
        if (start >= strlength)
            return (ft_strdup(""));
        if (start + len > strlength)
            len = strlength - start;
        substr = malloc((len + 1) * sizeof(char));
        if (substr == NULL)
            return (NULL);
        while (i < len && s[start + i] != '\0')
        {
            substr[i] = s[start + i];
            i++;
        }
        substr[i] = '\0';
        return (substr);
    }

    static char* read_lines(int fd,char *buff,char *store)
    {
        int bytes;
        char *temp;
        int iteration_count = 0;

        bytes = 1;
        while(bytes && iteration_count < 10000)
        {
            bytes = read(fd,buff,BUFFER_SIZE);
            if(bytes == -1)
                return(0);
            else if (bytes == 0)
                break;
            buff[bytes] = '\0';
            if(!store)
                store = ft_strdup("");
            temp = store;
            store = ft_strjoin(temp,buff);
            if(!store)
                return(NULL);
            free(temp);
            temp = NULL;
            if(ft_strchr(buff,'\n'))
                break;
        }
        return(store);
    }

    static char* update(char *lines)
    {
        int i;
        char *temp;

        i = 0;
        while(lines[i] != '\0' && lines[i] != '\n')
            i++;
        if(lines[i] == '\0')
            return(NULL);
        temp = ft_substr(lines, i + 1,ft_strlen(lines) - i);
        if(!temp)
            return(NULL);
        if(temp[0] == '\0')
        {
            free(temp);
            temp = NULL;
            return(NULL);

        }
        lines[i + 1] = '\0';
        return(temp);
    } 

    char *get_next_line(int fd)
    {
        char        *buff;
        char        *lines;
        static char *store;
        

        if (fd < 0 || BUFFER_SIZE <= 0)
            return(NULL);
        buff = malloc(sizeof(char) *(BUFFER_SIZE + 1));
        if(!buff)
            return(NULL);
        lines = read_lines(fd,buff,store);
        free(buff);
        if(!lines)
            return(NULL);
        store = update(lines);
        return(lines);
    }

    // #include <fcntl.h>
    // #include <stdio.h>

    // int	main(void)
    // {
    // 	int		fd;
    // 	char	*line;

    // 	fd = open("file.txt", O_RDONLY);
    // 	if (fd == -1)
    // 	{
    // 		perror("Error opening file");
    // 		return (1);
    // 	}
    // 	while ((line = get_next_line(fd)) != NULL)
    // 	{
    // 		printf("%s\n", line);
    // 		free(line);
    // 	}
    // 	close(fd);
    // 	return (0);
    // }
