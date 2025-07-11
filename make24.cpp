#include <bits/stdc++.h>
using namespace std;
int x;

int gcd(int a, int b){
    if (a == 0) return b;
    return gcd(b%a, a);
}

class Frac {
    public:
    int num, den;

    Frac(int x){
        num = x;
        den = 1;
    }

    Frac(int _num, int _den){
        int g = gcd(_num, _den);
        num = _num/g;
        den = _den/g;
    }

    Frac operator+(const Frac& other) const {
        return Frac(num*other.den + other.num*den, den*other.den);
    }

    Frac operator-(const Frac& other) const {
        return Frac(num*other.den - other.num*den, den*other.den);
    }

    Frac operator*(const Frac& other) const {
        return Frac(num*other.num, den*other.den);
    }

    Frac operator/(const Frac& other) const {
        return Frac(num*other.den, den*other.num);
    }

    bool operator==(int x) const {
        return (den*x == num);
    }

    bool operator!=(int x) const {
        return !(den*x == num);
    }

    friend ostream& operator<<(ostream& os, const Frac& frac);
};

ostream& operator<<(ostream& os, const Frac& frac){
    if (frac.den == 1){
        os << frac.num;
    } else {
        os << frac.num << "/" << frac.den;
    }
    return os;
}

class Move {
    public:
    char op;
    Frac a, b;

    Move(Frac _a, char _op, Frac _b): op(_op), a(Frac(_a.num, _a.den)), b(Frac(_b.num, _b.den)){
    }

    friend ostream& operator<<(ostream& os, const Move& m);
};

ostream& operator<<(ostream& os, const Move& m){
    os << m.a << " " << m.op << " " << m.b << " = ";
    if (m.op == '+') os << m.a+m.b;
    if (m.op == '-') os << m.a-m.b;
    if (m.op == '*') os << m.a*m.b;
    if (m.op == '/') os << m.a/m.b;
    return os;
}

bool make24(vector<Frac>& v, vector<Move>& moves){

    int n = v.size();

    if (n == 1) return (v[0] == 24);

    vector<Frac> temp;

    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            temp.clear();
            for (int k = 0; k < n; k++){
                if (k == i || k == j) continue;
                temp.push_back(v[k]);
            }

            temp.push_back(v[i]+v[j]);
            if (make24(temp, moves)){
                moves.push_back(Move(v[i], '+', v[j]));
                return true;
            }
            temp.pop_back();

            temp.push_back(v[i]-v[j]);
            if (make24(temp, moves)){
                moves.push_back(Move(v[i], '-', v[j]));
                return true;
            }
            temp.pop_back();

            temp.push_back(v[j]-v[i]);
            if (make24(temp, moves)){
                moves.push_back(Move(v[j], '-', v[i]));
                return true;
            }
            temp.pop_back();

            temp.push_back(v[i]*v[j]);
            if (make24(temp, moves)){
                moves.push_back(Move(v[i], '*', v[j]));
                return true;
            }
            temp.pop_back();

            if (v[j] != 0){
                temp.push_back(v[i]/v[j]);
                if (make24(temp, moves)){
                    moves.push_back(Move(v[i], '/', v[j]));
                    return true;
                }
                temp.pop_back();
            }

            if (v[i] != 0){
                temp.push_back(v[j]/v[i]);
                if (make24(temp, moves)){
                    moves.push_back(Move(v[j], '/', v[i]));
                    return true;
                }
                temp.pop_back();
            }
        }
    }

    return false;
}

int main(){

    cout << "Enter any number of integers:" << endl;
    string line;
    getline(cin, line);
    istringstream iss(line);
    vector<Frac> v;
    while (iss >> x){
        v.push_back(Frac(x, 1));
    }

    vector<Move> m;

    bool can = make24(v, m);

    if (can){
        reverse(m.begin(), m.end());
        for (vector<Move>::iterator it = m.begin(); it != m.end(); it++){
            cout << *it << endl;
        }
    } else {
        cout << "Impossible." << endl;
    }
    
}
