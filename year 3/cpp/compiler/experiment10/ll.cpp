#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <stdlib.h> // For exit()

using namespace std; // Added this line

// --- Part 1: LL(1) Checker & Table Generator ---
map<char, vector<vector<string>>> G;
map<char, set<string>> FI, FO;
map<pair<char, string>, vector<string>> Tbl;
set<char> N;
set<string> T;
const string E = "e", $ = "$";

set<string> Fs(const string& s);
set<string> Fp(const vector<string>& p) {
    set<string> f; bool a = true;
        set<string> fS = Fs(s);
        for (const auto& x : fS) if (x != E) f.insert(x);
        if (fS.find(E) == fS.end()) { a = false; break; }
    }
    if (a) f.insert(E); return f;
}
set<string> Fs(const string& s) {
    if (T.count(s)) return {s};
    if (N.count(s[0])) {
        if (FI.count(s[0])) return FI[s[0]];
        set<string> f;
        for (const auto& p : G[s[0]]) { set<string> fP = Fp(p); f.insert(fP.begin(), fP.end()); }
        return FI[s[0]] = f;
    }
    return {E};
}
void Cfo() {
    for (char n : N) FO[n] = {}; FO['E'].insert($);
    bool ch = true;
    while (ch) {
        ch = false;
        for (auto const& [n, ps] : G) for (const auto& p : ps) for (size_t i = 0; i < p.size(); ++i) {
            if (T.count(p[i])) continue;
            char B = p[i][0]; set<string> fBe = Fp(vector<string>(p.begin() + i + 1, p.end()));
            size_t oS = FO[B].size();
            for (const auto& f : fBe) if (f != E) FO[B].insert(f);
            if (fBe.count(E) || i == p.size() - 1) FO[B].insert(FO[n].begin(), FO[n].end());
            if (FO[B].size() != oS) ch = true;
        }
    }
}
bool isLL1() {
    cout << "\n--- Building Parse Table (LL(1) Check) ---\n";
    for (auto const& [n, ps] : G) for (const auto& p : ps) {
        set<string> fP = Fp(p);
        for (const string& t : fP) if (t != E) {
            if (Tbl.count({n, t})) { cout << "Conflict! Not LL(1).\n"; return false; }
            Tbl[{n, t}] = p;
        }
        if (fP.count(E)) for (const string& t : FO[n]) {
            if (Tbl.count({n, t})) { cout << "Conflict! Not LL(1).\n"; return false; }
            Tbl[{n, t}] = p;
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
            if (Tbl.find({n, c}) != Tbl.end()) {
                vector<string> p = Tbl[{n, c}];
                if (p.size() == 1 && p[0] == E) continue;
                for (int i = p.size() - 1; i >= 0; i--) s.push(p[i]);
            } else { cout << "\nRejected: " << in << endl; return; }
        }
    }
    cout << "\nAccepted: " << in << endl;
}

// --- Main Function ---
int main() {
    G['E'] = {{"T", "X"}}; G['X'] = {{"+", "T", "X"}, {E}}; G['T'] = {{"F", "Y"}};
    G['Y'] = {{"*", "F", "Y"}, {E}}; G['F'] = {{"(", "E", ")"}, {"i"}};
    N = {'E', 'X', 'T', 'Y', 'F'}; T = {"+", "*", "(", ")", "i", E};
    for(char n : N) Fs(string(1, n)); Cfo();
    if (isLL1()) {
        string t = "i+i*i"; runRD(t); runNRD(t);
    }
    return 0;
}