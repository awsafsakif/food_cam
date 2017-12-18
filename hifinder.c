#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *ptr_file;
    char text[100];
    int i =0;
    char buf[200];
    char dest_init[] = "/sys/class/hidraw/hidraw";
    char dest_final[] = "/device/modalias";
    char dest[100];
    strcat(dest, dest_init);
    strcat(dest, "1");
    strcat(dest, dest_final);
    ptr_file = fopen(dest, "r");

    if (ptr_file != NULL) {
        fgets(text, sizeof(text), ptr_file);

        if(strstr(text, "6604") != NULL) {
            snprintf(buf, sizeof(buf), "echo HID we want %s", text);
        }
        else {
            snprintf(buf, sizeof(buf), "echo Not the HID we want %s", text);
        }

        system(buf);
        fclose(ptr_file);
    }
    return 0;
}
