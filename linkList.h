#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED

struct node
{
    node *prev;
    int distanceTotal=0;
    int estimatedDistance=0;
    int x;
    int y;
};
void destroy (node *linkList);

#endif // LINKLIST_H_INCLUDED
