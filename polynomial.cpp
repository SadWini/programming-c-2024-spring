#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;
class Polynom{
    int size = 0; 
    double* coefs; 
public:
    Polynom();
    Polynom(int an);
    Polynom(int an, double* cfs);
    Polynom(const Polynom&); 
    ~Polynom();
    double& coef(int); 
    Polynom operator+(const Polynom&);   
    Polynom operator-(const Polynom&);   
    Polynom operator*(const Polynom&);
    friend ostream& operator<< (ostream& s, const Polynom& c); 
    friend istream& operator >> (istream& s, Polynom& c); 
};

Polynom::Polynom(){
    coefs = new double[1];
    coefs[0] = 0;
    cout << "constructor 0 " << this << endl;
}

Polynom::Polynom(int an){
    size = an;
    coefs = new double[size + 1];
    for (int i = 0; i <= size; i++){
        coefs[i] = 0;
    }
    cout << "constructor 1 " << this << endl;
}

Polynom::Polynom(int n, double* cfs) {
    size = n;
    coefs = new double[n + 1];
    for (int i = 0; i <= size; i++) {
        coefs[i] = 0;
    }
    cout << "constructor 2 " << this << endl;
}

Polynom::~Polynom(){
    cout << "destructor " << this << endl;
    delete[]coefs;
}

Polynom::Polynom(const Polynom& f){
    size = f.size;
    coefs = new double[size + 1];
    for (int i = 0; i <= size; i++)
        coefs[i] = f.coefs[i];
    cout << "constructor copy" << endl;
}

double& Polynom::coef(int i){
    static double c = -1;
    if (i <= size)
        return coefs[i];
    else
        cout << "Wrong given degree, no such coef";
    return c;
}

Polynom Polynom::operator-(const Polynom& t){
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
        return Polynom(Z.size, Z.coefs);
    }
}

Polynom Polynom::operator+(const Polynom& t)
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

Polynom Polynom::operator*(const Polynom& t){
    Polynom Y(size + t.size);
    for (int i = 0; i <= size; i++)
        for (int j = 0; j <= t.size; j++)
            Y.coefs[i + j] += coefs[i] * t.coefs[j];
    return Polynom(Y.size, Y.coefs);
}

istream& operator>>(istream& s, Polynom& c){
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
    int n, m;
    cout << "Введите степень полинома A и степень полинома B:" << '\n';
    cin >> n >> m;
    Polynom A(n), B(m);
    cout << "Введите коэфициенты полинома A:" << '\n';
    cin >> A;
    cout << "Введите коэфициенты полинома B:" << '\n';
    cin >> B;
    cout << setw(17) << "Многочлен А:" << setw(5) << A << '\n';
    cout << setw(17) << "Многочлен B:" << setw(5) << B << '\n';
    cout << setw(17) << "Многочлен D=A+B:" << setw(5) << A + B << '\n';
    //cout << setw(17) << "Многочлен K=A-B:" << setw(5) << (K = A - B) << '\n';
    //cout << setw(17) << "Многочлен K=A-B:" << setw(5) << (Y = A * B) << '\n';
    return 0;
}