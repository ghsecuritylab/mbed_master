/*
 * Console.cpp
 *
 *  Created on: 17 Mar 2018
 *      Author: Janus
 */
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include "mbed_stats.h"

#include "Console.h"

void Console::help(int argc,char *argv[])
{
   printf(GREEN("TermCMD commands:\r\n"));

   int index = 0;
   cmd_list_t* cmdList = mCmdTable[index++];
   while(cmdList)
   {
      cmd_list_t* t_ptr = 0;
      int k = 0;
      do
      {
         t_ptr = &cmdList[k++];
         if(!t_ptr || !t_ptr->cmd)
            break;

         if(t_ptr->f)
         {
            char txt[16];
            sprintf(txt,"%s %s", t_ptr->cmd, t_ptr->argDesc);
            printf("  %-10s - ",txt);
            printf("%s\r\n",t_ptr->desc);
         }
         else
         {
            //this is a caption
            printf(BLUE("%s\r\n"), t_ptr->cmd);
         }

      }while(t_ptr->cmd);

      cmdList = mCmdTable[index++];
   }

}

void Console::dumpThreadInfo(int argc,char *argv[])
{
    printf("Thread Info:\r\n");
    mbed_stats_stack_t stacks[10];
    int cnt = mbed_stats_stack_get_each(stacks, 10);
    for(int k = 0; k < cnt; k++)
    {
        printf("%d - TH[%lu]: max: %lu, res: %lu\r\n", k, stacks[k].thread_id, stacks[k].max_size, stacks[k].reserved_size);
    }
}

void Console::date(int argc,char *argv[])
{
    time_t seconds = time(0);

    if(argc > 5)
    {
        printf("Set time %s %s %s %s:%s\r\n", argv[1], argv[2], argv[3], argv[4], argv[5]);

        struct tm t;
        // adjust for tm structure required values
        t.tm_year = atoi(argv[1]) - 1900;
        t.tm_mon = atoi(argv[2]) - 1;
        t.tm_mday = atoi(argv[3]);
        t.tm_hour = atoi(argv[4]);
        t.tm_min = atoi(argv[5]);
        t.tm_sec = 0;
        set_time(mktime(&t));
    }

    seconds = time(0);
    printf("Seconds since January 1, 1970: %d\n", (int)seconds);
    printf("Date: %s\r\n", ctime(&seconds));

}

const Console::cmd_list_t shellCommands[] =
{
      {"MBED OS"    ,0,0,0},
      {"h",       "",                   "Show this help info", Console::help},
      {"dt",      "",                   "Dump Thread info", Console::dumpThreadInfo},
      {"date",    "<yyyy mm dd HH:MM>", "show / set current time", Console::date},
      {0,0,0}
};


Console *Console ::__instance = 0;

void Console::init(Serial *serial, const char *prompt)
{
    if(!__instance)
        __instance = new Console(serial, prompt);
}

Console::Console(Serial *serial, const char *prompt) : mSerial(serial), mPrompt(prompt)
{
    printf("New Console\r\n%s $", mPrompt);
    work.start(callback(ReceiveSerial, this));

    mIndex = 0;
}

Console::~Console()
{
}

void util_parse_params(char *str,char *argv[],int &argc,char delim1,char delim2)
{

   int max_args = argc;
   char * cmdl = str;
   bool done = false;
   argc = 0;
   char delim = delim1;
   while ( !done )
   {
      /* Strip Leading Whitespce */
      while ( isspace(*cmdl) )
      {
         if ( *cmdl )
         {
            cmdl++;
         }
         else
         {
            done = true;
            break;
         }
      }
      /* Now we are at an arg */
      if ( !done && *cmdl )
      {
         argv[argc] = cmdl;
         argc++;
         if(argc >= max_args)
         {
            done =true;
            break;
         }
      }
      /* Go to the next delim */
      while ( delim != *cmdl )
      {
         if ( *cmdl )
         {
            cmdl++;
         }
         else
         {
            done = true;
            break;
         }
      }
      if ( *cmdl )
      {
         *cmdl = 0;
         cmdl++;
      }
      else
      {
         done = true;
      }
      if(argc)
      {
         delim = delim2;
      }
   }
}

void Console::ReceiveSerial(Console *instance)
{
    while(__instance)
    {
        __instance->handleByte(__instance->mSerial->getc());
    }
}

void Console::handleByte(char byte)
{
    mSerial->putc(byte);

    mBuffer[mIndex] = byte;

    if(mIndex++ > 128)
    {
        handleCommand(mBuffer);
        return;
    }

    if((byte == '\n') || (byte == '\r'))
    {
        mSerial->putc('\n');

        mBuffer[mIndex - 1] = 0;
        if(mIndex > 1)
            handleCommand(mBuffer);

        mIndex = 0;

        printf("%s $", mPrompt);
    }
}

void Console::handleCommand(char *cmd)
{
    char *argv[10];
    int argc = 10;

    util_parse_params(cmd,argv,argc,' ',' ');
    process(argc, argv);
}

void Console::process(int argc,char *argv[])
{
   int index = 0;
   cmd_list_t* cmdList = mCmdTable[index++];

//   if(!strcmp(argv[0], "debug"))
//   {
//      cDebug::porcessDebug(t, argc, argv);
//      return;
//   }


   while(cmdList)
   {
      cmd_list_t* t_ptr = 0;
      int k = 0;
      do
      {
         t_ptr = &cmdList[k++];
         if(!t_ptr || !t_ptr->cmd)
            break;

//         //Special AT commands for modem
//         if(!strncmp(argv[0],"AT",2))
//         {
//            if(mMdm)
//               mMdm->ATcmd(t, argc, argv);
//
//            return;
//         }

         if(t_ptr->f && !strcmp(argv[0],t_ptr->cmd))
         {
            t_ptr->f(argc, argv);
            return;
         }
      }while(t_ptr->cmd);

      cmdList = mCmdTable[index++];
   }

   printf(RED("Unknown Command \'%s\'. Type help for a list of commands\r\n"), argv[0]);
}
