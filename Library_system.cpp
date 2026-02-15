#include <iostream>
#include <string>

using namespace std;

class item{
	
	private:
		string title;
		
	public:
		 item(string title="untitled"){
		 	this->title=title;
		 }
		 
		 virtual void display(){
		 	cout<<endl<<"title:"<<title<<endl;
		 }
	
	friend class book;
};

class book: public item{
	
	private:
		
		int pages;
		int isbn;
		string author;
		int yearpub;
		
	public:
		
		book(string title = "Untitled", int isbn= 0, int yearpub= 0, string author= "Unknown", int pages = 0): item("untitled"){ 
			  this->author=author;
			  this->isbn=isbn;
			  this->pages=pages;
			  this->yearpub=yearpub; 	 
		}
	
	    void display () override {	
	    	cout<<endl<<"title: "<<endl<<"author: "<<author<<endl<<"pages: "<<pages<<endl<<"isbn: "<<isbn<<endl;	
		}
	
	friend class item;
	friend class library;
	
};


class librarian{
	
	private:
		string name;
		int id;
		
	public:
		
		librarian (string name= "Unnamed", int id = 0){
			this->name=name;
			this->id=id;
		}
		
		void setname(string n){ name=n;
		}
		
		void setid(int i){ id=i;
		}
		
		void display() {
			cout<<endl<<"name: "<<name<<endl<<"id: "<<id<<endl;
		}

};

class library{
	
	private:
		book* books;
		int size;
		librarian lib;
		
	public:
		
		library(int size,string name,int id){
			this->size=size;
			books=new book [size];
			lib.setname(name);
			lib.setid(id);
			
		}
		
		~library(){
			delete [] books ;
			cout<<endl<<"Library memory released";
		}
	
		void showlibrarian(){
			lib.display();	
		}
		
		int getsize(){ return size;
		}
		
		book& operator[](int n){
			
			if( n<0 || n>size-1){
				cout<<endl<<"invalid index";
			}	
			else
			    return books[n];
		}
	
	
	
	
};

int main() {

    int n, choice;
    string librarianName;
    int librarianID;

    cout << "===== LIBRARY MANAGEMENT SYSTEM =====" << endl;

    cout << "How many books will the library hold? ";
    cin >> n;

    cout <<endl<< "Enter librarian name: ";
    cin >> librarianName;

    cout <<endl<<"Enter librarian ID: ";
    cin >> librarianID;

    library li(n, librarianName, librarianID);

    do {
        cout <<endl<< "========== MENU ==========" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Show All Books" << endl;
        cout << "3. Show Librarian Info" << endl;
        cout << "4. Exit" << endl;
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            int index;
            cout <<endl<<"Enter book position (0 - " << li.getsize() - 1 << "): ";
            cin >> index;

            if (index < 0 || index >= li.getsize()) {
                cout <<endl<<"Invalid index!" << endl;
                break;
            }

            string title, author;
            int pages, isbn, year;

            cout <<endl<<"Title: ";
            cin >> title;

            cout <<endl<< "Author: ";
            cin >> author;

            cout <<endl<< "Pages: ";
            cin >> pages;

            cout <<endl<<"ISBN: ";
            cin >> isbn;

            cout <<endl<<"Year: ";
            cin >> year;

            li[index] = book(title, isbn, year, author, pages);

            cout <<endl<<"Book added successfully!" << endl;
            break;
        }

        case 2:
            cout <<endl<< "===== BOOK LIST =====" << endl;
            for (int i = 0; i < li.getsize(); i++) {
                cout <<endl<<"Book " << i + 1 << endl;
                li[i].display();
            }
            break;

        case 3:
            cout <<endl<< "===== LIBRARIAN INFO =====" << endl;
            li.showlibrarian();
            break;

        case 4:
            cout <<endl<< "Exiting system..." << endl;
            break;

        default:
            cout <<endl<< "Invalid choice! Please try again." << endl;
        }

    } while (choice != 4);

    return 0;
}
