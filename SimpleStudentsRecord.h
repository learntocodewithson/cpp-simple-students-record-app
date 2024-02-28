#ifndef SIMPLESTUDENTSRECORD_H
#define SIMPLESTUDENTSRECORD_H

 #include<sstream>
 #include<fstream>
 #include<string>

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
 

#endif