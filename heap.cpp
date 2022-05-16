#include <iostream>
#include <fstream>
using namespace std;

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

class Heap
{
public: int *A;
public: int heapSize;   //current heapsize
public: int arraySize; //max array size

//init method
public:
    //Constructor
    Heap(int arraySize){
        heapSize = 0;
        arraySize = 20;
        A = new int[heapSize];
    }
        
    //Class methods
    void insert(int key);
    void decreaseKey(int i,int new_val);
    int extractMin();
    void sinkDown(int root);
    void floatUp(int pos);
};
 
void Heap::sinkDown(int root){

    int minChild; //setMinChild = first child 
    int midChild, lastChild;
    minChild = root*3+1;
    midChild = root*3+2;
    lastChild = root*3+3;
    //Start the loop 
    while (minChild<arraySize){

        //Find the minChild among 3 children
        if (minChild > midChild)
            minChild = midChild;
        else if (minChild > lastChild)
            minChild = lastChild;
        else    
            minChild = minChild;
       
        if (A[minChild] <= A[root]){
             swap(&A[minChild], &A[root]);
             sinkDown(minChild);
        }
    }

/*    
    //find the min child among 3 children
    if (A[firChild]<A[minChild])
        minChild = firChild;
    if (A[secChild]<A[minChild])
        minChild = secChild;
    if (A[thirChild]<A[minChild])
        minChild = thirChild;
    //minChhild << arraySize -> break;
    //check if minChild = root, if not, then switch 
    if (A[minChild] <= A[root]){
        swap(&A[root], &A[minChild]);
        sinkDown(minChild);
    }
*/
}

void Heap:: floatUp(int pos){ //pos is child 
    int parent = (pos-1)/3;

    while (parent >= 0){
        if (A[pos]<A[parent]){
            swap(&A[parent], &A[pos]);
            pos = parent;
            parent = (pos-1)/3;
        }
        else   
            break;
    }
}
void Heap::insert(int key){
        //increment heap size
        heapSize++;

        //put new key to the last position
        A[heapSize-1] = key;

        floatUp(heapSize-1);   //call floatUp function to fix the heap
        //cout<<h.A[0];

}

int Heap::extractMin(){
        int min = A[0]; //set the root as minimum
        swap(A[0],A[heapSize-1]); //swap the root to the last element

        heapSize--;//decrement size of array

        //Call sinkDown
        sinkDown(heapSize);
        return min;
}

void Heap::decreaseKey(int i, int new_val){
        A[i] = new_val;
        int parent = (i-1)/3;
        while (i != 0 && A[parent] > A[i]){
            swap(&A[i], &A[parent]);
            i = parent;
        }
}

int main (){
    string command;
    int num1, num2;
    ifstream infile;
    infile.open("inputFile.txt");
    infile >> num1;  
    //cout<<num1<<endl;
     //get the number of instructions 
    int numOfIns = num1;  //size of the heap

    Heap h(numOfIns);
    
    if(infile.is_open()){
        while (!infile.eof()){
            //nt i=0;
            infile >> command;  //start reading string on each line 
            //cout<<command<<endl;
            //char *token = strtok(command, " ");
            if(command == "IN"){    //if the line contains insert 

                infile >> num1;
                //cout<<num1<<endl;
                h.insert(num1);
            }
            if (command == "EM"){
                cout << h.extractMin()<<endl;
                //cout<<"Hello"<<endl;
                
            }

            if (command == "DK"){
                infile >> num1 >> num2;
                //cout<< num1<<","<<num2<<endl;
                h.decreaseKey(num1,num2);
            }
            //cout<<h.heapSize<<endl; 
    
        } 
    }
    else 
        cout << "Unable to open input file."<<endl;
    cout<<endl;
    infile.close();
    

    

}
