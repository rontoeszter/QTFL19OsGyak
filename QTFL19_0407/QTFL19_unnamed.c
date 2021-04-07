#include <stdio.h>
#include <unistd.h>

//UNNAMED

int main(){

   int fd[2]; // Itt foglalunk helyet a k�t f�jlle�r�nak.
   int child;

   /* A pipe f�ggv�ny megnyitja, �s l�trehozza a cs�vezet�ket, illetve visszaadja fd v�ltoz�ban a k�t f�jlle�r�t. */
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

    /* A sz�l�folyamat lez�rja az �r�v�get, mert csak olvasni fog, majd kiolvassa az �zenetet, �s lez�rja az olvas�v�get is. */
    close(fd[0]);

   } else if(child == 0) {

    /* A gyerekfolyamat lez�rja az olvas�v�get, mert csak �rni fog, majd be�rja az �zenetet, �s lez�rja az �r�v�get is. */
      close(fd[0]);
      write(fd[1], "RE QTFL19 \n", 12);
      close(fd[1]);
    }

  return 0;
}
