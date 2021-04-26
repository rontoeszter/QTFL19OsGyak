#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>
#define MSGKEY 654321L



struct msgbuf1 {
	long mtype;
	char mtext[512];
} sndbuf, *msgp;		// Üzenet buffer és pointere

struct msqid_ds ds, *buf;




int main()
{
	int msgid;		// Üzenetsor azonosító
	key_t key;		// Kulcs az üzenetsorhoz
	int msgflg;		// flag a kreáciohoz, üzenetküldéshez
	int rtn, msgsz;		// return es méret

	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT;
	msgid = msgget( key, msgflg);

 	if ( msgid == -1) {
                perror("\n Az msgget rendszerhívás sikertelen!");
                exit(-1);
        }


	msgp = &sndbuf;
	msgp->mtype = 1;   			// Text típus
 	strcpy(msgp->mtext,"Az egyik üzenet");
	msgsz = strlen(msgp->mtext) + 1;	// Az üzenet hossza

    rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);

	strcpy(msgp->mtext,"Másik üzenet");
	msgsz = strlen(msgp->mtext) + 1;
	rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);

if (msgp->mtext == "exit"){     //Ha exit az üzenet, kilép
    exit(0);
}


	key_t kulcs;		// Kulcs az üzenetsorhoz
	int tipus;      // Típusa
	int meret;		// Méret

	kulcs = MSGKEY;		// Beállítom a kulcsot
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(kulcs, msgflg);
 	if ( msgid == -1) {
                perror("\n Az msgget rendszerhívás sikertelen!");
                exit(-1);
        }
	printf("\n Az üzenet ID: %d\n\n",msgid);

	msgp = &sndbuf;
	buf = &ds;
	meret = 20;
	tipus = 0;
	rtn = msgctl(msgid,IPC_STAT,buf);

	rtn = msgrcv(msgid,(struct msgbuf *)msgp, meret, tipus, msgflg);
	rtn = msgctl(msgid,IPC_STAT,buf);

do {
    printf("\n Válasszon a menübõl");
    printf("\n 0. Üzenet darabszám");
    printf("\n 1. 1 üzenet kiolvasása");
    printf("\n 2. Üzenetsor megszüntetése");
    printf("\n 3. Kilépés\n");
    scanf("%d", &msgid);
  }while(msgid < 0 && msgid > 1);

  switch(msgid)
  {
    case 0:
        printf("\n Az üzenetek száma: %ld\n",buf->msg_qnum);
        break;

    case 1:
        printf("\n A kiküldött üzenet: %s\n", msgp->mtext);
        break;

    case 2:
        rtn = msgctl(msgid, IPC_RMID, NULL);
        printf("\n Üzenetsor megszüntetve\n");
        break;

    case 3:
        exit(0);
  }
}
