#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Person
{
string name;
string lastName;
string idNumber;
string currentBooks;
string totalBarrowed;
};

struct Book
{
string bookId;
string bookName;
string totalCopies;
string availableCopies;
};

struct Barrow
{
string personId;
string bookId;
string bookName;
string copyNumber;
string dateBorrowed;
string dateReturned;
string status;
};

vector<Person> allStudents;
vector<Book> allBooks;
vector<Barrow> allBorrows;

void creatFiles (){
ofstream personfile("person.txt",ios::app);
if (personfile.tellp() == 0) personfile << "Name | LastName | IdNumber | currentBooks | TotalBarrowed " << endl;
personfile.close();
ofstream bookfile("book.txt",ios::app);
if (bookfile.tellp() == 0) bookfile << " BookId | BookName | TotalCopies | AvailableCopies " << endl;
bookfile.close();
ofstream barrowfile ("barrow.txt",ios::app);
if (barrowfile.tellp() == 0) barrowfile << "personId | BookId | BookName | CopyNumber | DateBorrowed | DateReturned |status" << endl;
barrowfile.close();
}

void loadFiles (){
ifstream personfile("person.txt");
ifstream bookfile("book.txt");
ifstream barrowfile("barrow.txt");
string line;
getline(personfile, line);
while (getline(personfile, line)){
    stringstream ss(line);
    Person p;
    getline(ss,p.name , '|');
    getline(ss,p.lastName , '|');
    getline(ss,p.idNumber ,'|');
    getline(ss,p.currentBooks , '|');
    getline(ss,p.totalBarrowed , '|');
    allStudents.push_back(p);
}

getline(bookfile, line);
while (getline(bookfile, line)){
    stringstream ss(line);
    Book B;
    getline(ss,B.bookId , '|');
    getline(ss,B.bookName , '|');
    getline(ss,B.totalCopies , '|');
    getline(ss,B.availableCopies , '|');
    allBooks.push_back(B);
}

getline(barrowfile, line);
while (getline(barrowfile, line)){
    stringstream ss(line);
    Barrow b;
    getline(ss,b.personId , '|');
    getline(ss,b.bookId , '|');
    getline(ss,b.bookName , '|');
    getline(ss,b.copyNumber , '|');
    getline(ss,b.dateBorrowed , '|');
    getline(ss,b.dateReturned , '|');
    getline(ss,b.status , '|');
    allBorrows.push_back(b);    
}
personfile.close();
bookfile.close();
barrowfile.close();
}

void AddPerson (Person p){
ofstream personfile("person.txt",ios::app);
personfile << p.name << " | " << p.lastName << " | " << p.idNumber << " | " << p.currentBooks << " | " << p.totalBarrowed << endl;
personfile.close();
}

void deletePerson (string idNumber){
ofstream temp("temp.txt");
ifstream personfile("person.txt");
string line;
getline(personfile, line);
temp << line << endl;
while (getline(personfile, line)){
    stringstream ss(line);
    Person p;
    getline(ss,p.name , '|');
    getline(ss,p.lastName , '|');
    getline(ss,p.idNumber ,'|');
    getline(ss,p.currentBooks , '|');
    getline(ss,p.totalBarrowed , '|');
    if (p.idNumber != idNumber) temp << line << endl;
}
personfile.close();
temp.close();
remove("person.txt");
rename("temp.txt", "person.txt"); 
}

void PersonInfo (string idNumber){
ifstream personfile("person.txt");
string line;
getline(personfile, line);
while (getline(personfile, line)){
    stringstream ss(line);
    Person p;
    getline(ss,p.name , '|');
    getline(ss,p.lastName , '|');
    getline(ss,p.idNumber ,'|');
    getline(ss,p.currentBooks , '|');
    getline(ss,p.totalBarrowed , '|');
    if (p.idNumber == idNumber) cout << p.name << " | " << p.lastName << " | " << p.idNumber << " | " << p.currentBooks << " | " << p.totalBarrowed << endl;
}
personfile.close();
}

void ShowPersonFile (){
    ifstream personFile("person.txt");
    string line ;
    while (getline (personFile,line))cout << line << endl;
    personFile.close();
}

void UpdateBookFile(){
    ofstream bookFile ("book.txt");
    bookFile << "BookId | BookName | TotalCopies | AvailabaleCopies"<<endl;
    for (Book &b : allBooks){
        bookFile << b.bookId << "|" << b.bookName << "|" << b.totalCopies << "|" << b.availableCopies << endl;
    }
    bookFile.close();
}

void AddBook (Book B){
bool found = false ;
string line  ;
for (Book &b : allBooks){
if (B.bookId == b.bookId){
    int total = stoi(b.totalCopies) + stoi(B.totalCopies);
    int avail = stoi(b.availableCopies) + stoi(B.availableCopies);
    b.availableCopies = to_string (avail);
    b.totalCopies = to_string (total);
    
    found = true;
    break;
}}
if (!found){
    allBooks.push_back(B);
}
UpdateBookFile () ;
}

void DeletBook(Book B){
    for (int i = 0; i < allBooks.size(); i++){
        if (allBooks[i].bookId == B.bookId){
            allBooks.erase(allBooks.begin() + i);
            UpdateBookFile();
            cout << "Book deleted" << endl;
            return;
        }
    }

    cout << "Book not found" << endl;
}




int main(){
    creatFiles();
    loadFiles();
int MainMenu , personMenu , bookMenu , barrowMenu;
bool MainMenuExit = false ;
do{
    bool PersonMenuExit = false , BookMenuExit = false , BarrowMenuExit = false;
    cout<<"---<MAIN MENU>---"<<endl;
    cout<<"1-Person Menu"<<endl;
    cout<<"2-Book Menu"<<endl;
    cout<<"3-Barrow Menu"<<endl;
    cout<<"0-Exit and close"<<endl;
    cout<<"---> ";
cin >> MainMenu;
switch (MainMenu){
case 1:{
    do{
    cout<<"---<PERSON MENU>---"<<endl;
    cout<<"1-Add person"<<endl;
    cout<<"2-Delete person"<<endl;
    cout<<"3-Person info"<<endl;
    cout<<"4-Show all person"<<endl;
    cout<<"0-Exit person menu"<<endl;
    cout<<"---> ";
    cin >> personMenu;
    switch (personMenu)
    {
    case 1:{
        Person p;
        cin.ignore();
        cout<<"Enter person name : ";
        getline (cin , p.name);
        cout<<"Enter person last name : ";
        getline (cin , p.lastName);
        cout<<"Enter person id number : ";
        getline (cin , p.idNumber);
        cout<<"Enter person current books : ";
        getline (cin , p.currentBooks);
        cout<<"Enter person total barrowed : ";
        getline (cin ,p.totalBarrowed);
        allStudents.push_back(p);
        AddPerson(p);
        break;
    }
    case 2:{
        string idNumber;
        cin.ignore();
        cout<<"Enter person id number : ";
        getline (cin , idNumber);
        deletePerson(idNumber);
        break;
    }
    case 3:{
        string idNumber;
        cin.ignore();
        cout<<"Enter person id number : ";
        getline (cin , idNumber);
        PersonInfo(idNumber);
    break;
    }
    case 4:{
        ShowPersonFile ();
        break;
    }
    case 0:{
        PersonMenuExit = true ;
        break;
    }
    default:
    cout<<"Invalid input"<<endl;
        break;
    }
    }while (!PersonMenuExit);
    break;
}
case 2:{
do{
    cout<<"---<BOOK MENU>---" << endl;
    cout<<"1-add book" << endl;
    cout<<"2-delet book" << endl;
    cout<<"3-book info" << endl;
    cout<<"4-show all book" << endl;
    cout<< "--->" << endl;
    cin >> bookMenu ;
    switch (bookMenu){
    case 1:{
        Book B;
        cin.ignore();
        cout<< "Enter the id of book : " << endl;
        getline(cin,B.bookId);
        cout<< "Enter the name of the book : " << endl;
        getline(cin,B.bookName);
        cout<< "Enter the number of the copys : " << endl;
        getline(cin,B.totalCopies);
        B.availableCopies = B.totalCopies;
        AddBook(B);
        break;
    }
    case 2:{
        Book B ;
        cin.ignore();
        cout << "Enter the id you  want to delet : " << endl;
        getline(cin,B.bookId);
        DeletBook(B);
        break;
    }
    case 3:{
        


    }


    case 0:{
        BookMenuExit = true ;
        break;
    }

    default:
        break;
    }


}while (!BookMenuExit);








}






}







}while (!MainMenuExit);
    return 0;
}




