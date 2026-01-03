#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;
struct student{
    int roll;
    string name;
    string course;
    int age;   
};
int main(){
    vector<student> v;
    for(int i=0;i<5;i++){
        string name,course;
        int roll,age;
        roll = rand()%100;
        name = "Student" + to_string(i+1);
        course = "Course" + to_string((i%3)+1);
        age = 18 + rand()%5;
        student s = {roll, name, course, age};
        v.push_back(s); 
    }
    for(auto i:v){
        cout<<"Roll: "<<i.roll<<", Name: "<<i.name<<", Course: "<<i.course<<", Age: "<<i.age<<endl;
    }

}