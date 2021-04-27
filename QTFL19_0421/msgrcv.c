#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// kulcs
#define MSGKEY 2222L

struct msgbuf1 {
	long mtype;
	int  t[11];

} recvbuf, *msgp;		/* message buffer es pointere */

struct msqid_ds ds, *buf;	/* uzenetsorhoz asszocialt struktura
					 es pointere*/

main()
{	int i;
	int hanyszam;
	int msgid;		/* uzenetsor azonosito */
	key_t key;		/* kulcs az uzenetsorhoz */
	int mtype, msgflg;	/* tipus, flag */
	int ret, msgsz;		/* return es meret */

	key = MSGKEY;		/* beallitom a kulcsot */
	msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

	msgid = msgget(key, msgflg);
 	if (msgid == -1) {
                perror("msgget() nem sikerult");
                exit(-1);
        }
	printf("Az msgid: %d\n",msgid);

	msgp = &recvbuf;	/* uzenetfogado buffer cime */
	buf = &ds;		/* uzenetsor jellemzo adataihoz */
	msgsz = 100;		/* max hossz */
	mtype = 0;		/* minden tipust varok */

	ret = msgctl(msgid, IPC_STAT, buf); /* uzenetsor adatokat lekerdezem */
	printf("Az uzenetek szama az uzenetsorban: %d\n", buf->msg_qnum);

	int ossz[10];
	int j=0;
	/*while (buf->msg_qnum) {*/		/* van-e uzenet?*/
		/* veszem a kovetkezo uzenetet: */
		ret = msgrcv(msgid,(struct msgbuf *)msgp, msgsz, mtype, msgflg);

		for( i=1;i<msgp->t[0];i++){
		ossz[j]=(msgp->t[i]);
		printf("msgrcv() visszaadta: %d, a kapott uzenet: %s\n",ret, msgp->t[i]);
		j++;
		}
		ret = msgctl(msgid, IPC_STAT, buf); /* uzenetsor adatokat lekerdezem,
						     benne azt is, hany uzenet van meg */


	//}
	ret = msgctl(msgid, IPC_RMID, NULL);	// uzenetsor torles msgctl()-el, IPC_RMID !
	printf ("\n Visszatert: %d\n", ret);

	//ide kiírni a fájlokba elõtte létre kell hozni parancssorban a fájlokat


	int fd=open("rendezett.txt",O_RDWR);
	if (fd == -1) {
	    perror("open() hiba!");
	    exit(-1);
	}
	char* ki=(char*)malloc(2*(msgp->t[0])+1);
        for(i=1; i<msgp->t[0]; i++)
        {
          char c[2];
          sprintf(c,"%d\n", ossz[i]);
 	  ki=strcat(ki, c);
        }
	 ret=write(fd,ki,2*(msgp->t[0]));

        printf("%d\n",ret);
	close(fd);


	exit(0);
	}


