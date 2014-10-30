#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define MAX_COMMAND_SIZE 256
#define MAX_COMMAND_ARGUMENTS 15
#define HOST_NAME_MAX 20

int exec_external(char* command, char** argv);

main()
{
  int i, j, na;
  char *cwd, *pwd, *owd, *username, *systemname, *homedir,*nd, *comm, *temp, **arglist, **t;
  arglist    = (char**)malloc(MAX_COMMAND_ARGUMENTS*sizeof(char*));
  systemname = (char*)malloc(HOST_NAME_MAX*sizeof(char));
  comm       = (char*)malloc(MAX_COMMAND_SIZE*sizeof(char));
  homedir    = getenv ( "HOME" ); //get home directory address in variable
  username   = getenv ( "USER" ); //get username directory address in variable
  cwd        = getenv ( "PWD" );
  owd        = getenv ( "OLDPWD" );

 gethostname(systemname, HOST_NAME_MAX);
 do {
	t = arglist;
	arglist = (char**)malloc(MAX_COMMAND_ARGUMENTS*sizeof(char*));
	free(t);
	pwd = cwd;

	for(i = 0; *(cwd+i) != '\0'; i++)
	if(*(cwd+i) == '/')
	pwd = (cwd + i+1);
	printf("[%s@%s: %s]$ ",username,systemname,pwd);
	gets(comm);
        for(i = 0, j = 0, arglist[0] = comm; (i < MAX_COMMAND_ARGUMENTS - 1) && (comm[j+1] != '\0'); j++)
        if(comm[j] == ' ' && comm[j+1] != ' ')
        {
	       comm[j] = '\0';
	       arglist[++i] = comm+j+1;
	      }
	na = i;
	if(na == MAX_COMMAND_ARGUMENTS)
	printf("\nReached max arguments\n\n");
	if(!strcmp(arglist[0],"echo"))
	 {
	 for(i = 1; i <= na; i++)
	 printf("%s ",arglist[i]);
	 printf("\n");
	 }
	else if(strcmp(arglist[0],"cd") == 0)
	 {
	  i = 3;
	  if(arglist[1] == NULL)
	    {
	   if(homedir == NULL)
	   continue;
	   else
	    {
	     i = chdir(homedir);
	     nd = (char*)malloc(strlen(homedir)*sizeof(char));
	     strcpy(nd, homedir);
      }
    }
  else
    {
	   if(arglist[1][0] != '~')
	    {
	         i = chdir(arglist[1]);
           nd = (char*)malloc(strlen(arglist[1])*sizeof(char));
           strcpy(nd, arglist[1]);
      }
    else
      {
	        nd = (char*)malloc((strlen(arglist[1])+strlen(homedir))*sizeof(char));
          strcpy(nd,homedir);
          i = chdir(strcat(nd, arglist[1]+1));
       }
    }

       if(i == 0)
       {
	 temp = owd;
	 owd  = cwd;
	 cwd  = nd;
	 if((temp != getenv("OLDPWD")) && (temp != getenv("PWD")))
	 free(temp);
       }
     }
     else if(strcmp(arglist[0],"quit"))
     {
	if(exec_external(arglist[0],arglist))
	printf("myshell: %s: command unable to execute\n", arglist[0]);
     }
  }while(strcmp(arglist[0],"quit"));
 }

int exec_external(char* command, char** argv)
   {
    pid_t pid;
    pid = fork();
    if(pid == 0)
    return execvp(command,argv);
    else
      wait(NULL);
      return 0;
  }
