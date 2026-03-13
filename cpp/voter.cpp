#include<iostream>
#include<string>

int main(){
    std:: string name,county,constituency;
    int age,idNo;
std::cout <<"Enter your name: ";
std::cin >>name;

std::cout <<"Enter you age: ";
std::cin >>age;
if(age<18){
std::cout<<"You are underage\n";
return false;
}else{
    std::cout<<"You can vote\n";
}

std::cout  <<"Enter your County: ";
std::cin  >>county;

std::cout  <<"Enter your Constituency: ";
std::cin>>  constituency;

std::cout<<"Enter your Id Number: ";
std::cin>> idNo;

for(int i=0;i<5;i++){
    std::cout<<"Joshua Juma\n";
}

std::cout<< "Hello, "<<name<<" You are "<<age<<" Years old\n";
return 0;
}