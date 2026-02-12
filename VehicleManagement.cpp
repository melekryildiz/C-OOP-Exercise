#include<iostream>
#include<string>

using namespace std;



class vehicle{
	
	
	
		
	
	public:
		string manifacturer;
		int cylinders;
	
		vehicle(){
			manifacturer=" ";
			cylinders=0;
		}	
		
		vehicle(string manifacturer,int cylinders){
			
			this->manifacturer=manifacturer;
			this->cylinders=cylinders;
		}
		
		vehicle(const vehicle& a){
			
			manifacturer=a.manifacturer;
			cylinders=a.cylinders;
			
		}
		
		vehicle& operator=(const vehicle&a){
			manifacturer=a.manifacturer;
			cylinders=a.cylinders;
			
			return *this;
		}
		
		bool operator == (vehicle& a){
			
			if((a.cylinders==cylinders)&&(a.manifacturer==manifacturer))
			{
				return true;
			}
			
			
			else
			return false;
		}
		
		string getmanifacturer()const{return manifacturer;
		}	
		int getcylinders()const{return cylinders;
		}
		void setmanifacturer(string& manifact){
			
			manifacturer=manifact;
			
		}
		void setcylinders(int cyl){
			cylinders=cyl;
		}
	friend	ostream& operator<<(ostream& os,const vehicle& a);
	friend	istream& operator>>(istream& is,vehicle& a);
	
};

ostream& operator<<(ostream& os,const vehicle& a   ){
	
	os<<" "<<a.cylinders<<endl;
	os<<" "<<a.manifacturer<<endl;
	
	return os;
	
}

istream& operator>>(istream& in, vehicle& a){
	
	in>>a.cylinders;
	in>>a.manifacturer;
	
	return in;
	
}


class truck:public vehicle{
	
private:
	double load;
	int towing;
	
public:
		
	truck()
	{
		load=0.0;
		towing=0;
	}
		
	truck(double load,int towing,string manifacturer,int cylinders):vehicle(manifacturer,cylinders){
			
		this->load=load;
		this->towing=towing;
		
	}
		
	truck(const truck& a):vehicle(a){
			
		load=a.load;
		towing=a.towing;
			
	}
	
	truck& operator=(const truck& a){
		if(&a!= this){
		
		manifacturer=a.manifacturer;
		cylinders=a.cylinders;
		load=a.load;
		towing=a.towing;
	}
		
		return *this;
		
	}
		
	double getload()const{return load;
	}
	int gettowing()const{return towing;
	}
	void setload(double a){load=a;
	}
	void settowing(int a){towing=a;
	}
	
	bool operator==(const truck& a)const{
		
		if(a.cylinders==cylinders&&a.manifacturer==manifacturer&&a.load==load&&a.towing==towing){
			
			return true;
		}
		else 
		return false;
		
	}
	bool operator<(const truck& a) const {
    return towing < a.towing;
	}
	
	truck operator+(const truck& a) const {
    	truck temp(*this);
    	temp.load += a.load;
    	temp.towing += a.towing;
    	return temp;
	}
			
	
	friend ostream& operator<<(ostream& os,const truck& a);
	
	friend	istream& operator>>(istream& is,truck& a);
	
	
	
	
	
	
};

ostream& operator<<(ostream& os,const truck& a){
	
	os<<" "<<a.getcylinders()<<endl;
	os<<" "<<a.getmanifacturer()<<endl;
	os<<" "<<a.gettowing()<<endl;
	os<<" "<<a.getload()<<endl;
	
	return os;
	
	
}

istream& operator>>(istream& is,truck& a){
	
	int cyl,tow;
	double lo;
	string man;
	is>>cyl;
	is>>lo;
	is>>man;
	is>>tow;
	
	
	a.setcylinders(cyl);
	a.setload(lo);
	a.setmanifacturer(man);
	a.settowing(tow);
	
	return is;
	
	
}

int main(void){
	
	truck t1, t2;

    cout << "Enter first truck information:\n";
    cin >> t1;

    cout << "\nEnter second truck information:\n";
    cin >> t2;

    cout << "\n Truck 1 \n";
    cout << t1;

    cout << "\n Truck 2 \n";
    cout << t2;

	if (t1 == t2)
        cout << "\nTrucks are equal.\n";

    if (t1 < t2)
        cout << "Truck 1 has smaller towing capacity than Truck 2.\n";

    truck t3 = t1 + t2;

    cout << "\n   Combined Truck (t1 + t2)   \n";
    cout << t3;

	
	return 0;
}
