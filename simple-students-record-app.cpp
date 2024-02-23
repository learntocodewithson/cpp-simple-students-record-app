#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

class Student {
 string student_id;
 string full_name;
 string course;
 int year;

 public:
  string displayTitle(){
   return "\n\t" + displayLine() + "\n\tSimple Students Record App\n";
  }
  string displayMenu(){
   return "\t\tMain Menu\n"
    "\t1.) Add New Student\n"
    "\t2.) Edit Student\n"
    "\t3.) View Student\n"
    "\t4.) Delete Student\n"
    "\t5.) Exit\n\t" + 
    displayLine();
  }
  string displayLine(){
   return "===========================";
  }
};

void addNewStudent(Student &student);
void editStudent(Student &student);
void viewStudent(Student &student);
void deleteStudent(Student &student);
void exitProgram();

int main(){
 Student student;
 int choice;
 bool exit_program = false;

 do {
  system("clear");

  cout << student.displayTitle();
  cout << student.displayMenu();
  // 
  cout << "\n\n< Enter from 1 to 5 >";
  cout << "\nWhat do you want to do?: ";
  cin >> choice;

  switch (choice) {
   case 1:
    addNewStudent(student);
    break;
   case 2:
    editStudent(student);
    break;
   case 3:
    viewStudent(student);
    break;
   case 4:
    deleteStudent(student);
    break;
   default:
    exit_program = true;
    exitProgram();
    break;
  }
 } while(!exit_program);

 return 0;
}

void addNewStudent(Student &student){
 cout << "Add new student";
}

void editStudent(Student &student){
 cout << "Edit student";
}

void viewStudent(Student &student){
 cout << "View student";
}

void deleteStudent(Student &student){
 cout << "Delete student";
}

void exitProgram(){
 cout << "Thank you for using this app.";
}