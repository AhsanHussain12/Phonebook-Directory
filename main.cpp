#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
#include<windows.h>  
#include<unistd.h>
#include"phonebook.h"
using namespace std;
int display();
int menu();
void generateusername(char[],char[],char[]);
int inRecord(char[]);

int inRecord(string username){
	ifstream fin("Records.txt");
	if (fin.is_open())
	{
		string line;
		while (getline(fin, line))
	    {
	    	if(line==username){
	    		fin.close();
				return 1;
			}
		}
	    
	}					
}


int menu(char name[100]){
	int select;
	system("cls");
	do{
	cout<<"\n\n\n\n\n\n\n\t\t\t\t\tWELCOME TO "<<name<<"'s PHONEBOOK DIRECTORY: \t\t\n\n";
	cout << "\t\t\t\t1) Add new contact \n";
	cout << "\t\t\t\t2) Update contact \n";
	cout << "\t\t\t\t3) Delete contact \n";
	cout << "\t\t\t\t4) Search contact \n";
	cout << "\t\t\t\t5) View all contacts \n";
	cout << "\t\t\t\t0) To Exit \n";
	cout << "\t\t\t\tEnter your choice: ";
	cin >> select;
}while(select<0||select>5);
return select;
}
void generateusername(char x[60],char y[50],char z[10]){
			strcpy(x,y);
			strcat(x,z);
			
}
int operations(char name[100], PhoneBook &obj)
{
	int select,update;
	char na[100],num[15],email[200];
	Contact *point, *duplicate;
	
	
	do{
		
		select=menu(name);
	switch(select)
	{
		//INSERT
		case 1:
			system("cls");
			fflush(stdin);
			cout << "\n\n\n\n\n\n\n\t\t\t\t\tADD CONTACT:\n\n";
			cout << "\t\t\t\t\tEnter Name: ";
			gets(na);
			while(strlen(na)==0)
			{
				cout << "\t\t\t\t\tName can not be empty, Re-enter: ";
				gets(na);
			}
			point=obj.SearchContact(na);
			if(point!=NULL){
				cout<<"\n\n\n\n\n\t\t\t\t\t|| Contact Already Exists ! ||\n";
				sleep(1);
				obj.display(point,1);
				break;
			}
			cout << "\t\t\t\t\tEnter Phone Number: ";
				do
				{
					fflush(stdin);
					gets(num);
					if(strlen(num)!=11)
					cout << "\t\t\t\t\tEnter Correct Phone Number: ";
					else  break;
				}while(strlen(num)!=11);
			fflush(stdin);
			cout << "\t\t\t\t\tEnter Email: ";
			gets(email);
			while(strlen(email)==0)
			{
				cout << "\t\t\t\t\tEmail can not be empty, Re-enter: ";
				gets(email);
			}
			obj.AddContact(na,num,email);
		break;
		
		//UPDATE
		case 2:
			{
			system("cls");
			fflush(stdin);
			cout << "\n\n\n\n\n\n\n\t\t\t\t\tUPDATE CONTACT:\n\n";
			cout << "\t\t\t\t\tEnter Name: ";
			gets(na);
			cout<< endl;
			while(strlen(na)==0)
			{
				cout << "\t\t\t\t\tName can not be empty, Re-enter: ";
				gets(na);
			}
			cout<< endl;
			point=obj.SearchContact(na); 
			if(point==NULL){
				cout<<"No Contact Exsits\n";
				system("pause");
				break;
			}
			obj.display(point,1);
			do
			{
			system("cls");
			cout << "\n\n\n\n\n\n\n\t\t\t\tUPDATE CONTACT:\n\n";
			cout << "\t\t\t\t1) Update Name \n";
			cout << "\t\t\t\t2) Update Number \n";
			cout << "\t\t\t\t3) Update Email \n";
			cout << "\t\t\t\t4) Back \n";
			cout << "\t\t\t\tEnter your choice: ";
			cin >> update;
			if(update==1)
			{
				cout << "\n\t\t\t\t\tEnter Name: ";
				fflush(stdin);
				gets(na);
				while(strlen(na)==0)
				{
					cout << "\t\t\t\t\tName can not be empty, Re-enter: ";
					gets(na);
				}
				duplicate=obj.SearchContact(na);
				if(duplicate==NULL){
				strcpy(point->name,na);
				}
				else{
					cout<<"Contact "<<duplicate->name<<" Already Exists!!"<<endl;
					obj.display(duplicate,1);
					break;
				}
				system("pause");
			}
			else if(update==2)
			{						
				cout << "\n\t\t\t\tEnter Phone Number: ";
				do
				{
					fflush(stdin);
					gets(num);
					if(strlen(num)!=11)
					cout << "\t\t\t\tEnter Correct Phone Number: ";
					else  break;
				}while(strlen(num)!=11);
				strcpy(point->number,num);
				system("pause");
			}
			else if(update==3)
			{
				fflush(stdin);
				cout << "\n\t\t\t\tEnter Email: ";
				gets(email);
				while(strlen(email)==0)
				{
					cout << "\t\t\t\t\tEmail can not be empty, Re-enter: ";
					gets(email);
				}
				strcpy(point->email,email);
				system("pause");
			}
				
			}while(update!=4);								
			obj.UpdateContact(point->name,point->number,point->email);
			}
		break;
		
		// Delete
		case 3:
			system("cls");
			fflush(stdin);
			cout << "\n\n\n\n\n\n\n\t\t\t\t\tDELETE CONTACT:\n\n";
			cout << "\t\t\t\t\tEnter Name: ";
			gets(na);
			cout<< endl;
			while(strlen(na)==0)
			{
				cout << "\t\t\t\t\tName can not be empty, Re-enter: ";
				gets(na);
			}
			cout << endl;
			point=obj.DeleteContact(na);
			if(point==NULL){
				cout<<"No Contact Exsits\n";
				system("pause");
				break;
			}
			cout << "\t\t\t\t\tContact deleted successfully!\n";
			system("pause");
		break;
		
		//SEARCH
		case 4:
			system("cls");
			cout << "\n\n\n\n\n\n\n\t\t\t\t\tSEARCH CONTACT:\n\n";
			cout << "\t\t\t\t\tEnter Name: ";
			fflush(stdin);
			gets(na);
			while(strlen(na)==0)
			{
				cout << "\t\t\t\t\tName can not be empty, Re-enter: ";
				gets(na);
			}
			point=obj.SearchContact(na);
			if(point!=NULL){
				obj.display(point,1);
				break;
			}
			else{
				obj.DisplaySimilarCon(na);
			}
		break;
		
		//DISPLAY CONTACTS
		case 5:
			point=obj.print();
			if(point==NULL){
				system("cls");
				cout<<"\n\n\n\n\n\t\t\t\t\t\t||EMPTY LIST||\n\n\n\n";
				system("pause");
				break;
			}
		break;
			
	}	
	
	}while(select!=0);
}
int display(){
	int x;
	system("cls");
	cout<<"\n\n\n\n\n\n\n\t\t\t\t_________________________________________\n";
	cout<<"\t\t\t\t|\t\tMAIN MENU: \t\t|\n\t\t\t\t|\t\t\t\t\t|\n";
	cout<<"\t\t\t\t|\t1) Create New Directory \t|\n";
	cout<<"\t\t\t\t|\t2) Open Existing Directory \t|\n";
	cout<<"\t\t\t\t|\t3) Exit \t\t\t|\n";
	cout<<"\t\t\t \t|_______________________________________|\n";
	cout<<"\t\t\t \tEnter your choice: ";
	cin>>x;

return x;	
}

int main(){
	system("Color F0");
	int choice;
	int ex,ex1;
	char name[50],username[60],userfile[60];
	string pass,checkpass;
	char login[10]="login.txt";
	char type[10]=".doc";
	ofstream fout;
	ifstream fin;
//	ofstream fileout;
	do
	{
	int choice=display();
	switch(choice){
		case 1:
			{
			system("cls");
			fflush(stdin);
			cout<<"\n\n\n\n\n\n\n\t\t\t\t\tCREATE NEW PHONEBOOK DIRECTORY: \t\t\n\n";
			cout << "\t\t\t\t Directory Name: ";	
			gets(name);
			while(strlen(name)==0)
			{
				cout << "\t\t\t\tDirectory Name can not be empty, Re-enter: ";
				gets(name);
			}
			// creates username eg: userlogin.txt in username[]	
			generateusername(username,name,login);
			if(inRecord(case_sensitive(username))==1){
				system("CLS");
				char selection;
				cout<<"\n\n\n\n\n\n\n\t\t\t\t\t"<<name<<"'s Phonebook Directory Already Exists.\n\t\t\t\t 1.To Open Directory [y] \n\t\t\t\t 2.To Return [n]\n\n";
				cin>>selection;
				if(selection=='y' || selection=='Y')
				goto exist;
				else if(selection=='n' || selection=='N')
				break;
				else break;
			}
			else{
				fout.open("Records.txt",ios::app);
				fout<<case_sensitive(username)<<endl;
				fout.close();
			}
		
			// verifyies the username does not already exists
			cout << "\t\t\t\tSet password: ";	
			getline(cin,pass);
			//writesFile
			while(pass.length()==0)
			{
				cout << "\t\t\t\tPassword can not be empty, Re-enter: ";
				getline(cin,pass);
			}
			fout.open(username,ios::out);
			fout<<pass<<endl;	
			fout.close(); 
			
					
			
			//creates a phonebook LL & perform function accordingly
			generateusername(userfile,name,type);
				PhoneBook obj;	
					
						system("cls");
						operations(name,obj);
					
					// before exiting writes file
					if(obj.writefile(userfile)==1){
					cout << "\t\t\t\t\t";
					cout<<"File Written\n";						
					}
					else
					cout<<"\t\t\t\t\tFile NOT Written\n";					
				
			}
		break;
		
		case 2:
			exist:
			system("cls");
			fflush(stdin);
			cout<<"\n\n\n\n\n\n\n\t\t\t\t\tOPEN EXISTING PHONEBOOK DIRECTORY: \t\t\n\n";
			cout << "\t\t\t\tEnter Directory Name: ";	
			gets(name);
			fflush(stdin);
			while(strlen(name)==0)
			{
				cout << "\t\t\t\tDirectory Name can not be empty, Re-enter: ";
				gets(name);
			}
			fflush(stdin);
			// generates username of type txt (userlogin.txt)
			generateusername(username,name,login);
			// opens userlogin
			fin.open(username,ios::out|ios::in);
			if(!fin){
				cout<<"\t\t\t\t||USER NOT FOUND!||\n"<<endl;
				system("pause");
				system("cls");
				break;
			}
			else{
			fflush(stdin);
			cout << "\t\t\t\tEnter password: ";	getline(cin,pass);
			while(!fin.eof())
			{
			fin >> checkpass;
			}
			fin.close();
			
		// Verification
			if(pass==checkpass)
			{
				// generate userfile name type doc (user.doc)
				generateusername(userfile,name,type);
				PhoneBook obj;
				int flag=obj.readfile(obj,userfile);				
				if(flag==1)
				{
					system("cls");
					operations(name,obj);			
					// before exiting writes file
					if(obj.writefile(userfile)==1){
					cout<<"\t\t\t\tFile Written\n";						
					}
					else
					cout<<"\t\t\t\tFile NOT Written\n";					

				}

			}
			else
			{
				cout << "\t\t\t\tIncorrect Password!\n";
			}
			
			system("pause");
			}
			break;
				
		case 3:
			cout << "\n\n\n\t\t\t\t||Phone Book Directory Exited Successfully||\n";
			return 0;
		}
	}while(choice!=3);
}

