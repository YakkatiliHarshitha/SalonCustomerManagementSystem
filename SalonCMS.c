#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Customer {
    char name[50];
    char phone[15];
    char service[30];
    float cost;
    char date[15];
};

void addCustomer();
void displayCustomers();
void searchCustomer();
void updateCustomer();
void deleteCustomer();
void generatebill();

int main() {
    int choice;

    while (1) {
        printf("\n===  SALON CUSTOMER MANAGEMENT SYSTEM ===\n");
        printf("\n==========where beauty meets perfection\n");
        printf("1. Add Customer\n");
        printf("2. Display All Customers\n");
        printf("3. Search Customer by Name\n");
        printf("4. Update Customer Details\n");
        printf("5. Delete Customer\n");
        printf("6.GenerateBill");
        printf("\n 7.Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCustomer(); break;
            case 2: displayCustomers(); break;
            case 3: searchCustomer(); break;
            case 4: updateCustomer(); break;
            case 5: deleteCustomer(); break;
            case 6: generatebill();break;
            case 7:
                printf("\nThank you for using the system!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

// Function to add new customer
void addCustomer() {
    FILE *fp;
    struct Customer c;

    fp = fopen("customers.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter customer name: ");
    scanf("%s", c.name);
    printf("Enter phone number: ");
    scanf("%s", c.phone);
    printf("Enter service taken: ");
    scanf("%s", c.service);
    printf("Enter service cost: ");
    scanf("%f", &c.cost);
    printf("Enter appointment date (DD/MM/YYYY): ");
    scanf("%s", c.date);

    fprintf(fp, "%s %s %s %.2f %s\n", c.name, c.phone, c.service, c.cost, c.date);
    fclose(fp);

    printf("\n Customer added successfully!\n");
}

// Function to display all customers
void displayCustomers() {
    FILE *fp;
    struct Customer c;

    fp = fopen("customers.txt", "r");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- All Customer Records ---\n");
    printf("%-15s %-12s %-15s %-10s %-12s\n", "Name", "Phone", "Service", "Cost", "Date");
    printf("---------------------------------------------------------------\n");

    while (fscanf(fp, "%s %s %s %f %s", c.name, c.phone, c.service, &c.cost, c.date) != EOF) {
        printf("%-15s %-12s %-15s %-10.2f %-12s\n", c.name, c.phone, c.service, c.cost, c.date);
    }

    fclose(fp);
}

// Function to search customer by name
void searchCustomer() {
    FILE *fp;
    struct Customer c;
    char searchName[50];
    int found = 0;

    fp = fopen("customers.txt", "r");
    if (fp == NULL) {
        printf("No records available!\n");
        return;
    }

    printf("Enter customer name to search: ");
    scanf("%s", searchName);

    while (fscanf(fp, "%s %s %s %f %s", c.name, c.phone, c.service, &c.cost, c.date) != EOF) {
        if (strcmp(c.name, searchName) == 0) {
            printf("\n Customer Found:\n");
            printf("Name: %s\nPhone: %s\nService: %s\nCost: %.2f\nDate: %s\n",
                   c.name, c.phone, c.service, c.cost, c.date);
            found = 1;
            break;
        }
    }

    if (found==0)
        printf("\n Customer not found!\n");

    fclose(fp);
}

// Function to update customer details
void updateCustomer() {
    FILE *fp, *temp;
    struct Customer c;
    char name[50];
    int found = 0;

    fp = fopen("customers.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter name of customer to update: ");
    scanf("%s", name);

    while (fscanf(fp, "%s %s %s %f %s", c.name, c.phone, c.service, &c.cost, c.date) != EOF) {
        if (strcmp(c.name, name) == 0) {
            printf("\nEnter new phone number: ");
            scanf("%s", c.phone);
            printf("Enter new service: ");
            scanf("%s", c.service);
            printf("Enter new cost: ");
            scanf("%f", &c.cost);
            printf("Enter new date (DD/MM/YYYY): ");
            scanf("%s", c.date);
            found = 1;
        }
        fprintf(temp, "%s %s %s %.2f %s\n", c.name, c.phone, c.service, c.cost, c.date);
    }

    fclose(fp);
    fclose(temp);

    remove("customers.txt");
    rename("temp.txt", "customers.txt");

    if (found)
        printf("\n Customer details updated successfully!\n");
    else
        printf("\n Customer not found!\n");
}

// Function to delete a customer record
void deleteCustomer() {
    FILE *fp, *temp;
    struct Customer c;
    char name[50];
    int found = 0;

    fp = fopen("customers.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter name of customer to delete: ");
    scanf("%s", name);

    while (fscanf(fp, "%s %s %s %f %s", c.name, c.phone, c.service, &c.cost, c.date) != EOF) {
        if (strcmp(c.name, name) != 0)
            fprintf(temp, "%s %s %s %.2f %s\n", c.name, c.phone, c.service, c.cost, c.date);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("customers.txt");
    rename("temp.txt", "customers.txt");

    if (found)
        printf("\n Customer deleted successfully!\n");
    else
        printf("\n Customer not found!\n");
}
void generatebill(){

    FILE *fp;
    struct Customer c;
    char name[50];
    int found = 0;
    float gst, total;

    fp = fopen("customers.txt", "r");
    if (fp == NULL) {
        printf("No records available!\n");
        return;
    }

    printf("Enter customer name for billing: ");
    scanf("%s", name);

    while (fscanf(fp, "%s %s %s %f %s", c.name, c.phone, c.service, &c.cost, c.date) != EOF) {
        if (strcmp(c.name, name) == 0) {
            found = 1;
            gst = c.cost * 0.18;       // 18% GST
            total = c.cost + gst;

            printf("\n==========  BEAUTYCARE BILL  ==========\n");
            printf("Customer Name  : %s\n", c.name);
            printf("Phone Number   : %s\n", c.phone);
            printf("Service Taken  : %s\n", c.service);
            printf("Service Cost   : %.2f\n", c.cost);
            printf("------------------------------------------\n");
            printf("GST (18%%)      : %.2f\n", gst);
            printf("Total Amount   : %.2f\n", total);
            printf("Date           : %s\n", c.date);
            printf("==========================================\n");
            printf("   Thank you for visiting our saloon!  Visit Again...... \n");
            break;
        }
    }

    if (!found)
        printf("\n Customer not found for billing!\n");

    fclose(fp);
}

