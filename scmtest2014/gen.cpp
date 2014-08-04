#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <random>
#include <chrono>
#include <cassert>

#define CHAR_SUPPORT
#define STRING_SUPPORT
//#define INEXACT_SUPPORT

#define TYPE_INT            0x00000001
#define TYPE_RAT            0x00000003
#define TYPE_REAL           0x00000007
#define TYPE_CMPLX          0x0000000F
#define TYPE_BOOL           0x00000010
#define TYPE_CHAR           0x00000020
#define TYPE_STR            0x00000040
#define TYPE_PROC           0x00000080
#define TYPE_OBJ            0xFFFFFFFF

using namespace std;
using namespace std::chrono;

class Node
{
public:
    static vector<Node*> pool;
    string name;
    int type;
    int arg;
    int lower;
    int upper;

    Node(const string &_name, const int &_type, const int &_arg, const int &_lower, const int &_upper): name(_name), type(_type), arg(_arg), lower(_lower), upper(_upper)
    {
        pool.push_back(this);
    }

    static void prepare()
    {
        clear();
        new Node("equal?", TYPE_BOOL, TYPE_OBJ, 2, 2);
        new Node("number?", TYPE_BOOL, TYPE_OBJ, 1, 1);
        //new Node("complex?", TYPE_BOOL, TYPE_OBJ, 1, 1);
        //new Node("real?", TYPE_BOOL, TYPE_OBJ, 1, 1);
        new Node("rational?", TYPE_BOOL, TYPE_OBJ, 1, 1);
        new Node("integer?", TYPE_BOOL, TYPE_OBJ, 1, 1);
        //new Node("exact?", TYPE_BOOL, TYPE_CMPLX, 1, 1);
        //new Node("inexact?", TYPE_BOOL, TYPE_CMPLX, 1, 1);
        new Node("=", TYPE_BOOL, TYPE_RAT, 2, 0x7FFFFFFF);
        new Node("<", TYPE_BOOL, TYPE_RAT, 2, 0x7FFFFFFF);
        new Node(">", TYPE_BOOL, TYPE_RAT, 2, 0x7FFFFFFF);
        new Node("<=", TYPE_BOOL, TYPE_RAT, 2, 0x7FFFFFFF);
        new Node(">=", TYPE_BOOL, TYPE_RAT, 2, 0x7FFFFFFF);
        new Node("zero?", TYPE_BOOL, TYPE_RAT, 1, 1);
        new Node("positive?", TYPE_BOOL, TYPE_RAT, 1, 1);
        new Node("negative?", TYPE_BOOL, TYPE_RAT, 1, 1);
        new Node("odd?", TYPE_BOOL, TYPE_INT, 1, 1);
        new Node("even?", TYPE_BOOL, TYPE_INT, 1, 1);
        new Node("max", TYPE_REAL, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("max", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("min", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("min", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
#ifdef INEXACT_SUPPORT
        new Node("+", TYPE_CMPLX, TYPE_CMPLX, 1, 0x7FFFFFFF);
        new Node("+", TYPE_REAL, TYPE_REAL, 1, 0x7FFFFFFF);
        new Node("*", TYPE_CMPLX, TYPE_CMPLX, 1, 0x7FFFFFFF);
        new Node("*", TYPE_REAL, TYPE_REAL, 1, 0x7FFFFFFF);
        new Node("-", TYPE_CMPLX, TYPE_CMPLX, 1, 0x7FFFFFFF);
        new Node("-", TYPE_REAL, TYPE_REAL, 1, 0x7FFFFFFF);
        new Node("/", TYPE_CMPLX, TYPE_CMPLX, 1, 0x7FFFFFFF);
        new Node("/", TYPE_REAL, TYPE_REAL, 1, 0x7FFFFFFF);
        new Node("abs", TYPE_REAL, TYPE_REAL, 1, 1);
        new Node("ceiling", TYPE_REAL, TYPE_REAL, 1, 1);
        new Node("truncate", TYPE_REAL, TYPE_REAL, 1, 1);
        new Node("round", TYPE_REAL, TYPE_REAL, 1, 1);
        new Node("floor", TYPE_REAL, TYPE_REAL, 1, 1);
        //new Node("rationalize", TYPE_RAT, TYPE_REAL, 2, 2);
        new Node("exp", TYPE_CMPLX, TYPE_CMPLX, 1, 1);
        new Node("exp", TYPE_REAL, TYPE_REAL, 1, 1);
        new Node("log", TYPE_CMPLX, TYPE_CMPLX, 1, 1);
        new Node("sin", TYPE_CMPLX, TYPE_CMPLX, 1, 1);
        //TODO new Node("sin", TYPE_REAL, TYPE_REAL, 1, 1);
        new Node("cos", TYPE_CMPLX, TYPE_CMPLX, 1, 1);
        //TODO new Node("cos", TYPE_REAL, TYPE_REAL, 1, 1);
        new Node("tan", TYPE_CMPLX, TYPE_CMPLX, 1, 1);
        //TODO new Node("tan", TYPE_REAL, TYPE_REAL, 1, 1);
        new Node("asin", TYPE_CMPLX, TYPE_CMPLX, 1, 1);
        new Node("acos", TYPE_CMPLX, TYPE_CMPLX, 1, 1);
        new Node("atan", TYPE_CMPLX, TYPE_CMPLX, 1, 1);
        new Node("atan", TYPE_CMPLX, TYPE_REAL, 1, 2);
        new Node("sqrt", TYPE_CMPLX, TYPE_CMPLX, 1, 1);
        new Node("expt", TYPE_CMPLX, TYPE_CMPLX, 2, 2);
        new Node("expt", TYPE_REAL, TYPE_REAL, 2, 2);
        //new Node("expt", TYPE_INT, TYPE_INT, 2, 2);
        new Node("make-polar", TYPE_CMPLX, TYPE_REAL, 2, 2);
        new Node("make-rectangular", TYPE_CMPLX, TYPE_REAL, 2, 2);
        new Node("real-part", TYPE_REAL, TYPE_CMPLX, 1, 1);
        //TODO new Node("imag-part", TYPE_REAL, TYPE_CMPLX, 1, 1);
        new Node("magnitude", TYPE_REAL, TYPE_CMPLX, 1, 1);
        //new Node("magnitude", TYPE_RAT, TYPE_RAT, 1, 1);
        //new Node("magnitude", TYPE_INT, TYPE_INT, 1, 1);
        new Node("angle", TYPE_REAL, TYPE_CMPLX, 1, 1);
        //new Node("angle", TYPE_INT, TYPE_REAL, 1, 1);
        new Node("exact->inexact", TYPE_CMPLX, TYPE_CMPLX, 1, 1);
        new Node("exact->inexact", TYPE_REAL, TYPE_REAL, 1, 1);
        //new Node("exact->inexact", TYPE_RAT, TYPE_RAT, 1, 1);
        //new Node("exact->inexact", TYPE_INT, TYPE_INT, 1, 1);
        new Node("inexact->exact", TYPE_CMPLX, TYPE_CMPLX, 1, 1);
        new Node("inexact->exact", TYPE_REAL, TYPE_REAL, 1, 1);
        new Node("inexact->exact", TYPE_RAT, TYPE_RAT, 1, 1);
        new Node("inexact->exact", TYPE_INT, TYPE_INT, 1, 1);
#endif
        new Node("+", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("+", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("+", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("+", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("+", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("+", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("+", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("+", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("+", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("+", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("+", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("*", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("*", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("*", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("*", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("*", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("*", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("*", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("*", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("*", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("*", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("-", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        //new Node("/", TYPE_RAT, TYPE_RAT, 1, 0x7FFFFFFF);
        new Node("abs", TYPE_RAT, TYPE_RAT, 1, 1);
        new Node("abs", TYPE_INT, TYPE_INT, 1, 1);
        //new Node("quotient", TYPE_INT, TYPE_INT, 2, 2);
        //new Node("remainder", TYPE_INT, TYPE_INT, 2, 2);
        //new Node("modulo", TYPE_INT, TYPE_INT, 2, 2);
        new Node("gcd", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        new Node("lcm", TYPE_INT, TYPE_INT, 1, 0x7FFFFFFF);
        //TODO new Node("numerator", TYPE_INT, TYPE_RAT, 1, 1);
        //new Node("denominator", TYPE_INT, TYPE_RAT, 1, 1);
        //new Node("make-rectangular", TYPE_CMPLX, TYPE_RAT, 2, 2);
        //new Node("real-part", TYPE_RAT, TYPE_RAT, 1, 1);
        //new Node("real-part", TYPE_INT, TYPE_INT, 1, 1);
        //new Node("imag-part", TYPE_INT, TYPE_REAL, 1, 1);
#ifdef INEXACT_SUPPORT
#ifdef STRING_SUPPORT
        new Node("number->string", TYPE_STR, TYPE_RAT, 1, 1);
#endif
#endif
        //(number->string z radix)
        //TODO new Node("string->number", TYPE_CMPLX, TYPE_STR, 1, 1);
        //(string->number string radix)
        new Node("not", TYPE_BOOL, TYPE_OBJ, 1, 1);
        new Node("boolean?", TYPE_BOOL, TYPE_OBJ, 1, 1);
        new Node("char?", TYPE_BOOL, TYPE_OBJ, 1, 1);
#ifdef CHAR_SUPPORT
        new Node("char=?", TYPE_BOOL, TYPE_CHAR, 2, 2);
        new Node("char<?", TYPE_BOOL, TYPE_CHAR, 2, 2);
        new Node("char>?", TYPE_BOOL, TYPE_CHAR, 2, 2);
        new Node("char<=?", TYPE_BOOL, TYPE_CHAR, 2, 2);
        new Node("char>=?", TYPE_BOOL, TYPE_CHAR, 2, 2);
        new Node("char-ci=?", TYPE_BOOL, TYPE_CHAR, 2, 2);
        new Node("char-ci<?", TYPE_BOOL, TYPE_CHAR, 2, 2);
        new Node("char-ci>?", TYPE_BOOL, TYPE_CHAR, 2, 2);
        new Node("char-ci<=?", TYPE_BOOL, TYPE_CHAR, 2, 2);
        new Node("char-ci>=?", TYPE_BOOL, TYPE_CHAR, 2, 2);
        new Node("char-alphabetic?", TYPE_BOOL, TYPE_CHAR, 1, 1);
        new Node("char-numeric?", TYPE_BOOL, TYPE_CHAR, 1, 1);
        new Node("char-whitespace?", TYPE_BOOL, TYPE_CHAR, 1, 1);
        new Node("char-upper-case?", TYPE_BOOL, TYPE_CHAR, 1, 1);
        new Node("char-lower-case?", TYPE_BOOL, TYPE_CHAR, 1, 1);
        new Node("char->integer", TYPE_INT, TYPE_CHAR, 1, 1);
        //new Node("integer->char", TYPE_CHAR, TYPE_INT, 1, 1);
        new Node("char-upcase", TYPE_CHAR, TYPE_CHAR, 1, 1);
        new Node("char-downcase", TYPE_CHAR, TYPE_CHAR, 1, 1);
#endif
        new Node("string?", TYPE_BOOL, TYPE_OBJ, 1, 1);
#ifdef STRING_SUPPORT
        //new Node("make-string", TYPE_STR, TYPE_INT, 1, 1);
        //(make-string k char)
        new Node("string", TYPE_STR, TYPE_CHAR, 0, 0x7FFFFFFF);
        new Node("string-length", TYPE_INT, TYPE_STR, 1, 1);
        //(string-ref string k)
        new Node("string=?", TYPE_BOOL, TYPE_STR, 2, 2);
        new Node("string-ci=?", TYPE_BOOL, TYPE_STR, 2, 2);
        new Node("string<?", TYPE_BOOL, TYPE_STR, 2, 2);
        new Node("string>?", TYPE_BOOL, TYPE_STR, 2, 2);
        new Node("string<=?", TYPE_BOOL, TYPE_STR, 2, 2);
        new Node("string>=?", TYPE_BOOL, TYPE_STR, 2, 2);
        new Node("string-ci<?", TYPE_BOOL, TYPE_STR, 2, 2);
        new Node("string-ci>?", TYPE_BOOL, TYPE_STR, 2, 2);
        new Node("string-ci<=?", TYPE_BOOL, TYPE_STR, 2, 2);
        new Node("string-ci>=?", TYPE_BOOL, TYPE_STR, 2, 2);
        //(substring string start end)
        new Node("string-append", TYPE_STR, TYPE_STR, 0, 0x7FFFFFFF);
        new Node("string-copy", TYPE_STR, TYPE_STR, 1, 1);
#endif
        new Node("procedure?", TYPE_BOOL, TYPE_OBJ, 1, 1);
    }

    static void clear()
    {
        for (auto iter = pool.begin(); iter != pool.end(); ++iter)
            delete *iter;
        pool.clear();
    }
};

vector<Node*> Node::pool;

int depth, length, size;

inline bool flip()
{
    return rand() % depth;
}

inline string rand_sym()
{
    if (rand() & 1)
        return "-";
    return (rand() & 1) ? "+" : "";
}

inline string rand_exp()
{
    ostringstream buffer;
    buffer << rand() % 201-100;
    return buffer.str();
}

inline string rand_uint()
{
    string exp = string("")+(char)(rand() % 9+'1');
    for (; rand() % length; exp += (char)(rand() % 10+'0'));
    return exp;
}

inline string rand_int()
{
    return rand_sym()+rand_uint();
}

inline string rand_rint()
{
    int r = rand() & 3;
    int radix[] = {2, 8, 10, 16};
    string prefix[] = {"#b", "#o", "#d", "#h"};
    char digit[] = "0123456789abcdef";
    if (r == 2)
        return (rand() & 1) ? "#d"+rand_int() : rand_int();
    string exp = rand_sym()+digit[rand() % (radix[r]-1)+1];
    for (; rand() % length; exp += digit[rand() % radix[r]]);
    return exp;
}

inline string rand_urat()
{
    return rand_uint()+"/"+rand_uint();
}

inline string rand_rat()
{
    return rand_sym()+rand_urat();
}

inline string rand_ureal()
{
    switch (rand() % 4)
    {
    case 0:
        return rand_uint()+"."+rand_uint();
    case 1:
        return "."+rand_uint();
    case 2:
        return rand_uint()+"."+rand_uint()+"e"+rand_exp();
    case 3:
        return "."+rand_uint()+"e"+rand_exp();
    }
    return rand_uint();
}

inline string rand_real()
{
    return rand_sym()+rand_ureal();
}

inline string rand_cmplx()
{
    switch (rand() % 18)
    {
    case 0:
        return rand_real()+((rand() & 1) ? "+" : "-")+((rand() & 1) ? rand_ureal() : "")+"i";
    case 1:
        return rand_rat()+((rand() & 1) ? "+" : "-")+((rand() & 1) ? rand_ureal() : "")+"i";
    case 2:
        return rand_int()+((rand() & 1) ? "+" : "-")+((rand() & 1) ? rand_ureal() : "")+"i";
    case 3:
        return rand_real()+((rand() & 1) ? "+" : "-")+((rand() & 1) ? rand_urat() : "")+"i";
    case 4:
        return rand_rat()+((rand() & 1) ? "+" : "-")+((rand() & 1) ? rand_urat() : "")+"i";
    case 5:
        return rand_int()+((rand() & 1) ? "+" : "-")+((rand() & 1) ? rand_urat() : "")+"i";
    case 6:
        return rand_real()+((rand() & 1) ? "+" : "-")+((rand() & 1) ? rand_uint() : "")+"i";
    case 7:
        return rand_rat()+((rand() & 1) ? "+" : "-")+((rand() & 1) ? rand_uint() : "")+"i";
    case 8:
        return rand_int()+((rand() & 1) ? "+" : "-")+((rand() & 1) ? rand_uint() : "")+"i";
    case 9:
        return rand_real()+"@"+rand_real();
    case 10:
        return rand_rat()+"@"+rand_real();
    case 11:
        return rand_int()+"@"+rand_real();
    case 12:
        return rand_real()+"@"+rand_rat();
    case 13:
        return rand_rat()+"@"+rand_rat();
    case 14:
        return rand_int()+"@"+rand_rat();
    case 15:
        return rand_real()+"@"+rand_int();
    case 16:
        return rand_rat()+"@"+rand_int();
    case 17:
        return rand_int()+"@"+rand_int();
    }
    return rand_real();
}

inline string rand_char()
{
    if (rand() % 64 < 10)
        return string("#\\")+(char)(rand() % 10+'0');
    if (rand() % 54 < 26)
        return string("#\\")+(char)(rand() % 26+'A');
    if (rand() % 34 < 26)
        return string("#\\")+(char)(rand() % 26+'a');
    return (rand() & 1) ? "#\\space" : "#\\newline";
}

inline string rand_str()
{
    string s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890:;!@#$%^&*()<>,./?`~|[]{}+=_- \t";
    string exp = "\"";
    for (; rand() % length; exp += (rand() % s.length() < 2) ? ((rand() & 1) ? string("\\\\") : string("\\\"")) : string("")+s[rand() % s.length()]);
    exp += "\"";
    return exp;
}

inline string rand_ws()
{
    if (rand() % 10 < 5)
        return " ";
    if (rand() % 5 < 2)
        return string((int)round(max(log(max(log(rand()), 0.0)), 0.0))+1, ' ');
    return rand() % 3 < 2 ? "\t" : "\n";
}

inline string rand_delim()
{
    if (rand() % 10 < 7)
        return "";
    if (rand() % 3 < 2)
        return " ";
    if (rand() % 2 < 1)
        return string((int)round(max(log(max(log(rand()), 0.0)), 0.0))+1, ' ');
    return rand() % 3 < 2 ? "\t" : "\n";
}

inline string rand_endl()
{
    if (rand() % 10 < 6)
        return "\n";
    if (rand() % 4 < 1)
        return "\t";
    if (rand() % 3 < 2)
        return " ";
    return string((int)round(max(log(max(log(rand()), 0.0)), 0.0))+1, ' ');
}

inline string constant(const int &t)
{
    vector<int> type;
    if ((t & TYPE_INT) == TYPE_INT)
        type.push_back(TYPE_INT);
    if ((t & TYPE_RAT) == TYPE_RAT)
        type.push_back(TYPE_RAT);
    if ((t & TYPE_REAL) == TYPE_REAL)
        type.push_back(TYPE_REAL);
    if ((t & TYPE_CMPLX) == TYPE_CMPLX)
        type.push_back(TYPE_CMPLX);
    if ((t & TYPE_BOOL) == TYPE_BOOL)
        type.push_back(TYPE_BOOL);
    if ((t & TYPE_CHAR) == TYPE_CHAR)
        type.push_back(TYPE_CHAR);
    if ((t & TYPE_STR) == TYPE_STR)
        type.push_back(TYPE_STR);
    if ((t & TYPE_PROC) == TYPE_PROC)
        type.push_back(TYPE_PROC);
    switch (type[rand() % type.size()])
    {
    case TYPE_INT:
        return rand_int();
    case TYPE_RAT:
        return rand_rat();
    case TYPE_REAL:
        return rand_real();
    case TYPE_CMPLX:
        return rand_cmplx();
    case TYPE_BOOL:
        return (rand() & 1) ? "#t" : "#f";
    case TYPE_CHAR:
        return rand_char();
    case TYPE_STR:
        return rand_str();
    case TYPE_PROC:
        return Node::pool[rand() % Node::pool.size()]->name;
    }
    return "";
}

string dfs(const int &t, const int &d)
{
    if (! flip() || d <= 0)
        return constant(t);
    Node* f = Node::pool[rand() % Node::pool.size()];
    for (; (f->type & t) != f->type; f = Node::pool[rand() % Node::pool.size()]);
    string exp = "("+rand_delim()+f->name;
    for (int i = 1; i <= f->lower; ++i)
        exp += rand_ws()+dfs(f->arg, d-1);
    for (int i = f->lower+1; i <= f->upper && rand() <= RAND_MAX/(i-f->lower); ++i)
        exp += rand_ws()+dfs(f->arg, d-1);
    exp += rand_delim()+")";
    return exp;
}

string generate()
{
   //int flag = TYPE_OBJ & ~TYPE_PROC;
   int flag = TYPE_OBJ;
#ifndef CHAR_SUPPORT
   flag &= ~TYPE_CHAR;
#endif
#ifndef STRING_SUPPORT
   flag &= ~TYPE_STR;
#endif

#ifdef INEXACT_SUPPORT
   flag |= TYPE_CMPLX;
   return rand_delim()+dfs(flag, depth*3)+rand_delim();
#else
   flag &= ~(TYPE_CMPLX);
   flag |= TYPE_RAT;
   //flag |= TYPE_STR;

   if (rand() < RAND_MAX/4)
       return string("(")+rand_delim()+"newline"+rand_delim()+")";
   return string("(")+rand_delim()+"display"+rand_ws()+dfs(flag, depth*3)+rand_delim()+")";
#endif
}

int main(int argc, char *argv[])
{
    srand(system_clock::now().time_since_epoch().count());
    if (argc == 4)
    {
        depth = atoi(argv[1]);
        length = atoi(argv[2]);
        size = atoi(argv[3]);
    }
    else
    {
        cerr << "Please input depth, length and size: ";
        cin >> depth >> length >> size;
    }
    Node::prepare();
    ostringstream buffer;
    for (; buffer.str().length() < size; buffer << generate() << rand_endl());
    buffer << "(" << rand_delim() << "newline" << rand_delim() << ")" << rand_endl();
    cout << buffer.str() << endl;
    Node::clear();

    return 0;
}

