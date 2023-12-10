/*Employee Management System's user will be the admin of the company, 
who will be able to add/find employees and do more other things*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creating a struct with detailes of each employee
struct Employee {
    char name[50];
    char surname[50];
    char age[5];
    char gender[10];
    char skills[100];
    int yearsOfExperience;
    char department[50];
    float salary;
};


// function for finding a suitable employee for the given department and complexity (for menu choice 3)
int findSuitableEmployee(struct Employee employees[], int numEmployees, char department[], int complexity) {
    int assignedEmployeeIndex = -1;

    for (int i = 0; i < numEmployees; i++) {
        //if the department correspnds, check if the years of experience correspond to the complexity of the work
        if (strcmp(employees[i].department, department) == 0) {
            if ((complexity >= 1 && complexity <= 5 && employees[i].yearsOfExperience >= 1) ||
                (complexity >= 6 && complexity <= 8 && employees[i].yearsOfExperience >= 4) ||
                (complexity >= 9 && complexity <= 10 && employees[i].yearsOfExperience >= 6)) {
                assignedEmployeeIndex = i; // store the assigned employee's index
                break; // exit the loop once an employee is assigned
            }
        }
    }

    return assignedEmployeeIndex; // return the assigned employee's index or -1 if not found
}



      
// function for assigning work to an employee (for menu choice 3)
void assignWork(struct Employee employees[], int numEmployees, char work[], int complexity) {
    char department[50];

   //finding out the department based on the phrases from the work that is needed to be done
   
    if (strstr(work, "struggles to use") || strstr(work, "signing up")) {
        strcpy(department, "Customer Support");
    }
    else if (strstr(work, "bug on the website") || strstr(work, "page on the website")) {
        strcpy(department, "IT");
    }
    else if (strstr(work, "financial report") || strstr(work, "count the expenses")) {
        strcpy(department, "Finances");
    }
    else if (strstr(work, "team-building") || strstr(work, "collaboration")) {
        strcpy(department, "HR");
    }
    else if (strstr(work, "month") || strstr(work, "long-term client")) {
        strcpy(department, "Sales");
    }
    else {
        printf("no suitable matches.\n");
        return;
    }

    printf("\nAssigning work: %s (Complexity: %d, Department: %s)\n\n", work, complexity, department);


    //giving the output of the function of finding suitable employee(-1 or the i of the employee)
    //to the variable assignedEmployeeIndex
    int assignedEmployeeIndex = findSuitableEmployee(employees, numEmployees, department, complexity);
  
    
    if (assignedEmployeeIndex != -1) {
        // a suitable employee was found
        struct Employee *assignedEmployee = &employees[assignedEmployeeIndex];
        printf("Assigned to employee: %s %s\n", assignedEmployee->name, assignedEmployee->surname);
    } else {
        // no suitable employee found
        printf("\nNo suitable employee found for this work and complexity in the %s department.\n", department);
    }
    
}



// function to find an employee by name (for menu choice 4)
int findEmployeeByName(struct Employee employees[], int numEmployees, char name[], char surname[]) {
    for (int i = 0; i < numEmployees; i++) {
        // Using strcasecmp for case-insensitive comparison
        if (strcasecmp(employees[i].name, name) == 0 && strcasecmp(employees[i].surname, surname) == 0) {
            return i; // returns the index of the found employee
        }
    }
    return -1; // returns -1 if employee is not found
}



// function to display all data of an employee by name (for menu choice 4)
void displayEmployeeData(struct Employee employees[], int numEmployees) {
    
    char nameToFind[50];
    char surnameToFind[50];
    printf("\nEnter the name of the employee: ");
    getchar(); // clears the input buffer
    fgets(nameToFind, sizeof(nameToFind), stdin); //equivalent of scanf but more efficient
    nameToFind[strcspn(nameToFind, "\n")] = '\0'; 
    // removes the trailing newline (strcspn returns the index of the first character found)

    printf("Enter the surname of the employee: ");
    fgets(surnameToFind, sizeof(surnameToFind), stdin);
    surnameToFind[strcspn(surnameToFind, "\n")] = '\0'; 

    int employeeIndex = findEmployeeByName(employees, numEmployees, nameToFind, surnameToFind);
    if (employeeIndex != -1) {
        // if employee is found, we display it's information (salary, department, ...)
        struct Employee emp = employees[employeeIndex];
        printf("\nEmployee Details:\n");
        printf("Name: %s\nSurname: %s\nGender: %s\nAge: %s\nDepartment: %s\nYears of experience: %d\nSalary: $%.2f\n\n",
               emp.name, emp.surname, emp.gender, emp.age, emp.department, emp.yearsOfExperience, emp.salary);
    } else {
        printf("Employee not found.\n");
    }
}





int main() {
    int MenuChoice;
    int i = 0; 
    struct Employee employees[100]; // creating an array, to store employees
    int numEmployees=0; //to initialize the employee index
    int employeeNumber = 0; //to initialize the employee index (for menu choice 2)

    int employeeNumberfile = 0; // Initialize employee number (for the file)
    int age;
    
    

    // read the last saved employee number from the file , to lis temployees in incrementing order, by their index
    FILE* file = fopen("EmployeeData.txt", "r");
    if (file != NULL) {
        char lineCount[100];
        while (fgets(lineCount, sizeof(lineCount), file)) {
            if (lineCount[0] == 'E' && lineCount[1] == 'm') {
                sscanf(lineCount, "Employee %d:", &employeeNumberfile);
            }
        }
        fclose(file);
    }
  


    printf("Welcome to Employee Management System :)\n");
    
    //asking for permission of creating a file on user's computer
    int perm;
    printf("\nWARNING: By working with this program, the employees' data will be saved in a file on your computer. \nDo you give permission to that?\n\n1) Yes\n2) No\nChoose 1 or 2: ");
    scanf("%d", &perm);
    if (perm==2){
        printf("\nPermission not granted. Exiting the program.\n");
        exit (1);
    }
    else{
    //putting the menu in do while loop, so that it shows again after finishing a task
    do {
        printf("\nMain Menu:\n");
        printf("1) Add Employee\n");
        printf("2) List of Employees\n");
        printf("3) Work Assignment\n");
        printf("4) Find an employee\n");
        printf("5) Exit\n");
        printf("Choose 1-5: ");
        scanf("%d", &MenuChoice);


        switch (MenuChoice) {
        
        //if user chooses 1 from the menu: Add Employee
        case 1:
        
            printf("\nAdding a new employee...\n");
            struct Employee employee;
            
            // gathering employee information
            printf("\nEnter employee's name: ");
            getchar(); // to clear the input buffer
            fgets(employee.name, sizeof(employee.name), stdin); //more efficient than scanf
            employee.name[strcspn(employee.name, "\n")] = '\0'; 

            printf("Enter employee's surname: ");
            fgets(employee.surname, sizeof(employee.surname), stdin);
            employee.surname[strcspn(employee.surname, "\n")] = '\0'; 


            // checking the age and allow going back to the menu if the age is less than 18 or bigger than 65
            printf("Enter employee's age (18-65): ");
            scanf("%s", employee.age);

            age = atoi(employee.age); // atoi used to convert age into an integer
            
            if (age < 18 || age > 65) {
                printf("You have to be 18-65 y.o. to work with us.\n");
                break;
            }
            //continue inputting employee information if age is ok (18-65)
            else {
                int genderChoice;
                printf("Employee's gender\n1. Female\n2. Male\n");
                printf("Choose 1 or 2: ");
                scanf("%d", &genderChoice);
                if (genderChoice == 1) {
                    strcpy(employee.gender, "Female");
                }
                else if (genderChoice == 2) {
                    strcpy(employee.gender, "Male");
                }
                else {
                    printf("\nInvalid choice.\n");
                    break;
                }
            }
            
            
            //choosing employee's best skill to assign a department
        
            printf("\nPersonal information is saved. Continue with inputting Professional information:");
            printf("\nHere is the list of skills necessary to work in our company:\n\n");
            printf("1. Programming and coding skills (e.g., Python, Java, C++)\n");  //for IT department
            printf("2. Cybersecurity\n");                        //for IT department
            printf("3. Sales and negotiation skills\n");                ///for Sales department
            printf("4. Presentation skills\n");          //for Sales department
            printf("5. Recruitment and staffing\n");        //for HR department
            printf("6. Employment law and compliance\n");         //for HR department
            printf("7. Patience and empathy\n");          //for Customer Service department
            printf("8. Adaptability to different customer needs\n");       //for Customer Service department
            printf("9. Budgeting and financial planning\n");          //for Finances department
            printf("10. Taxation knowledge\n");         //for Finances department
  
            int skillChoice;
            printf("\nEnter the number of the skill the new employee has\n(if multiple, select only the best one they possess): ");
            scanf("%d", &skillChoice);

            if (skillChoice < 1 || skillChoice > 10) {
                printf("\nInvalid skill choice.\n");
                break;
            }


          //assigning the department based on the chosen skill
            switch (skillChoice) {
            case 1:
            case 2:
                strcpy(employee.department, "IT");
                break;
            case 3:
            case 4:
                strcpy(employee.department, "Sales");
                break;
            case 5:
            case 6:
                strcpy(employee.department, "HR");
                break;
            case 7:
            case 8:
                strcpy(employee.department, "Customer Support");
                break;
            case 9:
            case 10:
                strcpy(employee.department, "Finances");
                break;
            default:
                printf("Error, Run the code again.");
                break;
            }
            printf("\nCorresponds to the %s.\n\n", employee.department);

            printf("Enter years of experience: ");
            scanf("%d", &employee.yearsOfExperience);

            if (employee.yearsOfExperience<0 || employee.yearsOfExperience > 60) {
                printf("\nInvalid input\n");
                break;
            }
           
            
            // calculating salary based on department and years of experience
            float baseSalary;
            if (strcmp(employee.department, "IT") == 0) {
                baseSalary = 3000;
            }
            else if (strcmp(employee.department, "Sales") == 0) {
                baseSalary = 2600;
            }
            else if (strcmp(employee.department, "HR") == 0) {
                baseSalary = 2500;
            }
            else if (strcmp(employee.department, "Customer") == 0) {
                baseSalary = 2000;
            }
            else if (strcmp(employee.department, "Finances") == 0) {
                baseSalary = 2200;
            }
            else {
                baseSalary = 0;  // default to 0 if department is unknown
            }

            //more salary if more years of experience
            employee.salary = baseSalary + (150 * employee.yearsOfExperience);

            printf("\nThe monthly salary will be: $%.2f\nEmployee added successfully.\n", employee.salary);
         
         
            employees[numEmployees] = employee; 
            //assigning "employee" (that we just added) as the member of array "employees" with index numEmployees.
            numEmployees++;



            // Save employee data to the file called EmployeeData.txt
            file = fopen("EmployeeData.txt", "a");
                if (file == NULL) {
                    printf("Unable to open the file.\n");
                    break;
                }
            

                // writing employee data to the file
                fprintf(file, "Employee %d:\n", ++employeeNumberfile);
                fprintf(file, "Name: %s\nSurname: %s\nGender: %s\nAge: %s\nDepartment: %s\nYears of experience: %d\nSalary: $%.2f\n\n",
                        employee.name, employee.surname, employee.gender, employee.age, employee.department, employee.yearsOfExperience, employee.salary);
                
                fclose(file); // closing the file after writing
                break;


 
       //if user chooses 2 from the menu: List of Employees
        case 2:
                printf("\nList of Employees:\n\n");
            
            //we will list employees by reading from the file
                file = fopen("EmployeeData.txt", "r");
                if (file == NULL) {
                    printf("Unable to open the file for reading.\nFirstly, you should add employees.\n");
                    break;
                }

                char line[100];
                employeeNumber=0;
                while (fgets(line, sizeof(line), file)) {
                    if (line[0] == '\n') {
                        continue;           // for skipping empty lines
                    }
                    if (line[0] == 'E' && line[1] == 'm') {
                        if (employeeNumber > 0) {
                            printf("\n");
                        }
                        printf("Employee %d:\n", ++employeeNumber);
                    }
                    else {
                        printf("%s", line);
                    }
                }

                fclose(file);


                break;

            

       //if user chooses 3 from the menu: Assign Work
        case 3:
                // works to assign to employees
                char works[10][100]= {
                    "Help a client who struggles to use the website of the company",
                    "Fix a bug on the website",
                    "Make the last month's financial report",
                    "Organize a team-building to address recent team work problems",
                    "Go to a meeting with another company that is a potential long-term client",
                    "Add a page on the website",
                    "Make the sales 1.5x times more this month",
                    "Work on team's collaboration",
                    "Count the expenses after giving salaries to all employees",
                    "Contact a client who had problems with signing up to the company's website"
                };

                printf("\nHere are the jobs needed to be done at this moment.\nSelect a job to assign (1-10):\n");
                for (int i = 0; i < 10; i++) {
                    printf("%d. %s\n", i + 1, works[i]);
                }
                int choice;
                scanf("%d", &choice);

                if (choice < 1 || choice > 10) {
                    printf("Invalid choice.\n");
                    break;
                }

                // getting the complexity rating of the job
                int complexity;
                printf("Enter the complexity rating (1-10) for this work: ");
                scanf("%d", &complexity);

                if (complexity < 1 || complexity > 10) {
                    printf("Invalid complexity rating. Run the code again.\n");
                    break;
                }

                // assign the selected work  (assignWork function is before int main)
               assignWork(employees, numEmployees, works[choice - 1], complexity);

                break;
                
    
      //if user chooses 4 from the menu: Find employee        
       case 4: 
               //  (displayEmployeeData function is before int main)
                displayEmployeeData(employees, numEmployees);
                break;
      //if user chooses 5 from the menu: Exit
        case 5:
           printf("Exiting the program.\n");
           return 0;
           break;

     //if user types something else
      default: 
                printf("Invalid choice.\n");
                return 0;
                break; 

        }


            
       } while (1);
    
    }
    fclose(file); 

    return 0;

}