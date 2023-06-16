#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

char *getpath(char **enviroment, char *name);

int main(int argc, char **argv, char **environment) 
{
	if(argc < 2)
    {
		printf("You didn't enter path\n");
		exit(0);
	}
    printf("Child process %s starts!\n", argv[0]);
    printf("Pid is %d,Ppid is %d.\n", (int)getpid(), (int)getppid());
    printf("Path -  %s\n", argv[1]);
    
    char temp[255];

    FILE* f= fopen(argv[1], "r");
    if(f)
    {
    	while(fgets(temp, 255, f) != NULL){
            temp[strlen(temp) - 1] = 0;

    		char *buffer = getpath(environment, temp);
    		if(strlen(buffer))
            {
    			printf("%s is ", temp);
    			printf("%s\n", buffer);
    		}
    		free(buffer);
    	}
    } 
    else 
    {
    	printf("File is not opened.\n");
    }
    exit(0);
}

char *getpath(char **enviroment, char *name)
{
    char *result = (char*)calloc(255, sizeof(char));

int i = 0;
    while(enviroment[i])
    {
		int check = 1;
		int j = 0;

		for(; j < (int)strlen(name); ++j)
        {
			if(name[j] != enviroment[i][j])
            {
				check = 0;
				break;
			}
		}
		++j;
		int k = 0;
		if(check == 1)
        {
			while(j < (int)strlen(enviroment[i]))
				result[k++] = enviroment[i][j++];
			break;
		}
		++i;
	}
	return result;
}