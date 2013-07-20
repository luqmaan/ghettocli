#ifndef _stacktrace_h
#define _stacktrace_h

#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void segmentation_handler(int sig);
void activate_segmentation_handler();

#endif
