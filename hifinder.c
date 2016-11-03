#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv) {
    int i;
    
    
    char dest_init[] = "/sys/class/hidraw/hidraw";
    char dest_final[] = "/device/modalias";
     
    for(i=0; i<3; i = i + 1) {
    FILE *ptr_file;
    char dest[100];
    char buf[200];
    char str[1];
    char text[100];
    sprintf(str, "%d", i);
    strcat(dest, dest_init);
    strcat(dest, str);
    strcat(dest, dest_final);
    
    ptr_file = fopen(dest, "r");

    if (ptr_file != NULL) {
        fgets(text, sizeof(text), ptr_file);

        if(strstr(text, "6604") != NULL) {
            snprintf(buf, sizeof(buf), "echo HID we want %s", text);
            break;
        }
        else {
            snprintf(buf, sizeof(buf), "echo Not the HID we want %s", text);
        }

        system(buf);
        fclose(ptr_file);
        }
    dest[0] = '\0';
    }
    char file_path[100];
    char print_path[100];
    char destination[] = "/dev/hidraw";
    strcat(file_path, destination);
    char hid_no[1];
    sprintf(hid_no, "%d", i);
    strcat(file_path, hid_no);
    snprintf(print_path, sizeof(print_path), "echo file path: %s", file_path);
    system(print_path);    
    return 0;
}
