#import "Interfaces.h"
#include<bits/stdc++.h>
#pragma once

class StringReverser : public Solver<string,string>{
public:
    string solve(string str){
        reverse(str.begin(), str.end());
        return str;
    };
};

class SearcherSolver : public Solver<string,Solution<string>>{
public:
    Searchable<string>* srcble;
    Searcher<string>* srcr;
    SearcherSolver(Searchable<string>* s1, Searcher<string>* s2){
        srcble = s1;
        srcr = s2;
    }
    Solution<string> solve(string str){
        return srcr->search(*srcble);
    };
};

class BestFS : public Searcher<string> {

    Solution<string> search(Searchable<string> subject) {
        /*Solution <string> sol;
        deque <helper> closed;
        auto cmp = [](helper left, helper right) { return left.value < right.value; };
        priority_queue<helper, vector<helper>, decltype(cmp)> open(cmp);

        open.push(helper{subject.getInitialNode(), 0, subject.node.emptyNode});
        helper h;
        while (!open.empty()) {
            h = open.top();
            open.pop();
            closed.push_front(h);
            if (h.nd.equals(subject.getGoalNode())) { //get route & value
                double val=h.value;
                list<Node<string>> route;
                helper* ptr = &h;

                while(ptr->previous.equals(ptr->nd.emptyNode)){
                    route.push_front(ptr->nd);
                    ptr=ptr->previous.
                }


            }
            list <Node<string>> neighbours1 = subject.getNeighbours(h.nd);
            list <helper> neighbours2;
            for (Node <string> x : neighbours1) {
                neighbours2.push_front(helper{x, h.value + x.cost, h.nd});
            }
            for (helper x : neighbours2) { // for each neighbour
                //check if x is in 'closed' and in 'open'
                bool openB = false;
                bool closedB = false;
                for(helper y : closed){
                    if (x.nd.equals(y.nd)){
                        closedB=true;
                    }
                }
                list<helper> lst;
                while(!open.empty()){
                    lst.push_front(open.top());
                    open.pop();
                }
                for(helper y : lst){
                    if (x.nd.equals(y.nd)){
                        openB=true;
                    }
                }
                while(!lst.empty()){
                    open.push(lst.front());
                    lst.pop_front();
                }
                if(!openB && !closedB){ //if x not in 'open' and 'closed'
                    open.push(x);
                }
                else{ //else
                    //find x in open:
                    while(!x.nd.equals(open.top().nd)){
                        lst.push_front(open.top());
                        open.pop();
                    }
                    // x is now on top of 'open'
                    double value = -999;
                    if(openB){
                        value = open.top().value;
                    }

                    if(x.value<value){
                        if(!openB){
                            open.push(x);
                        }
                        else{
                            open.pop();
                            open.push(x);
                        }
                    }

                    while (!lst.empty()){//get the items back to open
                        open.push(lst.front());
                        lst.pop_front();
                    }
                }
            }
        }
        return sol;*/

        deque <Node<string>> closed;
        auto cmp = [](Node <string> left, Node <string> right) { return left.cost < right.cost; };
        priority_queue < Node < string > , vector < Node < string >>, decltype(cmp) > open(cmp);
        open.push(subject.getInitialNode());

        while (!open.empty()) {
            Node <string> n = open.top();
            open.pop();
            closed.push_front(n);
            if (n.equals(subject.getGoalNode())) { // found goal
                //create sol
                Solution <string> s;
                s.value = n.cost;
                while (n.cameFrom != NULL) {
                    s.route.push_front(n);
                    n = *n.cameFrom;
                }
                return s;
            }
            list <Node<string>> neighbours = subject.getNeighbours(&n);
            for (Node <string> nei : neighbours) {
                //check if nei is in closed & open
                bool neiInClosed = false;
                bool neiInOpen = false;

                neiInClosed = find(closed.begin(), closed.end(), nei) != closed.end();

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
                    if(nei.cost<open.top().cost){
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
    Solution<string> search(Searchable<string> subject) {
        Solution<string> sol;
        list<Node<string>> neighList;
        queue<Node<string>> nodeQ;

        subject.getInitialNode().setDistance(0); /// initialzing the distance to 0
        subject.getInitialNode().setColor(0);/// initializing the color to white
        nodeQ.push(subject.getInitialNode()); /// pushhing the initiali node inside the Q
        while (nodeQ.size()!=0){ /// as long as the Q is not empty
            Node<string> u;  /// node u
            u = nodeQ.front(); /// initialize u with the first node in Q
            nodeQ.pop(); /// moving forword the Q

            for( Node<string> v : subject.getNeighbours(&u)){ /// for each v in adj(u)
                if (v.color == 0){ /// if the color of the neigh is white
                    v.setColor(1);/// make it grey
                    v.setDistance(u.distance +1 ); /// intialize the neigh with distance+1
                    v.cameFrom =&u; /// initialize the came from with u
                    nodeQ.push(v); /// insert the niegh into the Q
                }
            }
            u.setColor(2); /// finished with u, coloring it with black
        }

        return sol;
    }
};

class DFS : public Searcher<string> {
    Solution<string> search(Searchable<string> subject) {
        Solution<string> sol;



        return sol;
    }
};

class Astar : public Searcher<string> {
    Solution<string> search(Searchable<string> subject) {
        Solution<string> sol;



        return sol;
    }
};