#include "header.h"
#include "LinkedList.h"
#include "Data.h"
#include "ProfileArray.h"

class GameRunner
{
    private:
        // array of profiles
        ProfileArray profilesArray;

        // linked list that stores commands
        LinkedList<Data> commandsList;
        int numProfiles;

    public:
        // constructor
        GameRunner()
        {
            loadCommandsList();
            loadProfile();
        }

        // deconstructor, only needs to delete profilesArray since only dynamically allocated memory
        ~GameRunner()
        {
            saveCommands();
            saveProfiles();
        }

        void displayMenu();
        void displayGameRules() const;
        void playNewGame(string currName, int currPoints);
        void loadPreviousGame();
        void addCommand();
        void removeCommand();
        void loadCommandsList();
        void loadProfile();
        void saveCommands();
        void saveProfiles();
        void insertProfile(const Profile &newProfile);
        void displayQuestion(int& points);
        void displayAllCommands() const;
        void randomShuffle(vector<string>& descriptions);
        void deallocateLinkedList();
        
};

void GameRunner::displayMenu()
{
    int choice = 0;
    int run = 1;
    do {
        cout << "---Main Menu---" << endl;
        cout << "1. Game Rules" << endl;
        cout << "2. Play New Game" << endl;
        cout << "3. Load Previous Game" << endl;
        cout << "4. Add Command" << endl;
        cout << "5. Remove Command" << endl;
        cout << "6. Display All Commands" << endl;
        cout << "7. Save and Exit" << endl;
 
        cin >> choice;

        switch(choice)
        {
            case 1:
                displayGameRules();
                choice = 0;
                break;

            case 2:
                // load data from commands.csv, load to front of list
                loadCommandsList();
                playNewGame("", 0); 
                break;

            case 3:
                loadPreviousGame();
                break;

            case 4:
                addCommand();
                break;
            
            case 5:
                removeCommand();
                break;

            case 6:
                displayAllCommands();
                break;

            case 7:
                saveCommands();
                saveProfiles();
                deallocateLinkedList();
                run = 0;
                break;
        }
    } while (run);
}

void GameRunner::displayGameRules() const
{
    cout << "For this game you will be given a random Linux command and 3 descriptions " << endl;
    cout << "you need to match the correct description to the Linux command. If you get it wrong " << endl;
    cout << "you will lose a point. Try and get the most points by getting them all correct!" << endl;
}

void GameRunner::playNewGame(string currName, int currPoints)
{
    string name;
    int numberQuestions;
    int points = 0;
    
    if (currName != "")
    {
        name = currName;
        points = currPoints;
    } else
    {
        cout << "Enter your name: " << endl;
        cin >> name;
    }

    do {
        cout << "\nHow many questions do you want to answer? You can answer 5-30 questions!" << endl;
        cin >> numberQuestions;
        if (numberQuestions < 5 || numberQuestions > 30)
        {
            cout << "You can only answer 5-30 questions, try again." << endl;
        }
    } while (numberQuestions < 5 || numberQuestions > 30);

    
    for(int i = 0; i < numberQuestions; i++)
    {
        displayQuestion(points);
    }
    cout << "You answered " << numberQuestions << " questions!" << endl;

    profilesArray.insertOrUpdateProfile(name, points);
}

void GameRunner::displayQuestion(int& totalPoints)
{
    if(commandsList.isEmpty())
    {
        cout << "Commands list is empty" << endl;
    }

    // get a random command from linked list
    Data randomCommand = commandsList.getRandomCommand(commandsList);

    // generate three random descriptions (one is the the correct one)
    vector<string> descriptions;
    descriptions.push_back(randomCommand.getDescription());

    while (descriptions.size() < 3) 
    {
        Data randomDescription = commandsList.getRandomCommand(commandsList);
        if (find(descriptions.begin(), descriptions.end(), randomDescription.getDescription()) == descriptions.end()) 
        {
            descriptions.push_back(randomDescription.getDescription());
        }
    }
    randomShuffle(descriptions);
    
    cout << "\nMatch the command '" << randomCommand.getCommand() << "' with the correct description: " << endl;
    for (int j = 0; j < 3; j++) 
    {
        cout << j + 1 << ". " << descriptions[j] << endl;
    }

    int userChoice;
    cout << "Enter your choice (1-3): ";
    cin >> userChoice;

    // check if the choice is correct
    if (userChoice >= 1 && userChoice <= 3) 
    {
        if (descriptions[userChoice - 1] == randomCommand.getDescription()) 
        {
            cout << "Correct! You earned " << randomCommand.getPoints() << " points." << endl;;
            totalPoints += randomCommand.getPoints();
        } else {
            cout << "Incorrect! You lose 1 point." << endl;;
            totalPoints--;
        }
    } else 
    {
        cout << "Invalid choice, you got this question wrong" << endl;
        totalPoints--;
    }
    cout << "Here's your total points: " << totalPoints << endl;;
}

void GameRunner::randomShuffle(vector<string>& descriptions) 
{
    srand(static_cast<unsigned int>(time(nullptr)));

    int size = static_cast<int>(descriptions.size());

    // here I used the Fisher-Yates shuffle
    for (int i = size - 1; i > 0; --i) 
    {
        // get random index between 0 and i
        int randomIndex = rand() % (i + 1);

        // swap the elements at randomIndex and i
        swap(descriptions[i], descriptions[randomIndex]);
    }
}

void GameRunner::loadCommandsList()
{
    ifstream file("commands.csv");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            istringstream iss(line);
            string command;
            string description;
            int points;

            getline(iss, command, ',');
            getline(iss, description, ',');
            iss >> points;

            Data newData(command, description, points);
            commandsList.insertAtFront(newData);
        }
        file.close();
    }
}

void GameRunner::saveCommands()
{
    ofstream outputFile("commands.csv");
        if (!outputFile.is_open()) 
        {
            cout << "Error: Unable to open commands.csv" << endl;
            exit(EXIT_FAILURE);
        }

        Node<Data>* current = commandsList.getHead();

        while (current != nullptr) 
        {
            outputFile << current->getData().getCommand() << "," << current->getData().getDescription() << "," << current->getData().getPoints() << endl;
            current = current->getNext();
        }
        outputFile.close();
}

void GameRunner::saveProfiles()
{
    ofstream outputFile("profiles.csv");
    if (!outputFile.is_open()) 
    {
        cout << "Error: Unable to open profiles.csv" << endl;
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < profilesArray.getNumProfiles(); i++) 
    {
        outputFile << profilesArray.getProfile(i).getName() << "," << profilesArray.getProfile(i).getPoints() << endl;
    }

    outputFile.close();
}

void GameRunner::addCommand()
{
    string newCommand;
    string newDescription;
    int newPoints;

    cout << "Enter the new command: ";
    cin >> newCommand;

    // check for duplicate command
    if (commandsList.searchCommand(newCommand)) 
    {
        cout << "Error: Command already exists." << endl;
        return;
    }

    cout << "Enter the description for '" << newCommand << "': ";
    // clears newline from buffer
    cin.ignore(); 
    getline(cin, newDescription);

    cout << "Enter the points for '" << newCommand << "': ";
    cin >> newPoints;

    commandsList.insertAtFront(Data(newCommand, newDescription, newPoints));
    cout << "Command added successfully." << endl;
}

void GameRunner::removeCommand()
{
    string commandToRemove;
    cout << "Enter the command to remove: " << endl;
    cin >> commandToRemove;

    if (commandsList.searchCommand(commandToRemove)) 
    {
        commandsList.remove(commandToRemove);
        cout << "Command '" << commandToRemove << "' removed successfully!" << endl;
    } else 
    {
        cout << "Error: Command not found." << endl;
    }
}


void GameRunner::loadPreviousGame()
{
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    int profileIndex = profilesArray.searchProfile(playerName);

    if (profileIndex != -1) 
    {
        // profile found
        cout << "Welcome back, " << playerName << "!" << endl;
        cout << "Your current points: " << profilesArray.getProfile(profileIndex).getPoints() << endl;
        playNewGame(playerName, profilesArray.getProfile(profileIndex).getPoints());
    } else {
        cout << "Profile not found. Please check your name." << endl;;
    }
}

void GameRunner::loadProfile()
{
    ifstream inputFile("profiles.csv");
    if (!inputFile.is_open()) 
    {
        cout << "Error: Unable to open profiles.csv" << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    while (getline(inputFile, line)) 
    {
        istringstream ss(line);
        string playerName;
        int playerPoints;

        getline(ss, playerName, ',');
        ss >> playerPoints;

        profilesArray.insertOrUpdateProfile(playerName, playerPoints);
    }
    inputFile.close();
}

void GameRunner::displayAllCommands() const 
{
    commandsList.displayAllCommands();
}


void GameRunner::deallocateLinkedList() 
{
    commandsList.~LinkedList();
}

