#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    string name;
    int age;
    double salary;

public:
    // Конструктор за замовчуванням
    Employee() : name("Unknown"), age(0), salary(0.0) {}

    // Конструктор із параметрами
    Employee(string n, int a, double s) : name(n), age(a), salary(s) {}

    // Перевантажений конструктор
    Employee(string n, int a) : Employee(n, a, 10000.0) {} 

    // Деструктор
    ~Employee() {
        cout << "Employee " << name << " has been deleted." << endl;
    }

    // Метод для введення інформації
    void input() {
        cin.ignore(); // Очистка буфера вводу перед введенням рядка
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter salary: ";
        cin >> salary;
    }

    void display() const {
        cout << "--------------------------" << endl;
        cout << "Employee Information:" << endl;
        cout << "Name: " << name << "\nAge: " << age << "\nSalary: " << salary << "\n";
        cout << "--------------------------" << endl;
    }
};

class Department {
private:
    string deptName;
    int numEmployees;

public:
    Department() : deptName("Unknown"), numEmployees(0) {}

    Department(string dName, int num) : deptName(dName), numEmployees(num) {}

    // Деструктор
    ~Department() {
        cout << "Department " << deptName << " has been deleted." << endl;
    }

    void display() const {
        cout << "Department: " << deptName << "\nNumber of Employees: " << numEmployees << "\n";
    }
};

class Company {
private:
    string companyName;
    int yearFounded;

public:
    Company() : companyName("Unknown"), yearFounded(2000) {}

    Company(string cName, int year) : companyName(cName), yearFounded(year) {}

    // Деструктор
    ~Company() {
        cout << "Company " << companyName << " has been deleted." << endl;
    }

    void display() const {
        cout << "Company: " << companyName << "\nFounded: " << yearFounded << "\n";
    }
};

int main() {
    Employee emp1;
    cout << "Enter details for first employee:" << endl;
    emp1.input();

    Employee emp2;
    cout << "Enter details for second employee:" << endl;
    emp2.input();

    Department dept("IT", 10);
    Company comp("TechCorp", 1999);

    cout << "\nDisplaying Information:" << endl;
    emp1.display();
    emp2.display();
    dept.display();
    comp.display();

    return 0;
}
