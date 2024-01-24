/*
    Tabletop RPG Downtime Skill System

    This program assists players in managing their characters' skills during downtime in any tabletop role-playing games.
    It includes functionality to:
    - Add, remove, and rename skills.
    - Improve skills through simulated practice (random dice rolls).
    - Store and retrieve character data (names and skills) from .txt files.

    The program utilizes a 20-sided dice modified random roll for skill improvement and maintains an updated record of character progress in text files.

*/




#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

int getMenuSelection(int skillOptions, int totalOptions);

int main()
{
    srand(time(0)); // initialize random number generation based on system time.

    // vectors to store character names, skills, and skill values.
    std::vector<std::string> characterName;
    std::vector<std::string> characterSkillNames;
    std::vector<int> characterSkillValues;


    // reading character names from file.
    std::ifstream characterWords("characterName.txt");
    while (characterWords.peek() != EOF)
    {
        std::string currentWord;

        characterWords >> currentWord;
        characterName.push_back(currentWord);
    }
    characterWords.close();

    //reading character skill names and values from file.
    std::ifstream characterData("characterData.txt");
    int numberofData = 0;
    while (characterData.peek() != EOF)
    {
        std::string currentSkillName;
        int currentSkillValue;
        characterData >> currentSkillName;
        characterSkillNames.push_back(currentSkillName);
        characterData >> currentSkillValue;
        characterSkillValues.push_back(currentSkillValue);
        numberofData++;
    }
    characterData.close();

    // Main loop of the program
    bool programExit = false;
    do
    {
        //Displaying the main menu
        std::cout << "||DnD Downtime Skill System||"
                  << "\n\n";

        for (int i = 0; i < characterName.size(); i++)
        {
            std::cout << characterName.at(i) << " ";
        }
        std::cout << "\n\n";
        for (int i = 0; i < characterSkillNames.size(); i++)
        {
            std::cout << (i + 1) << ". " << characterSkillNames.at(i) << ": ";
            std::cout << characterSkillValues.at(i) << std::endl;
        }
        std::cout << "\n";


        //Additional menu options
        int skillMenuOptions = characterSkillNames.size();
        std::cout << skillMenuOptions + 1 << ". Name Character\n";
        std::cout << skillMenuOptions + 2 << ". Add A Skill\n";
        std::cout << skillMenuOptions + 3 << ". Remove A Skill\n";
        std::cout << skillMenuOptions + 4 << ". Quit Program\n";

        int totalMenuOptions = skillMenuOptions + 4;
        int userChoice = getMenuSelection(skillMenuOptions, totalMenuOptions);
        int skillSelection = userChoice - 1;


        // Handling user's menu choices

        // Renaming Character
        if (userChoice == skillMenuOptions + 1)
        {
            std::string userNameInput;
            std::cout << "You have chosen to Name/Rename your Character.\n\n";

            std::cout << "Enter your character's name: ";
            std::getline(std::cin, userNameInput);

            while (userNameInput.length() > 20)
            {
                std::cin.clear();

                std::cout << "Enter less than 20 characters.\n";
                std::cout << "Enter your character's name: ";
                std::getline(std::cin, userNameInput);
            }


            std::ofstream characterNameWrite("characterName.txt");
            if (!characterNameWrite.is_open()) 
            {
                std::cerr << "Error: File could not be opened. Exiting..." << std::endl;
                exit(0);
            }
            
                characterNameWrite << userNameInput;
            

            characterNameWrite.close();

            std::ifstream characterWords2("characterName.txt");
            if (!characterWords2.is_open()) 
            {
                std::cerr << "Error: File could not be opened. Exiting..." << std::endl;
                exit(0);
            }
            std::string currentWord;
            int word2 = 0;


            // Takes user's character name even if it is multiple words 
            while (characterWords2.peek() != EOF)
            {
                characterWords2 >> currentWord;
                if (characterName.size() > word2)
                {
                    characterName.at(word2) = currentWord;
                }
                else
                {
                    characterName.push_back(currentWord);
                }
                word2++;
            }
            characterName.resize(word2);

            std::cout << "Character name changed!\n";
        }


        // Adding a Skill
        else if (userChoice == skillMenuOptions + 2)
        {
            std::string newSkill;
            int existingSkillPoints;
            std::cout << "You have chosen to add a skill.\n\n";

            std::cout << "What is the name of the skill you would like to add? (Skills names are only a single word): ";
            std::cin >> newSkill;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');




            std::cout << "What is the current number of skill points in " << newSkill << "?: ";
            std::cin >> existingSkillPoints;
            while (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\nEnter an integer number.\n";
                std::cout << "What is the current number of skill points in " << newSkill << "?: ";
                std::cin >> existingSkillPoints;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            characterSkillNames.push_back(newSkill);
            characterSkillValues.push_back(existingSkillPoints);

            std::ofstream characterDataWrite("characterData.txt");
            if (!characterDataWrite.is_open()) 
            {
                std::cerr << "Error: File could not be opened. Exiting..." << std::endl;
                exit(0);
            }

            for (int i = 0; i < characterSkillNames.size(); i++)
            {
                characterDataWrite << " " << characterSkillNames.at(i) << " ";
                characterDataWrite << characterSkillValues.at(i);
            }
            std::cout << "\nSkill added.\n";
            characterDataWrite.close();
        }


        // Remove A Skill
        else if (userChoice == skillMenuOptions +3)
        {
            int userRemovalInput;
            int removalSelection;

            if (characterSkillNames.empty())
            {
                std::cout << "\nThere are no skills to remove.\n\n";
            }
            else
            {
                std::cout << "\nYou have chosen to remove a skill.\n";
                std::cout << "Enter the number of the skill you want to remove: ";

                std::cin >> userRemovalInput;
                removalSelection = userRemovalInput - 1;
                while ((removalSelection > (skillMenuOptions -1)) || (removalSelection < 0))
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Enter a valid input of an existing skill.\n";
                    std::cout << "Enter the number of the skill you want to remove: ";
                    std::cin >> userRemovalInput;
                    removalSelection = userRemovalInput - 1;
                }

                std::cout << "Are you sure you want to remove " << characterSkillNames.at(removalSelection) << "? Y for Yes or N for No: ";
                std::string removeChoiceCheck;
                std::cin >> removeChoiceCheck;

                if (removeChoiceCheck == "Y")
                {

                characterSkillNames.erase(characterSkillNames.begin() + removalSelection);
                characterSkillValues.erase(characterSkillValues.begin() + removalSelection);        

                std::ofstream characterDataWrite("characterData.txt");
                if (!characterDataWrite.is_open()) 
                {
                    std::cerr << "Error: File could not be opened. Exiting..." << std::endl;
                    exit(0);
                }

                    for (int i = 0; i < characterSkillNames.size(); i++)
                    {
                        characterDataWrite << " " << characterSkillNames.at(i) << " ";
                        characterDataWrite << characterSkillValues.at(i);
                    }
                    skillMenuOptions--;
                    std::cout << "Skill removed.\n\n";

                    }
            }


        }


        // Exit Program
        else if (userChoice == skillMenuOptions + 4)
        {
            std::cout << "\n\nExiting...\n";
            programExit = true;
        }


        // Improving Character Skill
        else
        {
            int daysPracticed;
            int rollModifier;
            int rollMultiplier;

            std::cout << "\nYou have chosen to improve your " << characterSkillNames.at(skillSelection) << " skill!\n";

            std::cout << "\nHow many days do you work on " << characterSkillNames.at(skillSelection) << "?: ";

            std::cin >> daysPracticed;
            while (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\nEnter an integer number.\n";
                std::cout << "\nHow many days do you work on " << characterSkillNames.at(skillSelection) << "?: ";
                std::cin >> daysPracticed;
            }
            std::cout << "\nWhat is your modifier on each roll?: +";

            std::cin >> rollModifier;
            while (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\nEnter an integer number.\n";
                std::cout << "\nWhat is your modifier on each roll?: +";
                std::cin >> rollModifier;
            }

            std::cout << "\n";


            int rollResult;
            int totalIncrease = 0;
            for (int i = 1; i < daysPracticed; i++)
            {
                rollResult = ((1 + rand() % 20 + rollModifier));

                std::cout << "Day " << i << ": " << rollResult << " points gained\n";
                totalIncrease = totalIncrease + rollResult;
            }
            characterSkillValues.at(skillSelection) = characterSkillValues.at(skillSelection) + totalIncrease;

            std::ofstream characterDataWrite("characterData.txt");
            if (!characterDataWrite.is_open()) 
            {
                std::cerr << "Error: File could not be opened. Exiting..." << std::endl;
                exit(0);
            }

            for (int i = 0; i < characterSkillNames.size(); i++)
            {
                characterDataWrite << " " << characterSkillNames.at(i) << " ";
                characterDataWrite << characterSkillValues.at(i);
            }

            std::cout << "\nYour character gained " << totalIncrease << " skill points in " << characterSkillNames.at(skillSelection) << "! Good stuff!\n";
            std::cout << "Your total points in " << characterSkillNames.at(skillSelection) << " is " << characterSkillValues.at(skillSelection) << "!\n\n";

            characterDataWrite.close();

            for (int i = 0; i < characterSkillNames.size(); i++)
            {
                characterDataWrite << " " << characterSkillNames.at(i) << " ";
                characterDataWrite << characterSkillValues.at(i);
            }
        }
    } while (programExit == false);

    return 0;
}

//Gets user menu selection and validates the input
int getMenuSelection(int skillOptions, int totalOptions)
{
    int userInput = 0;
    int menuChoice = 0;

    std::cout << "\nSelect a skill to improve or a menu option by entering a number: ";
    std::cin >> userInput;
    while ((std::cin.fail()) || (userInput <= 0) || (userInput > totalOptions))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEnter a valid input.\n";
        std::cout << "Select a menu options by entering a number: ";
        std::cin >> userInput;
    }

    menuChoice = userInput;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return menuChoice;
}