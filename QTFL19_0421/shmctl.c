//shmctl.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 654321L

main()
{
  int shmid;
  key_t key;
  int meret = 512;
  int flg, rtn, sm;
  struct shmid_ds shmid_ds, *buf;

  buf = &shmid_ds;
  key = SHMKEY;
  flg = 0;

  if((shmid = shmget(key, meret, flg)) < 0)
  {
     perror("\n Sikertelen volt a shmget!");
     exit(-1);
  }

  do {
    printf("\n Valasszon a menubol");
    pritnf("\n 0. status lekerese");
    printf("\n 1. memoria torlese");
    scanf("%d", &sm);
  }while(sm < 0 && sm > 1);

  switch(sm)
  {
    case 0: rtn = shmctl(shmid, IPC_STAT, buf);
	    printf("\n meret: %d", buf->shm_segsz);
	    printf("\n pid: %d", buf->shm_lpid);
	    break;
    case 1: rtn = shmctl(shimd, IPC_RMID, NULL);
	    printf("\n szegmens megsz�ntetve");
  }

  exit(0);
}
