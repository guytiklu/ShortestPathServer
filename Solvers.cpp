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
                }
                s.route.push_front(n);
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

/*class BFS : public Searcher<string> {
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
};*/

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