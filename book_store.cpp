#include <iostream>
#include <string>

using namespace std;

class book{
	
	private:
	string title;
	string isbn;
	double price;
	int stok;
	
    public:
    
    book(){
    	title=" ";
    	isbn=" ";
    	price=0.0;
    	stok=0;
	}
	
	book(const string& title, const string& isbn,double price,int stok=0){
		
		this->title=title;
		this->isbn=isbn;
		this->price=price;
		this->stok=stok;
	}
	
	string getTitle()const{ return title;
	}
	string getIsbn()const{ return isbn;	
	}
	double getprice()const{ return price;
	}
	int getstok()const{ return stok;
	}

	void setprice( double price){ this->price=price;	
	}
	void addstok(int n){
		if(n>=0)
			stok=stok+n;				
	}
	void removestok(int n){
		if(stok>0 && (stok-n)>=0)
			stok=stok-n;	
	}
	
	bool operator==(book& a){
		 return (isbn==a.getIsbn())	;
	}
	
	book operator+=(int n){
		if(n>0)
			stok+=n;
			
		return *this;
	}

	book operator-=(int n){
		if(stok>0 && stok-n>=0)
			stok-=n;
		
		return *this;
		
	}
	
	friend ostream& operator<<(ostream& out,const book& a);
	friend istream& operator>>(istream& is,book& a);
	
};

ostream& operator<<(ostream& out,const book& a){
	
	out<<"title: "<<a.getTitle()<<endl;
	out<<"isbn: "<<a.getIsbn()<<endl;
	out<<"price: "<<a.getprice()<<endl;
	out<<"stok: "<<a.getstok()<<endl;
	
	return out;
}

istream& operator>>(istream& is, book& b) {
        cout << "Title: "; is >> b.title;
        cout << "ISBN: "; is >> b.isbn;
        cout << "Price: "; is >> b.price;
        cout << "Stok: "; is >> b.stok;
        return is;
}


class writer{
	
	private:
	string name;
	book* catalog;
	int size;
	int capacity;
	static double totalrevenue;
	
	public:
	
	writer() {}

	writer(const string& name)
    {
    	this->name = name;
    	size = 0;
    	capacity = 1;
    	catalog = new book[capacity];
    }

	writer(const string& name, int capacity)
	{
		this->name=name;
		this->capacity=capacity;
		size=0;
		catalog = new book[capacity];
	
	}
	
	~writer(){
		delete []catalog;
	}
	
	writer(const writer& other){

     name = other.name;
     capacity = other.capacity;
     size = other.size;

     catalog = new book[capacity];

     for(int i = 0; i < size; i++)
        catalog[i] = other.catalog[i];
    }

	int getsize(){return size;
	}
	const string& getName() const{return name;
	}
	 
	writer& operator=(const writer& other){
	 	name=other.name;
		capacity=other.capacity;
		size=other.size;
		catalog=new book[other.size];
		for(int i=0;i<other.size;i++){
	
			catalog[i]=other.catalog[i];
		}
	 	return *this;
	 }
	void ensureCapacity(int mincapacity){

     if(mincapacity > capacity){

        int newCapacity = (capacity == 0) ? 1 : capacity * 2;

        book* newcatalog = new book[newCapacity];

        for(int i = 0; i < size; i++)
            newcatalog[i] = catalog[i];

        delete[] catalog;
        catalog = newcatalog;
        capacity = newCapacity;
      }
    }   

	int indexOfIsbn(const string& a) const{
     for(int i=0;i<size;i++){
        if(a == catalog[i].getIsbn())
            return i;
     }
     return -1;
    }

	void removeAt(int idx){
	 	
	 	for(int i = idx; i < size - 1; i++)
    		catalog[i] = catalog[i+1];
		size--;
		book* newcatalog=new book[size];
	 	for(int i=0;i<(size);i++){
	 	  newcatalog[i]=catalog[i];
		}
		delete [] catalog;
	 	book* catalog=new book[size];
		for(int i=0;i<size;i++){
		  catalog[i]=newcatalog[i];
		}
		delete []newcatalog;
		
	 }
	 
	
	book& findByIsbn(const string& a){
     for(int i = 0; i < size; i++){
        if(catalog[i].getIsbn() == a){
            return catalog[i];  
        }
     }
    
    }

	int sell(const string& isbn, int qty){

     for(int i = 0; i < size; i++){

        if(catalog[i].getIsbn() == isbn){

            if(catalog[i].getstok() >= qty){

                catalog[i].removestok(qty);  
                totalrevenue += qty * catalog[i].getprice();

                return catalog[i].getstok();
            }
            else{
                cout << "Not enough stock!" << endl;
                return -1;
            }
        }
    }

    cout << "Book not found!" << endl;
    return -1;
   }


	void purgeEmpty(){
     for(int i=0;i<size;i++){
        if(catalog[i].getstok()== 0){
            removeAt(i);
            i--;
        }
     }
    }

	static double getTotalRevenue(){ return totalrevenue;
	}
	
	writer& operator+=(const book& b) {
        int idx = indexOfIsbn(b.getIsbn());
        if (idx != -1) {
            catalog[idx] += b.getstok();
        } else {
            ensureCapacity(size + 1);
            catalog[size++] = b;
        }
        return *this;
    }
    
    writer& operator-=(const string& isbn) {
        int idx = indexOfIsbn(isbn);
        if (idx != -1)
            removeAt(idx);
        return *this;
    }
	book& operator[](int i) {
        if (i < 0 || i >= size) {
            cout << "Index out of bounds!\n";
            exit(1);
        }
        return catalog[i];
    }
    bool operator<(const writer& other) const {
        return size < other.size;
    }
    
    friend ostream& operator<<(ostream& os, const writer& w) ;
	
};

double writer::totalrevenue = 0.0;

ostream& operator<<(ostream& os, const writer& w) {
	
    os <<endl<<"Writer: " << w.name <<endl<< "Books:"<<endl;
    for (int i = 0; i < w.size; i++)
        os << w.catalog[i] << endl;
    return os;
}

int main() {

    int maxWriters;
    cout << "How many writers will be created? ";
    cin >> maxWriters;

    writer** writers = new writer*[maxWriters];   
    int writerCount = 0;

    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Create writer\n";
        cout << "2. Add/update book\n";
        cout << "3. Sell book\n";
        cout << "4. Remove out-of-stock books\n";
        cout << "5. Display writer info\n";
        cout << "6. Show statistics\n";
        cout << "7. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {

            if (writerCount >= maxWriters) {
                cout << "Writer capacity reached!\n";
                continue;
            }

            string name;
            cout << "Writer name: ";
            cin >> name;

            writers[writerCount++] = new writer(name);   
            cout << "Writer created successfully.\n";
        }

        else if (choice == 2) {

            string name;
            cout << "Writer name: ";
            cin >> name;

            bool found = false;

            for (int i = 0; i < writerCount; i++) {
                if (writers[i]->getName() == name) {

                    book b;       
                    cin >> b;
                    *writers[i] += b;

                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Writer not found!\n";
        }

        else if (choice == 3) {

            string name, isbn;
            int qty;

            cout << "Writer name: ";
            cin >> name;
            cout << "ISBN: ";
            cin >> isbn;
            cout << "Quantity: ";
            cin >> qty;

            bool found = false;

            for (int i = 0; i < writerCount; i++) {
                if (writers[i]->getName() == name) {

                    int result = writers[i]->sell(isbn, qty);

                    if (result >= 0)
                        cout << "Sale successful. Remaining stock: " << result << endl;
                    else
                        cout << "Sale failed.\n";

                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Writer not found!\n";
        }

        else if (choice == 4) {

            string name;
            cout << "Writer name: ";
            cin >> name;

            for (int i = 0; i < writerCount; i++) {
                if (writers[i]->getName() == name) {
                    writers[i]->purgeEmpty();
                    cout << "Empty books removed.\n";
                    break;
                }
            }
        }

        else if (choice == 5) {

            for (int i = 0; i < writerCount; i++)
                cout << *writers[i] << endl;
        }

        else if (choice == 6) {

            if (writerCount == 0) {
                cout << "No writers available.\n";
                continue;
            }

            cout << "Total Revenue: "
                 << writer::getTotalRevenue() << endl;  

            writer* maxWriter = writers[0];  

            for (int i = 1; i < writerCount; i++) {
                if (*maxWriter < *writers[i])
                    maxWriter = writers[i];
            }

            cout << "Writer with most books: "
                 << maxWriter->getName() << endl;
        }

    } while (choice != 7);


    for (int i = 0; i < writerCount; i++)
        delete writers[i];

    delete[] writers;

    cout << "Program terminated successfully.\n";

    return 0;
}


