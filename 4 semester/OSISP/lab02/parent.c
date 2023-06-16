#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int child_status;
extern char **environ;


int count(char** args);

char pick_opt();

void exchange(char** first, char** second);

void sort(char ***string,int size );

char *getpath(char **enviroment, char *name);

char *increasenum(char *str1, int num);

int main(int argc, char **args,  char **enviroment)
{
    
if(argc < 2)
{
	printf("You didn't enter path\n");
	exit(0);
}

int size = count(environ);

sort(&environ, size);

for (int i = 0; i < size; ++i) 
{
    printf("%s\n", environ[i]);
}

char *firstpath=getpath(enviroment,"CHILD_PATH");

char *secondpath = getpath(environ, "CHILD_PATH");

for (int j = 0; j <= 50; ++j) 
{
    	char *str = increasenum("CHILD_", j);
    	char *arguments[] = {str, args[1], (char*)0};
    	char a;
    	
    	printf("Enter option: +, *, & , q (to quit).\n");

       if((a = pick_opt()) == 'q')
        {
    		break;
    	}
    	
    	pid_t pid = fork();

    	if (pid == -1) 
        {
    	    printf("Process followed by error with code code - %d\n", errno);
    	    exit(errno);
    	}

        if(pid == 0)
        {
            switch(a)
            {
                case '+':
                
                printf("Child process with option + is created.\n");
    	        execve(getenv("CHILD_PATH"), arguments, enviroment);
                break;
            
                case '*':
                
                printf("Child process with option * is created.\n");
    	        execve(firstpath, arguments, enviroment);
                break;
                
                case '&':
                
                printf("Child process with option & is created.\n");
                execve(secondpath, arguments, enviroment);
                break;
                
            }
        }
    	
        wait(&child_status);
        free(str);
        printf("Child process ended with %d exit status\n", child_status);

}

        printf("Parent process ended.\n");   
        free(firstpath);
        free(secondpath);
        exit(0);
}

char *getpath(char **enviroment, char *name)
{
   char* result = (char*)calloc(255, sizeof(char));
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


int count(char** args)
{
	int size = 0;
    while(environ[size] != NULL)
    {
    	++size;
    }
    return size;
}

char pick_opt()
{
	char a;
	while(1)
    {
    	scanf("%c", &a);
		if(a == '+' || a == '*' || a == '&' || a == 'q') break;	
	}
	
	return a;
}

void exchange(char** first, char** second)
{
    char *buff = (*first);
    (*first) = (*second);
    (*second) = buff;
}

void sort(char ***string,int size )
{
    for (int i = 0; i < size - 1; ++i) 
    {
        for (int j = 0; j < size - i - 1; ++j) 
        {
            if (strcoll((*string)[j],(*string)[j+1]) > 0) 
            {
                exchange(&((*string)[j]),&((*string)[j+1]));
            }
        }
    }
}

char *increasenum(char *str1, int num)
{
    char check[10];

	int i = 0;
    int j = 0;

	if(num == 0)
	{
		check[i++] = num + '0';
	} 
    else 
    {
		while(num!=0)
        {
			check[i++] = (num% 10) + '0';
            num /= 10;
		};
	}
	
	check[i] =0;
    i=0;
    char *result = (char*)calloc((int)strlen(str1) + (int)strlen(check) + 1, sizeof(char));

    for(;j < (int)strlen(str1); ++j){
		result[i++] = str1[j];
	}

    j = (int)strlen(check) - 1;

	for(;j >= 0; --j){
		result[i++] = check[j];
	}

    return result;
}


