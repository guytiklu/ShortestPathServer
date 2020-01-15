#include "Interfaces.h"

class MySearchable : public Searchable<string>{
    int n;
    int matrix[3][3];
    string startPoint;
    string endPoint;
public:
    MySearchable(string str) {
        //create matrix, start point, end point - from the string
        //while building set the starting node to value 0;





    }
    //node - state,cost,cameFrom
    int getValue(string str){
        int a,b;
        string delimiter = ",";
        a = stoi(str.substr(0, str.find(delimiter)));
        b = stoi(str.substr(str.find(delimiter)+1, str.length()-1));
        return matrix[a][b];
    }
    Node<string> getInitialNode(){
        Node<string> n{};
        n.state = startPoint;
        n.cost = 0;
        n.cameFrom = NULL;
        return n;
    };
    Node<string> getGoalNode(){
        Node<string> n{};
        n.state = endPoint;
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
        b = stoi(str.substr(str.find(delimiter)+1, str.length()-1));

        if(inField(a,b+1)){
            Node<string> neigh;
            string str = to_string(a);
            str += ",";
            str += to_string(b+1);
            neigh.state=str;
            neigh.cameFrom = new Node<string>(nd);
            neigh.cost= getValue(neigh.state)+nd->cost;
            list.push_front(neigh);
        }
        if(inField(a,b-1)){
            Node<string> neigh;
            string str = to_string(a);
            str += ",";
            str += to_string(b-1);
            neigh.state=str;
            neigh.cameFrom = new Node<string>(nd);
            neigh.cost= getValue(neigh.state)+nd->cost;
            list.push_front(neigh);
        }
        if(inField(a-1,b)){
            Node<string> neigh;
            string str = to_string(a-1);
            str += ",";
            str += to_string(b);
            neigh.state=str;
            neigh.cameFrom = new Node<string>(nd);
            neigh.cost= getValue(neigh.state)+nd->cost;
            list.push_front(neigh);
        }
        if(inField(a+1,b)){
            Node<string> neigh;
            string str = to_string(a+1);
            str += ",";
            str += to_string(b);
            neigh.state=str;
            neigh.cameFrom = new Node<string>(nd);
            neigh.cost= getValue(neigh.state)+nd->cost;
            list.push_front(neigh);
        }
        return list;
    };

};