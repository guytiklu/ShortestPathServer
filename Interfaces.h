#include <iostream>
#include <sstream>
#include <list>
#include <cstring>

#pragma once
using namespace std;

class ClientHandler{
public:
    virtual void handleClient(int socket){};
};

namespace server_side {

    class Server {
    public:
        virtual void open(int port, ClientHandler c) {};

        virtual void closed(int socket) {};
    };
}


template <typename Problem,typename Solution>
class CacheManager{
public:
    CacheManager<Problem,Solution>(){};
    virtual bool exists(Problem p){};
    virtual Solution getSolution(Problem p){};
    virtual void saveSolution(Problem p, Solution s){};
};

template <typename Problem,typename Solution>
class Solver{
public:
    Solver<Problem,Solution>(){};
    virtual Solution solve(Problem p){};
} ;

template <typename T>
class Node{
public:
    T state;
    double cost;
    int color =0 ;
    int distance = 999999;
    Node<T>* cameFrom;
    Node<T>(){

    }
    Node<T>(Node<T>* n){
        this->state = n->state;
        this->cost = n->cost;
        this->cameFrom = n->cameFrom;
    }
    bool equals(Node<T> check){
        if (std::is_same<T, string>::value){
            string str1 = (string)state;
            string str2 = (string)check.state;
            if(strcmp(str1.c_str(),str2.c_str())==0){
                return true;
            }
        }
        else{
            if (state==check.state){
                return true;
            }
        }
        return false;
    }
    void setColor(int d){
        color= d;
    }
    void setDistance(int d){
        distance=d;
    }
};

template <typename T>
class Searchable{
public:
    Node<T> node;
    virtual Node<T> getInitialNode(){};
    virtual Node<T> getGoalNode(){};
    virtual list<Node<T>> getNeighbours(Node<string>* nd){};
};

template <typename T>
struct Solution{
    double value;
    list<Node<T>> route;
};

template <typename T>
class Searcher{
public:
    virtual Solution<T> search(Searchable<T>*){};
};
