#include <stdio.h>
#include <unistd.h>

//UNNAMED

int main(){

   int fd[2]; // Itt foglalunk helyet a két fájlleírónak.
   int child;

   /* A pipe függvény megnyitja, és létrehozza a csõvezetéket, illetve visszaadja fd változóban a két fájlleírót. */
   if( pipe(fd)){
    perror("pipe");
    return 1;
   }

   child = fork();

   if(child > 0) {
    char s[1024];
    close(fd[1]);
    read(fd[0], s, sizeof(s));
    printf("%s", s);

    /* A szülõfolyamat lezárja az íróvéget, mert csak olvasni fog, majd kiolvassa az üzenetet, és lezárja az olvasóvéget is. */
    close(fd[0]);

   } else if(child == 0) {

    /* A gyerekfolyamat lezárja az olvasóvéget, mert csak írni fog, majd beírja az üzenetet, és lezárja az íróvéget is. */
      close(fd[0]);
      write(fd[1], "RE QTFL19 \n", 12);
      close(fd[1]);
    }

  return 0;
}
