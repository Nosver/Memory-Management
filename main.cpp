#include <iostream>
#include <vector>
#include <queue>
#include <random> 

using namespace std;

#define processNumber 3

int getRandom(int minBound, int maxBound) {
    if (maxBound < minBound) {swap(minBound, maxBound);}
    int range = maxBound - minBound + 1;    
    return minBound + (rand() % range);;
}


struct process{
    
    string name;                // process name (P1, P2, etc.)
    unsigned int duration;   // time for process (2, 3, etc.)
    unsigned int resources[processNumber];   // resources being used (e: 2, 3, 4)
    bool isInProcess;
    process* next;

    process(string name, unsigned int duration, unsigned int R1, unsigned int R2, unsigned int R3){
        this->name = name;
        this->duration = duration;
        this->resources[0] = R1;
        this->resources[1] = R2;
        this->resources[2] = R3;
        this->isInProcess = false;
    }

    process(string name){this->name = name;}

    process(){}

    void print(){
        cout << name << ", Time: " << duration << ", R: [" << resources[0] << ", " << resources[1] << ", " << resources[2] << endl;
    }

    void generateRandomProcess(unsigned int &count){
        count++;
        this->name = "P" + to_string(count);
        this->duration = getRandom(1, 7);
        for(int i=0; i < processNumber; i++){this->resources[i] = getRandom(1, 7);}
        this->isInProcess = false;
    }

};

struct comparator{
    bool operator()( process* A,  process* B) const {
        return A->duration < B->duration;   // ??
    }
};

class runtime{

    private:

        vector<process*> Q;
        unsigned int count;
        process* index;

        void sortQ(){
            sort(Q.begin(), Q.end(), comparator());
            for(int i=0; i < 3; i++){
                if(i == 2){
                    Q.at(i)->next = Q.at(0);
                }
                else{
                    Q.at(i)->next = Q.at(i+1);
                }
            }
        }

    public:

        void getInput(){
            for(int i=0; i < 3; i++){
                cout << "Enter the process informations:" <<  endl;
                process *PX = new process();
                cout << "Name: ";
                cin >> PX->name;
                cout << "Duration: ";
                cin >> PX->duration;
                for(int i=0; i < processNumber; i++){
                    cout << "Resource [" << i+1 << "]: ";
                    cin >> PX->resources[i];
                }
                Q.push_back(PX);
            }
        }

        runtime(){
            getInput();
            this->count = 3;
        }

        ~runtime(){
            for(int i=0; i < Q.size(); i++){Q.pop_back();}
        }

        bool isAvailable(process* P){
            return P->resources[0] <= mainResources[0] && P->resources[1] <= mainResources[1] && P->resources[2] <= mainResources[2];
        }

        void run(){
    
        }

        void printAll(){
            cout << "o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o" << endl;
            for(int i=0; i < Q.size(); i++){
                Q[i]->print();
            }
            cout << "o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o-o" << endl;
        }

};

unsigned int mainResources[3] = {10, 10, 10};
process P1("P1", 4, 2, 3, 5);
process P2("P2", 2, 3, 4, 2);
process P3("P3", 5, 5, 3, 3);

int main(){

    srand(static_cast<unsigned>(time(nullptr)));

    runtime A;

    return 0;
}