#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Інтерфейс через чисто віртуальні функції
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

    // Чисто віртуальна функція
    virtual void display() const = 0;

    virtual ~Person() {
        cout << "Person " << name << " deleted." << endl;
    }
};

// Клас Employee (успадковує Person і реалізує Workable)
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

    // Віртуальна функція work()
    virtual void work() const override {
        cout << name << " is working." << endl;
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

// Дочірній клас Manager (забороняємо подальше успадкування)
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

    void work() const override {
        cout << name << " is managing a team of " << teamSize << " people." << endl;
    }

    ~Manager() {
        cout << "Manager " << name << " deleted." << endl;
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

    void work() const override {
        cout << name << " is coding in " << programmingLanguage << "." << endl;
    }

    ~Developer() {
        cout << "Developer " << name << " deleted." << endl;
    }
};

// Поліморфізм через показник
void showWork(Employee* emp) {
    emp->display();
    emp->work();
}

// Поліморфізм через посилання
void showWorkByRef(const Employee& emp) {
    emp.display();
    emp.work();
}

// Використання інтерфейсу
void processWork(const Workable& worker) {
    worker.work();
}

int main() {
    // перевизначення через поліморфізм
    Employee* employees[3];
    employees[0] = new Manager("Alex", 40, 5000, 10);
    employees[1] = new Developer("Kate", 30, 4000, "C++");
    employees[2] = new Developer("John", 25, 3500, "Python");

    cout << "\n=== Showing Employees by pointer ===\n";
    for (int i = 0; i < 3; ++i) {
        showWork(employees[i]);
    }

    cout << "\n=== Showing Employees by reference ===\n";
    for (int i = 0; i < 3; ++i) {
        showWorkByRef(*employees[i]);
    }

    cout << "\n=== Using Interface ===\n";
    for (int i = 0; i < 3; ++i) {
        processWork(*employees[i]);
    }

    cout << "\nTotal Employees: " << Employee::getEmployeeCount() << endl;

    for (int i = 0; i < 3; ++i) {
        delete employees[i];
    }

    return 0;
}
