#ifndef HTABLE_DEFINED
#define HTABLE_DEFINED

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <iomanip>
using namespace std;

// typedef unordered_map<string, int> htable;
class htable : public unordered_map<string, int> {
public:
	void absorb(const unordered_set<string> &s) {
		for(const string &x: s) {
			(*this)[x]++;
		}
	}
	void absorb(const unordered_map<string, int> &s) {
		for(const auto &x: s) {
			(*this)[x.first] += x.second;
		}
	}
	friend ostream& operator<<(ostream &os, const htable &ht) {
		os << "===== htable follows =====" << endl;
		const int print = 10;
		int till = min((int)ht.size(), print);
		for(const auto &xx: ht) {
			os << setw(15) << xx.first;
			os << " --> " << setw(6) << xx.second << endl;
		}
		if(ht.size() > print) {
			os << ".\n.\n.\n and " << ht.size() - print << " more ..." << endl;
		}
		return os << "=====  htable  ends  =====" << endl;
	}
};

#endif
