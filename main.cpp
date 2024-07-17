#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <Windows.h>


using namespace std;

const int MAX_ITEMS = 100;
const int SCREEN_WIDTH = 80;
// Declare arrays to store product information
string item[MAX_ITEMS];
double price[MAX_ITEMS];
int stock[MAX_ITEMS];

// Declare arrays to store cart information
string cartItems[MAX_ITEMS];
double cartPrices[MAX_ITEMS];
int cartQuantities[MAX_ITEMS];
int cartCount = 0;
// Declare variables to keep track of totals
double total_price = 0;
int total_stock = 0;
int total_item = 0;

const string FILENAME = "LIST.txt";// File to store product information
ofstream outfile;// Output file stream 
ifstream infile;// Input file stream 

// Function prototypes
void manageOrder();
void addProduct();
void deleteProduct();
void showProduct();
void addToCart();
void managefeedback();
void provideFeedback();
void viewCart();
void managePayment();
void loadProducts();
void purchaseProducts();
void setWindowSize(int, int);
void centerPrint(const string&);

int main() {

    setWindowSize(SCREEN_WIDTH, 25);

    int choice;
    char selection;
    int select;
    loadProducts();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    string lines[] = {

        "  __    _______     ______",
        " / /   / ___/ /__  / / / /",
        "/ /   / /__/ / _ \\/ / / /",
        "\\ \\  /___  /  __/ /_/ / ",
        " \\_\\/____/\\___/\\____/ ",
        "------------------------------------------",
        "/ / / /      / / / /    / / /     / / / / ",
        "/            /     /      /       /       ",
        "/ / / /      / / / /      /       /       ",
        "/            /            /       /       ",
        "/ / / /      /          / / /     / / / / ",
        "                                          ",
        "                   EPIC                   ",
        "..............................................................",
        ".                 Welcome to EPIC PRO App ^_^                .",
        ".      Hope you have a wonderful shopping experience!!!      .",
        ".............................................................."
    };

    // Print the welcome message
    for (const auto& line : lines) {
        centerPrint(line);
    }
    system("pause");
    system("cls");
    // Set text color to blue and high intensity
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    // Main menu loop
    do {

        centerPrint("1. Admin Menu");
        centerPrint("2. Buyer Menu");
        centerPrint("3. Exit      ");
        cout << setw((SCREEN_WIDTH + string("Enter your choice: ").length()) / 2) << "Enter your choice: ";
        cin >> choice;
        system("cls");



        if (choice == 2) {
            int buyerChoice;
            // Set text color to blue and high intensity for buyer menu
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            do {

                centerPrint("1. Show Products     ");
                centerPrint("2. View Cart         ");
                centerPrint("3. Provide Feedback  ");
                centerPrint("4. Manage Payment    ");
                centerPrint("5. Exit              ");
                cout << endl;
                cout << setw((SCREEN_WIDTH + string("Enter your choice: ").length()) / 2) << "Enter your choice: ";
                cin >> buyerChoice;
                system("cls");

                if (buyerChoice == 1) {
                    addToCart();
                }
                else if (buyerChoice == 2) {
                    viewCart();
                }
                else if (buyerChoice == 3) {
                    provideFeedback();
                }
                else if (buyerChoice == 4) {
                    managePayment();
                }
                else if (buyerChoice == 5) {
                    break;
                }
                else {
                    centerPrint("Invalid choice. Try again.");
                }
            } while (buyerChoice != 5);
        }
        else if (choice == 1) {

            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            do {
                centerPrint("Do you want to add items?         Press 1   ");
                centerPrint("Do you want to manage order?      Press 2   ");
                centerPrint("Do you want to check feedback?    Press 3   ");
                cout << setw((SCREEN_WIDTH + string("Enter your choice: ").length()) / 2) << "Enter your choice: ";
                cin >> select;
                system("cls");

                if (select == 1) {
                    addProduct();
                }
                else if (select == 2) {
                    manageOrder();
                }
                else if (select == 3) {
                    managefeedback();
                }

                centerPrint("Run the admin menu again? (Y/N)");
                cin >> selection;
                system("cls");

            } while (selection == 'y' || selection == 'Y');
            cout << fixed << setprecision(2) << endl;
            centerPrint("The total items is: " + to_string(total_item));
            centerPrint("The total price is: " + to_string(total_price));
            centerPrint("The total stock is: " + to_string(total_stock));
            system("pause");
            system("cls");
        }
        else if (choice < 1 || choice > 3) {
            return 0;
        }

    } while (choice != 3);


    centerPrint("----------------------------------Welcome to visit us next time! THANK YOU ^ _ ^----------------------------------------");

    return 0;
}

void centerPrint(const string& text) {
    cout << setw((SCREEN_WIDTH + text.length()) / 2) << text << endl;
}


void manageOrder() {
    string selection;
    int select;
    // Manages product orders, allowing admin to list, add, and delete items
    do {
        centerPrint("List out all the items      Press 1");
        centerPrint("Add product                 Press 2");
        centerPrint("Delete items                Press 3");
        cin >> select;
        system("cls");

        if (select == 1) {
            showProduct();
        }
        else if (select == 2) {
            addProduct();
        }
        else if (select == 3) {
            deleteProduct();
        }

        centerPrint("Do you want manage order again? (Y/N)");
        cin >> selection;

    } while (selection == "Y" || selection == "y");
}


void addProduct() {
    char sel;
    do {
        int team;
        cin.ignore();
        bool name = true;
        do {
            centerPrint("Enter items name:(alphabet)");

            getline(cin, item[total_item]);
            if (item[total_item] == "") {
                centerPrint("Please input again !");
                cout << endl;
            }
            else {
                name = false;
            }
        } while (name);

        bool price1 = true;
        string userInput;
        do {
            centerPrint("Enter price(RM):(number)");
            getline(cin, userInput);

            for (int i = 0; i < userInput.length(); ++i) {
                char c = userInput[i];

                if (isalpha(c)) {
                    centerPrint("Please enter the number!");
                    cout << endl;
                    break;

                }
                else
                    price1 = false;
            }
        } while (price1);


        price[total_item] = stod(userInput);
        total_price += price[total_item];

        bool stock1 = true;
        string stockInput;
        do {
            centerPrint("Enter stock quantity:(number)");
            getline(cin, stockInput);

            for (int i = 0; i < stockInput.length(); ++i) {
                char a = stockInput[i];

                if (isalpha(a)) {
                    centerPrint("Please enter the number!");
                    cout << endl;
                    break;

                }
                else
                    stock1 = false;
            }
        } while (stock1);


        stock[total_item] = stod(stockInput);
        total_stock += stock[total_item];

        centerPrint("Add product successfully!");
        cout << endl;

        outfile.open(FILENAME, ios::app);
        if (outfile.is_open()) {
            outfile << item[total_item] << endl;
            outfile << price[total_item] << endl;
            outfile << stock[total_item] << endl;
        }
        else {
            centerPrint("Cannot open the file");
        }
        outfile.close();
        total_item++;
        centerPrint("Do you want to add more product? (Y/N)");

        cin >> sel;


    } while (sel == 'Y' || sel == 'y');

}


void managePayment() {
    int selection;
    double phoneNumber;
    double creditNumber;
    double number;
    string onlineBank;
    string address;

    ofstream outfile("PAYMENT.txt", ios::app);
    if (!outfile.is_open()) {
        centerPrint("Error opening payment file.");

    }
    else {
        centerPrint("Which payment method do you want to choose?");
        centerPrint("1. Touch And Go     ");
        centerPrint("2. Online Banking   ");
        centerPrint("3. Credit/Debit Card");
        centerPrint("4. Cash on delivery ");

        cin >> selection;
        system("cls");
        //allow buyer to choose 
        switch (selection) {
        case 1:
            centerPrint("Enter your TNG phone number:");
            cin >> phoneNumber;
            outfile << "Touch And Go Phone Number: " << phoneNumber << endl;
            break;
        case 2:
            centerPrint("Enter your online bank: ");
            cin.ignore();
            getline(cin, onlineBank);
            outfile << "Online Bank: " << onlineBank << endl;
            centerPrint("Enter your online banking number: ");
            cin >> number;
            outfile << "Online Banking Number: " << number << endl;
            break;
        case 3:
            centerPrint("Enter your Credit/Debit Card number: ");
            cin >> creditNumber;
            outfile << "Credit/Debit Card Number: " << creditNumber << endl;
            break;
        case 4:
            centerPrint("Enter your home address: ");
            cin.ignore();
            getline(cin, address);
            outfile << "Home Address: " << address << endl;
            break;
        default:
            centerPrint("Invalid selection!");
            break;
        }

        outfile.close();
        cout << endl;
        centerPrint("Payment Successfully!");
        cout << endl;
    }

}


void deleteProduct() {
    //allow admin to delete product
    string selection;
    int noWant;
    bool select = true;

    while (select) {
        showProduct();

        centerPrint("Which product do you want to delete? Enter the product number: ");
        cin >> noWant;

        if (noWant - 1 >= 0 && noWant - 1 < total_item) {
            item[noWant - 1] = "";
            price[noWant - 1] = 0;
            stock[noWant - 1] = 0;

            centerPrint("Product deleted.");
        }
        else {
            centerPrint("Invalid product number. Please enter a valid product number.");
        }


        outfile.close();
        outfile.open("list.txt", ios::out | ios::trunc);

        for (int i = 0; i < total_item; i++) {
            if (!item[i].empty()) {
                outfile << item[i] << endl;
                outfile << price[i] << endl;
                outfile << stock[i] << endl;
            }
        }



        centerPrint("Do you want to delete product again? (Y/N): ");
        cin >> selection;

        if (selection == "Y" || selection == "y") {
            select = true;
        }
        else {

            select = false;
        }
    }
}


void showProduct() {
    for (int i = 0; i < total_item; i++) {
        cout << (i + 1) << ") " << item[i] << endl;
        cout << "RM " << price[i] << endl;
        cout << "Stock: " << stock[i] << endl;
        cout << endl;
    }
    system("pause");
}


void addToCart() {
    // Display all the products first.
    showProduct();

    centerPrint("Do you want to:             ");
    centerPrint("1. Add Items to Cart        ");
    centerPrint("2. View Cart and Purchase   ");
    centerPrint("3. Exit to Main Menu        ");
    int choice;
    cin >> choice;
    system("cls");
    switch (choice) {
    case 1:
    {
        showProduct();
        centerPrint("Enter the product number you want to add to the cart: ");
        int productNumber;
        cin >> productNumber;

        if (productNumber > 0 && productNumber <= total_item) {
            centerPrint("Enter the quantity: ");
            int quantity;
            cin >> quantity;

            if (stock[productNumber - 1] >= quantity) {
                cartItems[cartCount] = item[productNumber - 1];
                cartPrices[cartCount] = price[productNumber - 1];
                cartQuantities[cartCount] = quantity;
                stock[productNumber - 1] -= quantity; // Reduce stock
                cartCount++;

                // Update stock values in the file
                outfile.open(FILENAME, ios::out | ios::trunc);
                for (int i = 0; i < total_item; i++) {
                    outfile << item[i] << endl;
                    outfile << price[i] << endl;
                    outfile << stock[i] << endl;
                }
                outfile.close();

                centerPrint("Product added to cart!");
                system("PAUSE");
                system("CLS");
            }
            else {
                centerPrint("Sorry, there's not enough stock for your request.");
            }
        }
        else {
            centerPrint("Invalid product number.");
        }
        break;
    }
    case 2:
        viewCart();
        purchaseProducts();  // Assuming you have this function already
        break;
    case 3:
        break;
    default:
        centerPrint("Invalid choice. Try again.\n");
        break;
    }
}


void managefeedback() {
    string comment;
    ifstream infile("FEEDBACK.txt", ios::app);
    int i = 0;

    if (infile.is_open()) {
        while (!infile.eof()) {
            cout << "                           Buyer " << i << endl;
            centerPrint("Leave the comment below : ");
            getline(infile, comment);

            centerPrint(comment);
            i++;

        }
    }
    else {
        centerPrint("Cannot open the file! Make sure the txt file have inside the folder!");

    }
    system("PAUSE");





}


void provideFeedback() {
    ofstream outfile("feedback.txt", ios::app);
    string comment;
    centerPrint("Please leave a comment here : ");
    cin.ignore();
    getline(cin, comment);
    system("cls");
    outfile << comment << endl;
    centerPrint("You have left a comment: ");
    cout << "                              " << comment << endl;
    centerPrint("Thank you for your comment. We will improve our service as soon as possible!");
    system("PAUSE");
    system("cls");
    outfile.close();
}


void viewCart() {
    double cartTotal = 0;
    centerPrint("--------------------- Your Cart--------------------");
    for (int i = 0; i < cartCount; i++) {
        cout << i + 1 << ". " << cartItems[i] << " ----- RM" << cartPrices[i] << " x " << cartQuantities[i] << " = RM" << (cartPrices[i] * cartQuantities[i]) << endl;
        cartTotal += cartPrices[i] * cartQuantities[i];
    }
    centerPrint("Total Price:(RM):");
    cout << " " << cartTotal << endl;
    if (cartTotal != 0) {

        centerPrint("Do you want to purchase these items? (Y/N):");
        char decision;
        cin >> decision;
        if (toupper(decision) == 'Y') {
            purchaseProducts();
        }
        else {
            centerPrint("Purchase cancelled.");
        }

    }
    else {
        centerPrint("No items in the cart ! Please add the items first !");
    }
    cout << endl;



}


void loadProducts() {

    infile.open(FILENAME);
    total_item = 0;

    while (getline(infile, item[total_item]) &&
        infile >> price[total_item] &&
        infile >> stock[total_item]) {
        total_price += price[total_item];
        total_stock += stock[total_item];
        total_item++;
        infile.ignore();
    }

    infile.close();
}


void purchaseProducts() {
    char decision;
    centerPrint("Do you want to proceed to payment page? (Y/N): ");
    cin >> decision;

    if (toupper(decision) == 'Y') {
        managePayment();
        cartCount = 0; // Emptying the cart after the purchase
    }
    else {
        centerPrint("Purchase cancelled.");
    }
}


void setWindowSize(int width, int height) {
    HANDLE hOut;
    COORD NewSize;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    NewSize.X = width;
    NewSize.Y = height;
    SetConsoleScreenBufferSize(hOut, NewSize);
}



