/*
 * Console.h
 *
 *  Created on: 17 Mar 2018
 *      Author: Janus
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "mbed.h"

#include "mbed-os/rtos/Thread.h"

#define INFO_TRACE(_class, _string, ...)    diag_printf( "%15s : " _string, _class, ##__VA_ARGS__)
#define DEBUG_TRACE(_lvl, _class, _string, ...)    dbg_printf(_lvl, "%15s : " _string, _class, ##__VA_ARGS__)
#define PRINT_REG(_base, _x)    diag_printf(#_x": 0x%08X\n", *((volatile CYG_WORD32 *)(_base + _x)));

#ifndef VT100_OFF
#define COLOR(__c,__x)    "\x1b[3" #__c "m" __x "\x1b[0m"
#define COLOR_BOLD(__c,__x)    "\x1b[3" #__c ";1m" __x "\x1b[0m"
#define UNDERLINE(__x) "\x1b[4m" __x "\x1b[0m"
#define CLEAR_SCREEN    "\x1b[2J\x1b[H"
#else
#define COLOR(__c,__x)    __x
#define COLOR_BOLD(__c,__x) __x
#define UNDERLINE(__x) __x
#define CLEAR_SCREEN
#endif
#define RED(__x)        COLOR(1, __x )
#define GREEN(__x)        COLOR(2, __x )
#define YELLOW(__x)        COLOR(3, __x )
#define BLUE(__x)        COLOR(4, __x )
#define MAGENTA(__x)    COLOR(5, __x )
#define CYAN(__x)        COLOR(6, __x )
#define RED_B(__x)        COLOR_BOLD(1, __x )
#define GREEN_B(__x)        COLOR_BOLD(2, __x )
#define YELLOW_B(__x)        COLOR_BOLD(3, __x )
#define BLUE_B(__x)        COLOR_BOLD(4, __x )
#define MAGENTA_B(__x)    COLOR_BOLD(5, __x )
#define CYAN_B(__x)        COLOR_BOLD(6, __x )

class Console
{
public:
    typedef void (*func_t)(int argc,char *argv[]);

    typedef struct
    {
        const char* cmd;
        const char* argDesc;
        const char* desc;
        func_t f;
    } cmd_list_t;

    static cmd_list_t *mCmdTable[];
    static void reset(int argc,char *argv[]);
    static void help(int argc,char *argv[]);
    static void dumpThreadInfo(int argc,char *argv[]);
    static void date(int argc,char *argv[]);

private:
    static Console *__instance;
    Serial *mSerial;

    const char *mPrompt;
    rtos::Thread work;

    char mBuffer[128];
    int mIndex;

    static void ReceiveSerial(Console *instance);
    void handleByte(char byte);
    void handleCommand(char *cmd);
    void process(int argc,char *argv[]);

    Console(Serial *serial, const char *prompt);

public:
    static void init(Serial *serial, const char *prompt);
	virtual ~Console();

};

extern const Console::cmd_list_t shellCommands[];

#endif /* CONSOLE_H_ */
