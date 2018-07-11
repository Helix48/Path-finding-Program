#include "libraries.h"
#include "board.h"

void breadthFirstSearch (int **previousBoardPaths, node*&shortestPath, vector <coord> points, vector <node*> nodesToExpand, int *index, int maxX, int maxY)
{
    int distanceAdded;
    if (nodesToExpand.size()>0)
    {
        node *path=nodesToExpand[0];
        int changes[8][2]= {{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
        nodesToExpand.erase(nodesToExpand.begin());
        for (int counter=0; counter<8; counter++)
        {
            distanceAdded=10;
            if (abs(changes[counter][0])==1 and abs(changes[counter][1])==1)
                distanceAdded=14;
            if (!(path->x+changes[counter][0]==maxX or path->x+changes[counter][0]==-1 or path->y+changes[counter][1]==maxY or path->y+changes[counter][1]==-1))
                if (path->distanceTotal+distanceAdded<previousBoardPaths[path->x+changes[counter][0]][path->y+changes[counter][1]])
                {
                    previousBoardPaths[path->x+changes[counter][0]][path->y+changes[counter][1]]=path->distanceTotal+distanceAdded;
                    cout<<path->x<<" "<<path->y<<endl;
                    node *newNode;
                    newNode=new node;
                    newNode->prev=path;
                    newNode->x=path->x+changes[counter][0];
                    newNode->y=path->y+changes[counter][1];
                    newNode->distanceTotal=path->distanceTotal+distanceAdded;
                    if (newNode->x==points[*index+1].x and newNode->y==points[*index+1].y)
                        shortestPath=newNode;
                    else
                        nodesToExpand.push_back(newNode);
                }
        }
        breadthFirstSearch(previousBoardPaths,shortestPath,points,nodesToExpand,index,maxX,maxY);
    }
}
node *closestNodeFinder (vector <node*> &nodesToExpand)
{
    int index=0;
    node *path=new node;
    path=nodesToExpand[0];
    for (int counter=1; counter<nodesToExpand.size(); counter++)
        if (nodesToExpand[counter]->distanceTotal+nodesToExpand[counter]->estimatedDistance<=path->distanceTotal+path->estimatedDistance)
        {
            path=nodesToExpand[counter];
            index=counter;
        }
    nodesToExpand.erase(nodesToExpand.begin()+index);
    return path;
}
void aStarSearch (int **previousBoardPaths, node*&shortestPath, vector <coord> points, vector <node*> nodesToExpand, int *index, int maxX, int maxY)
{
    int diagonalMoves,distanceAdded;
    if (nodesToExpand.size()>0)
    {
        node *path=closestNodeFinder(nodesToExpand);
        int changes[8][2]= {{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
        for (int counter=0; counter<8; counter++)
        {
            distanceAdded=10;
            if (abs(changes[counter][0])==1 and abs(changes[counter][1])==1)
                distanceAdded=14;
            if (!(path->x+changes[counter][0]==maxX or path->x+changes[counter][0]==-1 or path->y+changes[counter][1]==maxY or path->y+changes[counter][1]==-1))
                if (path->distanceTotal+distanceAdded<previousBoardPaths[path->x+changes[counter][0]][path->y+changes[counter][1]])
                {
                    previousBoardPaths[path->x+changes[counter][0]][path->y+changes[counter][1]]=path->distanceTotal+distanceAdded;
                    node *newNode;
                    newNode=new node;
                    newNode->prev=path;
                    newNode->x=path->x+changes[counter][0];
                    newNode->y=path->y+changes[counter][1];
                    newNode->distanceTotal=path->distanceTotal+distanceAdded;
                    diagonalMoves=abs(newNode->x-points[*index+1].x);
                    if (abs(newNode->x-points[*index+1].x)>abs(newNode->y-points[*index+1].y))
                        diagonalMoves=abs(newNode->y-points[*index+1].y);
                    newNode->estimatedDistance=(abs(newNode->x-points[*index+1].x)-diagonalMoves)*10+(abs(newNode->y-points[*index+1].y)-diagonalMoves)*10+diagonalMoves*14; //
                    nodesToExpand.push_back(path);
                    if (newNode->x==points[*index+1].x and newNode->y==points[*index+1].y)
                    {
                        shortestPath=newNode;
                        nodesToExpand.clear();
                        break;
                    }
                    else
                        nodesToExpand.push_back(newNode);
                }
        }
    aStarSearch(previousBoardPaths,shortestPath,points,nodesToExpand,index,maxX,maxY);
    }
}
int main()
{
    int index=0,pathFindingMethod;
    coord newCoord;
    node *shortestPath=new node;
    vector <node*> nodesToExpand;
    vector <coord> points, barriers;
    cout<<"Input 1 to use breadth first search or input 2 to use a* search"<<endl;
    do
    {
        pathFindingMethod=dummyproof();
        if (pathFindingMethod!=1 and pathFindingMethod!=2)
            cout<<"Invalid input"<<endl;
    }
    while (pathFindingMethod!=1 and pathFindingMethod!=2);
    cout<<"Input the dimensions of the board"<<endl;
    do
    {
        newCoord.getCoord();
        if (newCoord.x<=0 or newCoord.y<=0 or newCoord.x+newCoord.y==2)
            cout<<"Invalid coordinate"<<endl;
    }
    while (newCoord.x<=0 or newCoord.y<=0 or newCoord.x+newCoord.y==2);
    const int maxX=newCoord.x,maxY=newCoord.y;
    char** board=new char*[maxX];
    for (int counter=0; counter<maxX; counter++)
        board[counter]=new char[maxY];
    for (int counter=0; counter<maxX; counter++)
        for (int counter2=0; counter2<maxY; counter2++)
            board[counter][counter2]='*';
    cout<<"Input the coordinates of at least two points that will be connected, input a negative to stop"<<endl;
    do
    {
        do
        {
            newCoord.getCoord();
            if (newCoord.x>=maxX or newCoord.y>=maxY)
                cout<<"Invalid Coordinate"<<endl;
        }
        while (newCoord.x>=maxX or newCoord.y>=maxY);
        if (newCoord.x>=0 and newCoord.y>=0)
            if (board[newCoord.x][newCoord.y]=='*')
            {
                board[newCoord.x][newCoord.y]='@';
                points.push_back(newCoord);
            }
            else
                cout<<"Invalid Coordinate"<<endl;
    }
    while (newCoord.x>=0 and newCoord.y>=0 or points.size()<2);
    cout<<"Now input coordinates in pairs to create a barrier, input a negative to stop"<<endl;
    do
    {
        do
        {
            newCoord.getCoord();
            if (newCoord.x>=maxX or newCoord.y>=maxY)
                cout<<"Invalid Coordinate"<<endl;
        }
        while (newCoord.x>=maxX or newCoord.y>=maxY);
        if (newCoord.x>=0 and newCoord.y>=0)
            barriers.push_back(newCoord);
    }
    while (newCoord.x>=0 and newCoord.y>=0);
    for (int counter=1; counter<barriers.size(); counter+=2)
    {
        if (barriers[counter-1].x>barriers[counter].x)
        {
            int temp=barriers[counter].x;
            barriers[counter].x=barriers[counter-1].x;
            barriers[counter-1].x=temp;
        }
        if (barriers[counter-1].y>barriers[counter].y)
        {
            int temp=barriers[counter].y;
            barriers[counter].y=barriers[counter-1].y;
            barriers[counter-1].y=temp;
        }
        for (int counter2=barriers[counter-1].x; counter2<=barriers[counter].x; counter2++)
            for (int counter3=barriers[counter-1].y; counter3<=barriers[counter].y; counter3++)
                if (board[counter2][counter3]!='@')
                    board[counter2][counter3]='&';
    }
    do
    {
        int**previousBoardPaths=new int*[maxX];
        for (int counter=0; counter<maxX; counter++)
            previousBoardPaths[counter]=new int[maxY];
        for (int counter=0; counter<maxX; counter++)
            for (int counter2=0; counter2<maxY; counter2++)
                previousBoardPaths[counter][counter2]=maxX*maxY*10;
        for (int counter=1; counter<barriers.size(); counter+=2)
            for (int counter2=barriers[counter-1].x; counter2<=barriers[counter].x; counter2++)
                for (int counter3=barriers[counter-1].y; counter3<=barriers[counter].y; counter3++)
                    if (board[counter2][counter3]!='@')
                        previousBoardPaths[counter2][counter3]=0;
        previousBoardPaths[points[index].x][points[index].y]=0;
        node *path;
        path=new node;
        path->y=points[index].y;
        path->x=points[index].x;
        path->prev=NULL;
        if (pathFindingMethod==1)
        {
            nodesToExpand.push_back(path);
            breadthFirstSearch(previousBoardPaths,shortestPath,points,nodesToExpand,&index,maxX,maxY);
        }
        else
        {
            int diagonalMoves=abs(path->x-points[index+1].x);
            if (abs(path->x-points[index].x)>abs(path->y-points[index+1].y))
                diagonalMoves=abs(path->y-points[index+1].y);
            path->estimatedDistance=(abs(path->x-points[index+1].x)-diagonalMoves)*10+(abs(path->y-points[index+1].y)-diagonalMoves)*10+diagonalMoves*14; //
            nodesToExpand.push_back(path);
            aStarSearch(previousBoardPaths,shortestPath,points,nodesToExpand,&index,maxX,maxY);
        }
        index++;
        if (shortestPath->distanceTotal!=0)
        {
            setBoard(shortestPath,board);
            destroy(shortestPath);
        }
        else
            cout<<"No path could be found."<<endl;
        nodesToExpand.clear();
        delete previousBoardPaths;
    }
    while (index!=points.size()-1);
        cout<<"hi"<<endl;
    for (int counter=0; counter<maxX; counter++)
    {
        for (int counter2=0; counter2<maxY; counter2++)
            cout<<board[counter][counter2]<<" ";
        cout<<" |"<<counter<<endl;
    }
    for (int counter=0; counter<maxY; counter++)
        if (counter<10)
            cout<<counter%10<<" ";
        else
            cout<<counter/10<<" ";
    cout<<endl;
    for (int counter=0; counter<maxY; counter++)
        if (counter<10)
            cout<<"  ";
        else
            cout<<counter%10<<" ";
    delete board;
    return 0;
}
