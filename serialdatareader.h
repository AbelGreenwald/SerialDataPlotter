#ifndef SERIALDATAREADER_H
#define SERIALDATAREADER_H

#include <string>

void configure_serial(int USB, int speed);
int open_connection(const char* device);
void close_connection(void);
float read_line(int USB);
void flush();
#endif // SERIALDATAREADER_H
