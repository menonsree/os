#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<sys/stat.h>
 int main(int argc, char* argv[]){
 char dirname[10]; 
 DIR*p;            	//The DIR data type represents a directory stream.
 struct dirent *d; 	//The structure, struct dirent refers to directory entry.
			/*	struct dirent {
    				ino_t          d_ino;       ( inode number)
   			 	char           d_name[256];  ( filename )


			*/ 
 int i=0;
 struct stat buf;
 struct stat *filestat = &buf;
/* for(i=0;i<argc;i++)
 {
 printf("count:%d\n parameters: %s\n",argc,argv[i]);
 }*/
 if(argc==2)
 {
 printf("Enter directory name\n");
 scanf("%s",dirname);

  p=opendir(dirname);
  if(p==NULL)
   {
    printf("Cannot find directory");
    exit(-1);
   }
  while(d=readdir(p))
   {
  if((d->d_name[0])!='.')
  printf("%s\n",d->d_name); 
   }
 }
 else if(argc==3)
 { 
 if(argv[3]=='a')
 {
 printf("Enter directory name\n");
 scanf("%s",dirname);
 p=opendir(dirname);
 if(p==NULL)
   {
    printf("Cannot find directory");
    exit(-1);
   }
 while(d=readdir(p))
 printf("%s\n",d->d_name);
 }
 }

 else if(argc==3)
 {
switch(argv[2])
{
case"-a":
 	printf("Enter directory name\n");
 	scanf("%s",dirname);
 	p=opendir(dirname);
 	if(p==NULL)
   	{
    	printf("Cannot find directory");
    	exit(-1);
   	}
 	while(d=readdir(p))
 	printf("%s\n",d->d_name);
  	
 case"-l": printf("Enter directory name\n");
         scanf("%s",dirname);
   p=opendir(dirname);
  if(p==NULL) {
    printf("Cannot find directory");
    exit(-1);
  }
  while(d=readdir(p)){
  if (stat(dp->d_name, filestat)!= -1)
    {
    printf("File Size: \t\t%d bytes\n",filestat->st_size);
    printf("Number of Links: \t%d\n",filestat->st_nlink);
    printf("File inode: \t\t%d\n",filestat->st_ino);
    }
  }
}
return 0;
}
 :
