#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <cstdlib> // For exit()

using namespace std;

// --- Part 1: LL(1) Checker & Table Generator ---
map<char, vector<vector<string> > > G;
map<char, set<string> > FI, FO;
map<pair<char, string>, vector<string> > Tbl;
set<char> N;
set<string> T;
const string E = "e", $ = "$";

set<string> Fs(const string& s);
set<string> Fp(const vector<string>& p) {
    set<string> f; bool a = true;
    for (vector<string>::const_iterator it = p.begin(); it != p.end(); ++it) {
        const string& s = *it;
        set<string> fS = Fs(s);
        for (set<string>::const_iterator x_it = fS.begin(); x_it != fS.end(); ++x_it) {
            if (*x_it != E) f.insert(*x_it);
        }
        if (fS.find(E) == fS.end()) { a = false; break; }
    }
    if (a) f.insert(E); return f;
}
set<string> Fs(const string& s) {
    if (T.count(s)) {
        set<string> temp;
        temp.insert(s);
        return temp;
    }
    if (N.count(s[0])) {
        if (FI.count(s[0])) return FI[s[0]];
        set<string> f;
        const vector<vector<string> >& productions = G[s[0]];
        for (vector<vector<string> >::const_iterator it = productions.begin(); it != productions.end(); ++it) {
            set<string> fP = Fp(*it);
            f.insert(fP.begin(), fP.end());
        }
        return FI[s[0]] = f;
    }
    set<string> temp;
    temp.insert(E);
    return temp;
}
void Cfo() {
    for (set<char>::iterator it = N.begin(); it != N.end(); ++it) FO[*it] = set<string>();
    FO['E'].insert($);
    bool ch = true;
    while (ch) {
        ch = false;
        for (map<char, vector<vector<string> > >::const_iterator it = G.begin(); it != G.end(); ++it) {
            char n = it->first;
            const vector<vector<string> >& ps = it->second;
            for (vector<vector<string> >::const_iterator p_it = ps.begin(); p_it != ps.end(); ++p_it) {
                const vector<string>& p = *p_it;
                for (size_t i = 0; i < p.size(); ++i) {
                    if (T.count(p[i])) continue;
                    char B = p[i][0];
                    set<string> fBe = Fp(vector<string>(p.begin() + i + 1, p.end()));
                    size_t oS = FO[B].size();
                    for (set<string>::const_iterator f_it = fBe.begin(); f_it != fBe.end(); ++f_it) {
                        if (*f_it != E) FO[B].insert(*f_it);
                    }
                    if (fBe.count(E) || i == p.size() - 1) FO[B].insert(FO[n].begin(), FO[n].end());
                    if (FO[B].size() != oS) ch = true;
                }
            }
        }
    }
}
bool isLL1() {
    cout << "\n--- Building Parse Table (LL(1) Check) ---\n";
    for (map<char, vector<vector<string> > >::const_iterator it = G.begin(); it != G.end(); ++it) {
        char n = it->first;
        const vector<vector<string> >& ps = it->second;
        for (vector<vector<string> >::const_iterator p_it = ps.begin(); p_it != ps.end(); ++p_it) {
            const vector<string>& p = *p_it;
            set<string> fP = Fp(p);
            for (set<string>::const_iterator t_it = fP.begin(); t_it != fP.end(); ++t_it) {
                const string& t = *t_it;
                if (t != E) {
                    if (Tbl.count(make_pair(n, t))) { cout << "Conflict! Not LL(1).\n"; return false; }
                    Tbl[make_pair(n, t)] = p;
                }
            }
            if (fP.count(E)) {
                const set<string>& follow_n = FO[n];
                for (set<string>::const_iterator t_it = follow_n.begin(); t_it != follow_n.end(); ++t_it) {
                    const string& t = *t_it;
                    if (Tbl.count(make_pair(n, t))) { cout << "Conflict! Not LL(1).\n"; return false; }
                    Tbl[make_pair(n, t)] = p;
                }
            }
        }
    }
    cout << "Grammar is LL(1).\n"; return true;
}

// --- Part 2: Recursive-Descent Parser ---
string rd_in; size_t rd_p;
char L() { return rd_p < rd_in.length() ? rd_in[rd_p] : '$'; }
void M(char t) { if (L() == t) rd_p++; else exit(1); }
void R_F(); void R_Y(); void R_T(); void R_X(); void R_E();
void R_E() { R_T(); R_X(); }
void R_X() { if (L() == '+') { M('+'); R_T(); R_X(); } }
void R_T() { R_F(); R_Y(); }
void R_Y() { if (L() == '*') { M('*'); R_F(); R_Y(); } }
void R_F() { if (L() == '(') { M('('); R_E(); M(')'); } else M('i'); }
void runRD(string in) {
    cout << "\n--- Recursive-Descent Parser ---";
    rd_in = in + "$"; rd_p = 0; R_E();
    cout << (L() == '$' ? "\nAccepted: " : "\nRejected: ") << in << endl;
}

// --- Part 3: Non-recursive Predictive Parser ---
void runNRD(string in) {
    cout << "\n--- Non-recursive Predictive Parser ---";
    in += "$"; stack<string> s; s.push($); s.push("E"); int ip = 0;
    while (!s.empty()) {
        string t = s.top(), c(1, in[ip]);
        if (T.count(t) || t == $) { if (t == c) { s.pop(); ip++; } else { cout << "\nRejected: " << in << endl; return; }
        } else { s.pop(); char n = t[0];
            if (Tbl.find(make_pair(n, c)) != Tbl.end()) {
                vector<string> p = Tbl[make_pair(n, c)];
                if (p.size() == 1 && p[0] == E) continue;
                for (int i = p.size() - 1; i >= 0; i--) s.push(p[i]);
            } else { cout << "\nRejected: " << in << endl; return; }
        }
    }
    cout << "\nAccepted: " << in << endl;
}
// --- Main Function ---
int main() {
    // Initialize Grammar G
    vector<string> p1; p1.push_back("T"); p1.push_back("X");
    G['E'].push_back(p1);
    vector<string> p2; p2.push_back("+"); p2.push_back("T"); p2.push_back("X");
    vector<string> p3; p3.push_back(E);
    G['X'].push_back(p2); G['X'].push_back(p3);
    vector<string> p4; p4.push_back("F"); p4.push_back("Y");
    G['T'].push_back(p4);
    vector<string> p5; p5.push_back("*"); p5.push_back("F"); p5.push_back("Y");
    vector<string> p6; p6.push_back(E);
    G['Y'].push_back(p5); G['Y'].push_back(p6);
    vector<string> p7; p7.push_back("("); p7.push_back("E"); p7.push_back(")");
    vector<string> p8; p8.push_back("i");
    G['F'].push_back(p7); G['F'].push_back(p8);

    // Initialize Non-terminals N
    N.insert('E'); N.insert('X'); N.insert('T'); N.insert('Y'); N.insert('F');

    // Initialize Terminals T
    T.insert("+"); T.insert("*"); T.insert("("); T.insert(")"); T.insert("i"); T.insert(E);

    for(set<char>::iterator it = N.begin(); it != N.end(); ++it) {
        Fs(string(1, *it));
    }
    Cfo();
    if (isLL1()) {
        string t = "i+i*i"; runRD(t); runNRD(t);
    }
    return 0;
}