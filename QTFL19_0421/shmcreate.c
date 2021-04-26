//shmcreate.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMKEY 654321L

int main()
{
  int shmid;
  key_t key;
  int meret = 512;
  int flg;

  key = SHMKEY;
  flg = 0;
  if((shmid = shmget(key, meret, flg)) < 0)
  {
     //m�g nincs ilyen szegmens
     flg = 00666 | IPC_CREAT;
     if((shmid = shmget(key, meret, flg)) < 0)
     {
	perror("\n Sikertelen volt a shmget!");
	exit(-1);
     }
  }
  //else = van m�r ilyen szegmens

  printf("Az azonos�t� : %d", shmid);
  return 0;
}
