#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<conio.h>
using namespace std;
class Contact;
void DisplaySimilarCon(Contact*,char[]);
string case_sensitive(char[]);



string case_sensitive(char sentence[100]){
	string Lower_Case=sentence;
	for(int i=0;i<Lower_Case.length();i++){
		if(Lower_Case[i]>=65 && Lower_Case[i]<=90){
			// subtract ascii cap val from 65 and to ASCII 97 'a'
			int ASCII=Lower_Case[i];
			ASCII=ASCII-65;
			char alpha=97+ASCII;
			Lower_Case[i]=alpha;
		}
	}
	return Lower_Case;
}

class Contact{
	public:
		char name[100];
		char number[15];
		char email[200];
		Contact *next;
		Contact *prev;
	Contact(){
		
	}
	Contact(char name[100],char number[15],char email[200]){
		
		for(int i=0;i<100;i++)
		this->name[i]=name[i];
		
		
		for(int i=0;i<15;i++)
		this->number[i]=number[i];
		
		for(int i=0;i<200;i++)
		this->email[i]=email[i];
		
		next=NULL;
		prev=NULL;
	}
	string getname(){
	string x=name;
	return x;
	}
//	~Contact()
//	{
//		delete[] name;
//		delete[] number;
//		delete[] email;
//		delete next;
//		delete prev;
//	}
};

class PhoneBook{
	private:
	Contact *head;
	Contact *tail;
	int list;
/////////////////////// NEW NODE DMA ////////////////////////////////////////	
	Contact* createContact(char name[100],char number[15],char email[200]){
		Contact *nn=new Contact(name,number,email);
		return nn;
	}
////////////////////// FIND MID  /////////////////////////////////////////////	
    Contact* middle(Contact* start, Contact* last){
	    if (start == NULL)
	        return NULL;
	 
	    Contact* slow = start;
	    Contact* fast = start -> next;
	 
	    while (fast != last)
	    {
	        fast = fast -> next;
	        if (fast != last)
	        {
	            slow = slow -> next;
	            fast = fast -> next;
	        }
	    }
	    return slow;
	}	
////////////////////  DisplayContactsMenu  //////////////////////////////
	void display(Contact *temp){
		system("cls");
		cout<<"[ESC] to Exit";
		cout<<"\n\n\n\n\n\n\n\t\t";
		cout<<"----------------------------------------------------------\n\n";
		cout<<"\t\t\t\t\t";
		puts(temp->name);
		cout<<"\t\t\t\t\t";
		puts(temp->number);
		cout<<"\t\t\t\t\t";
		puts(temp->email);
		cout<<"\n\n\t\t[<-] ------------------------------------------------- [->]\n";
	}
////////////////////  Sort List  //////////////////////////////
	void swap(Contact *t1,Contact *t2){
		Contact obj(t1->name,t1->number,t1->email);
		strcpy(t1->name,t2->name);
		strcpy(t1->number,t2->number);
		strcpy(t1->email,t2->email);
		strcpy(t2->name,obj.name);
		strcpy(t2->number,obj.number);
		strcpy(t2->email,obj.email);
	}
	void SortContacts(){
		if(head==NULL){
			return ;
		}
		Contact *t1,*t2;
		for(t1=head;t1->next!=NULL;t1=t1->next){
			for(t2=t1->next;t2!=NULL;t2=t2->next){
				if(case_sensitive(t1->name) > case_sensitive(t2->name)){
					swap(t1,t2);
				}
			}
		}
	}
///////////////////////////////////////////////////////////////////////	
public:
	PhoneBook()
	{
		list=0;
		head=NULL;
		tail=NULL;
	}	
	~PhoneBook()
	{
		delete head;
		delete tail;
	}
/////////////////////   DisplaySimilarContacts   //////////////////////////////
	Contact* DisplaySimilarCon(char name[100]){
		Contact *temp=head;
		if(temp==NULL){
			return NULL;
		}
		else{
			string s2=case_sensitive(name);
			cout<<"\n\n\n\n\t\t\t\t\t Displaying Similar Contacts Now ! \n\n";
			while(temp!=NULL){
			string s1=case_sensitive(temp->name);
			if(s1[0]==s2[0]){	
			cout<<"*****************************************************************\n";
				cout<<"Name: "<<temp->name<<endl;
				cout<<"Number: "<<temp->number<<endl;
				cout<<"Email: "<<temp->email<<endl<<endl;
			}	
			temp=temp->next;		
			}
		}
		system("pause");
	}
//////////////////// INSERTION & SORT ////////////////////////////	
	Contact* AddContact(char name[100],char number[15],char email[200]){   
			
			if(head==NULL)
			{	
				Contact *newnode=createContact(name,number,email);
				head=tail=newnode;
				list++;
				return NULL;
			}
			
			Contact *temp=head;
			Contact *newnode=createContact(name,number,email);
			while(temp->next!=NULL)  // traversal to insert in a sorted manner alphabetical
			{ 
				temp=temp->next;
			}
			newnode->prev=temp;
			temp->next=newnode;
			tail=newnode;
			SortContacts();
			list++;
			return NULL;	
	}
////////////////////	UPDATE CONTACT /////////////////////////////////
	void UpdateContact(char name[100],char number[15],char email[200]){
		Contact *ptr=SearchContact(name);
		if(ptr==NULL){
			cout<<"\n|| No Such Contact Exits ! ||\n";
		}
		else{
		strcpy(ptr->name,name);
		strcpy(ptr->number,number);
		strcpy(ptr->email,email);
		SortContacts();
		}
		
	}
////////////////////  	SEARCH CONTACT //////////////////////////////
//Binary search to find contact if not found finds the contacts with similar starting alphabet displays them !
	Contact* SearchContact(char name[100]){	
		
	    Contact *start = head;
	    Contact *last = NULL;
	    string search=case_sensitive(name);
	 
	    do{
	
	        Contact *mid = middle(start, last);
	 
	        if (mid == NULL){return NULL;}
	
	        if (case_sensitive(mid->name) == search){return mid;}
	        
	        else if (case_sensitive(mid->name) < search ){start = mid -> next;}
	            
	 		else   last=mid;
	 
	    } while (last==NULL || last!=start);
	 
	    // NOT IN LIST
	    return NULL;
	}
////////////////////  Delete CONTACT /////////////////////////////////
	Contact* DeleteContact(char name[100]){	

		Contact *ptr=SearchContact(name);
		if(ptr==NULL){
			return NULL;
		}
		
		if(ptr->next==NULL && ptr->prev==NULL){
			head=tail=NULL;
			delete ptr;
		}

		else if(ptr->prev==NULL){
			Contact *del=ptr;
			ptr=ptr->next;
			ptr->prev=NULL;
			head=ptr;
			delete del;

		}
		else if(ptr->next==NULL){
			Contact *prevN=ptr->prev;
			prevN->next=ptr->next;
			tail=prevN;
			delete ptr;
		}
		else{
			Contact *prevN=ptr->prev;
			prevN->next=ptr->next;
			ptr->next->prev=prevN;
			delete ptr;
		}
		SortContacts();
		return ptr;
	}
////////////////////  Filing OF CONTACT //////////////////////////////
int writefile(char filename[60]){
		Contact *temp=head;
		FILE *fp = fopen(filename,"w");
		if(!fp){
		//	cout<<"\n||File Not Created||\n";
			return -1;
		}
		else{
	//	cout<<filename;	
		while(temp!=NULL){
			fwrite(temp,sizeof(Contact),1,fp);
			temp=temp->next;
		}
		fclose(fp);	
		return 1;
		}
}

int readfile(PhoneBook &P,char filename[60]){
		Contact s1;
		FILE *fp = fopen(filename,"r");
		cout<<filename;
		if(!fp){
			cout<<"\n||File Not Opened||\n";
			return -1;
		}
		else{
		while(fread(&s1,sizeof(Contact),1,fp)){
			P.AddContact(s1.name,s1.number,s1.email);
		}
		fclose(fp);
		return 1;
		}
}

//////////////////// DISPLAY  ///////////////////////////////////////

	Contact* print(){
		Contact *temp=head;
		int input=0;
		if(temp==NULL){
			return NULL;
		}
		do{
			display(temp);
			input=getch();

			if(input==75){   // <-
               if(temp->prev==NULL){
                temp=tail;
               }
               else temp=temp->prev;
			}
            
			else if(input==77){  // ->
               if(temp->next==NULL){
                temp=head;
               }
               else temp=temp->next;
			}
		}while(input!=27);	// ESC
	}
	void display(Contact *temp , int x){
		system("cls");
		cout<<"\n\n\n\n\n\n\n\t\t";
		cout<<"----------------------------------------------------------\n\n";
		cout<<"\t\t\t\t\t";
		puts(temp->name);
		cout<<"\t\t\t\t\t";
		puts(temp->number);
		cout<<"\t\t\t\t\t";
		puts(temp->email);
		cout<<"\n\n\t\t------------------------------------------------------------\n\n\n";
		system("pause");
	}

};

