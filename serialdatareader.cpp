#include <iostream>
#include <cstdlib>
#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>     // string function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <termios.h>    // POSIX terminal control definitions

#include <string>
#include "serialdatareader.h"

struct termios tty;
int USB;
void configure_serial(int USB, int speed) {
    cfsetospeed (&tty, speed);

    tty.c_cflag &= ~PARENB;    // set no parity, stop bits, data bits
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag     &=  ~CRTSCTS;       // no flow control
    tty.c_lflag     =   0;          // no signaling chars, no echo, no canonical processing
    tty.c_oflag     =   0;                  // no remapping, no delays
    tty.c_cc[VMIN]      =   0;                  // read doesn't block
    tty.c_cc[VTIME]     =   5;                  // 0.5 seconds read timeout
    tty.c_cflag     |=  CREAD | CLOCAL;     // turn on READ & ignore ctrl lines
    tty.c_iflag     &=  ~(IXON | IXOFF | IXANY);// turn off s/w flow ctrl
    tty.c_lflag     &=  ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    tty.c_oflag     &=  ~OPOST;              // make raw
    tcflush( USB, TCIFLUSH );

    if ( tcsetattr ( USB, TCSANOW, &tty ) != 0)
    {
        std::cout << "Error " << errno << " from tcsetattr" << std::endl;
    }

}

int open_connection(const char* device) {

    int USB = open(device, O_RDWR | O_NOCTTY);
    if ( USB < 0 )
    {
        std::cout << "Error " << errno << " opening " << "/dev/ttyACM0" << ": " << strerror (errno) << std::endl;
    }
    configure_serial(USB, 2000000);
    return USB;
}

void close_connection(int &USB)
{
    close(USB);

    return;
}

void flush(void) {
    tcflush( USB, TCIFLUSH );
}

float read_line(int USB) {
    char buf[1];
    std::string st_value = "";
    float fl_value;

    while (buf[0] != '\r') {
        memset(&buf, '\0', sizeof buf);
        read( USB, &buf , sizeof buf );
        st_value += buf[0];
        //std::cout << buf[0] << std::flush;
    }


    try
    {
        fl_value = std::stof(st_value);
    }
    catch (const std::exception& e)
    {
        fl_value = 0.5;
    }

    return fl_value;
}
