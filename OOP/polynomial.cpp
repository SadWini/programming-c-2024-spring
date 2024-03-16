#include<iostream>
#include<iomanip>
#include<fstream>
#include<initializer_list>

using namespace std;
class Polynom{
    int size = 0; 
    double* coefs; 
public:
    Polynom();
    Polynom(int an);
    Polynom(int an, double* cfs);
    Polynom(const Polynom&);
    Polynom(Polynom&&);
    Polynom(initializer_list<double>);
    ~Polynom();
    double& coef(int) const; 
    double value(double) const;
    Polynom int_cast(int) const;
    Polynom operator+(const Polynom&) const;   
    Polynom operator-(const Polynom&) const;   
    Polynom operator*(const Polynom&) const;
    Polynom& operator=(Polynom&);
    Polynom& operator=(Polynom&&);
    double operator()(double) const;
    double& operator[] (int);
    friend ostream& operator<< (ostream& s, const Polynom& c); 
    friend istream& operator >> (istream& s, const Polynom& c); 
};

Polynom::Polynom(){
    size = 0;
    coefs = new double[1];
    coefs[0] = 0;
    //cout << "constructor 0 " << this << endl;
}

Polynom::Polynom(int an){
    size = an;
    coefs = new double[size + 1];
    for (int i = 0; i <= size; i++){
        coefs[i] = 0;
    }
    //cout << "constructor 1 " << this << endl;
}

Polynom::Polynom(int n, double* cfs) {
    size = n;
    coefs = new double[n + 1];
    for (int i = 0; i <= size; i++) {
        coefs[i] = 0;
    }
    //cout << "constructor 2 " << this << endl;
}

Polynom::~Polynom(){
    //cout << "destructor " << this << endl;
    delete[]coefs;
}

Polynom::Polynom(const Polynom& f){
    size = f.size;
    coefs = new double[size + 1];
    for (int i = 0; i <= size; i++)
        coefs[i] = f.coefs[i];
    //cout << "constructor copy" << endl;
}

Polynom::Polynom(Polynom && x) : coefs(x.coefs), size(x.size){
    x.coefs = nullptr;
    x.size = 0;
}

Polynom::Polynom(initializer_list<double> s) {
    size = s.size() - 1;
    coefs = new double[size+1];
    copy(s.begin(), s.end(), coefs);
}

double& Polynom::coef(int i) const{
    static double c = -1;
    if (i <= size)
        return coefs[i];
    else
        cout << "Wrong given degree, no such coef";
    return c;
}

double Polynom::operator()(double x) const {
    double carry = 1;
    double res = 0;
    for (int i = 0; i <= size; i++) {
        res += coefs[i] * carry;
        carry *= x;
    }
    return res;
}

Polynom int_cast(int x) {
    double cfs[1] = { x };
    Polynom res = Polynom(0, cfs);
    return res;
}

Polynom Polynom::operator-(const Polynom& t) const{
    Polynom Z(max(size, t.size));
    if (size >= t.size){
        for (int i = 0; i <= t.size; i++)
            Z.coefs[i] = coefs[i] - t.coefs[i];
        return Z;
    } else {
        for (int i = 0; i <= size; i++)
            Z.coefs[i] = -t.coefs[i] + coefs[i];
        for (int i = size + 1; i <= t.size; i++)
            Z.coefs[i] = -t.coefs[i];
        return Z;
    }
}

Polynom Polynom::operator+(const Polynom& t) const
{
    Polynom Z(max(size, t.size));
    if (size >= t.size){
        for (int i = 0; i <= t.size; i++)
            Z.coefs[i] = coefs[i] + t.coefs[i];
        for (int i = t.size + 1; i <= size; i++)
            Z.coefs[i] = coefs[i];
        return Z;
    } else {
        for (int i = 0; i <= size; i++)
            Z.coefs[i] = t.coefs[i] + coefs[i];
        for (int i = size + 1; i <= t.size; i++)
            Z.coefs[i] = t.coefs[i];
    }
    return Z;
}

Polynom Polynom::operator*(const Polynom& t) const{
    Polynom Y(size + t.size);
    for (int i = 0; i <= size; i++)
        for (int j = 0; j <= t.size; j++)
            Y.coefs[i + j] += coefs[i] * t.coefs[j];
    return Y;
}

Polynom& Polynom::operator=(Polynom& p){ // конструктор копирования
    if (this == &p)
        return *this;
    size = p.size;
    coefs = new double[size + 1];
    for (int i = 0; i <= size; i++)
        coefs[i] = p.coefs[i];
    return *this;
}

Polynom& Polynom::operator=(Polynom &&p) { // перемещающая операция копирования
    size = p.size;
    swap(coefs, p.coefs);
    return *this;
}

double& Polynom::operator[] (int i) {
    return coefs[i];
}

istream& operator>>(istream& s, const Polynom& c){
    for (int i = 0; i <= c.size; i++){
        s >> c.coefs[i];
    }
    return s;
}
ostream& operator<<(ostream& s, const Polynom& c)
{
    int n = 0;
    for (int i = 0; i <= c.size; i++){
        if (c.coefs[i] != 0)
            n++;
    }
    if (n != 0) {
        if (c.coefs[0] != 0) {
            s << c.coefs[0];
        }
        for (int i = 1; i <= c.size; i++){
            if (c.coefs[i] < 0)
            {
                if (c.coefs[i] != -1)
                    s << c.coefs[i] << "X^" << i;
                else
                    s << "-" << "X^" << i;
            }
            else{
                if (c.coefs[i] != 0){
                    if (c.coefs[i] != 1)
                        s << "+" << c.coefs[i] << "X^" << i;
                    else
                        s << "+" << "X^" << i;
                }
            }
        }
        s << '\n';
    }
    else{
        s << 0;
    }
    return s;
}

int main()
{
    setlocale(LC_ALL, "");
    Polynom A = { 1, 2 };
    Polynom B = { 1, 2, 1 }, D, K;
    cout << setw(17) << "Многочлен А:" << setw(5) << A << '\n';
    cout << setw(17) << "Многочлен B:" << setw(5) << B << '\n';
    cout << setw(17) << "Многочлен D=A+B:" << setw(5) << (D = move(A + B)) << '\n';
    cout << setw(17) << "Многочлен A+B:" << setw(5) << (A + B) << '\n';
    cout << setw(17) << "Многочлен A*B:" << setw(5) << (A * B) << '\n';
    cout << setw(17) << "Многочлен K=:" << setw(5) << (K = move(B)) << endl;
    cout << setw(17) << "B[2] = " << B[2] <<  '\n';
    cout << setw(17) << "K(1.5) = " << setw(5) <<  K(1.5) << '\n';
    //cout << setw(17) << "Многочлен K=A-B:" << setw(5) << (Y = A * B) << '\n';
    return 0;
}
