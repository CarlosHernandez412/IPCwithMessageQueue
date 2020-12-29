#include <stdio.h>
#include <stdlib.h>
#include <string.h>      /* string handling functions */
#include <unistd.h>      /* header file for the POSIX API */
#include <time.h>        /* to write time */
#include <sys/types.h>   /* standard data types for systems programming */
#include <sys/file.h>    /* file-related system calls */
#include <sys/wait.h>    /* for wait() system call */ 
#include <signal.h>      /* signal handling calls */ 
#include <errno.h>       /* for perror() call */
#include <sys/ipc.h>     /* header file for SysV IPC */
#include <sys/msg.h>     /* message queue calls */ 

#define BUFSZ 100 

void zeroOutBuffer (char *str)
{
	int i;
	for(i=0; i < BUFSZ; i++)
		str[i] =0;
}

int status =0;

int main( int argc, char *argv[]) 
{ 
	char buf[100];
	//char fstr[100];
	//char n = 0;
	int logf;
	int ret;
	char pathname[132];
	pid_t parent, cpid;
	
	
	getcwd(pathname, 128);
	strcat (pathname, "/foo");

   // int mqid; 
  
    // ftok to generate unique key 
   key_t ipckey = ftok(pathname, 65); 
  
  
	struct { 
    long type; 
    char text[100]; 
	} mymsg; 
  
	
    // msgget creates a message queue 
    // and returns identifier 
    int mqid = msgget(ipckey,IPC_CREAT | 0666  ); 
    
	cpid = fork();
	if(cpid<0) {
		perror ("fork: " );
		exit (0);
	}
  
	/* parent 
	
    // msgsnd to send message 
     
  
    // display the message 
    printf("Message received: %s \n", message.mesg_text); 
  
    return 0; 
} */
if (cpid == 0) { /* child  */
	
	logf = open ("log", O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if(logf == -1)
		perror("File open error: ");
	
	ret = msgrcv(mqid, &mymsg, sizeof(mymsg), 0, 0);
	strncpy(buf, mymsg.text, 100);
	write (logf, buf, strlen(buf));
	write (logf, "\n" , 1);
	 

    close (logf);
    exit (0);
    }
    else /*parent */
    {
 
		write(1, "Message to send: ", 17); 
		scanf("%100[a-zA-z]", buf);
		mymsg.type = 1;
		strncpy(mymsg.text, buf, 100); 
		if ( msgsnd(mqid, &mymsg, sizeof(mymsg), 0) == -1)
		{
			perror ("IPC msgsnd: ");
		}
		wait (&status);
    if (WIFEXITED (status))
    {
        sprintf (buf, "child exited with exit code %d\n", WEXITSTATUS(status));
        write (1, buf, strlen(buf));

		
		
		
    msgctl (mqid, IPC_RMID, 0);
		  exit(EXIT_SUCCESS);
	}
	}
	}
