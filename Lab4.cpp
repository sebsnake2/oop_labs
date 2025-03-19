#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Базовий клас
class Person {
protected:
    string name;
    int age;

public:
    Person(string n = "Unknown", int a = 0) : name(n), age(a) {}

    // Функція для поліморфного виводу
    virtual void display() const {
        cout << left << setw(15) << name << setw(10) << age;
    }

    // Віртуальний деструктор для коректного виклику у спадкоємцях
    virtual ~Person() {
        cout << "Person " << name << " deleted." << endl;
    }
};

// Клас Employee (успадковує Person) 
class Employee : public Person {
protected:
    double salary;
    static int employeeCount;

public:
    Employee(string n = "Unknown", int a = 0, double s = 0.0) : Person(n, a), salary(s) {
        employeeCount++;
    }

    Employee(const Employee& other) : Person(other), salary(other.salary) {
        employeeCount++;
        cout << "Copy constructor called for " << name << endl;
    }

    Employee(Employee&& other) noexcept : Person(move(other)), salary(other.salary) {
        other.salary = 0.0;
        cout << "Move constructor called for " << name << endl;
    }

    // Оператор присвоєння копіювання
    Employee& operator=(const Employee& other) {
        if (this != &other) {
            Person::operator=(other);
            salary = other.salary;
        }
        return *this;
    }

    // Оператор присвоєння переміщення
    Employee& operator=(Employee&& other) noexcept {
        if (this != &other) {
            Person::operator=(move(other));
            salary = other.salary;
            other.salary = 0.0;
        }
        return *this;
    }

    // Перевизначений метод виводу інформації
    virtual void display() const override {
        Person::display();
        cout << setw(15) << salary;
    }

    static int getEmployeeCount() {
        return employeeCount;
    }

    virtual ~Employee() {
        employeeCount--;
        cout << "Employee " << name << " deleted." << endl;
    }
};

int Employee::employeeCount = 0;

// Дочірній клас
class Manager : public Employee {
private:
    int teamSize;

public:
    Manager(string n = "Unknown", int a = 0, double s = 0.0, int t = 0) : Employee(n, a, s), teamSize(t) {}

    // Перевизначений метод виводу інформації
    void display() const override {
        Employee::display();
        cout << setw(10) << teamSize << endl;
    }

    ~Manager() {
        cout << "Manager " << name << " deleted." << endl;
    }
};

// Дочірній клас Developer 
class Developer : public Employee {
private:
    string programmingLanguage;

public:
    Developer(string n = "Unknown", int a = 0, double s = 0.0, string lang = "Unknown")
        : Employee(n, a, s), programmingLanguage(lang) {
    }

    // Перевизначений метод виводу інформації
    void display() const override {
        Employee::display();
        cout << setw(15) << programmingLanguage << endl;
    }

    // Деструктор
    ~Developer() {
        cout << "Developer " << name << " deleted." << endl;
    }
};

int main() {
    int n;
    cout << "Enter the number of employees: ";
    cin >> n;

    // Масив покажчиків на базовий клас
    Employee** employees = new Employee * [n];

    for (int i = 0; i < n; ++i) {
        cout << "\nChoose type of employee (1 - Manager, 2 - Developer): ";
        int type;
        cin >> type;

        if (type == 1) {
            string name;
            int age, teamSize;
            double salary;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter salary: ";
            cin >> salary;
            cout << "Enter team size: ";
            cin >> teamSize;
            employees[i] = new Manager(name, age, salary, teamSize);
        }
        else if (type == 2) {
            string name, language;
            int age;
            double salary;
            cout << "Enter name: ";
            cin >> name;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter salary: ";
            cin >> salary;
            cout << "Enter programming language: ";
            cin >> language;
            employees[i] = new Developer(name, age, salary, language);
        }
    }

    cout << "\nDisplaying Employees:\n";
    cout << left << setw(15) << "Name" << setw(10) << "Age" << setw(15) << "Salary" << setw(15) << "Extra Info" << endl;
    cout << "---------------------------------------------------------------" << endl;

    for (int i = 0; i < n; ++i) {
        employees[i]->display();
    }

    cout << "\nTotal Employees: " << Employee::getEmployeeCount() << endl;

    for (int i = 0; i < n; ++i) {
        delete employees[i];
    }

    delete[] employees;

    return 0;
}