#import "Interfaces.h"
#import "MySearchable.cpp"
#include<bits/stdc++.h>
#pragma once

class StringReverser : public Solver<string,string>{
public:
    string solve(string str){
        reverse(str.begin(), str.end());
        return str;
    };
};

class SearcherSolver : public Solver<string,string>{
public:
    Searchable<string>* srcble;
    Searcher<string>* srcr;
    SearcherSolver(Searcher<string>* s2){
        srcr = s2;
    }
    string solve(string str){

        srcble = new MySearchable(str);

        Solution<string> s = srcr->search(srcble);
        cout<<"value:"<<s.value<<", steps:"<<s.route.size()-1<<endl;//#######################################
        if(s.value==INT32_MAX){
            return "No Path Yo";
        }
        string solution="";
        bool firstRun = true;
        for(Node<string> x : s.route){
            if(firstRun){
                firstRun=false;
                continue;
            }
            string add;
            string state1 = x.state;
            string state2 = x.cameFrom->state;
            int s1i= stoi(state1.substr(0, state1.find(",")));
            int s1j= stoi(state1.substr(state1.find(",")+1, state1.length()-1));
            int s2i= stoi(state2.substr(0, state2.find(",")));
            int s2j= stoi(state2.substr(state2.find(",")+1, state2.length()-1));
            if(s1i!=s2i){ // will be 'up' or 'down'
                if(s1i>s2i){
                    add="Down (";
                }
                else{
                    add="Up (";
                }
            } else { // will be 'left' or 'right'
                if(s1j>s2j){
                    add="Right (";
                }
                else{
                    add="Left (";
                }
            }

            solution+=add;
            solution+=to_string((int)x.cost);
            solution+="), ";

        }
        solution=solution.substr(0,solution.length()-2);
        solution+="\n";
        return solution;
    };
};

class BestFS : public Searcher<string> {

    Solution<string> search(Searchable<string>* subject) {
        deque <Node<string>> closed;
        auto cmp = [](Node <string> left, Node <string> right) { return left.cost > right.cost; };
        priority_queue < Node < string > , vector < Node < string >>, decltype(cmp) > open(cmp);
        open.push(subject->getInitialNode());

        while (!open.empty()) {
            Node <string> n = open.top();
            open.pop();
            closed.push_front(n);
            if (n.equals(subject->getGoalNode())) { // found goal
                //create sol
                Solution <string> s;
                s.value = n.cost;
                while (n.cameFrom != NULL) {
                    s.route.push_front(n);
                    n = *n.cameFrom;
                    if(n.cost>2000000000 || n.cost<0){
                        s.value=INT32_MAX;
                    }
                }
                s.route.push_front(n);
                if(n.cost>2000000000 || n.cost<0){
                    s.value=INT32_MAX;
                }
                return s;
            }
            list <Node<string>> neighbours = subject->getNeighbours(&n);
            for (Node <string> nei : neighbours) {
                //check if nei is in closed & open
                bool neiInClosed = false;
                bool neiInOpen = false;

                for(Node<string> x : closed){
                    if(x.equals(nei)){
                        neiInClosed = true;
                    }
                }

                list <Node<string>> tmpList;
                while (!nei.equals(open.top()) && !open.empty()) { //try to find nei in open
                    tmpList.push_front(open.top());
                    open.pop();
                }
                //now open has nei on top, or is empty
                if(!open.empty()){
                    neiInOpen = true;
                }

                if(!neiInClosed && !neiInOpen){
                    open.push(nei);
                } else {
                    if(neiInOpen && nei.cost<open.top().cost){ //@@@@@@@@@@@@@@@@@@@@@@@@
                        open.pop();
                        open.push(nei);
                    }
                }

                while (!tmpList.empty()){ // push back values we drawed from open
                    open.push(tmpList.front());
                    tmpList.pop_front();
                }
            }
        }
    }

};

class BFS : public Searcher<string> {
    bool findIfExistInList(Node<string> v, list<Node<string>> List){
        for(Node<string> x : List){
            if(x.equals(v)){
                return true;
            }
        }
        return false;
    }

    Solution<string> search(Searchable<string>* subject){
        Solution<string> sol;
        list<Node<string>> vistedList;
        queue<Node<string>> nodeQ;
        Node <string> answerNode;
        int iHaverouteFlag=0;

        nodeQ.push(subject->getInitialNode()); ///pushing the Q the first node S
        vistedList.push_front(subject->getInitialNode());///pushing the VistList the first node, marked as we have been here
        while(nodeQ.size()!=0){
            Node <string> n= nodeQ.front();
            nodeQ.pop();
            if(n.equals(subject->getGoalNode())){
                answerNode= n;
                iHaverouteFlag=1;
            }
            for( Node<string> v : subject->getNeighbours(&n)){
                if(!findIfExistInList(v,vistedList)){
                    if(v.cost>2000000000){
                        vistedList.push_back(v);
                    }
                    else {
                        vistedList.push_back(v);
                        nodeQ.push(v);
                    }
                }
            }
        }
        if (iHaverouteFlag==1){/// means BFS found a path
            sol.value=answerNode.cost; ///getting the cost to sol
            while (answerNode.cameFrom != NULL) { ///getting the path to sol
                sol.route.push_front(answerNode);
                answerNode = *answerNode.cameFrom;
            }
            sol.route.push_front(answerNode);


            return sol;
        }
        else{
            sol.value=INT32_MAX;
            return sol;
        }



    }
};

class DFS : public Searcher<string> {
    bool findIfExistInList(Node<string> v, list<Node<string>> List) {
        for (Node <string> x : List) {
            if (x.equals(v)) {
                return true;
            }
        }
        return false;
    }

    Solution<string> search(Searchable<string> *subject) {
        Solution <string> sol;
        list <Node<string>> vistedList;
        stack <Node<string>> nodeStack;
        Node <string> answerNode;
        int iHaverouteFlag = 0;

        nodeStack.push(subject->getInitialNode()); ///insert into the stack the startNode
        vistedList.push_front(subject->getInitialNode()); ///mark as read

        while (nodeStack.size() != 0) { ///while stack is not empty
            Node <string> v = nodeStack.top();
            nodeStack.pop();
            if (v.equals(subject->getGoalNode())) {
                answerNode = v;
                iHaverouteFlag = 1;
            }
            for (Node <string> u : subject->getNeighbours(&v)) {
                if (!findIfExistInList(u, vistedList)) { ///check if kodkodv v has been visited"
                    if (u.cost > 2000000000) {
                        vistedList.push_back(u);
                    } else {
                        vistedList.push_back(u);
                        nodeStack.push(u);
                    }
                }
            }
        }
        if (iHaverouteFlag == 1) {/// means BFS found a path
            sol.value = answerNode.cost; ///getting the cost to sol
            while (answerNode.cameFrom != NULL) { ///getting the path to sol
                sol.route.push_front(answerNode);
                answerNode = *answerNode.cameFrom;
            }
            sol.route.push_front(answerNode);

            return sol;
        }
        else {
            sol.value = INT32_MAX;
            return sol;
        }
    }
};

class Astar : public Searcher<string> {

    Node<string> goalNode;
    struct starNode{
        Node<string> node;
        int h;
        int f;
        starNode* cameFrom;
    };
    int getHeuristicValue(Node<string> sn){//manhattan style
        string state = sn.state;
        int nodei = stoi(state.substr(0, state.find(",")));
        int nodej = stoi(state.substr(state.find(",")+1, state.length()-1));
        state = goalNode.state;
        int goali = stoi(state.substr(0, state.find(",")));
        int goalj = stoi(state.substr(state.find(",")+1, state.length()-1));

        return abs(nodei-goali)+abs(nodej-goalj);

    }
    bool findIfExistInList(starNode v, list<starNode> List,int* f){
        for(starNode x : List){
            if(x.node.equals(v.node)){
                *f=x.f;
                return true;
            }
        }
        return false;
    }

    Solution<string> search(Searchable<string>* subject) {
        goalNode=subject->getGoalNode();
        Solution <string> sol;
        sol.value=INT32_MAX;
        list<starNode> closeList;
        auto cmp = [](starNode left, starNode right) { return left.f > right.f; };
        priority_queue < starNode , vector < starNode>, decltype(cmp) > openList(cmp);
        Node<string> n = subject->getInitialNode();
        starNode first{&n,getHeuristicValue(n),(int)n.cost+getHeuristicValue(n),NULL};
        openList.push(first);

        while(!openList.empty()){
            starNode tmp = openList.top();
            starNode* q = new starNode();
            q->node=tmp.node;
            q->h=tmp.h;
            q->f=tmp.f;
            q->cameFrom=tmp.cameFrom;
            if(q->node.cost==INT32_MAX){
                closeList.push_back(*q);
                continue;
            }

            openList.pop();
            list <Node<string>> neighbours = subject->getNeighbours(&q->node);
            list <starNode> starNeighbours;

            while(!neighbours.empty()) { //transform neighbours to starNeighbours
                Node<string> *ptr = &neighbours.front();
                starNode sn{ptr, getHeuristicValue(ptr), (int) ptr->cost + getHeuristicValue(ptr), q};
                if(sn.node.cost>2000000000 || sn.node.cost<-1){
                    sn.f=INT32_MAX;
                    closeList.push_back(sn);
                    neighbours.pop_front();
                    continue;
                }
                starNeighbours.push_back(sn);
                neighbours.pop_front();
            }


            for(starNode x : starNeighbours){
                if(x.node.equals(subject->getGoalNode())){ //if found goal
                    //create sol
                    Solution <string> s;
                    s.value = x.node.cost;
                    while (x.node.cameFrom != NULL) {
                        s.route.push_front(x.node);
                        x = *x.cameFrom;
                        if(x.node.cost>2000000000 || x.node.cost<0){
                            s.value=INT32_MAX;
                        }
                    }
                    s.route.push_front(x.node);
                    if(x.node.cost>2000000000 || x.node.cost<0){
                        s.value=INT32_MAX;
                    }
                    return s;
                }

                list<starNode>temp;
                bool xInOpen=false;
                int f;
                while(!openList.empty()){ //check if x is in open
                    if(x.node.equals(openList.top().node)){
                        xInOpen=true;
                        f=openList.top().f;
                    }
                    temp.push_back(openList.top());
                    openList.pop();
                }
                while(!temp.empty()){//insert nodes back to openlist
                    openList.push(temp.front());
                    temp.pop_front();
                }

                if(xInOpen){
                    if(f<x.f){
                        continue;
                    }
                }

                if(findIfExistInList(x,closeList,&f) && f<x.f) {
                    continue;
                } else {
                    openList.push(x);
                }
            }// end neighbours for

            closeList.push_back(*q);
        }// end while
        return sol;
    }
} ;