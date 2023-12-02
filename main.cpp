#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <string>
#include <algorithm>

using namespace std;

#define processNumber 3

unsigned int mainResources[3] = {10, 10, 10};

int getRandom(int minBound, int maxBound)
{
    if (maxBound < minBound)
    {
        swap(minBound, maxBound);
    }
    int range = maxBound - minBound + 1;
    return minBound + (rand() % range);
    ;
}

struct process
{

    string name;                           // process name (P1, P2, etc.)
    unsigned int duration;                 // time for process (2, 3, etc.)
    unsigned int resources[processNumber]; // resources being used (e: 2, 3, 4)
    bool isInProcess;
    process *next;

    process(string name, unsigned int duration, unsigned int R1, unsigned int R2, unsigned int R3)
    {
        this->name = name;
        this->duration = duration;
        this->resources[0] = R1;
        this->resources[1] = R2;
        this->resources[2] = R3;
        this->isInProcess = false;
    }

    process(string name) { this->name = name; }

    process() {}

    void print()
    {
        cout << name << ", Duration: " << duration << ", " << isInProcess << ", R: [" << resources[0] << ", " << resources[1] << ", " << resources[2] << "]"
             << "     " << endl;
    }

    void generateRandomProcess(unsigned int &count)
    {
        count++;
        this->name = "P" + to_string(count);
        this->duration = getRandom(1, 7);
        for (int i = 0; i < processNumber; i++)
        {
            this->resources[i] = getRandom(1, 7);
        }
        this->isInProcess = false;
    }
};

struct comparator
{
    bool operator()(process *A, process *B) const
    {
        return A->duration < B->duration; // ??
    }
};

process P1("P1", 4, 2, 3, 5);
process P2("P2", 2, 3, 4, 2);
process P3("P3", 6, 5, 3, 3);

class runtime
{

private:
    vector<process *> Q;
    unsigned int count;
    process *index;

    void sortQ()
    {
        sort(Q.begin(), Q.end(), comparator());
        for (int i = 0; i < 3; i++)
        {
            if (i == 2)
            {
                Q.at(i)->next = Q.at(0);
            }
            else
            {
                Q.at(i)->next = Q.at(i + 1);
            }
        }
    }

    void getInput()
    {
        for (int i = 0; i < 3; i++)
        {
            cout << "Enter the process informations:" << endl;
            process *PX = new process();
            cout << "Name: ";
            cin >> PX->name;
            cout << "Duration: ";
            cin >> PX->duration;
            for (int i = 0; i < processNumber; i++)
            {
                cout << "Resource [" << i + 1 << "]: ";
                cin >> PX->resources[i];
            }
            Q.push_back(PX);
        }
    }

    bool isAvailable(process *P)
    {
        return P->resources[0] <= mainResources[0] && P->resources[1] <= mainResources[1] && P->resources[2] <= mainResources[2];
    }

    void freeNpushRandom(process *&P)
    {
        for (int i = 0; i < 3; i++)
        {
            mainResources[i] += P->resources[i];
        }
        printAll();
        P->generateRandomProcess(count);
        this->index = P->next;

        sortQ();
    }

    void runOnce(bool isInitial = false)
    {

        if (isInitial == true)
        {
            sortQ();
            this->index = Q[0];
        }
        if (isAvailable(index) && !index->isInProcess)
        {
            // Decrease resource
            for (int i = 0; i < 3; i++)
            {
                mainResources[i] -= index->resources[i];
            }
            index->isInProcess = true;
        }
        if (index->isInProcess)
        {
            index->duration--;
            cout << endl
                 << "Recently Executed Process: " << index->name << endl;
        }

        if (index->duration == 0)
        {
            cout << "Recently Finished Process: " << index->name << endl;
            freeNpushRandom(index);
        }

        index = index->next;
        printAll();
    }
    bool isDeadlock()
    {
        for (int i = 0; i < Q.size(); i++)
        {
            if (isAvailable(Q[i]))
                return false;
            else if (!isAvailable(Q[i]) && Q[i]->isInProcess)
                return false;
        }
        return true;
    }

public:
    runtime()
    {
        // getInput();
        this->count = 3;
        // Push default processes if Q is empty P1, P2, P3
        Q.push_back(&P1);
        Q.push_back(&P2);
        Q.push_back(&P3);
    }

    ~runtime()
    {
        for (int i = 0; i < Q.size(); i++)
        {
            Q.pop_back();
        }
    }

    void run(int iteration)
    {
        cout << "T1"
             << "  ";
        runOnce(true);
        cout << "---------------------------" << endl;
        bool flag = false;
        for (int i = 0; i < iteration - 1; i++)
        {
            cout << "T" << i + 2 << "  ";
            runOnce();
            if (isDeadlock())
            {
                cout << "Deadlock happened; Processes cannot be executed." << endl;
                break;
            }
            cout << "---------------------------" << endl;
        }
    }

    void printAll()
    {
        cout << "Main Resources : "
             << "[" << mainResources[0] << "]"
             << "[" << mainResources[1] << "]"
             << "[" << mainResources[2] << "]" << endl;
        for (int i = 0; i < Q.size(); i++)
        {
            Q[i]->print();
        }
        cout << endl;
    }
};

int main()
{

    srand(static_cast<unsigned>(time(nullptr)));

    runtime A;

    A.run(30);

    return 0;
}