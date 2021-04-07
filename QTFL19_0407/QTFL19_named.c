#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//NAMED

int main()
{
    int child;

    /* Itt hozzuk létre a FIFO fájlt. A felhasználónak írási és olvasási joga lesz.*/
    mkfifo("qtfl19", S_IRUSR | S_IWUSR);

    child = fork();

    if(child > 0) {
        char s[1024];
        int fd;

    /* A szülőfolyamat megnyitja a fájlt olvasásra, mert csak olvasni fog, majd kiolvassa az üzenetet. */
    fd = open("qtfl19", O_RDONLY);
    read(fd, s, sizeof(s));
    printf("%s", s);

    /* Lezárja és törli a fájlt */
    close(fd);
    unlink("qtfl19");
    }else if(child == 0){
      int fd;

    /* A gyerekfolyamat megnyitja a fájlt írásra, mert csak írni fog, majd beleírja az üzenetet, végül lezárja. */
    fd = open("qtfl19", O_WRONLY);
    write(fd, "RE QTFL19 \n", 12);
    close(fd);
    }

    return 0;
}
