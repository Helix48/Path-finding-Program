#include "board.h"
#include "linkList.h"

int dummyproof(void) //dummproofing program function
{
    int input; //declares variables
    bool check;
    do//do statement to repeat program if error
    {
        cin>>input;//gets input from the user
        check=true; //sets check to true to prevent errors
        if(cin.fail()) //checks if integer from 1 to 20 was entered
        {
            input=0; //set variables to 0/false
            check=false;
            cout<<"Illegal value. Try again"<<endl; //displays error message
        }
        cin.clear(); //clears cin error
        cin.ignore(100,'\n'); //clears input buffer
    }
    while (check==false); //repeats if conditions are met
    return input; //keeps value of input for use later
}
void coord::getCoord (void)
{
    cout<<"x: ";
    x=dummyproof();
    if (x>=0)
    {
    cout<<"y: ";
    y=dummyproof();
    cout<<endl;
    }
    else
        y=x;
}
void setBoard (node *linkList, char **board)
{
    if (linkList!=NULL)
    {
        setBoard(linkList->prev,board);
        if (board[linkList->x][linkList->y]!='@')
        board[linkList->x][linkList->y]='#';
    }
}
double getSize (node *linkList)
{
    if (linkList->prev!=NULL)
    getSize(linkList->prev);
    else
        return linkList->distanceTotal;

}
