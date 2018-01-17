#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE* file = fopen("/proc/bus/input/devices", "r");
    char line[256];
    
    while (fgets(line, sizeof(line), file)) {
        //printf("%s", line);
        if(strstr(line, "6604") != NULL) {
            for(int i=0; i < 5; i++) {fgets(line, sizeof(line), file);}
            break;
        }
    }
    
    char ctostr[2];
    ctostr[1] = '\0';
    int i = 0;
    int len = strlen(line);
    while(i < len) {
        if(isdigit(line[i])) {
             ctostr[0] = line[i];
             break;
        }
        ++i;
    }   
    fclose(file);
    
    char dest_init[100] = "/dev/input/event";
    strncat(dest_init, ctostr, 2);
    printf(dest_init);
    
    int fd;
    
    fd = open(dest_init, O_RDONLY);
    struct input_event ev;
    

    char buffer[100];
    int evCode;
    while (1)
    {
        read(fd, &ev, sizeof(struct input_event));

        if(ev.type == 1)
            //printf("key %i state %i\n", ev.code, ev.value);
            if(ev.value == 0) {
                //printf(" : [key %i]\n ", ev.code);
		// Save the input to a string
		evCode = ev.code;
		sprintf(buffer + strlen(buffer), "%i", evCode);
                
		//Check input string for the 4 key combination from the button
		if (strstr(buffer, "125972231") != NULL) {
		    system("echo button pressed >> /home/pi/Desktop/freefood/log.txt");
                    system("sudo python /home/pi/Desktop/freefood/foodButton.py &");
               	    printf("Button Pressed \n");
                    buffer[0] = '\0';
                    //printf("String reset to size %i", strlen(buffer));
        	}
		else if(strlen(buffer) >=9) {
			buffer[0] = '\0';
			printf("Input not being received from button. Check /var/log/syslog");
		}
	}
	
    }

    return 0;
}
