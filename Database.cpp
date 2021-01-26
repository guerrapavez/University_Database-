// Include all the necessary libraries.
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string.h>
 
using namespace std;
 
//initializing the class student that will store the data.
class student 
{
    int stunum;
    char name[50];
    int eng_marks, math_marks, sci_marks, lang2_marks, cs_marks;
    double gpa;
    char grade;

    public:
    void getdata();
    void showdata() const;
    void calculate();
    int getstunum() const;
};
//class fxn to calculate the student letter grade. 
void student::calculate()
{
    gpa = ((eng_marks+math_marks+sci_marks+lang2_marks+cs_marks)/5.0);
    if (gpa>90){
        grade = 'A';
    }
    else if(gpa > 75){
        grade = 'B';
    }
    else if(gpa > 60){
        grade = 'C';
    }
    else if(gpa>50){
    grade ='D';
    }
    else{
        grade = 'F';
    }
}

// calss fxn to obtain information of a student.
void student::getdata(){
    std::cout << "\nEnter student number: " << endl;
    std::cin >> stunum;
    std::cout << "Enter student name: " << endl;
    std::cin.ignore();
    std::cin.getline(name, 50);
    std::cout<< "\nAll marks should be out of 100" << endl;
    std::cout<< "Enter English mark: "<< endl;
    std::cin >> eng_marks;
    std::cout << "Enter Math mark: " << endl;
    std::cin >> math_marks;
    std::cout << "Enter Science mark: " << endl;
    std::cin >> sci_marks;
    std::cout << "Enter Computer Science mark: " << endl;
    std::cin >> cs_marks;
    std::cout << "Enter Second Language mark: " << endl;
    std::cin >> lang2_marks;
    calculate();
}

//class fxn that displays the student and its info. 
void student::showdata() const{
    std::cout << "\nStudent Number: " << stunum << endl;
    std::cout << "Student Name: " << name << endl;
    std::cout << "English Mark: " << eng_marks << endl;
    std::cout << "Math Mark: " << math_marks << endl;
    std::cout << "Science Mark: " << sci_marks << endl;
    std::cout << "Computer Science Mark: " << cs_marks << endl;
    std::cout << "Second Language Mark: " << lang2_marks<< endl;
    std::cout << "Average Mark: " << gpa << endl;
    std::cout << "Student Grade: " << grade << endl;
}

//class function that returns the student id number. 
int student::getstunum() const{
    return stunum;
}

//fxns that ...
void create_student();
void display_item(int); //display a specific item
void display_all();      
void delete_item(int);  // delete a specific item
void change_student(int); // edit a specific item


// main fxn that deals with the users input. 
int main(){
    char choice; 
    do{
        char choice;
        int num;
        system("cls");
        std::cout<<"\n\n\n\tMENU";
        std::cout<<"\n\n\t1.Create student record";
        std::cout<<"\n\n\t2.Search student record";
        std::cout<<"\n\n\t3.Display all students records ";
        std::cout<<"\n\n\t4.Delete student record";
        std::cout<<"\n\n\t5.Modify student record";
        std::cout<<"\n\n\t6.Exit";
        std::cout<<"\n\nWhat is your Choice (1/2/3/4/5/6) ";
        std::cin >> choice;
        system("cls");
        switch(choice){
            case '1': create_student();break;
            case '2': std::cout<<"\n\nEnter the Student Number: ";
            std::cin>>num;
            display_item(num);break;
            case '3': display_all();break;
            case '4': std::cout<<"\n\n\tEnter Student Number: ";
            std::cin>>num;
            delete_item(num);
            case '5': std::cout << "\n\n\tEnter Student Number: ";
            std::cin >> num;
            change_student(num);break;
            case '6': std::cout << "Have a good day :)!"; exit(0);
        }
    }
    while(choice != '6');
        return 0;
}
    

    // writing the students to a file. 
void create_student(){
    student stud;
    ofstream oFile;
    oFile.open("student.dat", ios::binary|ios::app);
    stud.getdata();
    oFile.write(reinterpret_cast<char*> (&stud), sizeof(student));
    oFile.close();
    std::cout <<"\n\nStudent record has been created ";
    std::cin.ignore();
    std::cin.get();
}
void display_all(){
    student stud;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if(!inFile){
        std::cout<<"File can't be opened || Press any key to exit";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    std::cout<<"\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
    while(inFile.read(reinterpret_cast<char *> (&stud), sizeof(student))){
        stud.showdata();
        std::cout<<"\n\n====================================\n";
    }
    inFile.close();
    std::cin.ignore();
    std::cin.get();
}

void display_item(int n){
    student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    if (!iFile){
        std::cout<< "File could not be opened | press any key to exit.";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    bool flag = false;
    while(iFile.read(reinterpret_cast<char*> (&stud), sizeof(student))){
        if(stud.getstunum() == n){
            stud.showdata();
            flag = true;
        }
    }
    iFile.close();
    if(flag == false){
        std::cout<<"\n\nrecord does not exist";
        std::cin.ignore();
        std::cin.get();
    }

}

void change_student(int n){
    bool found = false;
    student stud;
    fstream fl;
    fl.open("student.dat",ios::binary|ios::in|ios::out);
    if(!fl){
        std::cout << "File could not be opened. || press any key to exit. ";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    while(!fl.eof() && found == false){
        fl.read(reinterpret_cast<char*> (&stud), sizeof(student));
        if(stud.getstunum() == n){
            stud.showdata();
            std::cout<< "\nEner the new student details: " << endl;
            stud.getdata();
            int pos=(-1)*static_cast<int>(sizeof(stud));
            fl.seekp(pos,ios::cur);
            fl.write(reinterpret_cast<char*> (&stud), sizeof(student));
            std::cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    fl.close();
    if(found == false){
        std::cout<<"\n\n Record Not Found ";
        std::cin.ignore();
        std::cin.get();
    }
}

void delete_item(int n){
    student stud;
    ifstream iFile;
    iFile.open("student.dat",ios::binary);
    if(!iFile){
        std::cout<<"File could not be opened... Press any Key to exit...";
        std::cin.ignore();
        std::cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat", ios::out);
    iFile.seekg(0, ios::beg);
    while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student))){
        if(stud.getstunum()!=n){
            oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
        }
    }
    oFile.close();
    iFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    std::cout << "\n\n\tRecord Deleted .. ";
    std::cin.ignore();
    std::cin.get();
}