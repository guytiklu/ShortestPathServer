#include "Interfaces.h"

class MySearchable : public Searchable<string>{
    int matrix[3][3];
    int n = 3;
public:
    MySearchable(){
        matrix[0][0]=6;
        matrix[0][1]=3;
        matrix[0][2]=5;
        matrix[1][0]=4;
        matrix[1][1]=4;
        matrix[1][2]=1;
        matrix[2][0]=8;
        matrix[2][1]=7;
        matrix[2][2]=100;
    }
    //node - state,cost,cameFrom
    int getValue(string str){
        int a,b;
        string delimiter = ",";
        a = stoi(str.substr(0, str.find(delimiter)));
        b = stoi(str.substr(str.find(delimiter), str.length()));
        return matrix[a][b];
    }
    Node<string> getInitialNode(){
        Node<string> n{};
        n.state = "0,0";
        n.cost = 0;
        n.cameFrom = NULL;
        return n;
    };
    Node<string> getGoalNode(){
        Node<string> n{};
        n.state = "2,2";
        n.cost = getValue(n.state);
        n.cameFrom = NULL;
        return n;
    };
    bool inField( int r, int c )
    {
        if( r < 0 || r >= n ) return false;
        if( c < 0 || c >= n ) return false;
        return true;
    }
    list<Node<string>> getNeighbours(Node<string>* nd){
        list<Node<string>> list;
        int i,j;
        int a,b;
        string str = nd->state;
        string delimiter = ",";
        a = stoi(str.substr(0, str.find(delimiter)));
        b = stoi(str.substr(str.find(delimiter), str.length()));

        if(inField(a,b+1)){
            Node<string> neigh;
            string str = to_string(a);
            str += ",";
            str += to_string(b+1);
            neigh.state=str;
            neigh.cameFrom = nd;
            neigh.cost= getValue(neigh.state)+getValue(neigh.cameFrom->state);
            list.push_front(neigh);
        }
        if(inField(a,b-1)){
            Node<string> neigh;
            string str = to_string(a);
            str += ",";
            str += to_string(b-1);
            neigh.state=str;
            neigh.cameFrom = nd;
            neigh.cost= getValue(neigh.state)+getValue(neigh.cameFrom->state);
            list.push_front(neigh);
        }
        if(inField(a-1,b)){
            Node<string> neigh;
            string str = to_string(a-1);
            str += ",";
            str += to_string(b);
            neigh.state=str;
            neigh.cameFrom = nd;
            neigh.cost= getValue(neigh.state)+getValue(neigh.cameFrom->state);
            list.push_front(neigh);
        }
        if(inField(a+1,b)){
            Node<string> neigh;
            string str = to_string(a+1);
            str += ",";
            str += to_string(b);
            neigh.state=str;
            neigh.cameFrom = nd;
            neigh.cost= getValue(neigh.state)+getValue(neigh.cameFrom->state);
            list.push_front(neigh);
        }
    };

};