# include <dirent.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <sys/stat.h>
# include <sys/errno.h>



int		main(int ac, char **av, char **env)
{
	char *buff[2] = {"-e", 0};
	printf("%s\n", buff[0]);
	execve("/bin/cat", buff, env);
	return (0);
}