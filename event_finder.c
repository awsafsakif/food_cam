#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    FILE* file = fopen("/proc/bus/input/devices", "r");
    char line[256];
    
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
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
    return 0;
}
