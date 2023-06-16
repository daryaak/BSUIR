#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <getopt.h>
#include <locale.h>
#include <langinfo.h>

void dirwalk(char* nameofdir, int check, int *size, char ***result) 
{
    DIR* Dir = opendir(nameofdir);
    if (Dir) 
    {
        struct dirent *temp; 
            while ((temp = readdir(Dir)) != NULL)
            {
                if (strcmp(temp->d_name, ".") && strcmp(temp->d_name, "..")) 
                {
                    char TempName[255];
                    strcpy(TempName, nameofdir);
                    strcat(TempName, "/");
                    strcat(TempName, temp->d_name);

                    if (temp->d_type == DT_DIR) 
                    {
                        dirwalk(TempName, check, size, result);
                    }

                    if(temp->d_type == DT_DIR &&( check==2||check ==0) )
                    {
                        (*result) = (char**)realloc((*result), sizeof(char*)*((*size) + 1)); 
                        (*result)[*size] = (char*)calloc(255 ,sizeof(char));
                        strcpy((*result)[*size], "[d] - ");
                        strcat((*result)[*size], TempName);
                        (*size) += 1;
                    } 

                    if(temp->d_type == DT_REG && (check==3||check==0))
                    {
                        (*result) = (char**)realloc((*result), sizeof(char*)*((*size) + 1)); 
                         (*result)[*size] = (char*)calloc(255 ,sizeof(char));
                        strcpy((*result)[*size], "[f] - ");
                        strcat((*result)[*size], TempName);
                        (*size) += 1;
                    } 

                    if(temp->d_type == DT_LNK && (check==1||check==0))
                    {
                        (*result) = (char**)realloc((*result), sizeof(char*)*((*size) + 1)); 
                         (*result)[*size] = (char*)calloc(255 ,sizeof(char));
                        strcpy((*result)[*size], "[l] - ");
                        strcat((*result)[*size], TempName);
                        (*size) += 1;
                    } 

                }
            }
       closedir(Dir);
    } 
}

int main(int argc, char* argv[]) 
{
   int Opt;
   int RSize = 0;
   char** Result = (char**)calloc((RSize)+1,sizeof(char*));
   int check =0 ;
   int S = 0;
   char NameOfDir[255];
   char buf[255];

    while ((Opt = getopt(argc, argv, "ldfs")) != -1) 
    {
        switch (Opt) {
        case 'l':
            check = 1;
            break;
        case 'd':
           check =2;
            break;
        case 'f':
            check=3;
            break;
        case 's':
            S =1;
            break;
        default:
            exit(EXIT_FAILURE);
        }
    }

    strcpy(NameOfDir,".");

    for(int i= 1; i<argc; ++i)  
    { 
        if ( (argv[i][0] =='/') || (argv[i][0] =='.'))
        {
            strcpy(NameOfDir,argv[i]);
        }
    }

    dirwalk(NameOfDir,check, &RSize, &Result);
    
    if(S == 1) 
    {
        for (int i = 0; i < RSize - 2; i++) 
        {
            for (int j = 0; j < RSize - i - 1; j++)
            {
                if (strcmp((Result)[j], (Result)[j + 1]) > 0) 
                {
                    strcpy(buf,Result[j]);
                    strcpy(Result[j],Result[j+1]);
                    strcpy(Result[j+1],buf);
                }
            }
        }
    }
     
    for(int i = 0;i < RSize; i++) 
    {
         printf("%s\n", Result[i]);
         free(Result[i]);
    }

    free(Result);
    return 0;
}