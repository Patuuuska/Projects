
#include <iostream>
#include <string>
#include <list>
#include<windows.h>


using namespace std;
#define PINK    "\033[35m"
#define BRIGHT_PINK "\033[1;35m" 
#define RESET   "\033[0m"
class Item {
private:
    static int nextId; 
    int id;
    string name;
    string description;
    bool check;

public:
    Item() : id(0), name(""), description(""), check(false) {}
    ~Item() = default;

    bool createCheck(string new_name, string new_description) {
        id = nextId++;
        name = new_name;
        description = new_description;
        return false;
    }

    int getId()
    {
        return id;
    }
    string getName()
    {
        return name;
    }
    string getDescription()
    {
        return description;
    }
    bool isCheck()
    {
        return check;
    }

    void setCheck(bool value) {
        check = value;
    }
};

int Item::nextId = 1;
int main()
{

    int choice, in_id;
    string in_name, in_description;
    list<Item> List;
    list<Item>::iterator i;

    List.clear();

   

    while (true) {
        system("cls");
        cout <<PINK<< "*****************************" << endl;
        cout << "*** "<< RESET << "Aplication ToDo List " << PINK << " ***\n";
        cout << "*****************************" << RESET << endl;

        cout << endl;
        if (!List.empty()) {
            cout << endl << BRIGHT_PINK << "List of your tasks:" << RESET << endl << endl;
        }


        for (i = List.begin(); i != List.end(); i++) {


            string checked = i->isCheck() ? "done" : "not done";
            
            
            cout << BRIGHT_PINK << "\n************************************************************************************************"<< endl;
            cout << "* "<<RESET<<"ID: " << i->getId() << endl;
            cout << BRIGHT_PINK << "* " << RESET << "Name: " << i->getName() << endl;
            cout << BRIGHT_PINK << "* " << RESET << "Description: " << i->getDescription() << endl;
            cout << BRIGHT_PINK << "* " << RESET << "Completed:  " << checked << endl;
            cout << BRIGHT_PINK << "************************************************************************************************" << RESET;

        }

        if (List.empty()) {
            cout << "Add your first task!\n" << endl;
        }
        cout << endl << endl;
        cout << " | "<<PINK<<"1" << RESET << " | - add a new task to your todo list" << endl;
        cout << " | " << PINK << "2" << RESET << " | - complete a task" << endl;
        cout << " | " << PINK << "0" << RESET << " | - exit" << endl;

        cout << "\n\nYour choice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Goodbye!\n";
            break;
        }
        else if (choice == 1) {
            cout << "Add a name of task: ";
            cin.ignore();
            getline(cin, in_name);
            cout << "Add a description: ";
            getline(cin, in_description);
            Item newItem;
            newItem.createCheck(in_name, in_description);
            List.push_back(newItem);

        }
        else if(choice == 2) {
            cout << "Enter the ID of the task you want to complete: ";
            cin >> in_id;
            for (i = List.begin(); i != List.end(); i++) {
                if (in_id == i->getId()) {
                    i->setCheck(true);
                    break;
                }

            }
        }
        
    }
    return 0;
}


