/**************************************************************************************************/
/* Copyright (C) zhouzhaoyu, SSE@USTC, 2014-2015                                                  */
/*                                                                                                */
/*  FILE NAME             :  cmddemo.c                                                            */
/*  PRINCIPAL AUTHOR      :  zhouzhaoyu                                                           */
/*  SUBSYSTEM NAME        :  cmddemo                                                              */
/*  MODULE NAME           :  cmddemo                                                              */
/*  LANGUAGE              :  C                                                                    */
/*  TARGET ENVIRONMENT    :  ANY                                                                  */
/*  DATE OF FIRST RELEASE :  2014/09/13                                                           */
/*  DESCRIPTION           :  This is a cmd demo program                                           */
/**************************************************************************************************/

/*
 * Revision log:
 *
 * Created by zhouzhaoyu, 2014/09/13
 *
 */


#include <stdio.h>
#include <stdlib.h>

/*function for logic*/
int Helper();

#define CMD_MAX_LEN 128
#define DESC_LEN    1024
#define CMD_NUM     10

typedef struct DataNode
{
    char*   cmd;
    char*   desc;
    int     (*handler)();
    struct  DataNode *next;
} tDataNode;

int ShowAllCmd(tDataNode* head)
{	
    /*show all cmds */
    printf("Menu List:\n");
    tDataNode *p = head;
    while(p != NULL)
    {
        printf("%s - %s\n", p->cmd, p->desc);
        p = p->next;
    }
    return 0; 
}

tDataNode* FindCmd(char* cmd , tDataNode* head)
{
    if(cmd == NULL || head == NULL)
    {
        return NULL;
    }    
    tDataNode *p = head;
    while(p != NULL)
    {
    	if(!strcmp(p->cmd, cmd))
        {
            return p;
            break;
        }
        p = p->next;
    }
    if(p == NULL) 
    {
        return NULL;
    }

} 

static tDataNode head[] = 
{
    {"help", "this is help cmd!", Helper,&head[1]},
    {"version", "cmd demo program v1.0", NULL, &head[2]},
    {"author", "luoxiaobo sse ustc", NULL, &head[3]},
    {"college", "ustc", NULL, &head[4]},
    {"age", "seven", NULL, NULL}
};

main()
{
   /* cmd line begins */
    while(1)
    {
        char cmd[CMD_MAX_LEN];
        printf("Input a command > ");
        scanf("%s", cmd);
        tDataNode* p = FindCmd(cmd,head);
        if(p!=NULL)
        {
            printf("%s - %s\n", p->cmd, p->desc);
            if(p->handler != NULL)
            {
                p->handler();
            }
        }
        else
        {
            printf("This is a wrong cmd!\n ");
        }       
    }
}

int Helper ()
{    
    ShowAllCmd(head);
    return 0;
}