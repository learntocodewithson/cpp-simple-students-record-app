#include<iostream>
using namespace std;

#include "SimpleStudentsRecord.h"

void addNewStudent(Student &student);
void editStudent(Student &student);
void viewStudent(Student &student);
void deleteStudent(Student &student);
void header(Student &student, string title);
void exitProgram();

int main(){
 Student student;
 int choice;
 bool exit_program = false;

 do {
  system("clear");

  if (student.getNotificationMessage() != ""){
    cout << student.getNotificationMessage();
    student.resetNotificationMessage();
  }

  cout << student.displayTitle();
  cout << student.displayMenu();

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
 string student_id, full_name, course;
 int year;
 

 header(student, "\nAdd New Student\n");

 cout << "\nEnter student id: ";
 cin >> student_id;

 cout << "Enter student full name: ";
 cin.ignore(numeric_limits<streamsize>::max(), '\n');
 getline(cin, full_name);

 cout << "Enter student course: ";
 getline(cin, course);

 cout << "Enter student course year: ";
 cin >> year;

 // set all input values to student variables
 student.setStudentId(student_id);
 student.setFullName(full_name);
 student.setCourse(course);
 student.setYear(year);

 // perform saving data to csv file
 student.create();
}

void editStudent(Student &student){
  string full_name, course, year, update_question;

  viewStudent(student);

  if(student.exists()){
    // printing the latest message
    cout << student.getNotificationMessage();

    cout << "\nEdit student full name <" << student.getFullName() << ">: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, full_name);

    cout << "Edit student course <" << student.getCourse() << ">: ";
    getline(cin, course);

    cout << "Edit student course year <" << student.getYear() << ">: ";
    getline(cin, year);

    // rule: if any of the variables are empty, skip updating the student object
    student.setFullName(full_name);
    student.setCourse(course);
    if(year != "")
      student.setYear(stoi(year));

    cout << "\nAre you sure you want to update this student? <yes or no>: ";
    cin >> update_question;

    if(update_question == "yes"){
      student.update();
      student.setNotificationMessage("\nStudent " + student.getStudentId() + " is successfully updated.\n");
      student.resetFields();
    }else{
      student.setNotificationMessage("\nStudent is not updated\n");
    }
  }
}

void viewStudent(Student &student){
 string student_id;
 header(student, "\nView Student\n");

 cout << student.displayAllStudentsId();

 cout << "\nEnter student id: ";
 cin >> student_id;

 student.searchByStudentId(student_id);

 if(student.exists()){
  student.setNotificationMessage("\n\tStudent Found -> \n\tStudent Id: " + student.getStudentId() + "\n\tStudent Name: " + student.getFullName() + "\n\tStudent Course: " + student.getCourse() + "\n\tStudent Course Year: " + to_string(student.getYear()) + "\n");
 } else {
  student.setNotificationMessage("\nStudent not found with student id " + student_id + "\n");
 }
}

void deleteStudent(Student &student){
  string delete_question;
  viewStudent(student);

  if(student.exists()){
    cout << student.getNotificationMessage();

    cout << "\nAre you sure you want to delete this student? <yes or no>: ";
    cin >> delete_question;

    if(delete_question == "yes"){
      student.deleteNow();
      student.setNotificationMessage("\nStudent " + student.getStudentId() + " is now deleted.\n");
      student.resetFields();
    }else{
      student.setNotificationMessage("\nStudent is not deleted\n");
    }
  }
}

void exitProgram(){
 cout << "Thank you for using this app.";
}

void header(Student &student, string title){
 system("clear");

 cout << student.displayLine();
 cout << title;
 cout << student.displayLine();
}
