#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "linux/input.h"

//Keyboard hook
int main() {
    //event5 for mouse position
    //EV_ABS: ABS_X, ABS_Y
    //event4 for mouse buttons
    //EV_KEY: BTN_LEFT, BTN_RIGHT, BTN_MIDDLE
    //EV_REL: REL_WHEEL, REL_HWHEEL
    //event2: for keyboard
    int fd1 = 0;
    if( (fd1 = open("/dev/input/event2", O_RDONLY | O_NDELAY | O_NOCTTY)) > 0 )
    {
        struct input_event event;
        unsigned int scan_code = 0;
        bool exit_sign = false;
        ssize_t evt_size = sizeof(event);

        printf("Try read %ld bytes\n", evt_size);

        while (!exit_sign)
        {
            ssize_t n = read(fd1, &event, evt_size);
            if (n == (ssize_t)-1)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK )
                    continue;
                else
                {
                    printf("Unknown error:%d\n", errno);
                    break;
                }
            }
            else if (n != evt_size)
            {
                printf("Unexpected event:%ld\n", n);
                return -1; // Keyboard events are always of type EV_KEY
            }

            //if(event.type == EV_MSC || event.type == SYN_REPORT)
            //{
            //    continue;
            //}

            if(event.type != EV_KEY) continue;
            if(event.value != 1) continue;

            printf("type:%x, code:%x, value:%x\n", event.type, event.code, event.value);

            if(event.value == EV_KEY)
            {
                scan_code = event.code;
                printf("read back scan_code is: %d \n", scan_code);
                if (scan_code == KEY_X)
                    exit_sign = true;
            }
        }
        close(fd1);
    }
}
