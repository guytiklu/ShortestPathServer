#include "Interfaces.h"
#include <string>
#include <unordered_map>
#include <fstream>

#pragma once

template <typename Problem,typename Solution>
class FileCacheManager : public CacheManager<Problem,Solution> {
private:
    unordered_map<Problem,string> solutionMap; // map will hold key, and string=filename holding the solution
    hash<Problem> hasher;
    bool fileExists (const string& name) {
        ifstream f(name.c_str());
        return f.good();
    }
public:
    bool exists(Problem p)  {
        //check if file exists. update the table.
        string fileName = "sol_" + to_string(hasher(p));
        if(fileExists(fileName)){
            solutionMap.emplace(p,fileName);
            return true;
        }
        return false;


    }

    Solution getSolution(Problem p) {
        Solution s;
        if (exists(p)) {
            fstream file;
            file.open(solutionMap[p]);
            getline(file,s);
            file.close();
            return s;
        } else {
            throw "key does not exist";
        }
    }

    void saveSolution(Problem p, Solution s) {
        string fileName = "sol_" + to_string(hasher(p));
        ofstream file(fileName);
        file<<s<<endl;
        file.close();
        solutionMap.emplace(p,fileName);
    }

} ;