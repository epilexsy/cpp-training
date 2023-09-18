// Library management system
#include <iostream>
#include <string>
#include <vector>

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define GRAY    "\033[90m"

#define CLS     "\033[2J\033[H"
#define DIVIDER "-----------------------------------------"

void cls(){
    std::cout << CLS;
}

std::string input(const std::string prompt, bool multiword=true){
    std::string input_;
    std::cout << prompt;
    if(multiword){
        std::cin >> std::ws;
        std::getline(std::cin, input_);
    }
    else {
        std::cin >> input_;
    }
    return input_;
}

void print(std::string text="\n", bool sticky=false, std::string color=RESET){
    text = color + text + RESET;

    std::cout << text;
    if (!sticky and text != "\n"){
        std::cout << "\n";
    }
}

void grayprint(std::string text="\n", bool sticky=false, std::string color=GRAY){print(text, sticky, color);}
void errorprint(std::string text="\n", bool sticky=false, std::string color=RED){print(text, sticky, color);}
void notifprint(std::string text="\n", bool sticky=false, std::string color=GREEN){print(text, sticky, color);}
void blueprint(std::string text="\n", bool sticky=false, std::string color=BLUE){print(text, sticky, color);}
void yellowprint(std::string text="\n", bool sticky=false, std::string color=YELLOW){print(text, sticky, color);}


class Book {
public:
    std::string name;
    std::string author;

    Book(std::string name_, std::string author_){
        name = name_;
        author = author_;
    }
};

class UserAccount {
private:
    bool admin_privilege;
    std::string password;
    
public:
    std::string username;
    std::vector<Book*> books;

    UserAccount(std::string username, std::string password, bool admin_privilege = false){
        this->username = username;
        this->password = password;
        this->admin_privilege = admin_privilege;
    }

    bool checkPassword(std::string password){
        if (this->password == password){
            return true;
        }
        return false;
    }

    bool setPassword(std::string oldPassword, std::string password){
        if (checkPassword(oldPassword) == true){
            this->password = password;
            return true;
        }
        return false;
    }

    bool getAdminPrivilege(){
        return admin_privilege;
    }

    void setAdminPrivilege(bool i){
        admin_privilege = i;
    }

    void giveBook(Book* book){
        books.push_back(book);
    }

    Book* takeBook(int index){
        Book* book = books[index];
        books.erase(books.begin()+index);
        return book;
    }

    void displayBooks(){
        int i = 0;
        if(books.size()){
            for (Book* book : books){
                print(std::to_string(++i) + ". '"+book->name+"' by "+book->author);
            }
        }
        else {
            print("EMPTY");
        }
    }

    ~UserAccount(){
        for (Book* book : books){
            delete book;
        }
    }

};


class Library {
public:
    static const int MAX_ACCOUNT_LIMIT = 10;
    
    std::vector<UserAccount*> accounts;
    std::vector<Book*> books;

    Library() {
        accounts.push_back(new UserAccount("root", "root", true));
    }

    UserAccount* getAccount(std::string username){
        for (UserAccount* account : accounts){
            if (account->username == username){
                return account;
            }
        }
        return NULL;
    }

    UserAccount* addAccount(std::string username, std::string password){
        if (getAccount(username)){
            return NULL;
        }
        if (accounts.size() < MAX_ACCOUNT_LIMIT){
            accounts.push_back(new UserAccount(username, password));
            return accounts.back();
        }
        return NULL;
    }

    bool deleteAccount(const std::string username) {
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if ((*it)->username == username) {
                delete *it;
                accounts.erase(it);
                return true;
            }
        }
        return false;
    }

    void giveBook(std::string username, Book* book){
        getAccount(username)->giveBook(book);
    }

    Book* takeBook(std::string username, int index){
        UserAccount* acc = getAccount(username);
        if (index < acc->books.size()){
            return acc->takeBook(index);
        }
        return NULL;
    }

    Book* getBook(std::string name){
        for (Book* book : books){
            if (book->name == name){
                return book;
            }
        }
        return NULL;
    }

    Book* addBook(std::string name, std::string author){
        if (!getBook(name)){
            books.push_back(new Book(name, author));
            return books.back();
        }
        return NULL;
    }

    bool deleteBook(const std::string name) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if ((*it)->name == name) {
                delete *it;
                books.erase(it);
                return true;
            }
        }
        return false;
    }

    void displayBooks() {
        int i = 0;
        if(books.size()){
            for (Book* book : books){
                print(std::to_string(++i) + ". '"+book->name+"' by "+book->author);
            }
        }
        else {
            print("EMPTY");
        }
    }

    void displayUsers() {
        int i = 0;
        if (accounts.size()) {
            for (UserAccount* account : accounts){
                grayprint(std::to_string(++i) + ". ", true);
                print(account->username, true);
                yellowprint((account->getAdminPrivilege()) ? " (ADMIN)" : "", true);
                grayprint(" - [ISSUED: "+std::to_string(account->books.size())+"]");
            }
        }
        else {
            print("EMPTY");
        }
    }

    ~Library() {
        for (UserAccount* account : accounts){
            delete account;
        }

        for (Book* book : books){
            delete book;
        }
    }

    int menu(UserAccount* user){
        int choice;
        int index;
        std::string name;
        std::string author;

        while(true){
            grayprint("USER PANEL [", true);
            print(user->username, true);
            grayprint("]");
            grayprint(DIVIDER);
            print("1.  Logout");
            print("2.  Issue a book");
            print("3.  Return a Book");
            print("4.  Books in posession");

            if (user->getAdminPrivilege() == true) {
                blueprint(DIVIDER);
                blueprint("ADMIN OPTIONS");
                blueprint(DIVIDER);
                print("5.  Add a book to system");
                print("6.  Delete book from system");
                print("7.  Add User to system");
                print("8.  Delete User from system");
                print("9.  List un-issued books in system");
                print("10. List all system Users");
            }

            grayprint(DIVIDER);
            grayprint("> ", true);
            std::cin >> choice;
            
            cls();

            if (choice == 1) {
                return 0;
            }

            else if (choice == 2) {
                grayprint("-- Issue Book --\n");
                grayprint("Available books in library:");
                displayBooks();
                grayprint("\nEnter book index: ", true);

                std::cin >> index;
                index--;

                cls();

                if (index >= books.size()) {
                    errorprint("No such index exists.\n");
                    continue;
                }

                Book* book = books[index];
                books.erase(books.begin()+index);
                giveBook(user->username, book);
                
                cls();
                
                notifprint("Book '"+book->name+"' was issued!\n");
                continue;
            }

            else if (choice == 3) {
                grayprint("-- Return Book --\n");
                grayprint("Your issued books:");
                user->displayBooks();

                grayprint("\nEnter book index: ", true);
                std::cin >> index;

                index--;

                cls();

                if (index >= user->books.size()) {
                    errorprint("No such index exists.\n");
                    continue;
                }

                Book* book = user->takeBook(index);
                addBook(book->name, book->author);

                cls();

                notifprint("Book '"+book->name+"' was returned!\n");
                continue;

            }

            else if (choice == 4) {
                grayprint("-- Issued Books --");
                user->displayBooks();

                input("\n\n-- enter x to close: ");
                cls();
                continue;
            }

            else {
                if (user->getAdminPrivilege() != true){
                    errorprint("No such option\n");
                    continue;
                }
            }

            if (choice == 5) {
                grayprint("-- Add Book --");
                name = input("Name of book: ");
                author = input("Name of author: ");

                cls();

                if(addBook(name, author)){
                    notifprint("Book '"+name+"' was added!\n");
                }
                else{
                    errorprint("A book with this name already exists!\n");
                }
            }

            else if(choice == 6) {
                grayprint("-- Delete book from system --");
                displayBooks();
                name = input("\nName of book: ");

                cls();

                if(!deleteBook(name)){
                    errorprint("Book does not exist.\n");
                }
                else {
                    notifprint("Book '"+name+"' was deleted.\n");
                }
            }

            else if(choice == 7) {
                char admin_privilege;
                std::string username, password;
                
                grayprint("-- Add user to system --");
                username = input("\nEnter username: ", false);
                password = input("Enter password: ");

                yellowprint("Add ADMIN privileges? (y/n) : ", true);
                std::cin >> admin_privilege;

                cls();

                if (getAccount(username)){
                    errorprint("User already exists\n");
                    continue;
                }

                UserAccount* acc = addAccount(username, password);
                
                if(!acc){
                    errorprint("User account limit exceeded!\n");
                    continue;
                }

                (admin_privilege == 'y') ? acc->setAdminPrivilege(1) : acc->setAdminPrivilege(0);

                notifprint("User '"+username+"' added to system.\n");

            }

            else if(choice == 8) {
                std::string username;

                grayprint("-- Delete User from system --\n");
                grayprint("Existing users:");
                
                displayUsers();

                username = input("\nEnter username: ", false);

                cls();

                if (username == user->username) {
                    yellowprint("You cannot delete a currently operating account.\n");
                    continue;
                }

                if (!deleteAccount(username)) {
                    errorprint("No such account exists.\n");
                }
                else {
                    notifprint("User '"+username+"' was removed from system.\n");
                }


            }

            else if (choice == 9) {
                grayprint("Un-Issued books in system:");
                displayBooks();
                input("\n-- enter x to close: ");
                cls();

            }

            else if (choice == 10) {
                grayprint("Existing users in system:");
                displayUsers();
                input("\n-- enter x to close: ");
                cls();
            }

            else {
                errorprint("No such option exists.\n");
            }
        }
    }
};


int main(){
    int choice;
    std::string username;
    std::string password;
    
    Library* library = new Library();

    cls();

    while(true){
        grayprint("Library Management System");
        grayprint(DIVIDER);
        print("1. Exit");
        print("2. Login");
        print("3. Register");
        grayprint(DIVIDER);
        grayprint("> ", true);

        std::cin >> choice;

        cls();
        
        if (choice == 1)
            break;

        else if (choice == 2) {
            grayprint("-- LOGIN --");
            username = input("Enter username: ", false);
            password = input("Enter password: ");
            
            cls();

            UserAccount* acc = library->getAccount(username);

            if (!acc){
                errorprint("Username does not exist.\n");
                continue;
            }
            if(!acc->checkPassword(password)){
                errorprint("Wrong password.\n");
                continue;
            }
            notifprint("Login Succesful.\n");
            
            library->menu(acc);

            yellowprint("Logged out.\n");
            continue;
        }
        else if (choice == 3) {
            grayprint("-- REGISTER --");
            username = input("Enter username: ", false);
            password = input("Enter password: ");

            cls();

            if (library->getAccount(username)){
                errorprint("User already exists.\n");
                continue;
            }

            UserAccount* acc = library->addAccount(username, password);
            
            if(!acc){
                errorprint("User account limit exceeded.\n");
                continue;
            }

            notifprint("User registered and logged in.\n");

            library->menu(acc);
            
            continue;

        }
        else {
            errorprint("No such option exists.\n");
            continue;
        }

    }    

    delete library;
    return 0;
}