#include <stdlib.h>
#include <stdio.h>

#define MAX_CDS 1000000

int main(int argc, char* args[]) {
    int jack_catalog[MAX_CDS];
    int jill_catalog[MAX_CDS];
    int jack, jill;

    while (scanf("%d%d", &jack, &jill) == 2) {
        if (jack == 0 && jill == 0)
            break;

        for (int i = 0; i < jack; i++)
            scanf("%d", jack_catalog+i);
        for (int i = 0; i < jill; i++)
            scanf("%d", jill_catalog+i);

        int sell = 0;
        int jack_index = 0;
        int jill_index = 0;
        while (jack_index < jack && jill_index < jill) {
            int jack_catnum = jack_catalog[jack_index];
            int jill_catnum = jill_catalog[jill_index];
            if (jack_catnum == jill_catnum)
                sell++;
            } else if (jill_catnum < jack_catnum) {
                jill_index++;
            } else {
                jack_index++;
                jill_index++;
            }
        }
        
        printf("%d\n", sell);
    }

    return EXIT_SUCCESS;
}
