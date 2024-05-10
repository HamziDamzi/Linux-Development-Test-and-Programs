#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
 
#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)
 
int main()
{
        int fd;
        int32_t value;
        int number;
    
        printf("Test_App_for_IOCTL\n");
 
        printf("\nOpening Driver\n");
        fd = open("test.txt", O_RDWR);
        if(fd < 0) 
        {
                printf("Cannot open device file...\nMay be your Path for file is changed.\nI have set it according to my System.\nEnter Path According to your Choice.\n\n");
                return 0;
        }
 
        printf("Enter the Value to send\n");
        scanf("%d",&number);
        printf("Writing Value to Driver\n");
        ioctl(fd, WR_VALUE, (int32_t*) &number); 
 
        printf("Reading Value from Driver\n");
        ioctl(fd, RD_VALUE, (int32_t*) &value);
        printf("Value is %d\n", value);
        printf("\nIf does'nt print value, check file extenstion. Its working for my system\n\n");
 
        printf("Closing Driver\n");
        close(fd);
}
