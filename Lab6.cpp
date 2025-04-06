#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include <ctime>

using namespace std;

class Workable {
public:
    virtual void work() const = 0;
    virtual ~Workable() {}
};

class Person {
protected:
    string name;
    int age;

public:
    Person(string n = "Unknown", int a = 0) : name(n), age(a) {}
    virtual void display() const = 0;
    virtual string toString() const = 0;
    virtual ~Person() {}
};

class Employee : public Person, public Workable {
protected:
    double salary;
    static int employeeCount;

public:
    Employee(string n = "Unknown", int a = 0, double s = 0.0)
        : Person(n, a), salary(s) {
        employeeCount++;
    }

    virtual void display() const override {
        cout << left << setw(15) << name << setw(10) << age << setw(15) << salary;
    }

    virtual string toString() const override {
        return name + " " + to_string(age) + " " + to_string(salary);
    }

    virtual void work() const override {
        cout << name << " is working." << endl;
    }

    static int getEmployeeCount() {
        return employeeCount;
    }

    virtual ~Employee() {
        employeeCount--;
    }
};

int Employee::employeeCount = 0;

class Manager final : public Employee {
private:
    int teamSize;

public:
    Manager(string n = "Unknown", int a = 0, double s = 0.0, int t = 0)
        : Employee(n, a, s), teamSize(t) {
    }

    void display() const override {
        Employee::display();
        cout << setw(10) << teamSize << endl;
    }

    string toString() const override {
        return Employee::toString() + " " + to_string(teamSize);
    }

    void work() const override {
        cout << name << " is managing a team of " << teamSize << " people." << endl;
    }
};

class Developer : public Employee {
private:
    string programmingLanguage;

public:
    Developer(string n = "Unknown", int a = 0, double s = 0.0, string lang = "Unknown")
        : Employee(n, a, s), programmingLanguage(lang) {
    }

    void display() const override {
        Employee::display();
        cout << setw(15) << programmingLanguage << endl;
    }

    string toString() const override {
        return Employee::toString() + " " + programmingLanguage;
    }

    void work() const override {
        cout << name << " is coding in " << programmingLanguage << "." << endl;
    }
};

vector<unique_ptr<Employee>> employees;
const string ADMIN_PASSWORD = "admin123"; 

// Функція для завантаження даних із файлу з обробкою винятків
void loadFromFile() {
    try {
        ifstream file("employees.txt");
        if (!file) throw runtime_error("Error: Cannot open file for reading.");

        string name, lang;
        int age, teamSize;
        double salary;

        while (file >> name >> age >> salary) {
            if (file.peek() == '\n' || file.eof()) {
                employees.push_back(make_unique<Employee>(name, age, salary));
            }
            else {
                file >> lang;
                employees.push_back(make_unique<Developer>(name, age, salary, lang));
            }
        }
        file.close();
    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
}

// Функція для збереження даних у файл з обробкою винятків
void saveToFile() {
    try {
        ofstream file("employees.txt");
        if (!file) throw runtime_error("Error: Cannot open file for writing.");
        
        for (const auto& emp : employees) {
            file << emp->toString() << endl;
        }
        file.close();
    }
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
    }
}



// Функція для запису дії адміністратора в файл та виведення часу в термінал
void logAction(const string& action) {
    ofstream logFile("action_log.txt", ios::app); 
    if (logFile.is_open()) {
        time_t now = time(0); // Отримуємо поточний час
        char dt[26]; 
        ctime_s(dt, sizeof(dt), &now); 

        cout << "Action performed at: " << dt << endl;

        // Записуємо дію та час в файл
        logFile << dt << ": " << action << endl;
    }
    logFile.close();
}

void adminMenu() {
    int choice;
    do {
        try {
            cout << "\nAdmin Menu:" << endl;
            cout << "1. Add Employee" << endl;
            cout << "2. Display Employees" << endl;
            cout << "3. Save and Exit" << endl;
            cout << "Choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Invalid input. Please enter a number.");
            }

            if (choice == 1) {
                string name, role, lang;
                int age, teamSize;
                double salary;

                cout << "Enter name: ";
                cin >> name;

                cout << "Enter age: ";
                if (!(cin >> age)) throw invalid_argument("Invalid age input.");

                cout << "Enter salary: ";
                if (!(cin >> salary)) throw invalid_argument("Invalid salary input.");

                cout << "Enter role (developer/manager): ";
                cin >> role;

                if (role == "developer") {
                    cout << "Enter programming language: ";
                    cin >> lang;
                    employees.push_back(make_unique<Developer>(name, age, salary, lang));
                }
                else if (role == "manager") {
                    cout << "Enter team size: ";
                    if (!(cin >> teamSize)) throw invalid_argument("Invalid team size input.");
                    employees.push_back(make_unique<Manager>(name, age, salary, teamSize));
                }
                else {
                    throw invalid_argument("Invalid role selected.");
                }
            }
            else if (choice == 2) {
                for (const auto& emp : employees) {
                    emp->display();
                    cout << endl;
                }
            }
        }
        catch (const exception& e) {
            cerr << "Exception: " << e.what() << endl;
        }
    } while (choice != 3);

    saveToFile();
}

void userMenu() {
    cout << "\nEmployees List:" << endl;
    for (const auto& emp : employees) {
        emp->display();
        cout << endl;
    }
}

int main() {
    loadFromFile();
    int userType;
    cout << "1. Admin\n2. User\nEnter type: ";
    cin >> userType;
    if (userType == 1) {
        string password;
        cout << "Enter admin password: ";
        cin >> password;
        if (password == ADMIN_PASSWORD) {
            adminMenu();
        }
        else {
            cout << "Incorrect password!" << endl;
        }
    }
    else {
        userMenu();
    }
    return 0;
}
