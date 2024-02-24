#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

class Student {
 string student_id;
 string full_name;
 string course;
 string message;
 int year;

 public:
  // setter
  void setStudentId(string s){
    student_id = s;
  }

  void setFullName(string s){
    full_name = s;
  }

  void setCourse(string s){
    course = s;
  }

  void setYear(int n){
    year = n;
  }

  void setNotificationMessage(string s){
    message = s;
  }

  string getNotificationMessage(){
    return message;
  }

  void resetNotificationMessage(){
    message = "";
  }
  
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

  void create(){
    ofstream Students("students.csv", ios::app);
    if(Students.is_open()){
      Students << student_id << "," << full_name << "," << course << "," << year << endl;
      
      Students.close();

      setNotificationMessage("\nNew student record has been successfully added.\n");
    }
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

  if (student.getNotificationMessage() != ""){
    cout << student.getNotificationMessage();
    student.resetNotificationMessage();
  }

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
 string student_id;
 string full_name;
 string course;
 int year;
 
 system("clear");

 cout << student.displayLine();
 cout << "\nAdd New Student\n";
 cout << student.displayLine();

 cout << "\nEnter student id: ";
 cin >> student_id;

 cout << "Enter student full name: ";
 cin.ignore(numeric_limits<streamsize>::max(), '\n');
 getline(cin, full_name);

 cout << "Enter student course: ";
 getline(cin, course);

 cout << "Enter student course year: ";
 cin >> year;

 student.setStudentId(student_id);
 student.setFullName(full_name);
 student.setCourse(course);
 student.setYear(year);

 student.create();
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