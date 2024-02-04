//Finding the roots of an equation by using false position method

#include <bits/stdc++.h>
using namespace std;

double fx(double x, int a[], int n);

int main () {
    double a, b, c, fa, fb, fc, p_c = 0,es;
    int iteration, degree;
    cout << "Degree of the polynomial function = ";                     //Get the equation 
    cin >> degree;
    int coefficient[degree+1];
    for (int i = degree; i > 0; --i) 
    {
        cout << "Coefficient of x^" << i << ": ";
        cin >> coefficient[i];
    }
    cout << "Constant term = ";
    cin >> coefficient[0];
    cout << "Lower bound, a = ";
    cin >> a;
    cout << "Upper bound, b = ";
    cin >> b;
    // cout << "Number of iteration = ";
    // cin >> iteration;
    cout<<"Stoping error"<<endl;                                        //Get the stopping criteria
    cin>>es;
    double ea= 100;
    for (int i = 1; ea>=es/100; ++i) 
    {
        fa = fx(a, coefficient, degree);
        fb = fx(b, coefficient, degree);
        c = (a*fb - b*fa) / (fb - fa);
        fc = fx(c, coefficient, degree);
        ea = (abs(c - p_c) / c) * 100;
        p_c = c;
        cout << "\nIteration number: " << i << '\n';
        cout << "a = " << a << ", b = " << b << ", c = " << c << '\n';
        cout << "f(a) = " << fa << ", f(b) = " << fb << ", f(c) = " << fc << '\n';   //Showing all roots
        cout << "Approximate error = " << ea << "%\n";
        
        if (fa * fc < 0)
            b = c;
        else
            a = c;
    }
}


//Gain the value of fa,fb or fc

double fx(double x, int a[], int n) 
{
    double fx = 0;
    for (int i = 0; i <= n; ++i)
        fx += (a[i] * pow(x, i));

    return fx;    
}
