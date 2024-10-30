#include <iostream>
#include <string>

class RomanFigure {
    int value;
    std::string figure;

    char base10[4] = { 'M', 'C', 'X', 'I' }; // k10
    char base5[3] = { 'D', 'L', 'V' }; // k5

    //static const char base10[4]; // k10
    //static const char base5[3];  // k5

    int CharValue(char c) const {
        int f = -1;
        int temp = 1000;
        for (int i = 0; i < 4; i++) {
            if (base10[i] == c) {
                f = temp;
                break;
            }
            temp /= 2;
            if (i < 3 && base5[i] == c) {
                f = temp;
                break;
            }
            temp /= 5;
        }
        return f;
    }

    std::string IntToRoman(int v) const {
        int temp = 1000;
        int basetemp = 0;
        std::string roman;
        while (v > 0) {
            while (v >= temp) {
                v -= temp;
                roman += base10[basetemp];
            }
            if (temp == 1) { break; }
            temp = (temp * 9) / 10;

            if (v >= temp) {
                v -= temp;
                roman += base10[basetemp + 1];
                roman += base10[basetemp];
            }
            temp = (temp * 5) / 9;

            if (v >= temp) {
                v -= temp;
                roman += base5[basetemp];
            }
            temp = (temp * 4) / 5;

            if (v >= temp) {
                v -= temp;
                roman += base10[basetemp + 1];
                roman += base5[basetemp];
            }
            temp = temp / 4;

            basetemp += 1;
        }
        return roman;
    }

    int RomanToInt(const std::string& roman) const {
        int v = 0, total = 0, prevv = 0;

        for (char c : roman) {
            v = CharValue(c);
            if (v > prevv) {
                total += v - 2 * prevv;
            }
            else {
                total += v;
            }
            prevv = v;
        }
        return total;
    }

public:

    RomanFigure() {};
    RomanFigure(int n) : value(n), figure(IntToRoman(n)) {};

    void out() const {
        std::cout << figure << "\n";
    }

    void in(int v) {
        value = v;
        figure = IntToRoman(v);
        try {
            if (v > 3999)
                throw "Римского числа больше 3999 быть не может!";
            if (v <= 0)
                throw "Римские числа могут быть только натуральными!";
        }
        catch (const char* str) {
            std::cout << str << "\n";
            value = 0;
            figure = "";
        }
    }

    std::string summ(std::string a, std::string b) {
        std::string c;
        int ta = static_cast<int>(size(a) - 1), tb = static_cast<int>(size(b) - 1);
        while (ta >= 0 && tb >= 0) {
            if (CharValue(a[ta]) < (CharValue(b[tb]))) {
                if (tb > 0) {
                    if (CharValue(a[ta]) < (CharValue(b[tb - 1]))) {
                        c.push_back(a[ta]);
                        ta--;
                    }
                    else if (CharValue(a[ta]) == (CharValue(b[tb - 1]))) {
                        c.push_back(b[tb]);
                        tb -= 2;
                        ta--;
                    }
                    else {
                        c.push_back(a[ta]);
                        c.push_back(b[tb - 1]);
                        c.push_back(b[tb]);
                        ta--;
                        tb -= 2;
                    }
                }
                else {
                    c.push_back(a[ta]);
                    ta--;
                }
            }
            else if (CharValue(a[ta]) == (CharValue(b[tb]))) {
                if (ta > 0) {
                    if (tb > 0) {
                        if (CharValue(a[ta]) > (CharValue(a[ta - 1]))) {
                            if (CharValue(b[tb]) > (CharValue(b[tb - 1]))) {
                                switch (a[ta])
                                {
                                case 'M':
                                    c.push_back('C');
                                    c += "CCDM";
                                    break;
                                case 'D':
                                    c.push_back('C');
                                    c += "CD";
                                    break;
                                case 'C':
                                    c.push_back('X');
                                    c += "XXLC";
                                    break;
                                case 'L':
                                    c.push_back('X');
                                    c += "XC";
                                    break;
                                case 'X':
                                    c.push_back('I');
                                    c += "IIVX";
                                    break;
                                case 'V':
                                    c.push_back('I');
                                    c += "IX";
                                    break;
                                }
                                ta -= 2;
                                tb -= 2;
                            }
                            else {
                                c.push_back(a[ta]);
                                c.push_back(a[ta - 1]);
                                c.push_back(b[tb]);
                                tb--;
                                ta -= 2;
                            }
                        }
                        else {
                            if (CharValue(b[tb]) > (CharValue(b[tb - 1]))) {
                                c.push_back(b[tb]);
                                c.push_back(b[tb - 1]);
                                c.push_back(a[ta]);
                                ta--;
                                tb -= 2;
                            }
                            else {
                                c.push_back(a[ta]);
                                ta--;
                                c.push_back(b[tb]);
                                tb--;
                            }
                        }
                    }
                    else {
                        if (CharValue(a[ta]) > (CharValue(a[ta - 1]))) {
                            c.push_back(a[ta]);
                            c.push_back(a[ta - 1]);
                            c.push_back(b[tb]);
                            tb--;
                            ta -= 2;
                        }
                        else {
                            c.push_back(a[ta]);
                            ta--;
                            c.push_back(b[tb]);
                            tb--;
                        }
                    }
                }
                else {
                    if (tb > 0) {
                        if (CharValue(b[tb]) > (CharValue(b[tb - 1]))) {
                            c.push_back(b[tb]);
                            c.push_back(b[tb - 1]);
                            c.push_back(a[ta]);
                            ta--;
                            tb -= 2;
                        }
                        else {
                            c.push_back(a[ta]);
                            ta--;
                            c.push_back(b[tb]);
                            tb--;
                        }
                    }
                    else {
                        c.push_back(a[ta]);
                        ta--;
                        c.push_back(b[tb]);
                        tb--;
                    }
                }
            }
            else {
                std::swap(a, b);
                std::swap(ta, tb);
            }
        }
        if (ta != -1) {
            for (int i = ta; i > -1; i--) {
                c.push_back(a[i]);
            }
        }
        if (tb != -1) {
            for (int i = tb; i > -1; i--) {
                c.push_back(b[i]);
            }
        }
        /*char prv = '#';
        int k = 1;
        for (int i = 0; i < static_cast<int>(size(c)); i++) {
            if ((c[i] == prv) && (i!= static_cast<int>(size(c)) -1 )){
                k++;
            } else {
                switch (prv)
                {
                case 'V':
                    if (k == 2) {
                        c += "X";
                    }
                    else if (k == 3) {
                        c += "IX";
                    }
                    break;
                case 'I':
                    if (k == 4) {
                        c += "VI";
                    }
                    else if (k == 5) {
                        c += "V";
                    }
                    else if (k == 9) {
                        c += "XI";
                    }
                    break;
                }
                k = 1;
            }
            prv = c[i];
        }
        */
        std::string d;
        for(int i = static_cast<int>(size(c)-1); i > -1; i--) {
            d.push_back(c[i]);
        }
        return d;
    }

    RomanFigure operator+(RomanFigure a) {
        value = a.value + this->value;
        figure = summ(this->figure, a.figure);
        return *this;
    }

  

    /*RomanFigure operator+(RomanFigure a) {
        value = a.value + this->value;
        figure = IntToRoman(RomanToInt(a.figure) + RomanToInt(this->figure));
        return *this;
    }

    RomanFigure operator-(RomanFigure a) {
        try {
            if (RomanToInt(this->figure) - RomanToInt(a.figure) <= 0)
                throw "Разность римских чисел не является натуральным числом!";
        }
        catch (const char* str) {
            std::cout << str << "\n";
        }
        value = this->value - a.value;
        figure = IntToRoman(RomanToInt(this->figure) - RomanToInt(a.figure));
        return *this;
    }
    */
};


int main() {
    setlocale(LC_ALL, "RUS");

    RomanFigure a, b, c;
    int ai, bi;
    std::cin >> ai >> bi;
    a.in(ai);
    a.out();
    b.in(bi);
    b.out();
    c = a + b;
    c.out();
}