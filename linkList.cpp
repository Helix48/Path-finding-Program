#include "linkList.h"
#include "libraries.h"

void destroy (node *linkList)
{
    node *temp;
    node *current;
    current=linkList->prev;
    while (current!=NULL)
    {
        linkList->prev=current->prev;
        temp=current->prev;
        delete current;
        current=temp;
    }
    delete linkList;
}
