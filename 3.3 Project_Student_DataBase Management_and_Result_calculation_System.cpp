#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<stdlib.h>

using namespace std;

int UsnToBeUpdated=0;




class student 
{
	private:
		char Student_Name[50];
		int usn;
		int fs, st, wt, dj, ns, fsl, mad, stl;
		int crt1, crt2, crt3, crt4, crt5, crt6, crt7, crt8;
		int value1, value2, value3, value4, value5, value6, value7, value8;
		double student_sgpa;
		char Student_Grade;
		float total_percentage;
		bool flag;
		double total_sub;
		double total_crts;
		double sgpa;
		

		
		
		
		
	public:
		student();
		void getdata();
		void CheckForDuplicationInFile();
		void showdata();
		void TabularDisplay();
		int GetStudentRollNo();
		void ShowStudentRecord(int);
		void Write_Student_Record_In_File();
		void Update_Student_Record(int);
		void Delete_Student_Record(int);
		void Delete_From_Duplicate_File(int);
		void Show_Result_Menu();
		void Display_Class_Result();
		double grade_calculator(double totalMark, int crts);
		void value_of_subj();
		void CalculateGrade();
		
};


void student::getdata()
{
	flag=false;
	cout<<"\nEnter the RollNo of the student : ";
	cin>>usn;
	if(UsnToBeUpdated!=usn)
	CheckForDuplicationInFile();
	
	if(flag==true)
	{
		cout<<"Error duplicate record"<<endl;
		return;
	}
	cout<<"\n\nEnter the name of student: ";
	cin.ignore();
	cin.getline(Student_Name,50);
	cout<<"\nEnter The marks in filestructure out of 100 : ";
    cin>>fs;
    cout<<"Its Credit :";
    cin>>crt1;
    cout<<"\nEnter The marks in softwaretesting out of 100 : ";
    cin>>st;
    cout<<"Its Credit :";
    cin>>crt2;
    cout<<"\nEnter The marks in webtech out of 100 : ";
    cin>>wt;
    cout<<"Its Credit :";
    cin>>crt3;
    cout<<"\nEnter The marks in datamining/java out of 100 : ";
    cin>>dj;
    cout<<"Its Credit :";
    cin>>crt4;
    cout<<"\nEnter The marks in NCS/SCM out of 100 : ";
    cin>>ns;
    cout<<"Its Credit :";
    cin>>crt5;
    cout<<"\nEnter The marks in FS LAB out of 100 : ";
    cin>>fsl;
    cout<<"Its Credit :";
    cin>>crt6;
    cout<<"\nEnter The marks in MAD LAB out of 100 : ";
    cin>>mad;
    cout<<"Its Credit :";
    cin>>crt7;
    cout<<"\nEnter The marks in ST LAB out of 100 : ";
    cin>>stl;
    cout<<"Its Credit :";
    cin>>crt8;
    CalculateGrade();
	
}


void student::CheckForDuplicationInFile()
{
	int Current_usn=0;
	flag=false;
	ifstream infile("DuplicateCheckingFile.txt");
	while(!infile.eof())
	{
		infile>>Current_usn;
		if(Current_usn==usn)
		{
			flag=true;
		}
	}
	infile.close();
	if(flag==false)
	{
		ofstream outfile("DuplicateCheckingFile.txt",ios::app);
		outfile<<"\n"<<usn;
		outfile.close();
		
	}
}


void student::showdata()
{
	cout<<"\nRollNo of student = "<<usn;
	cout<<"\nName of the Student = "<<Student_Name;
	cout<<"\nMarks in filestructure = "<<fs;
	cout<<"\nMarks in softwaretesting = "<<st;
	cout<<"\nMarks in webtech = "<<wt;
	cout<<"\nMarks in datamining/java = "<<dj;
	cout<<"\nMarks in NCS/SCM = "<<ns;
	cout<<"\nMarks in FS lab = "<<fsl;
	cout<<"\nMarks in MAD lab = "<<mad;
	cout<<"\nMarks in ST lab = "<<stl;
	cout<<"\nSGPA = "<<sgpa;
	cout<<"\nGrade of the student = "<<Student_Grade;
	
}

student::student()
{
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	outFile.close();
	ofstream outDFile;
	outDFile.open("DuplicateCheckingFile.txt",ios::app);
	outDFile.close();
}

void student::Write_Student_Record_In_File()
{
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	
	getdata();
	
	if(flag==false)
	{
		outFile.write(reinterpret_cast<char*>(this),sizeof(student));
		outFile.close();
		cout<<"\n\n student record has been created\n";
	}
	if(flag==true)
	{
		cout<<"student record not created due to duplication\n";
		outFile.close();
	}
	cin.ignore();
	cin.get();
}

void student::Update_Student_Record(int n)
{
	UsnToBeUpdated=n;
	bool found=false;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
        cin.ignore();
        cin.get();
        return;
	}
	while(!File.eof()&&found==false)
	{
		File.read(reinterpret_cast<char*> (this), sizeof(student));
		if(GetStudentRollNo()==n)
		{
			showdata();
			cout<<"\n\nPlease Enter the New Details of student: "<<endl;
			getdata();
			if(flag==false)
			{
				int pos=(-1)*static_cast<int>(sizeof(*this));
				File.seekp(pos,ios::cur);
				File.write(reinterpret_cast<char *> (this), sizeof(student));
			}
			found=true;
		}
	}
	File.close();
	if(flag==true)
	{
		cout<<"could not update because this RollNo already exists";
	}
	if(found==false)
	{
		cout<<"\n\n Record Not Found";
	}
	cin.ignore();
	cin.get();
	
	if(flag==false&&found==true&&UsnToBeUpdated!=usn)
    {
    	Delete_From_Duplicate_File(n);
    }
    UsnToBeUpdated=0;
}


void student::Delete_Student_Record(int n)
{
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\nFile could not be opened..Press any key";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (this), sizeof(student)))
	{
		if(GetStudentRollNo()!=n)
		{
			outFile.write(reinterpret_cast<char *> (this), sizeof(student));
		}
	}
	
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\nRecord deleted..Press any key";
	cin.ignore();
	cin.get();
	Delete_From_Duplicate_File(n);
}


void student::Delete_From_Duplicate_File(int RollNoOfRecord)
{
	int Current_usn;
	ifstream InFile("DuplicateCheckingFile.txt");
	ofstream OutFile("TempFile.txt");
	InFile.seekg(0,ios::beg);
	while(!InFile.eof())
	{
		InFile>>Current_usn;
		if(Current_usn!=RollNoOfRecord)
		{
			OutFile<<"\n"<<Current_usn;
		}
	}
	
	InFile.close();
	OutFile.close();
	
	remove("DuplicateCheckingFile.txt");
	rename("TempFile.txt","DuplicateCheckingFile.txt");
	
	cin.ignore();
	cin.get();
}

double student::grade_calculator(double totalMark, int crts) { 

	
    
	if(totalMark>=9.0 && totalMark<=10.0)
    return totalMark*crts;
            
    else if(totalMark>=8.5 && totalMark<9.0)
    return totalMark*crts;
 
    else if(totalMark>=8.0 && totalMark<8.5)
    return totalMark*crts; 
 
    else if(totalMark>=7.5 && totalMark<8.0)
    return totalMark*crts;   
 
    else if(totalMark>=7.0 && totalMark<7.5)
    return totalMark*crts;
 
    else if(totalMark>=6.5 && totalMark<7.0)
    return totalMark*crts;
 
    else if(totalMark>=6.0 && totalMark<6.5)        
	return totalMark*crts;
 
    else if(totalMark>=5.0 && totalMark<6.0)        
	return totalMark*crts;
 
    else if(totalMark>=4.5 && totalMark<5.0)
    return totalMark*crts;
 
    else if(totalMark>=4.0 && totalMark<4.5)
    return totalMark*crts;
 
    else if(totalMark>=3.0 && totalMark<4.0)
    return totalMark*crts;
 
    else if(totalMark>=0 && totalMark<3.0)
    return totalMark*crts;
 
    else       
    return totalMark*crts;
}

void student::value_of_subj(){
//Grade multiply by it's crts for each subjects
value1=grade_calculator((fs/10),crt1);
value2=grade_calculator((st/10),crt2);
value3=grade_calculator((wt/10),crt3);
value4=grade_calculator((dj/10),crt4);
value5=grade_calculator((ns/10),crt5);
value6=grade_calculator((fsl/10),crt6);
value7=grade_calculator((mad/10),crt7);
value8=grade_calculator((stl/10),crt8);

	total_sub=value1+value2+value3+value4+value5+value6+value7+value8;
	total_crts=crt1+crt2+crt3+crt4+crt5+crt6+crt7+crt8;
	
	sgpa=total_sub/total_crts;
	
}



void student::CalculateGrade()
{

	value_of_subj();
	
	total_percentage=(fs+st+wt+dj+ns+fsl+mad+stl)/8.0;
	if(sgpa>=9.0)
	Student_Grade='S';
	if(sgpa>=8.0&&sgpa<=8.9)
    Student_Grade='A';
    if(sgpa>=7.0&&sgpa<=7.9)
    Student_Grade='B';
    if(sgpa>=6.0&&sgpa<=6.9)
    Student_Grade='C';
    if(sgpa>=5.0&&sgpa<=5.9)
    Student_Grade='D';
    if(sgpa>4.0&&sgpa<=4.9)
    Student_Grade='E';
    if(sgpa<=4.0)
    Student_Grade='F';
}

void student::TabularDisplay()
{

	cout<<usn<<setw(7)<<" "<<Student_Name<<setw(20-strlen(Student_Name))<<fs<<setw(5)<<st<<setw(5)<<wt<<setw(9)<<dj<<setw(12)<<ns<<setw(10)<<fsl<<setw(8)<<mad<<setw(8)<<stl<<setw(10)<<total_percentage<<setw(9)<<Student_Grade<<endl;
}

int student::GetStudentRollNo()
{
	return usn;
}

void student::ShowStudentRecord(int n)
{
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not opened !! Press any key to continue";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	
	while(inFile.read(reinterpret_cast<char *> (this),sizeof(student)))
	{
		if(GetStudentRollNo()==n)
		{
			showdata();
            flag=true;
		}
	}
	inFile.close();
    if(flag==false)
    cout<<"\n\nrecord does not exist";
    cin.ignore();
    cin.get();
}


void student::Show_Result_Menu()
{
	char ch;
	int rno;
	system("cls");
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\n\t3. Back to Main Menu/Home Screen";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
		case '1':Display_Class_Result();
			break;
		case '2':cout<<"\n\n\tEnter the RollNo of Student = ";
				 cin>>rno;
				 ShowStudentRecord(rno);		
				 break;
		case '3':break;
		default: cout<<"\a";
	}
}


void student::Display_Class_Result()
{
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be opened.. Press any key..";
		cin.ignore();
		cin.get();
		return;
	}
	
	cout<<"\n\n\t\tALL CLASS RESULT \n\n";
	cout<<"=================================================================================================================\n";
	cout<<"RNO       Name              fs   st   wt     dm/java     ncs/scm     FSL     MAD     STL     %age     Grade"<<endl;
	cout<<"=================================================================================================================\n";
	
	while(inFile.read(reinterpret_cast<char *> (this), sizeof(student)))
	{
		TabularDisplay();	
	}
	
	inFile.close();
	cin.ignore();
	cin.get();
}


void intro();
void entry_menu();
void display_all();

int main()
{
	system("CLS");
	system("color F0");
	char ch;
	student std_obj;
  	cout.setf(ios::fixed|ios::showpoint);
  	cout<<setprecision(2);
	intro();
	do
	{
	system("cls");
	intro();
	cout<<"\n\n\n\t\t\t\tHOME SCREEN\n\n\n";
	cout<<"\n\n\t1. Result Calculation System";
	cout<<"\n\n\t2. Student Database Management System";
	cout<<"\n\n\t3. Exit";
	cout<<"\n\n\n\n\n\tPlease Select Your Option (1-3)";
	cin>>ch;
	switch(ch)
	{
		case '1':
			std_obj.Show_Result_Menu();
			break;
		case '2':
			entry_menu();
			break;
		case '3': exit(1);
			break;
		default: cout<<"\a";
	}
	}while(ch!=3);
	
		
	system("pause");
	return 0;
}

void intro()
{
	cout<<"\n\n\n****  WELCOME TO STUDENT DATABASE MANAGEMENT AND RESULT CALCULATION SYSTEM  ****\n\n";
}

void entry_menu()
{
	char ch;
	int num;
	student std;
	system("CLS");
	cout<<"\n\n\n\t\t\tSTUDENT DATABASE MANAGEMENT SYSTEM MENU";
	cout<<"\n\n\t1. CREATE STUDENT RECORD";
	cout<<"\n\n\t2. SHOW RECORD OF ALL STUDENTS";
	cout<<"\n\n\t3. SEARCH STUDENTS RECORD";
	cout<<"\n\n\t4. UPDATE STUDENT RECORD";
	cout<<"\n\n\t5. DELETE STUDENT RECORD";
	cout<<"\n\n\t6. BACK TO HOME SCREEN";
	cout<<"\n\n\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
		case '1':
			std.Write_Student_Record_In_File();
			break;
		case '2':
			display_all();
			break;
		case '3':
			cout<<"\n\n\t Please Enter The RollNo: ";
			cin>>num;
			std.ShowStudentRecord(num);
			break;
		case '4':
			cout<<"\n\n\t Please Enter The RollNo: ";
			cin>>num;
			std.Update_Student_Record(num);
			break;
		case '5':
			cout<<"\n\n\t Please Enter The RollNo: ";
			cin>>num;
			std.Delete_Student_Record(num);
			break;
		case '6':
			break;
		default:cout<<"\a"; entry_menu();
		
	}
}

void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n==============================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}