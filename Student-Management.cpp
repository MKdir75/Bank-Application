#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Student {
    int id;
    string name;
    int age;
    string course;

public:
    Student(int id, string name, int age, string course) {
        this->id = id;
        this->name = name;
        this->age = age;
        this->course = course;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getCourse() const { return course; }

    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setCourse(string c) { course = c; }

    void display() const {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Age: " << age
             << " | Course: " << course << endl;
    }

    void save(ofstream &out) const {
        out << id << "," << name << "," << age << "," << course << endl;
    }

    static Student load(const string &line) {
        int id, age;
        string name, course;
        size_t p1 = line.find(",");
        size_t p2 = line.find(",", p1 + 1);
        size_t p3 = line.find(",", p2 + 1);

        id = stoi(line.substr(0, p1));
        name = line.substr(p1 + 1, p2 - p1 - 1);
        age = stoi(line.substr(p2 + 1, p3 - p2 - 1));
        course = line.substr(p3 + 1);

        return Student(id, name, age, course);
    }
};

vector<Student> students;

void saveStudents() {
    ofstream out("students.txt");
    for (const auto &s : students) {
        s.save(out);
    }
    out.close();
}

void loadStudents() {
    ifstream in("students.txt");
    string line;
    while (getline(in, line)) {
        students.push_back(Student::load(line));
    }
    in.close();
}

Student* findStudent(int id) {
    for (auto &s : students) {
        if (s.getId() == id) return &s;
    }
    return nullptr;
}

int main() {
    loadStudents();
    int choice;
    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id, age;
            string name, course;
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Course: ";
            cin.ignore();
            getline(cin, course);
            students.push_back(Student(id, name, age, course));
            cout << "Student added successfully!\n";
            saveStudents();
        }
        else if (choice == 2) {
            for (const auto &s : students) {
                s.display();
            }
        }
        else if (choice == 3) {
            int id;
            cout << "Enter Student ID: ";
            cin >> id;
            Student* s = findStudent(id);
            if (s) s->display();
            else cout << "Student not found!\n";
        }
        else if (choice == 4) {
            int id;
            cout << "Enter Student ID to update: ";
            cin >> id;
            Student* s = findStudent(id);
            if (s) {
                string name, course;
                int age;
                cout << "Enter new Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter new Age: ";
                cin >> age;
                cout << "Enter new Course: ";
                cin.ignore();
                getline(cin, course);
                s->setName(name);
                s->setAge(age);
                s->setCourse(course);
                cout << "Student updated successfully!\n";
                saveStudents();
            } else {
                cout << "Student not found!\n";
            }
        }
        else if (choice == 5) {
            int id;
            cout << "Enter Student ID to delete: ";
            cin >> id;
            bool deleted = false;
            for (auto it = students.begin(); it != students.end(); ++it) {
                if (it->getId() == id) {
                    students.erase(it);
                    deleted = true;
                    cout << "Student deleted successfully!\n";
                    saveStudents();
                    break;
                }
            }
            if (!deleted) cout << "Student not found!\n";
        }
    } while (choice != 6);

    cout << "Exiting... Students saved.\n";
    saveStudents();
    return 0;
}
