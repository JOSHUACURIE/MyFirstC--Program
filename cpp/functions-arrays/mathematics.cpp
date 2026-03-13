#include<iostream>

int add(int a,int b){
    int sum= a + b;
    return sum;
}
void printArray(int arr[],int size){
    for(int i=0;i<size;i++){
        std::cout<<arr[i]<<" "<<"\n";
    }
}
int main(){
    int result= add(12,43);
    std::cout<<"Sum: "<<result<< " \n";
    int numbers[5]={12,34,53,65,87};
    printArray(numbers,5);

    
return 0;
}