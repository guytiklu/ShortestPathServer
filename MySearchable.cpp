#include "Interfaces.h"
#include <limits>
#include <algorithm>

class MySearchable : public Searchable<string>{
    int n;
    int** matrix;
    string startPoint;
    string endPoint;
public:
    string removeSpaces(string str)
    {
        str.erase(remove(str.begin(), str.end(), ' '), str.end());
        return str;
    }
    int findTheSizeOfTheMatrix(string str) {
        int counter=0;
        string word;
        for (auto x : str) {
            if (x == ',') {
                counter++;
            }
            if(x== '\n'){
                break;
            }
        }
        return counter+1;
    }
    void printMatrix(int ** matrix,int size){
        cout<< "my matrix is: "<<endl;
        for(int i=0; i<size;i++){
            for (int j=0; j<size;j++){
                cout<<matrix[i][j]<<endl;
            }
        }
    }
    int** createMatrix(int size){
        int rows = size, cols = size;
        int** matrix = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new int[cols];
        }
        return matrix;
    }
    MySearchable(string str) {
        //create matrix, start point, end point - from the string
        //while building set the starting node to value 0;

        string info= removeSpaces(str); /// removing all the spaces in the string

        int size= findTheSizeOfTheMatrix(info); ///finding the size of the matrix
        n=size;
        matrix= createMatrix(size); ///making a matrix with the size we want

        /// now we need to actually build the matrix from the info we have
        int i=0;
        int j=0;
        int numberOfBackSlashN=0;
        int k=0;/// will be used to find the info after the matrix is fnished
        string word;
        for (auto x : info){
            k++;
            if (x== ','){
                int number= stod(word);
                if(number==-1){
                    number=INT32_MAX;
                }
                matrix[i][j]= number;
                j++;
                word= "";
            }
            else if(x=='\n'){
                int number= stod(word);
                if(number==-1){
                    number=INT32_MAX;
                }
                matrix[i][j]= number;
                word="";
                j=0;
                i++;
                numberOfBackSlashN++;
                if(numberOfBackSlashN==size){
                    break;;
                }
            }
            else {
                word = word + x;
            }
        }
        //printMatrix(matrix,size);
        ///now we have the matrix!

        /// now we need to get the startPoint and the endPoint


        ///getting the startPoint
        while(info[k]!='\n'){
            startPoint += info[k];
            k++;
        }
        k++;
        ///getting the endPoint
        while(info[k]!='\n'){
            endPoint += info[k];
            k++;
        }

        ///reseting the cost of the start point
        /*string delimiter = ",";
        int a,b;
        a = stoi(startPoint.substr(0, startPoint.find(delimiter)));
        b = stoi(startPoint.substr(startPoint.find(delimiter)+1, startPoint.length()-1));
        matrix[a][b]=0;*/
        //printMatrix(matrix,size);


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
        n.cost = getValue(n.state);
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