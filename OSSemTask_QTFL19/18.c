#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#define MSGKEY 6543L
#define MSGSZ 4

struct msgbuf {
  long mtype;
  int mtext[MSGSZ];
}sendbuf, *msg;

void main()
{
FILE* fp;
FILE* ki;

int x,y,z;
int q;

int msgid; 
key_t key;
int msgflg;
int ret;

key = MSGKEY;
msgflg = 00666 | IPC_CREAT;
msgid = msgget(key, msgflg);
if(msgid == -1)
{
  perror("\n Az msgget rendszerhívás sikertelen.");
  exit(-1);
}

msg = &sendbuf;

fp = fopen("haromszog.txt", "r");
if(fp == NULL)
{
  perror("Nem sikerült a fájlmegnyitás.");
}

fscanf(fp, "%d %d %d", &x, &y, &z);
printf("Az oldalak hossza: \n x = %d \n y = %d \n z = %d \n", x, y, z);

fclose(fp);

if((x+y)>z && (y+z)>x && (x+z)>y)
{
  q = 1;
  printf("\nEzekből az oldal méretekből szerkeszthető háromszög.\n");
}
else
{
  q = 0;
  printf("\nEzekből az oldal méretekből NEM szerkeszthető háromszög.\n");
}

ki = fopen("visszateres.txt", "w");

msg->mtype = 1;
msg->mtext[0] = x;
msg->mtext[1] = y;
msg->mtext[2] = z;
msg->mtext[3] = q;

ret = msgsnd(msgid,(struct msgbuf *)msg, MSGSZ, msgflg);
//printf("\nA vissza kapott értékek : ");
for(int i = 0; i < MSGSZ; i++)
{
  fprintf(ki, "%d", msg->mtext[i]);
  //printf("%d", msg->mtext[i]);
}
fclose(ki);
}