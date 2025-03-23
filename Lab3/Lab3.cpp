#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Employee {
private:
    string name;
    int age;
    double salary;
    static int employeeCount;

public:
    Employee() : name("Unknown"), age(0), salary(0.0) { employeeCount++; }

    Employee(string n, int a, double s) : name(n), age(a), salary(s) { employeeCount++; }

    // Перевантажений конструктор
    Employee(string n, int a) : Employee(n, a, 10000.0) {}

    // Конструктор копіювання
    Employee(const Employee& other) : name(other.name), age(other.age), salary(other.salary) {
        employeeCount++;
        cout << "Copy constructor called for " << name << endl;
    }

    // Оператор присвоєння копіювання
    Employee& operator=(const Employee& other) {
        if (this != &other) {
            name = other.name;
            age = other.age;
            salary = other.salary;
        }
        return *this;
    }

    // Конструктор переміщення
    Employee(Employee&& other) noexcept : name(move(other.name)), age(other.age), salary(other.salary) {
        other.age = 0;
        other.salary = 0.0;
        cout << "Move constructor called for " << name << endl;
    }

    // Оператор присвоєння переміщення
    Employee& operator=(Employee&& other) noexcept {
        if (this != &other) {
            name = move(other.name);
            age = other.age;
            salary = other.salary;
            other.age = 0;
            other.salary = 0.0;
        }
        return *this;
    }

    // Деструктор
    ~Employee() {
        employeeCount--;
        cout << "Employee " << name << " has been deleted." << endl;
    }

    // Використання вказівника this
    Employee& setSalary(double s) {
        this->salary = s;
        return *this;
    }

    void input() {
        cin.ignore();
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter salary: ";
        cin >> salary;
    }

    void display() const {
        cout << left << setw(15) << name << setw(10) << age << setw(15) << salary << endl;
    }

    // Перевантаження унарного оператора - (зменшення зарплати на 10%)
    void operator-() {
        salary *= 0.9;
    }

    // Перевантаження бінарного оператора + (збільшення зарплати)
    Employee operator+(double amount) {
        return Employee(name, age, salary + amount);
    }

    // Перевантаження операторів потокового введення/виведення
    friend ostream& operator<<(ostream& os, const Employee& e);
    friend istream& operator>>(istream& is, Employee& e);

    // Статичний метод
    static int getEmployeeCount() {
        return employeeCount;
    }
};

// Ініціалізація статичного поля
int Employee::employeeCount = 0;

ostream& operator<<(ostream& os, const Employee& e) {
    os << left << setw(15) << e.name << setw(10) << e.age << setw(15) << e.salary;
    return os;
}

istream& operator>>(istream& is, Employee& e) {
    cout << "Enter name: ";
    is.ignore();
    getline(is, e.name);
    cout << "Enter age: ";
    is >> e.age;
    cout << "Enter salary: ";
    is >> e.salary;
    return is;
}

int main() {
    int n;
    cout << "Enter the number of employees: ";
    cin >> n;

    Employee* employees = new Employee[n];

    for (int i = 0; i < n; ++i) {
        cout << "\nEnter details for employee " << i + 1 << ":\n";
        cin >> employees[i];
    }

    cout << "\nDisplaying Employees:" << endl;
    cout << left << setw(15) << "Name" << setw(10) << "Age" << setw(15) << "Salary" << endl;
    cout << "--------------------------------------" << endl;
    for (int i = 0; i < n; ++i) {
        cout << employees[i] << endl;
    }

    cout << "Total Employees: " << Employee::getEmployeeCount() << endl;

    delete[] employees;
    return 0;
}
