#include <iostream>
#include <string>
using namespace std;

class Airport {
private:
    string name;
    string city;
    string status;
    int runways;
public:
    Airport(string n, string c, string s, int r) {
        name = n;
        city = c;
        status = s;
        runways = r;
    }

    string getName()    { return name; }
    string getCity()    { return city; }
    string getStatus()  { return status; }
    int    getRunways() { return runways; }

    void setName(string n)    { name = n; }
    void setCity(string c)    { city = c; }
    void setStatus(string s)  { status = s; }
    void setRunways(int r)    { runways = r; }

    void outputTo() {
        cout << "Название аэропорта: " << name << endl;
        cout << "Город: " << city << endl;
        cout << "Статус: " << status << endl;
        cout << "Количество полос: " << runways << endl;
        cout << "------------------------" << endl;
    }
};

int main() {
    Airport *sheremetyevo = new Airport("Шереметьево", "Москва", "Международный", 4);
    Airport *domodedovo   = new Airport("Домодедово", "Москва", "Международный", 3);

    cout << "=== До изменений ===" << endl;
    sheremetyevo->outputTo();
    domodedovo->outputTo();

    sheremetyevo->setRunways(5);
    domodedovo->setStatus("Международный и местный");

    cout << "=== После изменений ===" << endl;
    sheremetyevo->outputTo();
    domodedovo->outputTo();

    delete sheremetyevo;
    delete domodedovo;
    return 0;
}
