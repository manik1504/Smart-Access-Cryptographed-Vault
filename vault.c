#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */ 
#include <errno.h>   /* ERROR Number Definitions           */
#include <time.h> 
  
void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) 
        ; 
}  
int upin=1511;
/*Function Declaration and definition for LOGIN Module*/
void login()
{
	printf("\nEnter the login pin:");
	int pin;					/*Storing user entered PIN*/
	scanf("%d",&pin);

	if(upin!=pin)					/*PIN verification*/
	{
		printf("\nWrong PIN Entered\n");
		exit(0);				/*Exit on Wrong PIN*/
	}
	
}
/*Function Declaration and definition for MOVE Module*/
void move()
{
	system("chmod +rwx .vault");			/*Giving Execution rights to user*/
	system("clear");

	printf("\t\t\t\t\tSmart Access Cryptographed Vault");
	printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tMove a FILE to the vault");
	printf("\n\n\n\t\t\t\t\tEnter the path of the file: ");			/*Source path input*/
	char path[2000];
	scanf("%s",path);
	printf("\n\t\t\t\t\tSource File:%s",path);
	char ch,ch1;
	printf("\n\t\t\t\t\tPress Enter to move the file to the vaultðŸ˜€");
	scanf("%c",&ch);
	ch1 = getchar ();
	if(ch1==10)								/*Detecting Enter key press*/
	{
		printf("\n\t\t\t\t\tFile Moving ...\n");
	}
	char task[2000]="mv ";
	strcat(task,path);							/*Creating the execution command*/
	strcat(task," .vault");
	if(system(task)==0)
	{

	printf("\n\t\t\t\t\tFile Moving Successful\n");

	}

	/*task[2000]="rm ";
	strcat(task,path);							/*Removing File from the source path
	system(task);*/
	system("chmod -rwx .vault");						/*Restricting permission*/
       
}
/*Function Declaration and definition for REMOVE Module*/
void removefile()
{
	system("chmod +rwx .vault");						
	system("clear");
	printf("\t\t\t\t\tSmart Access Cryptographed Vault");
	printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tRemove a FILE from the vault");
	printf("\n\n\n\t\t\t\t\tEnter the name of the file: ");
	char name[2000];
	scanf("%s",name);
	printf("\n\n\n\t\t\t\t\tEnter the new path of the file: ");
	char path[2000];
	scanf("%s",path);
	char ch,ch1;
	printf("\n\t\t\t\t\tPress Enter to Remove the file from the vaultðŸ˜€");
	scanf("%c",&ch);
	ch1 = getchar ();
	if(ch1==10)
	{
		printf("\n\t\t\t\t\tFile Removing ...\n");
        char task[2000]="mv ";
	strcat(task,name);
	strcat(task," ");
	strcat(task,path);
	system(task);
        
	}
        else {printf("\n\t\t\t\t\tERROR.....\n");}

	
	/*task[2000]="rm ";
	strcat(task,name);
	system(task);*/
	
system("chmod -rwx .vault");
}

    	void main(void)
    	{
        	int fd;/*File Descriptor*/

		/* Change /dev/ttyUSB0 to the one corresponding to your system */

        	fd = open("/dev/ttyACM0",O_RDWR | O_NOCTTY | O_NDELAY);                                        
		if(fd == -1)						/* Error Checking */
            	   printf("\n  Error! in Opening ttyUSB0  ");
        	else
            	   printf("\n  ttyUSB0 Opened Successfully.Scan your card. ");

	
		/*---------- Setting the Attributes of the serial port using termios structure --------- */
		
		struct termios SerialPortSettings;	/* Create the structure                          */

		tcgetattr(fd, &SerialPortSettings);	/* Get the current attributes of the Serial port */
		cfsetispeed(&SerialPortSettings,B9600); /* Set Read  Speed as 9600                       */
		cfsetospeed(&SerialPortSettings,B9600); /* Set Write Speed as 9600                       */

		SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
		SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
		SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
		SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */
	
		SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
		SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 
		
		
		SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
		SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

		SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/

		if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
		    printf("\n  ERROR ! in Setting attributes");
		else{
                    printf("\n");
delay(3000); 

			
			}
	        /*------------------------------- Write data to serial port -----------------------------*/

		char write_buffer[100];	/* Buffer containing characters to write into port	     */	
		int  bytes_written  = 0;  	/* Value for storing the number of bytes written to the port */ 

		bytes_written = read(fd,write_buffer,sizeof(write_buffer));/* use write() to send data to port                                            */
									     /* "fd"                   - file descriptor pointing to the opened serial port */
									     /*	"write_buffer"         - address of the buffer containing data	            */
									     /* "sizeof(write_buffer)" - No of bytes to write                               */	


if(write_buffer[0]=='1')
{

login();						/*Initiating login module*/
	system("mkdir -p vault");
	system("mv vault .vault");				/*Creating Vault on new system*/
	system("chmod -rwx .vault");
	int opt;
	a:
	system("clear");
	printf("\nChoose one of the following option\n ");
	printf("1. Moving a file in the vault\n ");
	printf("2. Removing a file from the vault\n ");
    	printf("3. Viewing the files in vault\n ");
    	printf("4. Logout & Exit\n ");
    	scanf("%d", &opt);
   
	switch(opt)
	{
        	case 1:

move();
            		goto a;

		case 2:
		        removefile();
            		goto a;

        	case 3:
            		system("chmod +rwx .vault");
	    		system("ls .vault");
	    		system("chmod -rwx .vault");
				
            		break;
				

        	case 4:
        		exit(0);
           		break;

        	default:
            		printf("Error! enter the correct option");
	}
}
else if(write_buffer[0]=='0')
{
printf("\n\n\n\nNot allowed");
}
		

	close(fd);/* Close the Serial port */


    	}

