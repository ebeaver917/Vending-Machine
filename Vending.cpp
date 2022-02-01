/*===========================================================================*/
/* Global headers and namespace */

#include <iostream>           //standard IO header
#include <fstream>            //file IO header
#include <string>             //for string manipulation
#include <iomanip>            //IO manipulation

using namespace std;          //standard namespace usage        

/*===========================================================================*/
/* Global named constants */

const int SIZE = 6;           //the max number of drinks in the machine

const double CAN_PROFIT = .25;//the profit for each can is $0.25 

/*===========================================================================*/
struct drink
{
   string name;               //the name of each soda in the machine
          
   double cost;               //the price of each soda
  
   int avail;                 //the current availability of each soda
};

/*===========================================================================*/
/* Global type definitions */

typedef drink machine[SIZE];  //define the array of structs

/*===========================================================================*/
/* Global function definitions */

void PrintWelcome();
void PrintMachine(drink*);
int GetDrink(int&, drink*);
void SelectionSort(drink*);

/*===========================================================================*/ 
int main()
{ /* main */

   /* Define local variables */

   drink machine[SIZE];      //define the type of machine
 
   int drinkChoice;          //the drink number the user chooses
 
   double payment,           //what the user pays the machine
          change,            //how much the machine owes the user
          profit;            //the total profit from the program run
  
   string names,             //the names of the sodas
          numbers;           //used only to skip the number lines in the file
   
   ifstream machineFile;     //define the input file

   /* Open the input file and check for validity */
   machineFile.open("machine.txt");

   /* If the file does not open, print an error message */
   if(!machineFile)
   {
      cout << "Unable to open input file." << endl;
   }
   
   /* Carry on normally if the file opens */
   else
   {  
      /* Read through the file */
      for (int i = 0; i < SIZE; i++)
      {
         /* Read in the names followed by the double and int values */
         getline(machineFile, machine[i].name);
         machineFile >> machine[i].cost >> machine[i].avail;

         /* Skip the lines in the file with the double and int values and */
         /* return back to the names */
         getline(machineFile, numbers);
      }

      /* Initialize profit at the start of the run */   
      profit = 0;

      /* Print the welcome heading on the machine */
      PrintWelcome();

      /* Print out the vending machine UI */
      PrintMachine(machine);

      /* Get the drink number and perform error checking */
      GetDrink(drinkChoice, machine);
      
      /* When the user enters a valid, nonzero drink number */ 
      /* the run continues */
      while(drinkChoice != 0)
      {
         /* Echoprint the user's input and prompt them to enter payment */
         cout << endl << "You have chosen drink number " << drinkChoice << ", " 
              << machine[drinkChoice - 1].name << "." << endl << endl;
         cout << "Please enter $1.00 (type 1.00) ->";
         cin >> payment;
         cout << endl;

         /* Check for any payment other than $1.00 */
         while (payment != 1.00)
         {
            cout << "Invalid payment. Please enter $1.00 (type 1.00) ->";
            cin >> payment;
         }
      
         /* Calculate the change for the order and print it */
         change = (payment - machine[drinkChoice - 1].cost);

         cout << "Your change for this purchase is $" << change << "."
              << endl << endl;

         /* Decrement the amount of cansin the machine for the user's 
         /* drink of choice */
         machine[drinkChoice - 1].avail--;

         /* Increment the total profit */
         profit++;     
  
         /*Each time the program loops, print an updated header message */
         cout << "**********************************************************"
              << "****" << endl
              << "| The updated drink choices follow this message :) Thanks!"
              << "   |" << endl
              << "**********************************************************"
              << "****" << endl;

         /*Print the machine UI again each time the program loops */
         PrintMachine(machine);

         /* Loop getting the drink number and error checking drinck choice */
         GetDrink(drinkChoice, machine);
    
      }
         cout << endl << "You have chosen to quit. Thank you!" << endl << endl;

         cout << "The total profit from this run was $" 
              << (profit * CAN_PROFIT) << endl << endl;
       
         cout << "A table displaying the machine's final state follows." 
              << endl;

         cout << "The table is sorted by amount of drinks left in the machine,"
              << endl << "from most to least." << endl << endl;

         cout << left << setw(20) << "Drink name:" << setw(15) 
              << "Drink price:" << "Cans remaining:" << endl;
         cout << left << setw(20) << "-----------" << setw(15) 
              << "------------" << "---------------" << endl;
        
         SelectionSort(machine);
  
         for (int j = 0; j < SIZE; j++)
         {
            cout << left << setw(24) << machine[j].name << setw(18) 
                 << machine[j].cost << machine[j].avail << endl << endl;
         }
         
         cout << endl;
         cout << "Program terminated normally." << endl << endl;
   }
  
return(0);

} /* main */

/*==========================Function Definitions=============================*/

void PrintWelcome()

/*--------------------------------------------------------------------------*/
/* This function prints an output heading on the vending machine UI, and is */
/* only called once. It is not included if the user decides to continue and */
/* purchase more drinks                                                     */
/*--------------------------------------------------------------------------*/

/* Called by: main */

{ /* PrintWelcome */

   cout << "**************************************************************"
        << endl
        << "| Hello! Thank you for choosing vending machine number 3363! |"
        << endl
        << "| The drink choices available to you follow this message :)  |"
        << endl
        << "**************************************************************"
        << endl;

} /* PrintWelcome */

/*===========================================================================*/

void PrintMachine(drink machine[SIZE])

/*-----------------------------------------------------------------------*/
/* This function prints out a table-like vending machine UI to the user. */
/* The vending machine updates every time the user selects a drink and   */
/* decreases the amount of total drinks of the drink the user just       */ 
/* selected by one                                                       */
/*-----------------------------------------------------------------------*/

{ /* PrintMachine */

   /* Print double values to two decimal places */
   cout << fixed << showpoint << setprecision(2);

   /* Print the first "row" of names */
   cout << "| 1) " << machine[0].name << setw(13) 
        << "| 2) " << machine[1].name << setw(8) 
        << "| 3) " << machine[2].name << setw(7) << setw(8) << "|" << endl;

   /* Print each drink's respective cost and availability below the name */
   cout << "| Price: $" << machine[0].cost << setw(13)
        << "| Price: $" << machine[1].cost << setw(18)
        << "| Price: $" << machine[2].cost << setw(9) << "|" << endl;
   
   /* Use setfill to prevent two character numbers (eg. 10) from shifting the */
   /* line over if the amount of drinks available reduces to one character */
   
   /* Example 9 will now become 09 */
   cout << "| " << setw(2) << setfill('0') << machine[0].avail << " can(s)"
        << setfill(' ') << setw(8);
   cout << "| " << setw(2) << setfill('0') << machine[1].avail << " can(s)"
        << setfill(' ') << setw(13);
   cout << "| " << setw(2) << setfill('0') << machine[2].avail << " can(s)"
        << setfill(' ') << setw(12) << "|" << endl;
  
   cout << "**************************************************************" 
        << endl;
   
   /* Print the second "row" of names */
   cout << "| 4) " << machine[3].name << setw(7) 
        << "| 5) " << machine[4].name << setw(11)
        << "| 6) " << machine[5].name << "|" << endl;

   /* Print the respective prices and availabilities of the drinks row two */
   cout << "| Price: $" << machine[3].cost << setw(13)
        << "| Price: $" << machine[4].cost << setw(18)
        << "| Price: $" << machine[5].cost << setw(9) << "|" << endl;
   
   cout << "| " << setw(2) << setfill('0') << machine[3].avail << " can(s)"
        << setfill(' ') << setw(8);
   cout << "| " << setw(2) << setfill('0') << machine[4].avail << " can(s)"
        << setfill(' ') << setw(13);
   cout << "| " << setw(2) << setfill('0') << machine[5].avail << " can(s)"
        << setfill(' ') << setw(12) << "|" << endl;
   
   cout << "**************************************************************"
        << endl;

} /* PrintMachine */

/*===========================================================================*/

int GetDrink(int& drinkChoice, drink machine[SIZE])

/*------------------------------------------------------------------------*/
/* This function serves to get the user's choice of drink every time the  */
/* program loops, as well as check for bad input data, such as an invalid */
/* drink number or if the machine is out of one drink. In addition to     */
/* this, the function recognizes when the user inputs zero to quit and    */
/* calculates profit.                                                     */
/*------------------------------------------------------------------------*/

/* Called by: main */

{ /* GetDrink */

   bool error = true;

   cout << "Please enter the drink number you wish to purchase, or press"
        << endl << "0 to quit ->";

   while (error == true)
   {
      cin >> drinkChoice;

      if (cin.fail())
      {
         cout << endl;
         cout << "Please enter an integer drink number (1-6), or press 0"
              << endl << "to quit->";
         break;
      }
  
      if (drinkChoice == 0)
      {
         return(0);
      }

      else if (drinkChoice > 6 || drinkChoice < 0)
      {
         cout << endl;
         cout << "Invalid drink number entered."
              << endl << endl;
         cout << "Please enter a valid drink number or press 0 to quit->";
      }

      else if (machine[drinkChoice - 1].avail < 1)
      {
         cout << endl;
         cout << "The drink you have chosen is currently not in stock."
              << endl << endl;
         cout << "Please enter another drink number or press 0 to quit->";
      }

      else 
      {
         error = false;
      }
   }
return drinkChoice;
}
/*===========================================================================*/

void SelectionSort(drink sortArr[SIZE])

{ /* SelectionSort */

   int start,
       largest,
       current;
       
   drink temp;
  
   for (start = 0; start < (SIZE - 1); start++)
   {
      largest = start;
     
      for (current = (start + 1); current < SIZE; current++)
      {
         if (sortArr[current].avail > sortArr[largest].avail)
         {
            largest = current;
         }
      }
      
      if (largest != start)
      {
         temp = sortArr[start];
         sortArr[start] = sortArr[largest];
         sortArr[largest] = temp;
      }
   }
} /* SelectionSort */
/*===========================================================================*/
/*           END OF PROGRAM SOFT DRINK VENDING MACHINE SIMULATION            */
/*===========================================================================*/

