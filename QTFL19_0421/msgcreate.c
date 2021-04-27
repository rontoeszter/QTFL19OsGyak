#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

// kulcs
#define MSGKEY 2222L

struct msgbuf1 {
	long mtype;
	int  t[11];

} sendbuf, *msgp;		/* message buffer es pointere */

main()
{

	int msgid;		/* uzenetsor azonosito */
	key_t key;		/* kulcs az uzenetsorhoz */
	int msgflg;		/* flag a kreaciohoz, uzenetkuldeshez */
	int ret, msgsz;		/* return es meret */
	int i,j,temp,r=0;
	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT; // jogosultsag + letrehozas flag
	msgid = msgget(key, msgflg);
 	if (msgid == -1) {
                perror(" msgget() nem sikerult!");
                exit(-1);
        }
	printf("Az msgid letrejott: %d, %x\n", msgid,msgid);

	msgp        = &sendbuf;
	msgp->mtype = 1;   			/* tipus = text */

    printf("add meg a db szamot\n");
    scanf("%d",&(msgp->t[0]));
    printf("toltsd fel a tombot\n");
    for (i=1;i<msgp->t[0];i++)
    {
    	scanf("%d",&(msgp->t[i]));
    }
    j=1;

    while(r==0){
    	r=1;
	for (i=(msgp->t[0])-1;i>j;i--)
		{
		if( msgp->t[i] < msgp->t[i-1] )
		        {
		            temp=msgp->t[i];
		            msgp->t[i]=msgp->t[i-1];
		            msgp->t[i-1]=temp;
		            r=0;
		        }

		}
	j++;
    }
    printf("a szamok sorrendben:\n");
    for (i=1;i<msgp->t[0];i++)
    {
    	printf("%d\n",msgp->t[i]);
    }




	msgsz       = sizeof(int)*((msgp->t[0])+1);	/* az uzenet hossza */
	/* bekuldes az uzenetsorba */
        ret = msgsnd(msgid,(struct msgbuf *)msgp, msgsz, msgflg);

	printf("Az 1. msgsnd() visszaadott: %d\n", ret);





	exit(0);
}
