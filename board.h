#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include "libraries.h"
#include "linkList.h"

class coord
{
    public:
    int x;
    int y;
    void getCoord (void);
};
int dummyproof(void);
void getCoord (int *x, int *y);
void setBoard (node *linkList, char **board);
double getSize (node *linkList);
bool locationCheck (node *linkList, int x, int y, bool valid);

#endif // BOARD_H_INCLUDED
