#include "header.h"


bool broken_connection = false;
pthread_mutex_t mutex;
char *root_directory;

void sigpipe_handler()
{
    printf("CLIENT BROKE CONNECTION\n");
    broken_connection = true;
}


int init (int *s)
{
    int sock;
    struct sockaddr_in svc_addr;

    if((sock = socket(AF_INET, SOCK_STREAM,0)) < 0)
    {
        perror("CANT CREATE SOCKET");
        return(ERROR_CREATE_SOCKET_FAILED);
    }
    memset((char *)&svc_addr, 0, sizeof(svc_addr));
    svc_addr.sin_family = AF_INET;
    svc_addr.sin_addr.s_addr = htonl(INADDR_ANY);  
    svc_addr.sin_port = htons(SERVER_FTP_PORT);   

    int flag = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int));
    if(bind(sock, (struct sockaddr *)&svc_addr, sizeof(svc_addr)) < 0)
    {
        perror("CANR BIND");
        close(sock);
        return(ERROR_BIND_FAILED);
    }
    listen(sock, MAX_CLIENTS);
    *s = sock;

    return(GOOD);
}

int send_message(int s, char *message, int size_of_message)
{
    int i;

    for(i = 0; i < size_of_message; i++)
    {
        fprintf(stdout,"%c",message[i]);
    }
    fprintf(stdout,"\n");

    if((send(s, message, size_of_message, 0)) < 0)
    {
        if (broken_connection == true)
        {
            close(s);
            broken_connection = false;
        }
        else
        {
            fprintf(stderr, "COULDNT SEND MESSAGE\n");
        }

        return(ERROR_SEND_FAILED);
    }
    return(GOOD);
}

int receive_message(int s, char *tmp, int size_of_tmp, int *size_of_message )
{
    int i;
    *size_of_message = recv(s, tmp, size_of_tmp, 0);

    if(*size_of_message < 0)
    {
        if (broken_connection == true)
        {
            close(s);
            broken_connection = false;
        }
        else
            fprintf(stderr, "COULDNT RECIEVE MESSAGE\n");

        return(ERROR_RECEIVE_FAILED);
    }

    for(i = 0; i < *size_of_message; i++)
    {
        fprintf(stdout, "%c", tmp[i]);
    }
    fprintf(stdout,"\n");

    return (GOOD);
}

void process_command_line(int size_of_message, const char *user_command_line, char *arg, char *command_line)
{
    int i = 0, j = 0;

    memset(command_line, 0, 1024);
    memset(arg, 0, 1024);
    while(user_command_line[i] == ' ')
    {
        i++;
    }
    while(i < size_of_message && user_command_line[i] != ' ' && user_command_line[i] != '\n')
    {
        command_line[j] = user_command_line[i];
        i++;
        j++;
    }
    while(user_command_line[i] == ' ')
    {
        i++;
    }
    j = 0;
    if(user_command_line[i] == '"') 
    {
        i++;
        while(i < size_of_message && user_command_line[i] != '"')
        {
            arg[j] = user_command_line[i];
            i++;
            j++;
        }
    }
    else
    {
        while(i < size_of_message && user_command_line[i] != ' ' && user_command_line[i] != '\n')
        {
            arg[j] = user_command_line[i];
            i++;
            j++;
        }
    }
}

void remove_substring(char *str1, char *str2)
{
    char* tmp;
    tmp = strstr(str1, str2);
    strcpy(str1, tmp + strlen(str2));
}


void option_ls(char *reply_message)                                                      
{   
    char *directory = get_current_dir_name();
    DIR *dir = opendir(directory);                                                              

    struct dirent *dir_entry;                                                                   
    struct stat file_stat;                                                                     
    while ((dir_entry = readdir(dir)) != NULL)                                                
    {    
        if (!(strcmp(dir_entry->d_name, ".") && strcmp(dir_entry->d_name, "..")))
        {
            continue;
        }

        char temp_name[255];
        strcpy(temp_name, directory);
        strcat(temp_name, "/");
        strcat(temp_name, dir_entry->d_name);
        lstat(temp_name, &file_stat); 

        if (S_ISDIR(file_stat.st_mode))                                                        
        {
            strcat(reply_message, dir_entry->d_name);
            strcat(reply_message, "/\n");
        }

        if (S_ISREG(file_stat.st_mode))                                                        
        {
            strcat(reply_message, dir_entry->d_name);
            strcat(reply_message, "\n");
        }

        if (S_ISLNK(file_stat.st_mode))                                                       
        {
            char link_target[1024];
            memset(link_target, 0, 1024);

            ssize_t len = readlink(dir_entry->d_name, link_target, 1024 - 1);
            if (len != -1) 
            {
                link_target[len] = '\0';
                char arrow_type[6];
                struct stat st;

                memset(arrow_type, 0, 6);

                if (lstat(link_target, &st) == 0 && S_ISREG(st.st_mode)) 
                {
                    strcpy(arrow_type, "-->");
                }
                else 
                {
                    strcpy(arrow_type, "-->>");
                }

                remove_substring(link_target, root_directory);
                remove_substring(link_target, "/");
                
                strcat(reply_message, dir_entry->d_name);
                strcat(reply_message, " ");
                strcat(reply_message, arrow_type);
                strcat(reply_message, " ");
                strcat(reply_message, link_target);
                strcat(reply_message, "\n");
            }
        }
    }

    closedir(dir);                                                                              
}

void option_cd(char *arg, char *reply_message, int *counter)
{

    char *substr;
    char dir[1024];
    char olddir[1024];
    int counter_start = counter;

    memset(dir, '\0', 1024);
    strcpy(olddir,get_current_dir_name());

    pthread_mutex_lock(&mutex);

    substr = strtok(arg, "/\n");
    while(*substr == ' ') substr++;
    if((strcmp(substr, "..") == 0 && *counter <= 0))
    {
        strcpy(dir, root_directory);
    }
    else if (strcmp(substr, "..") == 0)
    {
        (*counter)--;
        strcat(dir, substr);
    }
    else if (strcmp(substr, ".") != 0)
    {
        (*counter)++;
        strcat(dir, substr);
    }
    
    while ((substr = strtok(NULL, "/\n")) != NULL)
    {
        if((strcmp(substr, "..") == 0 && *counter <= 0))
        {
            continue;
        }

        if(strcmp(substr, ".") == 0)
            continue;
        
        strcat(dir, "/");
        if (strcmp(substr, "..") == 0)
        {
            (*counter)--;
            strcat(dir, substr);
        }
        else 
        {
            (*counter)++;
            strcat(dir, substr);
        }
    }
    printf("%s\n", dir);

    int res = chdir(dir);
    if (chdir(dir) != 0)
    {
        sprintf(reply_message, "NO SUCH DIRECTORY FOUND\n");
    } 
    else
    {
        sprintf(reply_message, "cmd 250 ok\n");
    }
    
    pthread_mutex_unlock(&mutex);
}

void option_info(char *tmp, char *reply_message)
{
    pthread_mutex_lock(&mutex);
    strcpy(tmp, "WELCOME TO MY_SERVER! SERVER IS READY WOR WORK!\n"
                   "ENTER HELP TO GET AVAILABLE COMMANDS.");
    sprintf(reply_message, "cmd 250 ok \n%s\n", tmp);
    pthread_mutex_unlock(&mutex);
}

void option_echo(char *arg, char *reply_message)
{
    sprintf(reply_message, "\n%s\n", arg);
}

void option_help(char *reply_message)
{
    strcpy(reply_message, "AVAILABLE COMMANDS:\n"
                      "HELP — ВЫВОД ПОМОЩИ\n"
                      "ECHO — ЭХО-ЗАПРОС, КОТОРЫЙ ВОЗВРАЩАЕТ ПОЛУЧЕННОЕ БЕЗ ИЗМЕНЕНИЯ\n"
                      "INFO — ПОЛУЧЕНИЕ ИНФОРМАЦИИ О СЕРВЕРЕ\n"
                      "CD   — СМЕНА ТЕКУЩЕГО КАТАЛОГА\n"
                      "LIST — СПИСОК ОБЪЕКТОВ ИЗ ТЕКУЩЕГО КАТАЛОГА\n"
                      "QUIT — ЗАВРЕШЕНИЕ СЕАНСА\n"
                      "ВВОД МОЖЕТ ПРОИЗВОДИТЬСЯ КАК С ПОМОЩЬЮ CAPS-LOCK, ТАК И БЕЗ\n");
}

void *func_for_client(void *args)
{
    int info = *(int*) args;
    int counter = 0;
    char user_command_line[1024];	
    char command_line[1024];		
    char arg[1024];
    char reply_message[4115];
    char tmp[4096];
    int status;
    int msg_size;       

    memset(reply_message, '\0', sizeof(reply_message));
    memset(reply_message, '\0', sizeof(user_command_line));
    memset(tmp, '\0', sizeof(tmp));

    option_info(tmp, reply_message);
    status = send_message(info, reply_message, strlen(reply_message) + 1);
    if(status != GOOD)
    {
        fprintf(stderr, "ERROR CONNECTING\n");
        exit(status);
    }

    do
    {
        memset(reply_message, '\0', sizeof(reply_message));
        memset(reply_message, '\0', sizeof(user_command_line));
        memset(tmp, '\0', sizeof(tmp));
        status = receive_message(info, user_command_line, sizeof(user_command_line), &msg_size);
        if(status < 0)
        {
            fprintf(stdout,"ERROR GETTING COMMAND\n");
            break;
        }
        process_command_line(msg_size, user_command_line, arg, command_line);
        fprintf(stdout,"CLIENT COMMAND IS %s\n", command_line);
        fprintf(stdout,"ARGUMENT IS  %s\n", arg);
        lower(command_line);
        
        if(strcmp(command_line, "list") == 0)
        {
            option_ls(reply_message);
        }
        else if(strcmp(command_line, "cd") == 0)
        {
            option_cd(arg, reply_message, &counter);
        }
        else if(strcmp(command_line, "echo") == 0)
        {
            option_echo(arg, reply_message);
        }
        else if(strcmp(command_line, "info") == 0)
        {
            option_info(tmp, reply_message);
        }
        else if(strcmp(command_line, "help") == 0) 
        {
            option_help(reply_message);
        }
        else if(strcmp(command_line, "quit") == 0) 
        {
            memset(reply_message, '\0', sizeof(reply_message));
            strcpy(reply_message, "CMD 231 OKAY, USER LOGGER OUT\n");
        } 
        else
        {
            sprintf(reply_message, "CMD 202 IS NOT VALID COMMAND\n");
        }

        status = send_message(info, reply_message, strlen(reply_message) + 1);
        if(status < 0)
        {
            break;
        }
    }while(strcmp(command_line, "quit") != 0);

    fprintf(stdout,"CLOSING CLIENT SOCKET\n");
    close (info);  
    pthread_exit(NULL);
}




int main(int argc, char *argv[])
{
    int socket_of_server;   
    int socket_of_client;  
    int status = GOOD;
    
    signal(SIGPIPE, sigpipe_handler);

    if (argc != 2)
    {
        fprintf(stderr, "HOW TO USE: ./server \"ROOT DIRECTORY FOR SERVER\"\n");
        exit(status);
    }

    if (chdir(argv[1]) < 0) 
    {
        perror("chdir");
        exit(status);
    }

    root_directory = get_current_dir_name();

    fprintf(stdout, "SERVER INIT\n");
    status = init(&socket_of_server);
    if (status != 0) 
    {
        fprintf(stdout, "INIT ERROR\n");
        exit(status);
    }

    fprintf(stdout, "FTP-SERVER WAITS FOR CLIENT CONNECTION\n");
    pthread_mutex_init(&mutex, NULL);

    while (true) 
    {
        struct sockaddr_in addr_of_client;
        socklen_t addr_of_client_length = sizeof(addr_of_client);
        socket_of_client = accept(socket_of_server, (struct sockaddr*) &addr_of_client, &addr_of_client_length);
        if (socket_of_client < 0) 
        {
            perror("CAN'T CREATE CONNECTION: ");
            fprintf(stderr, "SERVER HAD TO STOP WORKING!!!\n");
            close(socket_of_server);
            continue;
        }
        fprintf(stdout, "GOT ACCESS TO NEW CLIENT\n");
        pthread_t thread;
        int client = socket_of_client;
        if ((pthread_create(&thread, NULL, func_for_client, &client)) != 0) 
        {
            fprintf(stderr, "ERROR CONNECTING TO CLIENT\n");
            break;
        }
        pthread_detach(thread);
    }
    pthread_mutex_destroy(&mutex);
    fprintf(stdout,"CLOSING SOCKET SERVER\n");
    close(socket_of_server);
    return 0;
}

