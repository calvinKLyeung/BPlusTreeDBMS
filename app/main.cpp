#include "../code/BPlusTreeDBMS.h"
#include <iostream>
#include <string>
#include <map>

using namespace std;

void demo_with_CSPB_courses()
{
	BPlusTreeDBMS* myDBMS = new BPlusTreeDBMS;

	// Creating records
	std::cout << std::endl;
	std::cout << " =============== Demo: Creating Records in B+Tree Mini Database =============== " << std::endl;
	myDBMS->Create(1300, "Computer Science 1: Starting Computing");
	myDBMS->Create(2270, "Computer Science 2: Data Structures");
	myDBMS->Create(2400, "Computer Systems");
	myDBMS->Create(2824, "Discrete Structures");
	myDBMS->Create(3104, "Algorithms");
	myDBMS->Create(3155, "Principles of Programming Languages");
	myDBMS->Create(3308, "Software Development Methods and Tools");
	myDBMS->Create(1000, "Computer Science as a Field of Work and Study");
	myDBMS->Create(2820, "Linear Algebra with Computer Science Applications");
	myDBMS->Create(3022, "Introduction to Data Science with Probability and Statistics");
	myDBMS->Create(3112, "Professional Development in Computer Science");
	myDBMS->Create(3202, "Introduction to Artificial Intelligence");
	myDBMS->Create(3287, "Design and Analysis of Database Systems");
	myDBMS->Create(3302, "Introduction to Robotics");
	myDBMS->Create(3403, "Introduction to CyberSecurity for a Converged World");
	myDBMS->Create(3702, "Cognitive Science");
	myDBMS->Create(3753, "Design and Analysis of Operating Systems");
	myDBMS->Create(4122, "Information Visualization");
	myDBMS->Create(4253, "Datacenter Scale Computing - Methods, Systems and Techniques");
	myDBMS->Create(4502, "Data Mining");
	myDBMS->Create(4622, "Machine Learning");
	myDBMS->Create(4830, "Special Topics in Applied Computer Science");
	myDBMS->Create(4900, "Upper Division, Undergraduate Level Independent Study");

	// Read record by range scan
	std::cout << std::endl;
	std::cout << " =============== Demo: Read by range scan in B+Tree Mini Database =============== " << std::endl;
	myDBMS->ReadByRange(1000, 1999);
	myDBMS->ReadByRange(2000, 2999);
	myDBMS->ReadByRange(3000, 3999);
	myDBMS->ReadByRange(4000, 4999);

	// scanning empty range 

	std::cout << std::endl;
	std::cout << " =============== Demo: Read by scanning empty range in B+Tree Mini Database =============== " << std::endl;
	myDBMS->ReadByRange(0, 999);



	myDBMS->ReadByRange(5000, 7000);

	// read record by key
	std::cout << std::endl;
	std::cout << " =============== Demo: Read by Key in B+Tree Mini Database =============== " << std::endl;
	myDBMS->ReadByKey(2824); 
	myDBMS->ReadByKey(4830); 

	// read record by non-existent key
	std::cout << std::endl;
	std::cout << " =============== Demo: Read by non-existent Key in B+Tree Mini Database =============== " << std::endl;
	myDBMS->ReadByKey(2821); 
	myDBMS->ReadByKey(4831); 


	// unable to create record since the key 4830 already exists, and key must be unique
	std::cout << std::endl;
	std::cout << " =============== Demo: Key collision, Create failed =============== " << std::endl;
	myDBMS->Create(4830, "Distributed Computing");
	myDBMS->Create(2270, "Data Structures and Algorithms");


	// update key : value 
	std::cout << std::endl;
	std::cout << " =============== Demo: Update content =============== " << std::endl;
	myDBMS->Update(2824, "Discrete Structures	Credits: 3");
	myDBMS->Update(4830, "Special Topics in Computer Science: Current Topics in Computer Science: Advances in Datacenter Networking and Cloud Computing");

	// update non-existing key
	std::cout << std::endl;
	std::cout << " =============== Demo: Key does not exist, Update failed =============== " << std::endl;
	myDBMS->Update(3101, "History of Computing and Information");
	myDBMS->Update(4214, "Big Data Architecture");


	// read updated records
	myDBMS->ReadByKey(2824); 
	myDBMS->ReadByKey(4830);

	// read record by non-existent key
	myDBMS->ReadByKey(3101); 
	myDBMS->ReadByKey(4214);


	// Delete 
	myDBMS->Delete(4253);

	// try to read the delete key 
	myDBMS->ReadByKey(4253);

	delete myDBMS;
}

// void printMenu()
// {
//     // main menu
// 	std::cout << "============================================================" << std::endl;
//     std::cout << "• 1: Create" << std::endl;
//     std::cout << "• 2: Read" << std::endl;
//     std::cout << "• 3: Update" << std::endl;
//     std::cout << "• 4: Delete" << std::endl;
//     std::cout << "• 5: Demo" << std::endl;
//     std::cout << "• 0: Quit" << std::endl;
//     std::cout << "============================================================" << std::endl;
// }

// void invalidInput()
// {
//     std::cout << "Invalid choice. Choose 0-5." << std::endl;
// }
// void printHelp()
// {
//     // std::cout << "Help - your aim is to make money. Analyse the market and make bit and offers." << std::endl;
//     std::cout << " -------------------- Help -------------------- " << std::endl;
//     std::cout << "Create: create new key : value pair record in the database" << std::endl;
//     std::cout << "and offers. " << std::endl;
// }



// void processUserOption(int userOption, )
// {
//     // map from ints to function pointers
//     std::map<int,void(*)()> menu;
//     // connect 1 to the printHelp function
//     menu[0] = invalidInput;
//     menu[1] = printHelp;
//     menu[2] = printMarketStats;
//     menu[3] = enterOffer;
//     menu[4] = enterBid;
//     menu[5] = printWallet;
//     menu[6] = goToNextTimeFrame;

//     if (userOption < 0 || userOption > 5)
//     {
//         userOption = 0;
//     }


//     // call option [userOption]
//     menu[userOption]();
// }

// int getUserOpetion()
// {
//     int userOption;
//     std::cout << "Type in 1-6" << std::endl;
//     std::cin >> userOption;
//     std::cout << "Your choice: " << userOption << std::endl;
//     return userOption;
// }




int main (int argc, const char * argv[])
{
  // no argv[1] given
    
	demo_with_CSPB_courses();



	// while (true)
    // {
    //     // print menu
    //     printMenu();

    //     // get user input
    //     int userOption = getUserOpetion();

    //     // process user input
    //     processUserOption(userOption); 
    // }

	return 0;
}
