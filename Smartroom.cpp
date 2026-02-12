#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

class smartlight {
private:
    int brightness;

    void clamp() {
        if (brightness < 0) brightness = 0;
        if (brightness > 100) brightness = 100;
    }

public:
    smartlight(int b) : brightness(b) { clamp(); }

    void setb(int b) {          
        brightness += b;
        clamp();
    }

    int getb() const {
        return brightness;
    }

    smartlight& operator++() {  
        if (brightness <= 95) brightness += 5;
        else brightness = 100;
        return *this;
    }

    smartlight& operator--() {  
        if (brightness >= 5) brightness -= 5;
        else brightness = 0;
        return *this;
    }
};

class smartroom {
private:
    vector<smartlight> s;

public:
    
    smartroom& operator+=(smartlight l) {
        s.push_back(l);
        return *this;
    }

    smartlight& operator[](int a) {
        return s[a];
    }

    smartroom& operator--() {
        for (int i = 0; i < s.size(); i++) {
    --s[i];
}

        return *this;
    }

    void print() const {
        for (int i = 0; i < (int)s.size(); i++) {
            cout << "light " << i << ": " << s[i].getb() << "\n";
        }
        cout << "----\n";
    }
};

int main() {
    smartroom a;

    a += smartlight(80);
    a += smartlight(10);

    a.print();

    --a;
    a.print();

    ++a[1];
    a.print();

    return 0;
}

