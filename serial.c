#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*
	Description:		This program reads from serial port specifiad as "MODEMDEVICE" at a 
						baud rate specified as "BAUDRATE" and prints on the screen.
						It can be configured to print on a log file whatever is read from the
						serial port, adding a timestamp at th beggining of a line.
						It also speaks when an input has been detected and VOICE_THRESHOLD_SECS
						has been reached.

	Program:			serial.c
	Compile:			gcc serial.c -o serialc
	Run:				./serialc
	Programmer:			Michael Duarte
	Date:				May/2015
*/


/* baudrate settings are defined in <asm/termbits.h>, which is
included by <termios.h> */
#define BUF_SIZE 255
#define BAUDRATE B115200            
/* change this definition for the correct port */
#define MODEMDEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */

#define FALSE 0
#define TRUE 1

#define WRITE_TO_LOG 1

#define SPEAK_OUT 1
#define VOICE_THRESHOLD_SECS 6

volatile int STOP=FALSE; 

void runCommandOnChildProcess(const char *cmmnd){
	//since this function is only used to speak text, we can disable speaking from here
#ifdef SPEAK_OUT
	if(fork() == 0){
		system(cmmnd);
		exit(EXIT_SUCCESS);
	}
#endif
}

int main(int argc, char *argv[]){
    int fd,c, res;
    int firstSpeak = TRUE;
    struct termios oldtio,newtio;
    char buf[BUF_SIZE];
    /* 
    Open modem device for reading and writing and not as controlling tty
    because we don't want to get killed if linenoise sends CTRL-C.
    */
    fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY ); 
    if (fd <0) {
        perror(MODEMDEVICE);
        return (EXIT_FAILURE);
    }

    tcgetattr(fd,&oldtio); /* save current serial port settings */
    bzero(&newtio, sizeof(newtio)); /* clear struct for new port settings */

    /* 
    BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
    CRTSCTS : output hardware flow control (only used if the cable has
    all necessary lines. See sect. 7 of Serial-HOWTO)
    CS8     : 8n1 (8bit,no parity,1 stopbit)
    CLOCAL  : local connection, no modem contol
    CREAD   : enable receiving characters
    */
    newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

    /*
    IGNPAR  : ignore bytes with parity errors
    ICRNL   : map CR to NL (otherwise a CR input on the other computer
    will not terminate input)
    otherwise make device raw (no other input processing)
    */
    newtio.c_iflag = IGNPAR | ICRNL;

    /*
    Raw output.
    */
    newtio.c_oflag = 0;

    /*
    ICANON  : enable canonical input
    disable all echo functionality, and don't send signals to calling program
    */
    newtio.c_lflag = ICANON;

    /* 
    initialize all control characters 
    default values can be found in /usr/include/termios.h, and are given
    in the comments, but we don't need them here
    */
    newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */ 
    newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
    newtio.c_cc[VERASE]   = 0;     /* del */
    newtio.c_cc[VKILL]    = 0;     /* @ */
    newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
    newtio.c_cc[VTIME]    = 0;     /* inter-character timer unused */
    newtio.c_cc[VMIN]     = 2;     /* blocking read until 2 character arrives */
    newtio.c_cc[VSWTC]    = 0;     /* '\0' */
    newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */ 
    newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
    newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
    newtio.c_cc[VEOL]     = 0;     /* '\0' */
    newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
    newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
    newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
    newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
    newtio.c_cc[VEOL2]    = 0;     /* '\0' */

    /* 
    now clean the modem line and activate the settings for the port
    */
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);


#ifdef WRITE_TO_LOG
    /* Open file to log the received text and add the time to the logs*/
    char *filename = "log.txt";
    time_t rawtime, lastSpoke;
    FILE *f = fopen(filename, "a");
    if( f == NULL){
        printf("Could not open file %s. Logging will be disabled\n",filename);
    } else {
        printf("Logging enabled, saving as %s\n",filename);
    }
 #endif

    /*
    terminal settings done, now handle input
    In this example, inputting a 'z' at the beginning of a line will 
    exit the program.
    */
    int doubleEnterFix = FALSE;
    while (STOP==FALSE) {     /* loop until we have a terminating condition */
        /* read blocks program execution until a line terminating character is 
        input, even if more than BUF_SIZE chars are input. If the number
        of characters read is smaller than the number of chars available,
        subsequent reads will return the remaining chars. res will be set
        to the actual number of characters actually read */
        res = read(fd,buf,BUF_SIZE); 
        buf[res]=0;             /* set end of string, so we can printf */
#ifdef WRITE_TO_LOG
        FILE *f = fopen(filename, "a"); //append file
#endif
        time (&rawtime); // get current time
        char *timestring = ctime(&rawtime);// convert it to string
        int length = strlen (timestring); // get timestamp length
        timestring[length-1] = 0; // remove trailing line break

#ifdef SPEAK_OUT
        long long unsigned diff = (rawtime - lastSpoke);
        if ( diff > VOICE_THRESHOLD_SECS ){
	        if (firstSpeak){
        		runCommandOnChildProcess("espeak \"Booting system up\"");
        		firstSpeak = FALSE;
	        }
        	else{
        		runCommandOnChildProcess("espeak \"Motion detected\"");
        		printf("Previous voice notification : %llu secs ago.\n",diff);
        	}
    	
        	time (&lastSpoke);
    	}
#endif

        if(buf[0] == '\n'){
            if(doubleEnterFix){
                printf("%s", buf);
#ifdef WRITE_TO_LOG
                fprintf(f, "%s - (msg length:%d ): %s", timestring, res, buf);
#endif
                doubleEnterFix = FALSE;
            } else {
                doubleEnterFix = TRUE;
            }
        } else {
            doubleEnterFix = FALSE;
#ifdef WRITE_TO_LOG
            fprintf(f, "%s - (msg length:%d ): %s", timestring, res, buf);
#endif
            printf("%c",'\a');
            printf("(%d): %s", res, buf);
            if (buf[0]=='z') 
                STOP=TRUE;
        }
        fclose(f); // close file
    }
    /* restore the old port settings */
    tcsetattr(fd,TCSANOW,&oldtio);
    printf("Exiting serial.c\n");
    runCommandOnChildProcess("espeak \"Shutting system down\"");
    return EXIT_SUCCESS;
}