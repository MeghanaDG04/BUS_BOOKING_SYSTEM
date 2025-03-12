
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> // Include the time.h header for date and time functions


// Define file paths for storing data
#define USERS_FILE "users.txt"
#define BUSES_FILE "buses.txt"
#define PASSENGERS_FILE "passengers.txt"

// Define a structure to store bus information
struct Bus {
    int busNumber;
    char source[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
    float fare;
};

// Define a structure to store passenger information
struct Passenger {
    char name[50];
    int age;
    int seatNumber;
    int busNumber;
    char contactNumber[20];
    char contactEmail[50];
    char startingPoint[30];
    char destination[30];
     char bookingDateTime[20]; // To store booking date and time
     char bookedDateTime[20];
};

// Define a structure to store user login information
struct User {
    char username[50];
    char password[50];
    char role[10]; // New field for user role (user or admin)
};

// Function to display the main menu
void displayMainMenu() {
    printf("\n==== Bus Reservation System ====\n");
    printf("|                              |\n");
    printf("|       [1] -> Login           |\n");
    printf("|       [2] -> Signup          |\n");
    printf("|       [3] -> Exit            |\n");
    printf("|                              |\n");
    printf("================================\n");
    printf("Enter your choice: ");
}

// Function to display the user menu based on role
void displayUserMenu(char role[]) {
    printf("\n======== %s Menu ========\n\n", role);
    if (strcmp(role, "admin") == 0) {
        printf("[1] -> Add Bus\n");
        printf("[2] -> Delete Bus\n");
        printf("[3] -> Update Bus\n");
    } else {
        printf("[1] -> Book a Ticket\n");
        printf("[2] -> Cancel a Ticket\n");
        printf("[3] -> View Ticket Details\n");
    }
        printf("[4] -> Check Bus Status\n");
        printf("[5] -> Logout\n");

    printf("\n=============================\n");
    printf("Enter your choice: ");
}

// Function to perform user login
int loginUser(struct User users[], int numUsers, char username[], char password[], char role[]) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            strcpy(role, users[i].role); // Update role
            return i; // Return the index of the logged-in user
        }
    }
    return -1; // Return -1 if login fails
}

// Function to sign up a new user
void signUpUser(struct User users[], int* numUsers, char username[], char password[], char role[]) {
    strcpy(users[*numUsers].username, username);
    strcpy(users[*numUsers].password, password);
    strcpy(users[*numUsers].role, role);
    (*numUsers)++;
    printf("Sign up successful. You can now login.\n");
}

// Function to add a new bus
void addBus(struct Bus buses[], int* numBuses) {
    printf("\nEnter Bus Number: ");
    scanf("%d", &buses[*numBuses].busNumber);

    printf("Enter Source: ");
    scanf("%s", buses[*numBuses].source);

    printf("Enter Destination: ");
    scanf("%s", buses[*numBuses].destination);

    printf("Enter Total Seats: ");
    scanf("%d", &buses[*numBuses].totalSeats);

    buses[*numBuses].availableSeats = buses[*numBuses].totalSeats;

    printf("Enter Fare: ");
    scanf("%f", &buses[*numBuses].fare);

    (*numBuses)++;
    printf("Bus added successfully!\n");
}

// Function to delete a bus
void deleteBus(struct Bus buses[], int* numBuses) {
    printf("\nEnter Bus Number to delete: ");
    int busNumber;
    scanf("%d", &busNumber);

    int found = 0;
    for (int i = 0; i < *numBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            for (int j = i; j < (*numBuses) - 1; j++) {
                buses[j] = buses[j + 1];
            }
            (*numBuses)--;
            found = 1;
            printf("Bus deleted successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Bus with Bus Number %d not found.\n", busNumber);
    }
}

// Function to update bus details
void updateBus(struct Bus buses[], int numBuses) {
    printf("\nEnter Bus Number to update: ");
    int busNumber;
    scanf("%d", &busNumber);

    int found = 0;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            printf("Enter New Source: ");
            scanf("%s", buses[i].source);

            printf("Enter New Destination: ");
            scanf("%s", buses[i].destination);

            printf("Enter New Total Seats: ");
            scanf("%d", &buses[i].totalSeats);

            buses[i].availableSeats = buses[i].totalSeats;

            printf("Enter New Fare: ");
            scanf("%f", &buses[i].fare);

            found = 1;
            printf("Bus details updated successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Bus with Bus Number %d not found.\n", busNumber);
    }
}

int isValidEmail(char* email) {
    int atIndex = -1;
    int dotIndex = -1;
    int len = strlen(email);

    // Check if email length is appropriate
    if (len < 5) { // example@x.xx minimum length
        return 0;
    }

    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            if (atIndex == -1) {
                atIndex = i;
            } else {
                // More than one '@' symbol is invalid
                return 0;
            }
        } else if (email[i] == '.') {
            if (i > atIndex) {
                dotIndex = i;
            }
        }
    }

    // Check if '@' is present and not at the start or end
    if (atIndex <= 0 || atIndex >= len - 1) {
        return 0;
    }

    // Check if '.' is present after '@' and not at the end
    if (dotIndex <= atIndex + 1 || dotIndex >= len - 1) {
        return 0;
    }

    return 1;
}

bool isValidDateTime(const char *dateTime) {
    int day, month, year, hour, minute;
    if (sscanf(dateTime, "%2d/%2d/%4d %2d:%2d", &day, &month, &year, &hour, &minute) != 5) {
        return false;
    }

    // Check ranges of date and time components
    if (year < 2024 || year > 9999) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;

    // Check days in month
    int daysInMonth[] = {31, (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (day > daysInMonth[month - 1]) return false;

    return true;
}


void getCurrentDateTime(char dateTime[20]) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateTime, "%02d/%02d/%d %02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
}


void bookTicket(struct Bus buses[], int numBuses, struct Passenger passengers[], int* numPassengers, int userId) {
    printf("\nEnter Bus Number: ");
    int busNumber;
    scanf("%d", &busNumber);

    int busIndex = -1;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1) {
        printf("Bus with Bus Number %d not found.\n", busNumber);
        return;
    }

    if (buses[busIndex].availableSeats <= 0) {
        printf("No available seats on this bus.\n");
        return;
    }

    printf("\nEnter number of tickets you want to book: ");
    int numTickets;
    scanf("%d", &numTickets);

    for (int i = 0; i < numTickets; i++) {
        struct Passenger passenger;

        printf("\nEnter Passenger Name: ");
        scanf("%s", passenger.name);

        printf("Enter Passenger Age: ");
        scanf("%d", &passenger.age);

        // Assign a seat number to the passenger
        passenger.seatNumber = buses[busIndex].totalSeats - buses[busIndex].availableSeats + 1;

        // Update the passenger's bus number
        passenger.busNumber = busNumber;

                // Get current date and time
        getCurrentDateTime(passenger.bookedDateTime);

        // Ask for desired booking date and time
        while (true) {
            printf("Enter Booking Date and Time (dd/mm/yyyy hh:mm): ");
            scanf(" %[^\n]%*c", passenger.bookingDateTime); // Read date and time as string

            if (isValidDateTime(passenger.bookingDateTime)) {
                break;
            } else {
                printf("Invalid date and time format. Please try again.\n");
            }
        }
        // Ask for contact details
        char contactNumber[11];
        printf("\nEnter Contact Number (10 digits): ");
        scanf("%s", contactNumber);
        if (strlen(contactNumber) != 10) {
            printf("Please provide a 10 digit contact number.\n");
            i--;
            continue;
        }
        strcpy(passenger.contactNumber, contactNumber);

        char contactEmail[50];
        printf("Enter Contact Email{Format: example@x.xx minimum length}: ");
        scanf("%s", contactEmail);
        if (!isValidEmail(contactEmail)) {
            printf("Please provide a valid email address.\n");
            i--;
            continue;
        }
        strcpy(passenger.contactEmail, contactEmail);

        printf("Enter the Starting point of your journey: ");
        scanf("%s", passenger.startingPoint);

        printf("Enter the destination point: ");
        scanf("%s", passenger.destination);

        // Add the passenger to the list
        passengers[*numPassengers] = passenger;
        (*numPassengers)++;

        // Update available seats
        buses[busIndex].availableSeats--;
    }

    printf("Ticket(s) booked successfully!\n");
}




void cancelTicket(struct Bus buses[], int numBuses, struct Passenger passengers[], int* numPassengers) {
    printf("\nEnter Passenger Name to cancel ticket: ");
    char name[50];
    scanf("%s", name);

    printf("Enter Bus Number: ");
    int busNumber;
    scanf("%d", &busNumber);

    int busIndex = -1;
    for (int i = 0; i < numBuses; i++) {
        if (buses[i].busNumber == busNumber) {
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1) {
        printf("Bus with Bus Number %d not found.\n", busNumber);
        return;
    }

    int found = 0;
    for (int i = 0; i < *numPassengers; i++) {
        if (strcmp(passengers[i].name, name) == 0 && passengers[i].busNumber == busNumber) {
            // Increase available seats
            buses[busIndex].availableSeats++;

            // Remove the passenger entry
            for (int j = i; j < (*numPassengers) - 1; j++) {
                passengers[j] = passengers[j + 1];
            }
            (*numPassengers)--;
            found = 1;
            printf("Ticket canceled successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Passenger with name %s not found on bus number %d.\n", name, busNumber);
    }
}


// Function to view ticket details
/*void viewTicketDetails(struct Passenger passengers[], int numPassengers) {
    printf("\nTicket Details:\n");
    for (int i = 0; i < numPassengers; i++) {
        printf("Passenger Name: %s\n", passengers[i].name);
        printf("Passenger Age: %d\n", passengers[i].age);
        printf("Seat Number: %d\n", passengers[i].seatNumber);
        printf("Bus Number: %d\n", passengers[i].busNumber);
        printf("Contact Number: %s\n", passengers[i].contactNumber);
        printf("Contact Email: %s\n", passengers[i].contactEmail);
        printf("Starting Point: %s\n", passengers[i].startingPoint);
        printf("Destination: %s\n", passengers[i].destination);
        printf("Booking Date & Time: %s\n", passengers[i].bookingDateTime); // Display booking date and time
        printf("Booked on and at: %s\n", passengers[i].bookedDateTime); // Display booked date and time
        printf("---------------------------\n");
    }
}*/

void viewTicketDetails(struct Passenger passengers[], int numPassengers) {
    printf("\nTicket Details:\n");
    for (int i = 0; i < numPassengers; i++) {
        printf("Passenger Name: %s\n", passengers[i].name);
        printf("Passenger Age: %d\n", passengers[i].age);
        printf("Seat Number: %d\n", passengers[i].seatNumber);
        printf("Bus Number: %d\n", passengers[i].busNumber);
        printf("Contact Number: %s\n", passengers[i].contactNumber);
        printf("Contact Email: %s\n", passengers[i].contactEmail);
        printf("Starting Point: %s\n", passengers[i].startingPoint);
        printf("Destination: %s\n", passengers[i].destination);
        printf("Booking Date & Time: %s\n", passengers[i].bookingDateTime);
        printf("Booked on and at: %s\n", passengers[i].bookedDateTime);
        printf("---------------------------\n");
    }
}


// Function to check bus status
void checkBusStatus(struct Bus buses[], int numBuses) {
    printf("\nBus Status:\n");
    for (int i = 0; i < numBuses; i++) {
        printf("Bus Number: %d\n", buses[i].busNumber);
        printf("Source: %s\n", buses[i].source);
        printf("Destination: %s\n", buses[i].destination);
        printf("Total Seats: %d\n", buses[i].totalSeats);
        printf("Available Seats: %d\n", buses[i].availableSeats);
        printf("Fare: %.2f\n", buses[i].fare);
        printf("---------------------------\n");
    }
}

// Function to read users data from file
int readUsersFromFile(struct User users[]) {
    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL) {
        return 0; // Return 0 if the file doesn't exist or is empty
    }

    int numUsers = 0;
    while (fscanf(file, "%s %s %s", users[numUsers].username, users[numUsers].password, users[numUsers].role) != EOF) {
        numUsers++;
    }
    fclose(file);
    return numUsers;
}

// Function to write users data to file
void writeUsersToFile(struct User users[], int numUsers) {
    FILE *file = fopen(USERS_FILE, "w");
    for (int i = 0; i < numUsers; i++) {
        fprintf(file, "%s %s %s\n", users[i].username, users[i].password, users[i].role);
    }
    fclose(file);
}

// Function to read buses data from file
int readBusesFromFile(struct Bus buses[]) {
    FILE *file = fopen(BUSES_FILE, "r");
    if (file == NULL) {
        return 0; // Return 0 if the file doesn't exist or is empty
    }

    int numBuses = 0;
    while (fscanf(file, "%d %s %s %d %d %f", &buses[numBuses].busNumber, buses[numBuses].source, buses[numBuses].destination, &buses[numBuses].totalSeats, &buses[numBuses].availableSeats, &buses[numBuses].fare) != EOF) {
        numBuses++;
    }
    fclose(file);
    return numBuses;
}

// Function to write buses data to file
void writeBusesToFile(struct Bus buses[], int numBuses) {
    FILE *file = fopen(BUSES_FILE, "w");
    for (int i = 0; i < numBuses; i++) {
        fprintf(file, "%d %s %s %d %d %f\n", buses[i].busNumber, buses[i].source, buses[i].destination, buses[i].totalSeats, buses[i].availableSeats, buses[i].fare);
    }
    fclose(file);
}

// Function to read passengers data from file
/*int readPassengersFromFile(struct Passenger passengers[]) {
    FILE *file = fopen(PASSENGERS_FILE, "r");
    if (file == NULL) {
        return 0; // Return 0 if the file doesn't exist or is empty
    }

    int numPassengers = 0;
    while (fscanf(file, "%s %d %d %d %s %s %s %s %s %s", passengers[numPassengers].name, &passengers[numPassengers].age, &passengers[numPassengers].seatNumber, &passengers[numPassengers].busNumber, passengers[numPassengers].contactNumber, passengers[numPassengers].contactEmail, passengers[numPassengers].startingPoint, passengers[numPassengers].destination,passengers[numPassengers].bookingDateTime,passengers[numPassengers].bookedDateTime) != EOF) {
        numPassengers++;
    }
    fclose(file);
    return numPassengers;
}*/

int readPassengersFromFile(struct Passenger passengers[]) {
    FILE *file = fopen(PASSENGERS_FILE, "r");
    if (file == NULL) {
        return 0; // Return 0 if the file doesn't exist or is empty
    }

    int numPassengers = 0;
    while (fscanf(file, "%49s %d %d %d %10s %49s %49s %49s %19s %19s", passengers[numPassengers].name,
                  &passengers[numPassengers].age, &passengers[numPassengers].seatNumber, &passengers[numPassengers].busNumber,
                  passengers[numPassengers].contactNumber, passengers[numPassengers].contactEmail, passengers[numPassengers].startingPoint,
                  passengers[numPassengers].destination, passengers[numPassengers].bookingDateTime, passengers[numPassengers].bookedDateTime) == 10) {
        numPassengers++;
    }
    fclose(file);
    return numPassengers;
}


// Function to write passengers data to file
/*void writePassengersToFile(struct Passenger passengers[], int numPassengers) {
    FILE *file = fopen(PASSENGERS_FILE, "w");
    for (int i = 0; i < numPassengers; i++) {
        fprintf(file, "%s %d %d %d %s %s %s %s %s %s\n", passengers[i].name, passengers[i].age, passengers[i].seatNumber, passengers[i].busNumber, passengers[i].contactNumber, passengers[i].contactEmail, passengers[i].startingPoint, passengers[i].destination, passengers[i].bookingDateTime, passengers[i].bookedDateTime);
    }
    fclose(file);
}*/

void writePassengersToFile(struct Passenger passengers[], int numPassengers) {
    FILE *file = fopen(PASSENGERS_FILE, "w");
    for (int i = 0; i < numPassengers; i++) {
        fprintf(file, "%s %d %d %d %s %s %s %s %s %s\n", passengers[i].name, passengers[i].age, passengers[i].seatNumber,
                passengers[i].busNumber, passengers[i].contactNumber, passengers[i].contactEmail, passengers[i].startingPoint,
                passengers[i].destination, passengers[i].bookingDateTime, passengers[i].bookedDateTime);
    }
    fclose(file);
}


int main() {
    // Initialize user data
    struct User users[100];
    int numUsers = readUsersFromFile(users);

    // Initialize bus data
    struct Bus buses[10];
    int numBuses = readBusesFromFile(buses);

    struct Passenger passengers[500]; // Array to store passenger information
    int numPassengers = readPassengersFromFile(passengers); // Number of passengers

    char role[10]; // Variable to store user role (user or admin)
    int loggedInUserId = -1; // Index of the logged-in user

    while (1) {
        if (loggedInUserId == -1) {
            displayMainMenu();
            int choice;
            scanf("%d", &choice);

            if (choice == 1) {
                char username[50];
                char password[50];

                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);

                loggedInUserId = loginUser(users, numUsers, username, password, role);
                if (loggedInUserId == -1) {
                    printf("Login failed. Please check your username and password.\n");
                } else {
                    printf("Login successful. Welcome, %s!\n", username);
                }
            } else if (choice == 2) {
                char username[50];
                char password[50];
                char role[10];

                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);
                printf("Enter your role (user or admin): ");
                scanf("%s", role);

                /*signUpUser(users, &numUsers, username, password, role);
                writeUsersToFile(users, numUsers);*/
                if (strcmp(role, "user") != 0 && strcmp(role, "admin") != 0) {
                    printf("Error: Invalid role. Please check your spelling.\n");
                    continue;
                }

                signUpUser(users, &numUsers, username, password, role);
                writeUsersToFile(users, numUsers);
            } else if (choice == 3) {
                printf("Exiting the program.\n");
                break;
            } else {
                printf("Invalid choice. Please try again.\n");
            }
        } else {
            displayUserMenu(role);
            int userChoice;
            scanf("%d", &userChoice);

            switch (userChoice) {
                case 1:
                    if (strcmp(role, "admin") == 0) {
                        addBus(buses, &numBuses);
                        writeBusesToFile(buses, numBuses);
                    } else {
                         bookTicket(buses, numBuses, passengers,
                         &numPassengers, loggedInUserId);
                        writePassengersToFile(passengers, numPassengers);
                        writeBusesToFile(buses, numBuses);
                    }
                    break;
                case 2:
                    if (strcmp(role, "admin") == 0) {
                        deleteBus(buses, &numBuses);
                        writeBusesToFile(buses, numBuses);
                    } else {
                    cancelTicket(buses, numBuses, passengers, &numPassengers);
                        writePassengersToFile(passengers, numPassengers);
                        writeBusesToFile(buses, numBuses);
                    }
                    break;
                case 3:
                    if (strcmp(role, "admin") == 0) {
                        updateBus(buses, numBuses);
                        writeBusesToFile(buses, numBuses);
                    } else {
                        viewTicketDetails(passengers, numPassengers);
                    }
                    break;
                case 4:
                    if (strcmp(role, "user") == 0) {
                        checkBusStatus(buses, numBuses);
                    } else if (strcmp(role, "admin") == 0) {
                        checkBusStatus(buses, numBuses);
                    } else {
                        printf("Invalid choice. Please try again.\n");
                    }
                    break;
                case 5:
                    if (strcmp(role, "user") == 0 || strcmp(role, "admin") == 0) {
                        printf("Logging out.\n");
                        loggedInUserId = -1;
                    } else {
                        printf("Invalid choice. Please try again.\n");
                    }
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    }

    return 0;
}
