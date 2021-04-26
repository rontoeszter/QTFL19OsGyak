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
} sndbuf, *msgp;		// �zenet buffer �s pointere

struct msqid_ds ds, *buf;




int main()
{
	int msgid;		// �zenetsor azonos�t�
	key_t key;		// Kulcs az �zenetsorhoz
	int msgflg;		// flag a kre�ciohoz, �zenetk�ld�shez
	int rtn, msgsz;		// return es m�ret

	key = MSGKEY;
	msgflg = 00666 | IPC_CREAT;
	msgid = msgget( key, msgflg);

 	if ( msgid == -1) {
                perror("\n Az msgget rendszerh�v�s sikertelen!");
                exit(-1);
        }


	msgp = &sndbuf;
	msgp->mtype = 1;   			// Text t�pus
 	strcpy(msgp->mtext,"Az egyik �zenet");
	msgsz = strlen(msgp->mtext) + 1;	// Az �zenet hossza

    rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);

	strcpy(msgp->mtext,"M�sik �zenet");
	msgsz = strlen(msgp->mtext) + 1;
	rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);

if (msgp->mtext == "exit"){     //Ha exit az �zenet, kil�p
    exit(0);
}


	key_t kulcs;		// Kulcs az �zenetsorhoz
	int tipus;      // T�pusa
	int meret;		// M�ret

	kulcs = MSGKEY;		// Be�ll�tom a kulcsot
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(kulcs, msgflg);
 	if ( msgid == -1) {
                perror("\n Az msgget rendszerh�v�s sikertelen!");
                exit(-1);
        }
	printf("\n Az �zenet ID: %d\n\n",msgid);

	msgp = &sndbuf;
	buf = &ds;
	meret = 20;
	tipus = 0;
	rtn = msgctl(msgid,IPC_STAT,buf);

	rtn = msgrcv(msgid,(struct msgbuf *)msgp, meret, tipus, msgflg);
	rtn = msgctl(msgid,IPC_STAT,buf);

do {
    printf("\n V�lasszon a men�b�l");
    printf("\n 0. �zenet darabsz�m");
    printf("\n 1. 1 �zenet kiolvas�sa");
    printf("\n 2. �zenetsor megsz�ntet�se");
    printf("\n 3. Kil�p�s\n");
    scanf("%d", &msgid);
  }while(msgid < 0 && msgid > 1);

  switch(msgid)
  {
    case 0:
        printf("\n Az �zenetek sz�ma: %ld\n",buf->msg_qnum);
        break;

    case 1:
        printf("\n A kik�ld�tt �zenet: %s\n", msgp->mtext);
        break;

    case 2:
        rtn = msgctl(msgid, IPC_RMID, NULL);
        printf("\n �zenetsor megsz�ntetve\n");
        break;

    case 3:
        exit(0);
  }
}
