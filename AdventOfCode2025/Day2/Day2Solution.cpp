#include "Day2Solution.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <queue>

using namespace std;

namespace Day2 {

    using ullong = unsigned long long;

    class IdRange {
    public:
        ullong start;
        ullong end;
    };


    vector<IdRange> splitIdRanges(const string& line) {
        vector<IdRange> idRanges;
        stringstream ss(line);
        vector<string> v;
        string s;
        while (getline(ss, s, ',')) {
            const auto pos = s.find('-');
            string s1 = s.substr(0, pos);
            string s2 = s.substr(pos + 1);
            idRanges.push_back(IdRange{stoull(s1), stoull(s2)});
        }
        return idRanges;
    }

    vector<unsigned char> split(ullong i) {
        vector<unsigned char> v;
        do {
          v.push_back(i % 10);
        } while (i /= 10);
        std::reverse(v.begin(), v.end());
        return v;
    }

    ullong getRepeatedElementsInRange(const ullong num) {
        string snum = to_string(num);
        size_t len = snum.length();
        if (len % 2 == 0) {
            size_t len2 = len / 2;
            string left = snum.substr(0, len2);
            string right = snum.substr(len2);
            if (left == right) {
                return num;
            }
        }
        return 0;
    }

    string solve1(const vector<string>& input) {
        ullong counter = 0;
        for (auto& line: input) {
            vector<IdRange> idRanges = splitIdRanges(line);
            for (IdRange& idRange : idRanges) {
                for (ullong i = idRange.start; i <= idRange.end; i++) {
                    counter += getRepeatedElementsInRange(i);
                }
            }
        }
        return to_string(counter);
    }

    ullong getMultiRepeatedElementsInRage(ullong num) {
        string snum = to_string(num);
        size_t len = snum.length();
        vector<size_t> lcs(len, 0); // Declaramos el vector para la tabla LCS

        for (size_t i = 1; i < len; i++) { // i es donde finaliza el actual sufijo
            size_t j = lcs[i - 1]; // j empieza el indice del sufijo encotnrado previo cuando se ha llegado a i
            while (j > 0 && snum[i] != snum[j]) { // Saltamos valores diferentes
                j = lcs[j - 1];
            }
            if (snum[i] == snum[j]) { // Match
                j++;
            }
            lcs[i] = j; // Asignacion de lcs
        }

        const size_t k = lcs[len - 1];
        const size_t pattern_Length = len - k;
        if (k == 0 || len % pattern_Length)
            return 0;
        return num;
    }


    string solve2(const vector<string>& input) {
        ullong counter = 0;
        for (auto& line : input) {
            vector<IdRange> ranges = splitIdRanges(line);
            for (IdRange& idRange : ranges) {
                for (ullong i = idRange.start; i <= idRange.end; i++) {
                    counter += getMultiRepeatedElementsInRage(i);
                }
            }
        }
        return to_string(counter);
    }
}
