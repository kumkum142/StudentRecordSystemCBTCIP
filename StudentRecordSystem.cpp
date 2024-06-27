#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Student {
public:
    int rollNumber;
    string name;
    string address;
    float marks;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Marks: " << marks << endl;
    }
};

class StudentRecordManager {
    vector<Student> students;

public:
    void addStudent() {
        Student student;
        student.input();
        students.push_back(student);
        cout << "Student added successfully.\n";
    }

    void displayStudents() const {
        for (const auto& student : students) {
            student.display();
            cout << "----------------------\n";
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        for (const auto& student : students) {
            file << student.rollNumber << '\n'
                 << student.name << '\n'
                 << student.address << '\n'
                 << student.marks << '\n';
        }
        file.close();
        cout << "Records saved to file successfully.\n";
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "File not found.\n";
            return;
        }

        Student student;
        while (file >> student.rollNumber) {
            file.ignore();
            getline(file, student.name);
            getline(file, student.address);
            file >> student.marks;
            students.push_back(student);
        }
        file.close();
        cout << "Records loaded from file successfully.\n";
    }
};

int main() {
    StudentRecordManager manager;
    int choice;
    string filename = "students.txt";

    do {
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Save to File\n";
        cout << "4. Load from File\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addStudent();
                break;
            case 2:
                manager.displayStudents();
                break;
            case 3:
                manager.saveToFile(filename);
                break;
            case 4:
                manager.loadFromFile(filename);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

