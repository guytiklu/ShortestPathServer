#include "Interfaces.h"
#include <string>
#include <unordered_map>
#include <fstream>

#pragma once

template <typename Problem,typename Solution>
class FileCacheManager : public CacheManager<Problem,Solution> {
private:
    unordered_map<Problem,string> solutionMap; // map will hold key, and string=filename holding the solution
    int sol=0;
public:
    bool exists(Problem p)  {
        if (solutionMap.find(p) == solutionMap.end()){
            return false;
        } else {
            return true;
        }
    }

    Solution getSolution(Problem p) {
        Solution s;
        if (exists(p)) {
            fstream file;
            file.open(solutionMap[p], ios::in | ios::binary);
            file.read((char *) &s, sizeof(s));
            file.close();
            return s;
        } else {
            throw "key does not exist";
        }
    }

    void saveSolution(Problem p, Solution s) {
        string fileName = "sol_" + to_string(sol);
        sol++;
        fstream file;
        file.open(fileName, ios::out | ios::binary);
        file.write((char *) &s, sizeof(s));
        file.close();
        solutionMap.emplace(p,fileName);
    }

};