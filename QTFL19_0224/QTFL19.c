#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *text;
    text = fopen("Ront�.txt", "r");
    fprintf(text, "Ront� Eszter, Programtervez� info, QTFL19");
    int fclose( FILE *text);
    return 0;
}
