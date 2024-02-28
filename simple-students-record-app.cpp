#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;

class Student {
 string student_id, full_name, course, message;
 int year, students_count;

 public:
  // setter
  void setStudentId(string s){
    student_id = s;
  }

  void setFullName(string s){
    if(s != "")
      full_name = s;
  }

  void setCourse(string s){
    if(s != "")
      course = s;
  }

  void setYear(int n){
    if(n != 0)
      year = n;
  }

  // getter

  string getStudentId(){
    return student_id;
  }

  string getFullName(){
    return full_name;
  }

  string getCourse(){
    return course;
  }

  int getYear(){
    return year;
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

  string displayAllStudentsId(){
    string row_data, students_id;
    int counter = 0;

    ifstream Students("students.csv");
    cout << "\n\nStudent Id\n";
    while(getline(Students, row_data)){
      counter++;
      
      // row_data = "1231,Jhon Doe,BSIT,2013"
      istringstream scanner(row_data);
      string studentid;

      // 1231,
      getline(scanner, studentid, ',');

      students_id +=  to_string(counter) +  ".) " + studentid + "\n";
    }

    Students.close();

    return students_id;
  }

  bool exists(){
    return student_id != "" && full_name != "" && course != "" && year != 0;
  }

  void create(){
    ofstream Students("students.csv", ios::app);
    if(Students.is_open()){
      Students << student_id << "," << full_name << "," << course << "," << year << endl;
      
      Students.close();

      setNotificationMessage("\nNew student record has been successfully added.\n");
    }
  }

  void update(){
    setStudentsCount();

    string row_data, studentid, temp_students[students_count];
    string formatted_student_data = getStudentId() + "," + getFullName() + "," + getCourse() + "," + to_string(getYear());
    int counter = 0;

    // reading the records on the file and store it on the temporary array

    // open file
    ifstream ReadStudents("students.csv");
    while(getline(ReadStudents, row_data)){
     
     istringstream scanner(row_data);
     
     getline(scanner, studentid, ',');
      
     if(studentid == getStudentId()){
      temp_students[counter] = formatted_student_data;
     }else{
      temp_students[counter] = row_data;
     }

     counter++;
    }

    // closing the file
    ReadStudents.close();

    // open a new file students.csv and loop temporary students array and add all to the file
    
    ofstream WriteStudents("students.csv");

    if(WriteStudents.is_open()){

      // updating the new list of students
      for(int i = 0; i < students_count; i++){
        WriteStudents << temp_students[i] << endl;
      }

      WriteStudents.close();

    } else {
      setNotificationMessage("\nUnable to create and open a file");
    }

  }

  void deleteNow(){
    setStudentsCount();

    string row_data, studentid, temp_students[students_count];
    int counter = 0;
    // read students.csv
    ifstream ReadStudents("students.csv");
    while(getline(ReadStudents, row_data)){
     
      // object for parsing or splitting
      istringstream scanner(row_data);

      // split the first word with comma
      // 1231,
      getline(scanner, studentid, ',');

      if(studentid != getStudentId()){
        temp_students[counter] = row_data;
        
        // to avoid gap on the index
        counter++;
      }
    }
    ReadStudents.close();

    // open new students.csv
    ofstream WriteStudents("students.csv");
    if(WriteStudents.is_open()){
      for(int i = 0; i < students_count; i++){
        if(temp_students[i] != "")
          WriteStudents << temp_students[i] + "\n";
      }
       
      
      WriteStudents.close();
    }else{
      setNotificationMessage("\nUnable to create and open a file for students\n");
    }

  }

  void setStudentsCount(){
    students_count = 0;

    // holds the string each line on the file
    string row_data;

    // open the file
    ifstream ReadStudents("students.csv");

    // loop each row on the file and count it   
    while(getline(ReadStudents, row_data)){ students_count++; }

    // close the file
    ReadStudents.close();
  }

  void searchByStudentId(string studentid){
    string row_data, temp_year;
    bool found = false;

    ifstream Students("students.csv");

    while(getline(Students, row_data)){
      istringstream scanner(row_data);

      getline(scanner, student_id, ',');
      getline(scanner, full_name, ',');
      getline(scanner, course, ',');
      getline(scanner, temp_year);

      if(student_id == studentid){
        year = stoi(temp_year);
        found = true;
        break;
      }
    }
    Students.close();

    if(!found)
      resetFields();
  }

  void resetFields(){
    student_id = full_name = course = "";
    year = 0;
  }
};

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

 student.setStudentId(student_id);
 student.setFullName(full_name);
 student.setCourse(course);
 student.setYear(year);

 student.create();
}

void editStudent(Student &student){
  string full_name, course, year;
  string update_question;

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