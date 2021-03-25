#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd, ret;
    char buf[32];

    buf[0] = 0;

    //O_RDONLY - O_RDWR - O_WRONLY -- ezekbol valamelyik kotelezo
    //O_APPEND -- minden write utan a vegere pozicional
    //O_CHEAT -- letrehozas
    //O_TRUNC

    fd = open("QTFL19.txt", O_RDWR);

    if (fd == -1) {
        perror("open() hiba!");
        exit(-1);
    }

    ret = read(fd, buf, 32); //ret: mennyit sikerult olvasni
    printf("read() olvasott %d byteot, ami a kovetkezo: %s\n", ret, buf);
    strcpy(buf, "QTFL19");

    ret = lseek(fd, 0, SEEK_SET); //SEEK_CUR, SEEK_END - ret: hova allt be tenylegesen
    printf("lseek() mondja: %d\n", ret);

    ret = write(fd, buf, 6); //ret: mennyit irt ki valojaban
    printf("write() mondja: %d\n", ret);

    close(fd);

    return 0;
}
