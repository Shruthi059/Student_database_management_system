#include<stdlib.h>
#include<conio.h>
#include<cstring>
#include<iostream>
#include<fstream>
#include<windows.h>
#include<time.h>
#include<cstdio>
#define F_NOT_FOUND -1
#define USN_NOT_FOUND -2
#define SUCCESS 0
#define ADMIN_PASS "OOP"
using namespace std;
int flag,subject=0;
inline void clrscr(){
    system("cls");
}

inline void title(){
    clrscr();
	cout<<"==============================================================================="<<endl;
	cout<<"**************** Institute Student Database Management System *****************"<<endl;
	cout<<"==============================================================================="<<endl;
}

void getdate(char *tday){
	time_t tim;
	tim=time(NULL);
	struct tm *d=localtime(&tim);
	sprintf(tday,"%02d/%02d/%d",d->tm_mday,d->tm_mon+1,d->tm_year+1900);
}

//sets current date in file
void setbits(){
    ofstream setb;
	char today[11];
	getdate(today);
	switch(subject){
		case 1 :setb.open("VLSI.dat");
				setb<<today;
				break;
		case 2 :setb.open("COA.dat");
				setb<<today;
				break;
		case 3 :setb.open("MWA.dat");
				setb<<today;
				break;
		case 4 :setb.open("CCN.dat");
				setb<<today;
				break;
	}
	setb.close();
};

bool isAt_Done(){
	char entered[11],today[11];
	ifstream setb;
	switch(subject){
		case 1 :setb.open("VLSI.dat");
				break;
		case 2 :setb.open("COA.dat");
				break;
		case 3 :setb.open("MWA.dat");
				break;
		case 4 :setb.open("CCN.dat");
				break;
	}
	setb.getline(entered,15);
	setb.close();
	getdate(today);
	if(!strncmp(entered,today,10)) return true;
	else return false;
}

class STUDENT; 

class STAFF {
	protected :
         char staff_id[10];
         char staff_name[40];
         char staff_sub[5];
         char email[30];
    public : STAFF(){
				staff_id[0]=staff_name[0]=staff_sub[0]=email[0]='\0';
			}
			STAFF(char *id,char *name,char *sub,char *mail){
				strcpy(staff_id,id);
			  	strcpy(staff_name,name);
				strcpy(staff_sub,sub);
				strcpy(email,mail);
		     }
			char* getid(){
				return staff_id;
			}
		 int init(char*);
         int manageAttendence();
         int manageMarks();
 	virtual void showProfile(){
	clrscr();
	title();
    cout<<"Proifile...."<<endl;
	cout<<"_______________________________________________________________________________"<<endl;
    cout<<" Staff Name      \t :"<<staff_name<<endl;
    cout<<" Staff Id        \t :"<<staff_id<<endl;
    cout<<" Department      \t :"; if(subject==1) cout<<"VLSI"<<endl;
									else cout<<"Electronics and Communication Engineeering"<<endl;
	cout<<" Email id        \t :"<<email<<endl;
	cout<<"_______________________________________________________________________________"<<endl;
	fflush(stdin);
	cin.get();
	}
};

class ADMIN:public STAFF{
	char pass[10];
	public : ADMIN(char id[]){
				 strcpy(staff_id,id);
				 strcat(id,".dat");
		         ifstream fp(id,ios::in);
		         if(fp){
					fp>>pass;
			    	fp>>staff_name;
					fp>>email;
				 }
			}
	void setsub(char *s){ strcpy(staff_sub,s); }
		int addstaff();
		int admitStudent();
		int removeStaff(char*);
		int removeStudent(char*);
		void viewMarks();
		void viewAttendence();
	    int manageAttendence();
		int listStudent();
		int Notification();
	    int complaint();
	    int timetable();
		bool isValidPass(char *p){
			cout<<"\n\n\tAuthenticating...";
			Sleep(500);
			if(!strcmp(ADMIN_PASS,p)){
				return true;
			}else {false;
		}
	}
	void showProfile();
};

class STUDENT{
        int admissionNo;
        char usn[11];
        char name[30];
        char email[30];
        char dob[11];
        struct sub{
            int VLSI,COA,MWA,CCN;
            }marks,attendence;
		public : STUDENT(){
				admissionNo=-1;
				strcpy(usn,"\0");
				strcpy(usn,"\0");
				strcpy(email,"\0");
				strcpy(dob,"\0");
				marks.VLSI=-1;
				marks.COA=-1;
				marks.MWA=-1;
				marks.CCN=-1;
				attendence.VLSI=0;
				attendence.COA=0;
				attendence.MWA=0;
				attendence.CCN=0;
		 }

        int init(char*);
        void showProfile();
        void showAttendence();
        void showMarks();
        int Notification();
        int complaint();
        int paper();
        int timetable();
		friend class ADMIN;
		friend class STAFF;
		void operator++(int);
};

void ADMIN::showProfile(){
	clrscr();
	title();
    cout<<" Admin profile...."<<endl;
	cout<<"_______________________________________________________________________________"<<endl;
    cout<<" Admin Name      \t :"<<staff_name<<endl;
    cout<<" Admin Id        \t :"<<staff_id<<endl;
    cout<<" Email Id        \t :"<<email<<endl;
	cout<<"_______________________________________________________________________________"<<endl;
	fflush(stdin);
	cin.get();
}

void ADMIN:: viewMarks(){
	char usn[15];
	clrscr();
	title();
	cout<<endl<<"Please enter the student USN : "; cin>>usn;
	strupr(usn);
	STUDENT s;
	fflush(stdin);
	if(s.init(usn)){
		cout<<" Enter valid USN...";
		cin.get();
		return;
		}
	s.showMarks();
}

void ADMIN::viewAttendence(){
	char u[15];
	clrscr();
	title();
	cout<<"Please enter student USN : "; cin>>u;
	strupr(u);
	STUDENT s;
	fflush(stdin);
	if(s.init(u)){
		cout<<" Enter valid USN...";
		cin.get();
		return;
	}
	s.showAttendence();
}

int ADMIN::removeStudent(char *U){
	bool flag=false;
	long pos;
    fstream readfile("student.dat",ios::binary|ios::in|ios::out);
	if(!readfile){
        cerr<<"Error in opening the file...please try again";
        cin.get();
		return F_NOT_FOUND;
     }
    STUDENT temp;
	while(!readfile.eof()){
		pos=readfile.tellg(); 
        readfile.read((char*)&temp,sizeof(temp));
			if(!strcmp(U,temp.usn)){
            	flag=true;
            	break;
        	}
    }
	if(!flag){
        cerr<<"\tInvalid user "<<endl;
        return USN_NOT_FOUND;
		cin.get();
    	}
    

         	temp.admissionNo=0;
			strcpy(temp.name,"\0");

    		strcpy(temp.usn,"\0");
        	strcpy(temp.email,"\0");
			strcpy(temp.dob,"\0");

            temp.marks.VLSI=0;
			temp.marks.COA=0;
			temp.marks.MWA=0;
			temp.marks.CCN=0;

		    temp.attendence.VLSI=0;
			temp.attendence.COA=0;
			temp.attendence.MWA=0;
			temp.attendence.CCN=0;
	readfile.seekp(pos);
	readfile.write((char*)&temp,sizeof(temp));
	fflush(stdin);
	cout<<"Student record removed successfully...";
	cin.get();
	return SUCCESS;
}

int ADMIN::addstaff(){
	char name[40],sub[5],email[30],id[10];
	clrscr();
	ofstream putf("staff.dat",ios::binary|ios::out|ios::app);
	if(!putf){
		cerr<<"Unable to open student record file ";
		return F_NOT_FOUND;
	}
	title();
	cout<<" Please enter the following fields...[all fields are mandatory]"<<endl;
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<"\n Enter staff id                            : "; cin>>id;
	fflush(stdin);
	cout<<"\n Enter staff name                          : "; cin.getline(name,30);
	fflush(stdin);
	cout<<"\n Enter subject to handle[VLSI/COA/MWA/CCN]   : "; cin>>sub;
	strlwr(sub);
	fflush(stdin);
	cout<<"\n Enter the mail id                         : "; cin>>email;
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	STAFF temp(id,name,sub,email);
	fflush(stdin);
	cout<<"Press enter to proceed "; cin.get();
	clrscr();
	temp.showProfile();
	putf.write((char*)&temp,sizeof(temp));
	putf.close();
	cout<<endl<<" Staff member added successfully..."; cin.get();
	return SUCCESS;
}

int ADMIN::Notification(){
	clrscr();
	ofstream putf("notification.dat",ios::binary|ios::out|ios::app);
	if(!putf){
		cerr<<"Unable to open student record file ";
		return F_NOT_FOUND;
	}
	title();
	char today[11],note[500];
	getdate(today);
	 cout<<"\t\t\t\t\t\t\t    Today : "<<today;
	cout<<"\nEnter Notifications: \n";
	fflush(stdin);
	cin.getline(note,500);
    putf<<"\n_________________________________________________________________   "<<today<<"\n"<<note<<"\n\n\n";	
	putf.close();
	cout<<endl<<" Notification added successfully..."; cin.get();	
}

int ADMIN::complaint(){
	clrscr();
	char ch;
	cout<<"\n\tCOMPLAINT:\n\n";
    ifstream readfile1("complaint.dat",ios::binary|ios::in);
    if(!readfile1.is_open()){
              return F_NOT_FOUND;
    }
	fflush(stdin);
	title();
	readfile1.seekg(0);
	cout<<"\n ";
    while(!readfile1.eof()){
    readfile1.get(ch);
    cout<<ch;
    }
    cout<<"\nPress any key to return...";
	cin.get();
	readfile1.close();
}

int ADMIN::timetable(){
	clrscr();
	ofstream pf("table.dat",ios::binary|ios::out);
	if(!pf){
		cerr<<"Unable to open student record file ";
		return F_NOT_FOUND;
	}
	title();
	char today[11],note[20],start[10],end[10];
	getdate(today);
	 cout<<"\t\t\t\t\t\t\t    Today : "<<today;
	cout<<"\nEnter exam starting and ending time: \n";
	cin>>start>>end;
	fflush(stdin);
	pf<<"\n\n_______________________________________________________________     "<<today<<"\n\n\n";
	cout<<"Enter exam date for following subject :\n";
	   pf<<'|'<<" SUBJECT   "<<'|'<<"\t"<<"DATE     "<<'|'<<"\t"<<"START TIME "<<'|'<<"\t"<<"END TIME "<<" "<<'|'<<endl;
    cout<<"VLSI     : ";
	cin>>note;
	   pf<<'|'<<"       VLSI "<<'|'<<"\t"<<note<<" "<<'|'<<"\t"<<start<<"      "<<'|'<<"\t"<<end<<"     "<<'|'<<endl;
    cout<<"COA   : ";
    cin>>note;
       pf<<'|'<<"    COA "<<'|'<<"\t"<<note<<" "<<'|'<<"\t"<<start<<"      "<<'|'<<"\t"<<end<<"     "<<'|'<<endl;
    cout<<"MWA      : ";
    cin>>note;
       pf<<'|'<<"       MWA"<<'|'<<"\t"<<note<<" "<<'|'<<"\t"<<start<<"      "<<'|'<<"\t"<<end<<"     "<<'|'<<endl;
    cout<<"CCN      : "; 
    cin>>note;
       pf<<'|'<<"        CCN "<<'|'<<"\t"<<note<<" "<<'|'<<"\t"<<start<<"      "<<'|'<<"\t"<<end<<"     "<<'|'<<endl;
		
	pf.close();
	cout<<endl<<" Exam time table updated successfully..."; cin.get();	
	cin.get();
}


int ADMIN::removeStaff(char *U){
	bool flag=false;
	long pos;
    fstream readfile("staff.dat",ios::binary|ios::in|ios::out);
	if(!readfile){
        cerr<<"Error in opening file...please try again";
        return F_NOT_FOUND;
     }
    STAFF temp;
	while(!readfile.eof()){
		pos=readfile.tellg(); 
        readfile.read((char*)&temp,sizeof(temp));
			if(!strcmp(U,temp.getid())){
            	flag=true;
            	break;
        	}
    }
	if(!flag){
        cerr<<"\tInvalid user "<<endl;
        return USN_NOT_FOUND;
    	}
	readfile.seekp(pos);
	STAFF del;
	readfile.write((char*)&del,sizeof(STAFF));
	fflush(stdin);
	cout<<"Staff  removed successfully...";
	cin.get();
	return SUCCESS;
}

//administrator acces to change the attendenc
int ADMIN::manageAttendence(){
	       title();
		   char tday[10],date[11];
		   flag=0;
		   getdate(tday);
		   cout<<"\t\t\t\t\t\t\t    Today : "<<tday;
		   cout<<"\n\tYou have permission to change the attendence, only 6 days before the"<<endl;
		   cout<<" final exam to give eligibilty to the student who has less than 75%."<<endl;
		   cout<<endl<<"\n\nEnter the final exam date [DD/MM/YYYY] : ";
		   cin>>date;
		   int i,j,x,y;

		   x=tday[3]-'0';
		   x=x*10+(tday[4]-'0');
		   y=date[3]-'0';
		   y=y*10+(date[4]-'0');
		   i=tday[0]-'0';
		   i=i*10+(tday[1]-'0');
		   j=date[0]-'0';
		   j=j*10+(date[1]-'0');

		   Sleep(1000);
		   if(j-i<7&&x==y){
		   cout<<"Enter the subject to modify :";
		   cin>>staff_sub;
			    fflush(stdin);
		   strlwr(staff_sub);

		   cout<<"Enter the USN : ";

			   fflush(stdin);
			   char u[11];
			   cin>>u;
			   strupr(u);
			   STUDENT s;
			   fstream f("student.dat",ios::in|ios::in|ios::out);
			   int pos;
			   while(!f.eof()){
				   pos=f.tellg();
				   f.read((char*)&s,sizeof(s));
				   if(!strcmp(s.usn,u)){
					   flag=1;
					   break;
		          }
			   }
			   if(flag){
				   cout<<"Enter the attendence : ";
				   int num;
				   cin>>num;
				   if(subject==3)
						s.attendence.MWA=num;

				   	else if(subject==2)
							s.attendence.COA=num;
					else if(subject==4)
							s.attendence.CCN=num;
					else if(subject==1)
						s.attendence.VLSI=num;
						f.seekp(pos);
						f.write((char*)&s,sizeof(s));
						cout<<"Attendence updated.";
				   f.close();
				   fflush(stdin);
				   cin.get();

						}
			   else {cerr<<"USN not found...";
			   cin.get();
		   }
		   }
		   else {
			   cout<<"Sorry, You cannot change the attendance.";
			   Sleep(800);
		   return 0;
		   }
}

int ADMIN::listStudent(){
	title();
	char prev[12];
	ifstream readF("student.dat",ios::binary|ios::in);
	STUDENT temp;
	fflush(stdin);
	cout<<"\tUSN\t\tNAME"<<endl;
    int full=0;
    while(!readF.eof()){
        readF.read((char*)&temp,sizeof(temp));
		if(temp.admissionNo==-1){ cout<<endl<<"End of list";
			break;
		}
		full++;
		if(full>10){
                cout<<"Press enter to continue...";
                cin.get();
                full=0;
                title();
                cout<<"\tUSN\t\tNAME"<<endl;
               }
        if(!strcmp(prev,temp.usn)) continue;
        strcpy(prev,temp.usn);
		cout<<"\t"<<temp.usn<<"\t"<<temp.name<<endl;

    }
	cout<<"\nPress any key to return...";
	cin.get();
	readF.close();
}

int ADMIN::admitStudent(){
	clrscr();
	fstream putf("student.dat",ios::binary|ios::out|ios::app);
	if(!putf){
		cerr<<"Unable to open student record file ";
		return F_NOT_FOUND;
	}
	STUDENT temp;
	putf.seekp(ios::end);
	title();

	cout<<"Please enter the following fields...[all fields are mandatory]"<<endl;
	fflush(stdin);
	STUDENT t;
    int status=0;
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<"\n # Please enter usn number               : "; cin>>temp.usn;
	fflush(stdin);
	strupr(temp.usn);
	if(USN_NOT_FOUND!=t.init(temp.usn)){
		cout<<"This USN number is already assigned to : "<<t.name;
		Sleep(1000);
		if(++status<3)
		admitStudent();
		else return 0;
	}
	fflush(stdin);
	cout<<"\n # Please enter full name of the student : "; cin.getline(temp.name,30);
	fflush(stdin);
	cout<<"\n # Please enter date of birth            : "; cin>>temp.dob;
	fflush(stdin);
	cout<<"\n # Please enter new admission number     : "; cin>>temp.admissionNo;
	fflush(stdin);

	fflush(stdin);
	cout<<"\n # Please enter email id of the student  : "; cin>>temp.email;
	fflush(stdin);
	cout<<"\n Press enter to proceed ";
	cin.get();
	clrscr();
	title();
	cout<<"\n The new student details are as given below... "<<endl;
	cout<<endl<<"_______________________________________________________________________________"<<endl;

	cout<<"\n # Admission Number       : "<<temp.admissionNo<<endl;
	cout<<" # Student name           : "<<temp.name<<endl;
	cout<<" # University Seat Number : "<<temp.usn<<endl;
	cout<<" # Date of birth          : "<<temp.dob<<endl;
	cout<<" # Email id               : "<<temp.email<<endl;

		    temp.attendence.VLSI=0;
			temp.attendence.COA=0;
			temp.attendence.MWA=0;
			temp.attendence.CCN=0;
	cout<<" Are the above details correct?  [Y/N] : ";
	char yes;
	cin.get(yes); fflush(stdin);
	if(yes=='Y'||yes=='y') {

		putf.write((char*)&temp,sizeof(temp));
	cout<<"New student added successfully..."<<endl;
	cin.get();
	putf.close();
	}
	else {

		cout<<" Student details weren't added ";
		Sleep(800);
		return -1;
	}
	clrscr();
}

void STUDENT::showProfile(){
	clrscr();
	title();
	cout<<"My proifile...."<<endl;
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<" Name                :"<<name<<endl;
    cout<<" Admission number    :"<<admissionNo<<endl;
    cout<<" USN                 :"<<usn<<endl;
	cout<<" Branch              : Electronics and Communication Engineering"<<endl;
    cout<<" Date of birth       :"<<dob<<endl;
    cout<<" Email id            :"<<email<<endl;
	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<"Press any key to exit :";
	cin.get();
}

//display marks
void STUDENT::showMarks(){
	clrscr();
	title();
    cout<<" Test Result     : "<<name<<endl;
    cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<" SUBJECT NAME                          | MARKS "<<endl;
 	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<" Very large scale integration                       | "; (marks.VLSI>=0)?cout<<marks.VLSI<<endl:cout<<"Not Entered"<<endl;
    cout<<" Computer organization architecture           | ";  (marks.COA>=0)?cout<<marks.COA<<endl:cout<<"Not Entered"<<endl;
    cout<<" Microwave and antenna    | ";  (marks.MWA>=0)?cout<<marks.MWA<<endl:cout<<"Not Entered"<<endl;
	cout<<"Computer Communication and networking                           | ";  (marks.CCN>=0)?cout<<marks.CCN<<endl:cout<<"Not Entered"<<endl;
 	cout<<endl<<"_______________________________________________________________________________"<<endl;
	cout<<"Press any key to exit :";
	cin.get();
}

//dispaly attendencce
void STUDENT::showAttendence(){
	fflush(stdin);
	clrscr();
	title();
	cout<<" Attendence Result     : "<<name<<endl;
	cout<<endl<<"_________________________________________________________________________"<<endl;
	cout<<" SUBJECT NAME                        | Class Attended "<<endl;
    cout<<"_______________________________________________________________________________"<<endl;
	cout<<" Very large Scale integration                    | "<<attendence.VLSI<<endl;
    cout<<"     Computer organization architecture     | "<<attendence.COA<<endl;
    cout<<" Microwave and antenna | "<<attendence.MWA<<endl;
	cout<<" Computer Communication and networking                        | "<<attendence.CCN<<endl;

	cout<<"Press any key to exit :"; cin.get();

}

//initialize the student data with details of logged in student
// also checks if log-in id(USN) is correct/exist 
int STUDENT::init(char *U){
    bool flag=false;
	ifstream readfile("student.dat",ios::binary|ios::in);
    if(!readfile.is_open()){
              return F_NOT_FOUND;
    }

    STUDENT temp;
	readfile.seekg(0);
    while(!readfile.eof()){
        readfile.read((char*)&temp,sizeof(temp));

		if(!strcmp(U,temp.usn)){
            flag=true;
            break;
		}
		if(temp.admissionNo==-1)
			break;

    }
    if(!flag){
  		return USN_NOT_FOUND;
    }
    
	*this=temp;
	return SUCCESS;
}

int STUDENT::Notification(){
	clrscr();
	char ch;
	
    ifstream readfile("notification.dat",ios::binary|ios::in);
    if(!readfile.is_open()){
              return F_NOT_FOUND;
    }

	title();
	cout<<"\n\tNOTIFICATIONS: \n\n";
	readfile.seekg(0);
	cout<<"\n ";
    while(!readfile.eof()){
    readfile.get(ch);
    cout<<ch;
    }
    
    cout<<"\nPress any key to return...";
	cin.get();
	readfile.close();
}

int STUDENT::timetable(){
	clrscr();
	char ch;
    ifstream readfile1("table.dat",ios::binary|ios::in);
    if(!readfile1.is_open()){
              return F_NOT_FOUND;
    }

	title();
	cout<<"\t\t\tExam Time Table\n";
	readfile1.seekg(0);
	cout<<"\n ";
    while(!readfile1.eof()){
    readfile1.get(ch);
    cout<<ch;
    }
    cout<<"\n________________________________________________________________________ ";
    cout<<"\nPress any key to return...";
	cin.get();
	readfile1.close();
}

char u1[11];
int STUDENT::complaint(){
	clrscr();
    ofstream putf("complaint.dat",ios::binary|ios::out|ios::app);
	if(!putf){
		cerr<<"Unable to open student record file ";
		return F_NOT_FOUND;
	}

	title();
	char today[11],note[500];
	getdate(today);
	 cout<<"\t\t\t\t\t\t\t    Today : "<<today;
	cout<<"\nEnter Complaint: \n";
	fflush(stdin);
	cin.getline(note,500);
		putf<<"\n\n__________________________________________________________       "<<today<<"\n"<<note<<"\t -"<<u1<<"\n\n\n";
		
	putf.close();
	cout<<endl<<" Complaint given successfully..."; cin.get();	
}


int STAFF::init(char *id){
    bool flag=false;
    ifstream readfile("staff.dat",ios::binary|ios::in);
        if(!readfile.is_open()){
            cerr<<"\nError opening the record... please try again."<<endl;
            Sleep(3000);
			return F_NOT_FOUND;
        }
    STAFF temp;
    while(!readfile.eof()){

    readfile.read((char*)&temp,sizeof(temp));
		if(!strcmp(id,temp.staff_id)){
            flag=true;
            break;
		}
  }
    if(!flag){
        cout<<"\nStaff with staff id : ["<<id<<"] not found. Enter valid id"<<endl;
		Sleep(1000);
    return USN_NOT_FOUND;
    }

	*this=temp;
	if(!strcmp(staff_sub,"COA")) subject=2;
        else if(!strcmp(staff_sub,"MWA")) subject=3;
        else if(!strcmp(staff_sub,"CCN")) subject=4;
        else if(!strcmp(staff_sub,"VLSI")) subject=1;
    return SUCCESS;
}

int STAFF::manageMarks(){
	title();
    int c=0;
	int m;
	STUDENT temp;
    fstream readfile("student.dat",ios::binary|ios::in|ios::out);
	if(!readfile.is_open()){
		cout<<"Error : Student database file missing...";
		return F_NOT_FOUND;
	}
	cout<<"Enter the max. marks and press enter key : "; cin.get();
	clrscr();
	title();
	cout<<endl<<"Subject : ";
		switch(subject){
		case 1 :cout<<"Very large scale integration"; break;
		case 2 :cout<<"Computer Organization architecture"; break;
		case 3 :cout<<"Microwave and antenna "; break;
		case 4 :cout<<"Computer communication and networking"; break;
		}
	cout<<endl;
	readfile.seekg(0L);
    while(!readfile.eof()){
		fflush(stdin);
        readfile.read((char*)&temp,sizeof(temp));

	if(!strcmp(staff_sub,"VLSI")) {
          cout<<"#"<<temp.usn<<" ["<<temp.marks.VLSI<<"]"<<"=>";
          cin>>m;
          temp.marks.VLSI=m;
	}
	else if(!strcmp(staff_sub,"COA")) {
          cout<<"#"<<temp.usn<<" ["<<temp.marks.COA<<"]"<<"=>";
          cin>>m;
          temp.marks.COA=m;
	}
	else if(!strcmp(staff_sub,"MWA")) {
          cout<<"#"<<temp.usn<<" ["<<temp.marks.MWA<<"]"<<"=>";
			cin>>m;
          temp.marks.MWA=m;
	}
	else if(!strcmp(staff_sub,"CCN")) {
          cout<<"#"<<temp.usn<<" ["<<temp.marks.CCN<<"]"<<"=>";
          cin>>m;
          temp.marks.CCN=m;
	}
	//write back the changes amde to the attendence.
		readfile.seekp((long)readfile.tellg()-sizeof(temp));
		readfile.write((char*)&temp,sizeof(temp));
		c++;
		if(c>15) {
			clrscr();
			title();
    		c=0;
		}
		fflush(stdin);
		cin.get();
	}
	cout<<" Marks have been updated succesfully..."; Sleep(3000);
	return SUCCESS;

}



int STAFF::manageAttendence(){
	char day[10];
	clrscr();
	fflush(stdin);
	title();
	getdate(day);

	if(isAt_Done()){
		cout<<"\tDate : "<<day<<endl;;

		cout<<"You have already entered today's attendence...\nSorry, You cannot enter again..."<<endl;
		cin.get();
		return 0;
	}
	char presence;
	STUDENT temp[80];
    ifstream readfile("student.dat",ios::binary|ios::in);
	if(!readfile.is_open()){
		cout<<"Error : Student database file missing...";
		return F_NOT_FOUND;
	}
	int n=0;
	while(!readfile.eof()){
		readfile.read((char*)&temp[n],sizeof(temp[n]));
		if(!strcmp(temp[n].usn,"\0")) continue;
		n++;
		}
	  readfile.close();
	cout<<endl<<"Subject : ";
		switch(subject){
		case 1 :cout<<"Very large scale integration  "; break;
		case 2 :cout<<"Computer Organization architecture"; break;
		case 3 :cout<<"Microwave and antenna "; break;
		case 4 :cout<<"Computer communication and networking"; break;
		}
	cout<<"\tDate : "<<day<<endl;;

	cout<<"\t 1 : Mark all absent\n\t 2 : Enter absenties' usn "<<endl;
	cout<<"\t Select your choice : ";
	int choice;
	char yes;
	cin>>choice;
	if(choice==1){ cout<<"Marking everyone absent...\nAre you sure : [Y/N] ";
	  cin>>yes;
	  if(yes=='y'||yes=='Y'){
        setbits();
   	    cout<<"Attendence updated...";
		return 0;
	  		}
		}
	else if(choice!=2) return 0;
	clrscr();
	title();
	cout<<endl<<"Enter absenties usn : [Complete USN or last 3/2 digit(0 to end) ]\n_";
	char absent[12],l_absent[12]; 
	int count=0;

	fstream t("log.bin",ios::in|ios::out|ios::trunc);
	while(1){

		cin>>absent;

		if(!strcmp(absent,"0")) break;

		strupr(absent);
		if((strlen(absent))==3){
			strcpy(l_absent,"4AL21EC0");
			strcat(l_absent,absent);
			t<<l_absent<<endl;
		}
		else if((strlen(absent))==2){
			strcpy(l_absent,"4AL21EC0");
			strcat(l_absent,absent);
			t<<l_absent<<endl;
		}

		else
			t<<absent<<endl;
		count++;
	}
	t<<"0";
	title();
	t.seekp(0L);
	cout<<" Absenties list : \n"<<endl;
	while(1){
		t.getline(absent,11);
		if(!strcmp(absent,"0")) break;
		cout<<" \t"<<absent<<endl;
	}
	 t.close();
	fflush(stdin);
	cout<<"\n\tTotal absent   = "<<count<<endl;
	cout<<"\tTotal present = "<<n-count<<endl;
	cout<<"Press enter to proceed : ";
	cin.get();
	ofstream writefile("student.dat",ios::binary|ios::out);
	for(int i=0;i<n;i++){
			temp[i]++;
           writefile.write((char*)&temp[i],sizeof(temp[i]));

	}
	setbits();
	cout<<"Attendence updated...";
	cin.get();
	writefile.close();
}
void STUDENT::operator++(int){
	flag=0;
	ifstream log("log.bin");
	char absent[11];
	log.seekg(0L);
	while(!log.eof()){
		log.getline(absent,11);
		if(!strncmp(usn,absent,10)){
		flag=1; break;
		}
	}
	if(flag==0){
		if(subject==3)
		++attendence.MWA;


	else if(subject==2)
        attendence.COA++;
	else if(subject==4)
         attendence.CCN++;
	else if(subject==1)
		attendence.VLSI++;

		} log.close();
}

int setup(){
	title();
	ifstream fp("student.dat",ios::binary|ios::in);
	if(fp.is_open())
		return 0;
	cout<<endl<<"Initiating required files for first time usage... ";
    fp.close();
	ofstream ofp("student.dat",ios::binary|ios::out);
// Store the initial data to the file.
	if(!ofp.is_open()) return -1;
	ofp.close();
	ofstream _ofp("staff.dat",ios::binary|ios::out);
	if(!_ofp.is_open()) return -1;
	_ofp.close();
	ofstream _o("log.bin",ios::out);
	_o.close();
	ofstream _f("notification.dat",ios::binary|ios::out);
	if(!_f.is_open()) return -1;
	_f.close();
	ofstream _fi("complaint.dat",ios::binary|ios::out);
	if(!_fi.is_open()) return -1;
	_fi.close();
	ofstream _fii("topic.dat",ios::binary|ios::out);
	if(!_fii.is_open()) return -1;
	_fii.close();
	Sleep(2000);
	cout<<" : DONE";
	cin.get();
	return 0;
}

// User handler function, prototype;
int student(),staff(),guest(), admin();

int main(){
	if(setup()) {
		cout<<"Files are missing and unable to create new files...\n Please try again..."; Sleep(2000);
		exit(1);
	}
    while(1){
    clrscr();//inline fn
	title();//inline fn
	cout<<"\n\t\tLogin Option"<<endl;
    cout<<"\t\t 1 : Student "<<endl;
    cout<<"\t\t 2 : Staff   "<<endl;
    cout<<"\t\t 3 : Admin "<<endl;
	cout<<"\t\t 4 : Exit"<<endl;
	cout<<endl<<endl<<"\t\tEnter your choice : ";

	static int error;
    int logChoice;
    cin>>logChoice;
    switch(logChoice) {

        case 1 : error=0;
					while(error<4) {  //each time student gets max of 4 attempts to enter correct password or id
					        if(student())
							error++;
                  			else break;
								   }
					if(error>3) 	
							cerr<<" Authentication failed...";//console error: std o/p stream for errors 
				 			cin.get();// similar to getch()
					break;
	    case 2 :error=0;
					while(error<4) { if(staff())
							error++;
                  			else break;
								   }
				if(error>3) cerr<<" Authentication failed..."; cin.get();
					break;
	    case 3 :admin();
                	break;
		case 4 :cout<<"Terminating..."; Sleep(1000); //from WINAPI Sleep(DWORD)
				exit(0);
        default:cout <<"Invalid choice : "; 
		          Sleep(1000);
				  cin.get();
		}
    }
    return 0;
}



int student(){
	static int error;
    char usn[11];
	clrscr();
    title();
	cout<<"\tLogin type : Student."<<endl;
	cout<<endl<<"\tEnter your usn number : ";
    cin>>usn;
    strupr(usn);
    cout<<endl<<"\tEnter the password    : ";
    char pass[15],c;
	short i=0;
	//cin>>pass; /*
    while((c=getch())!=13){ pass[i]=c;
                i++; cout<<'*';
			}
	pass[i]='\0';
	strupr(pass);
	if(strcmp(usn,pass)){
       cout<<"\n\tInavlid usn or password..."<<endl;
       return -1;
		}
	int choice;
    STUDENT s;
	flag=s.init(usn);
    if(USN_NOT_FOUND==flag){
		cout<<"\n\tNo such usn assigned to student... ";
		cin.get();
		return 0;
	}
	else if(flag==F_NOT_FOUND){   
		cerr<<"\n\tError in opening file...please try again";
					Sleep(2000);
					return 0;
	}
	//object of student class initialized with usn
	while(1) {
        clrscr();
		title();
		cout<<"\tLogin type : Student  ["<<usn<<"]"<<endl;
       	cout<<"\t\tMenu"<<endl;
       	cout<<"\t\t1 : View profile\n\t\t2 : View attendence\n\t\t3 : View marks\n\t\t4 : View Notifications \n\t\t5 : Give a Complaint \n\t\t6 : Exit"<<endl;
       	cout<<"\tEnter your choice  : ";
       	cin>>choice;
       	switch(choice){
           case 1 : fflush(stdin);
		   			clrscr();
		   			s.showProfile();
                    break;
           case 2 : fflush(stdin);
                    clrscr();
		            s.showAttendence();
                     break;
           case 3 : fflush(stdin);
		   			clrscr();
		   			s.showMarks();
                    break;
           case 4 : fflush(stdin);
		   			clrscr();
		   			s.Notification();
                    break;        
           case 5 : fflush(stdin);
		   			clrscr();
		   			strcpy(u1,usn);
		   			s.complaint();
                    break;      
		   case 6 : cout<<"Logging out...["<<usn<<"]";
		   			Sleep(1000);
		   			return SUCCESS;
            default : cout<<"Select valid choice : ";
		   		Sleep(1000);
       }
    }
}
int staff(){
    char staffid[10];
	title();
	cout<<"\tLogin type : Staff"<<endl;
    fflush(stdin);
    cout<<endl<<"\tEnter staff id      : ";
    cin>>staffid;
    fflush(stdin);
    cout<<"\tEnter the password  : ";
    char pass[15],c;
	short i=0;
    while((c=getch())!=13){
			pass[i]=c; i++; cout<<'*';
		}
	pass[i]='\0';
	strupr(pass);
	strupr(staffid);
	if(strcmp(staffid,pass)){                       
       cout<<"Inavlid id/password..."<<endl;
      return -1;
    }
    STAFF staf;
	if(USN_NOT_FOUND==(flag=(staf.init(staffid)))){
		cin.get();
		return 0;
	}
	   else if(flag) return 0;
	//object of student class initialized with usn
    while(1){
    clrscr();
	title();
	cout<<"\tLogin type : Staff  ["<<staffid<<"]"<<endl;
       cout<<"\t\tMenu"<<endl;
       cout<<"\t\t1 : View profile\n\t\t2 : Manage attendence\n\t\t3 : Manage marks\n\t\t4 : Exit"<<endl;
       cout<<"\n\tEnter your choice  : ";
       int choice;
       cin>>choice;
       switch(choice){
           case 1 :fflush(stdin); clrscr(); staf.showProfile();

		   			break;
           case 2 : fflush(stdin); clrscr(); staf.manageAttendence();
                    break;
           case 3 : fflush(stdin); clrscr();
		   				staf.manageMarks();
                    break;
           case 4 : cout<<"Logging out...["<<staffid<<"]";
		   			Sleep(1000);
                    return SUCCESS;
            default : cout<<"Select valid choice : ";
		  Sleep(1000);
		         }
    }
}


int admin(){
    char id[10];
    char pass[15],c;
	clrscr();
	title();
	cout<<"\tLogin type : Administrator"<<endl;
    cout<<"\n\tEnter admin id           : ";
	cin>>id;
	fflush(stdin);
	strupr(id);
	strcpy(pass,id);
    ADMIN ad(pass);
    cout<<"\n\tEnter admin password     : ";
	short i=0;
    while((c=getch())!=13){ pass[i]=c; i++; cout<<'*';
	  }
	pass[i]='\0';
	if(!ad.isValidPass(pass)){
		cout<<"\r\tAuthentication error..."<<pass<<endl;
      	cin.get();
    	exit(0);
	}
	//object of student class initialized with usn
    while(1){
    clrscr();
	title();
    cout<<"\tLogin type : Administrator  ["<<id<<"]"<<endl;
    cout<<"\t\tMenu"<<endl;
    cout<<"_______________________________________________________________________________"<<endl;
	cout<<"\t\t1 : Admit student\n\t\t2 : Remove Student\n\t\t3 : Add Staff\n\t\t4 : Remove Staff\n\t\t5 : List Students\n\t\t6 : Manage attendance";
	cout<<"\n\t\t7 : View student attendance\n\t\t8 : View student marks \n\t\t9 : Notifications \n\t\t10: Check Complaints \n\t\t11: Exit"<<endl;
	cout<<"_______________________________________________________________________________"<<endl;
	cout<<"\n\tEnter your choice  : ";
    int choice;
    cin>>choice;
	char s[5];
	switch(choice){
           case 3 : ad.addstaff();
		   				break;
		   case 1 : clrscr();
		   			ad.admitStudent();
		   				break;
		   case 2 : cout<<"\n\tEnter the valid USN : "; cin>>pass;
					strupr(pass);
                    ad.removeStudent(pass);
		   				break;
			case 4 :cout<<"\n\tEnter the staff id : "; cin>>pass;
					strupr(pass);
					ad.removeStaff(pass);
						break;
			case 5 :clrscr();
		   			ad.listStudent();
                    	break;
			case 6 :clrscr();
		   			ad.manageAttendence();
                    break;
			case 8 :clrscr();
		   			ad.viewMarks();
		   		    	break;
		   	case 7 :clrscr();
		   			ad.viewAttendence();
		   		   		break;
		  	case 9 :clrscr();
		   		   	ad.Notification();
		   		   		break;
		   	case 10 :clrscr();
		   		   	ad.complaint();
		   		   		break;		   	
           	case 11 :cout<<"Logging out...["<<id<<"]";
		   			Sleep(1000);
                    	return 0;
			case 23 :
					ad.showProfile();
           default : cout<<"Select valid choice : ";
					Sleep(1000);
       }
    }
}



