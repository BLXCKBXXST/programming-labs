#include <iostream>
#include <string>
using namespace std;

class Airport {
private:
    string name;
    string city;
    string status;
    int runways;
    int day;
    int month;
    int year;

public:
    Airport() {
        name = "";
        city = "";
        status = "";
        runways = 0;
        day = 0;
        month = 0;
        year = 0;
    }

    Airport(string n, string c, string s, int r, int d, int m, int y) {
        name = n;
        city = c;
        status = s;
        runways = r;
        day = d;
        month = m;
        year = y;
    }

    void setName(string n)    { name = n; }
    void setCity(string c)    { city = c; }
    void setStatus(string s)  { status = s; }
    void setRunways(int r)    { runways = r; }
    void setDate(int d, int m, int y) { day = d; month = m; year = y; }

    string getName()   { return name; }
    string getCity()   { return city; }
    string getStatus() { return status; }
    int    getRunways(){ return runways; }

    int getDecade() {
        if (day >= 1 && day <= 10) return 1;
        else if (day >= 11 && day <= 20) return 2;
        else return 3;
    }

    string getSeason() {
        if (month == 12 || month == 1 || month == 2)
            return "Зима";
        else if (month >= 3 && month <= 5)
            return "Весна";
        else if (month >= 6 && month <= 8)
            return "Лето";
        else
            return "Осень";
    }

    int getCentury() {
        return (year / 100) + 1;
    }

    void outputTo() {
        cout << "\nАэропорт: " << name << " (" << city << ")" << endl;
        cout << "Статус: " << status << ", Полос: " << runways << endl;
        cout << "Дата открытия: " << day << "." << month << "." << year << endl;
        cout << "Декада открытия: " << getDecade() << "-я" << endl;
        cout << "Сезон открытия: " << getSeason() << endl;
        cout << "Век открытия: " << getCentury() << "-й" << endl;
    }
};

int main() {
    int N = 3;
    Airport *ports = new Airport[N];

    ports[0].setName("Шереметьево");
    ports[0].setCity("Москва");
    ports[0].setStatus("Международный");
    ports[0].setRunways(4);
    ports[0].setDate(25, 8, 1959);

    ports[1].setName("Домодедово");
    ports[1].setCity("Москва");
    ports[1].setStatus("Международный");
    ports[1].setRunways(3);
    ports[1].setDate(25, 5, 1964);

    ports[2].setName("Пулково");
    ports[2].setCity("Санкт-Петербург");
    ports[2].setStatus("Международный");
    ports[2].setRunways(2);
    ports[2].setDate(24, 6, 1932);

    cout << "========== РЕЗУЛЬТАТЫ ==========";
    for (int i = 0; i < N; i++) {
        ports[i].outputTo();
    }

    cout << "\n========== Конструктор с параметрами ==========" << endl;
    Airport domodedovo("Домодедово", "Москва", "Международный", 3, 25, 5, 1964);
    domodedovo.outputTo();

    delete[] ports;
    return 0;
}
