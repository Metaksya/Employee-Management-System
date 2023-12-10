# Employee-Management-System
A project which facilitates working with Employee data, helps count salaries based on the employee's department and years of experience, helps assign works to corresponding employees, helps find an employee's data by searching their name, saves employees' data in a separate file.

Detailed explanation of the code, highlighting key sections and algorithms:

Header Inclusions:

Purpose: These lines include essential standard C libraries for input/output operations, memory allocation, and string manipulation.




Employee Structure Definition:

Purpose: Defines the structure Employee encapsulating employee details.




Functions:

findSuitableEmployee:
Purpose: Locates an employee suitable for a given department and work complexity. Algorithm:
Iterates through the employee array to find a match based on the department and complexity criteria.
Employs nested if-else conditions to match the complexity ranges with years of experience required.


assignWork:

Purpose: Assigns a task to an employee based on task description and complexity. 

Algorithm:
Analyzes the task description to determine the appropriate department.
Calls findSuitableEmployee to assign the task to a suitable employee based on department and complexity.


findEmployeeByName:

Purpose: Searches for an employee by name and surname.  

Algorithm:

Compares inputted name and surname with the stored employee data using case-insensitive comparison (strcasecmp).
Returns the index of the found employee or -1 if not found.


displayEmployeeData:

Purpose: Displays detailed information about an employee. 

Algorithm:

Prompts for the name and surname of the employee to be displayed.
Calls findEmployeeByName to retrieve the employee's data and displays it if found.




Main Function:

Purpose: Drives the program's execution and user interaction.




Menu Interface:

Presents a menu-driven interface for functionalities: adding employees, listing them, assigning work, finding employees, and exiting the system.  Utilizes switch-case statements to execute the chosen functionality.




File Handling:

Purpose: Manages reading from and writing to 'EmployeeData.txt'.

Reading from File (fopen):
Reads the last saved employee number from the file to maintain an organized count.

Writing to File (fopen, fprintf):
Saves employee details in a structured format within the file for future reference.

