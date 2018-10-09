// This Project is Done By Yoo Seung Jae of Sogang University
#include <iostream>
#include <fstream>
#include <string>
#include "deltext.h"
#include "iobuffer.h"
#include "member.h"
#include "lecture.h"
#include "purchase.h"
#include "buffile.h"
#include "recfile.h"

#define Max_Buffer 12000

using namespace std;

int printMenu(void);
int showMember(void);
int showLecture(void);
int showPurchase(void);
int MemberTest(int);
int LectureTest(int);
int PurchaseTest(int);
int LecturePurchaseSystem(void);
int showSystemMenu(void);
int SearchingByID(int, string, string);
int InsertingByID(void);
int DeletingByID(void);
int ModifyingByID(void);
int DeleteMember(string);
int DeleteLecture(string);
int DeletePurchase(string);

Member* memberArr = new Member[Max_Buffer];
Lecture* lectureArr = new Lecture[Max_Buffer];
Purchase* purchaseArr = new Purchase[Max_Buffer];
int index;

int main(void) {
	string input;
	int change_to_int;
	int test_mode = 1;
	while (true) {
		printMenu();
		cin >> input;
		cout << "" << endl;
		cout << "*************************************" << endl;
		
		change_to_int = std::stoi(input);

		switch (change_to_int) {
			case 1:
				showMember();
				break;
			case 2:
				showLecture();
				break;
			case 3:
				showPurchase();
				break;
			case 4:
				MemberTest(test_mode);
				break;
			case 5:
				LectureTest(test_mode);
				break;
			case 6:
				PurchaseTest(test_mode);
				break;
			case 7:
				LecturePurchaseSystem();
				break;
			case 8:
				return 0;
			default:
				break;
		}
	}
	return 0;
}

int printMenu() {
	cout << "***************************************" << endl;
	cout << "* 1. showMember             ***********" << endl;
	cout << "* 2. showLecture            ***********" << endl;
	cout << "* 3. showPurchase           ***********" << endl;
	cout << "* 4. MemberTest             ***********" << endl;
	cout << "* 5. LectureTest            ***********" << endl;
	cout << "* 6. PurchaseTest           ***********" << endl;
	cout << "* 7. LecturePurchaseSystem  ***********" << endl;
	cout << "* 8. Exit                   ***********" << endl;
	cout << "***************************************" << endl;
	cout << "" << endl;
	cout <<  "input : ";

	return 0;
}


int showMember() {
	string filename = "listOfMember.txt";
	string error = "\nlistOfMember.txt File Open Error!\n";
	ifstream ifs(filename);
	long long streamsizeMax = numeric_limits<streamsize>::max();

	if (ifs.fail())
	{
		cout << error << endl;
		return 0;
	}
	else {
		ifs.ignore(streamsizeMax, '\n');

		int i = 0;
		while(i < 10)
		{
			Member M;
			ifs >> M;
			cout << M << endl;
			i++;
		}
		ifs.close();
		return 0;
	}
}

int showLecture() {
	string filename = "listOfLecture.txt";
	
	string error = "\nlistOfLetcure.txt File Open Error!\n";
	ifstream ifs(filename);
	long long streamsizeMax = numeric_limits<streamsize>::max();
	if (ifs.fail())
	{
		cout << error << endl;
		return 0;
	}
	else {
		ifs.ignore(streamsizeMax, '\n');
		int i = 0;
		while(i < 10)
		{
			Lecture L;
			ifs >> L;
			cout << L << endl;
			i++;
		}
		ifs.close();
		return 0;
	}

	
}

int showPurchase() {
	string filename = "listOfPurchase.txt";
	string error = "\nlistOfPurchase.txt File Open Error!\n";
	ifstream ifs(filename);
	long long streamsizeMax = numeric_limits<streamsize>::max();


	if (ifs.fail())
	{
		cout << error << endl;
		return 0;
	}

	else {
		int temporary;
		ifs >> temporary;
		ifs.ignore(streamsizeMax, '\n');

		int i = 0;
		while (i < 10)
		{
			Purchase P;
			ifs >> P;
			cout << P << endl;
			i++;
		}
		ifs.close();
		return 0;
	}
}

int MemberTest(int willprint) {
	ifstream ifs("listOfMember.txt");
	string error = "\nlistOfMember.txt File Open Error!\n";
	long long streamsizeMax = numeric_limits<streamsize>::max();
	int recordsize = 1000;
	char delimiter = '|';

	if (ifs.fail()) {
		cout << error << endl;
		return 0;
	}

	else {
		int record;
		ifs >> record;
		ifs.ignore(streamsizeMax, '\n');
		string error = "\nWrite Error!\n";

		DelimFieldBuffer buffer(delimiter, recordsize);
		RecordFile <Member> MemberFile(buffer);

		
		// MemberFile Class
		MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
		int i = 0;
		while(i < record) {
			Member mem;
			ifs >> mem;
			int recaddr;
			if ((recaddr = MemberFile.Write(mem)) == -1) {
				if (willprint) {
					cout << error << endl;
				}
				else {
					cout << "Write at " << recaddr << endl;
				}					
			}
			i++;
		}

		MemberFile.Close();
		
		MemberFile.Open("fileOfMember.dat", ios::in);
		i = 0;
		while(i < 10) {
			Member mem;
			MemberFile.Read(mem);
			if (willprint) {
				cout << mem << endl;
			}
			i++;
		}
		MemberFile.Close();
		ifs.close();
		return 0;
	}
}

int LectureTest(int willprint) {

	string filename = "listOfLecture.txt";
	string error = "\nlistOfLecture.txt File Open Error!\n";

	ifstream ifs(filename);
	long long streamMax = numeric_limits<streamsize>::max();
	char delimiter = '|';
	int recordSize = 1000;

	if (ifs.fail())
	{
		cout << error << endl;
		return 0;
	}
	int l;
	ifs >> l;
	ifs.ignore(streamMax, '\n');

	DelimFieldBuffer buffer(delimiter, recordSize);
	RecordFile <Lecture> LectureFile(buffer);

	
	// Class Create
	LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);
	int i = 0;

	while(i < l) {
		Lecture L;
		ifs >> L;
		int recaddr;
		if ((recaddr = LectureFile.Write(L)) == -1) {
			if (willprint) {
				cout << "\nWrite Error!\n" << endl;
			}
			else {
				cout << "Write at " << recaddr << endl;
			}
		}
		i++;
	}
	LectureFile.Close();

	LectureFile.Open("fileOfLecture.dat", ios::in);
	i = 0;
	while(i < 10) {
		Lecture L;
		LectureFile.Read(L);
		if (willprint) {
			cout << L << endl;
		}
		i++;
	}
	LectureFile.Close();
	ifs.close();
	return 0;
}

int PurchaseTest(int willprint) {
	string filename = "listOfPurchase.txt";
	string error = "\nlistOfPurchase.txt File Open Error!\n";
	long long streamMax = numeric_limits<streamsize>::max();
	char delimiter = '|';
	int bufferSize = 10000;

	ifstream ifs(filename);
	if (ifs.fail())
	{
		cout << error << endl;
		return 0;
	}

	else {
		int n;
		ifs >> n;
		ifs.ignore(streamMax, '\n');

		DelimFieldBuffer buffer(delimiter, bufferSize);
		RecordFile <Purchase> PurchaseFile(buffer);


		PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
		int i = 0;
		while(i < n) {
			Purchase s;

			ifs >> s;
			int recaddr;
			if ((recaddr = PurchaseFile.Write(s)) == -1) {
				if (willprint) {
					cout << "Write Error!" << endl;
				}
				else {
					cout << "Write at " << recaddr << endl;
				}
			}
			i++;
		}
		PurchaseFile.Close();

		// Purchase Class
		PurchaseFile.Open("fileOfPurchase.dat", ios::in);
		i = 0;
		while(i < 10) {

			Purchase P;

			PurchaseFile.Read(P);
			if (willprint) {
				cout << P << endl;
			}
			i++;
		}
		PurchaseFile.Close();
		ifs.close();
		return 0;
	}

	
}

int LecturePurchaseSystem() {
	string input;
	int change_to_int;
	int test_mode = 1;
	int real_mode = 0;
	string filename;
	string wantedID;
	static int istest = 0;

	if (istest == 0) {
		MemberTest(real_mode);
		LectureTest(real_mode);
		PurchaseTest(real_mode);
		istest = 1;
	}
	
	while (true) {
		showSystemMenu();
		cin >> input;
		cout << "***************************************" << endl;
		change_to_int = std::stoi(input);
		switch (change_to_int) {
			case 1:
				cout << "Submit file name : ";
				cin >> filename;
				cout << "Submit ID : ";
				cin >> wantedID;
				SearchingByID(test_mode, filename, wantedID);
				break;
			case 2:
				InsertingByID();
				break;
			case 3:
				DeletingByID();
				break;
			case 4:
				ModifyingByID();
				break;
			default:
				return 0;
		}
	}

	return 0;
}


int showSystemMenu() {
	cout << "" << endl;
	cout << "#######################################" << endl;
	cout << "# 1. Search               #############" << endl;
	cout << "# 2. Insert               #############" << endl;
	cout << "# 3. Delete               #############" << endl;
	cout << "# 4. Modify               #############" << endl;
	cout << "# The Others. Exit        #############" << endl;
	cout << "#######################################" << endl;
	cout << "" << endl;
	cout << "input : ";

	return 0;
}


int SearchingByID(int flag, string filename, string want_ID) {
	int ifs_last;
	int find_Addr = 0;
	int* addr_arr = (int*)malloc(sizeof(int));
	int id_cnt = 0;
	Member m;
	Purchase p;
	Lecture l;
	Purchase* p_arr = new Purchase[30];
	int errorflag = 0;
	long long streamMax = numeric_limits<streamsize>::max();
	string printError = " OPEN ERROR!!\n";
	char delimiter = '|';
	int bufferSize = 1000;
	int find_ID = 0;
	int reset = 0;
	ifstream ifs(filename);
	


	if (ifs.fail() == 1) {
		cout << filename << printError << endl;
		return 0;
	}

	else {
		ifs.ignore(streamMax, '\n');

		if (!filename.compare("fileOfMember.dat")) {
			DelimFieldBuffer buffer(delimiter, bufferSize);
			RecordFile <Member> MemberFile(buffer);
			MemberFile.Open("fileOfMember.dat", ios::in);

			ifs.clear();
			ifs.seekg(reset, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(reset, ifs.beg);

			while (ifs.tellg() < ifs_last) {
				MemberFile.Read(m);
				ifs.seekg(m.getLength(), ifs.cur);
				if (m.getID().compare(want_ID)==0) {
					find_ID = 1;
					id_cnt = id_cnt + 1;
					break;
				}
				find_Addr = find_Addr + m.getLength();
			}
			MemberFile.Close();
			ifs.close();
		}
		else if (!filename.compare("fileOfLecture.dat")) {
			DelimFieldBuffer buffer(delimiter, bufferSize);
			RecordFile <Lecture> LectureFile(buffer);
			LectureFile.Open("fileOfLecture.dat", ios::in);
			ifs.clear();
			ifs.seekg(reset, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(reset, ifs.beg);
			while (ifs.tellg() < ifs_last) {

				LectureFile.Read(l);
				ifs.seekg(l.getLength(), ifs.cur);

				if (memcmp(l.getLectureID(), want_ID.c_str(), strlen(l.getLectureID()))==0) {
					
					find_ID = 2;
					id_cnt = id_cnt + 1;
					break;
				}
				find_Addr = find_Addr + l.getLength();
			}

			LectureFile.Close();
			ifs.close();

		}
		else if (!filename.compare("fileOfPurchase.dat")) {
			DelimFieldBuffer buffer(delimiter, bufferSize * 10);
			RecordFile <Purchase> PurchaseFile(buffer);
			PurchaseFile.Open("fileOfPurchase.dat", ios::in);
			ifs.clear();
			ifs.seekg(reset, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(reset, ifs.beg);

			while (ifs.tellg() < ifs_last) {

				PurchaseFile.Read(p);
				ifs.seekg(p.getLength(), ifs.cur);
				if (strcmp(p.getPurchaseID(), want_ID.c_str())==0) {
					find_ID = 3;
					id_cnt = id_cnt + 1;
					break;
				}
				else if (strcmp(p.getLectureID(), want_ID.c_str())==0) {
					find_ID = 3;
					id_cnt = id_cnt + 1;
					break;
				}
				else if (p.getMemberID().compare(want_ID)==0) {
					find_ID = 3;
					id_cnt = id_cnt + 1;

					addr_arr = (int*)realloc(addr_arr, id_cnt * sizeof(int));
					int index = id_cnt - 1;
					p_arr[index] = p;
					addr_arr[index] = find_Addr;
				}
				if (errorflag) {
					cout << "error occured!" << endl;
					return 0;
				}
				find_Addr = find_Addr + p.getLength();
			}
			PurchaseFile.Close();
			ifs.close();
		}
		else {
			cout << "You have a wrong file." << endl;
			cout << "-----------------------" << endl;
			ifs.close();
		}

		if (find_ID) {
			if (errorflag) {
				cout << "Invalid operation!" << endl;
				return 0;
			}
			if (flag) {
				cout << "\nSearching Process Completed\n" << endl;
				cout << "-----------------------" << endl;
				cout << "From : " << filename << endl;
				switch (find_ID) {
				case 1:
					cout << m;
					break;
				case 2:
					cout << l;
					break;
				case 3:
					if (id_cnt) {
						cout << p;
					}
					else {
						int i = 0;
						while (i < id_cnt) {
							cout << p_arr[i] << endl;
							cout << " ****************** " << endl;
							cout << "starting address : " << addr_arr[i] << endl;
							i++;
						}
					}

					break;
				}
				if (id_cnt) {
					cout << " ****************** " << endl;
					cout << "starting address : " << find_Addr << endl;
				}
			}
			return 1;
		}
		else {
			if (flag==1) {
				cout << "This id doesn't exist in DB." << endl;
			}
			return 0;
		}
		return 0;
	}
	
}

int InsertingByID() {
	string want_ID;
	string filename;
	char delimiter = '|';
	int reset = 0;
	int errorflag = 0;
	int bufferSize = 1000;
	long long streamMax = numeric_limits<streamsize>::max();
	int find;
	cout << "Submit ID : ";
	cin >> want_ID;
	cout << "-----------------------" << endl;
	cout << "Submit file name : ";
	cin >> filename;
	cout << "-----------------------" << endl;
	find = SearchingByID(0, filename, want_ID);
	if (find == 1) {
		cout << "**********************" << endl;
		cout << "duplicate id" << endl;
		cout << "**********************" << endl;
	}
	else {
		if (!filename.compare("fileOfMember.dat")) {
			index = 0;
			ifstream ifs("fileOfMember.dat");
			if (ifs.fail() == 1) {
				cout << "fileOfMember.dat open error!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			ifs.ignore(streamMax, '\n');

			Member m;
			int ifs_last;
			DelimFieldBuffer buffer(delimiter, bufferSize);
			RecordFile <Member> MemberFile(buffer);
			MemberFile.Open("fileOfMember.dat", ios::in);
			
			ifs.clear();
			ifs.seekg(reset, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(reset, ifs.beg);
			Member m_temp;
			while (ifs.tellg() < ifs_last) {
				MemberFile.Read(m);

				if (m_temp.getID().compare(m.getID()) == 0) {
					break;
				}
				memberArr[index] = m;
				m_temp = m;
				index = index + 1;
				ifs.seekg(m.getLength(), ifs.cur);
			}

			if (errorflag) {
				cout << "error!!" << endl;
				return 0;
			}
			Member n;
			string temp;
			char* temporary = new char(100);

			n.setID(want_ID);

			cout << "Submit New Pwd : ";
			cin >> temp;
			n.setPassword(temp);
			cout << "-----------------------" << endl;

			cout << "Submit New Name : ";
			cin >> temp;
			n.setName(temp);
			cout << "-----------------------" << endl;

			cout << "Submit New Phone-Number : ";
			cin >> temp;
			n.setPhoneNumber(temp);
			cout << "-----------------------" << endl;

			cout << "Submit New Address : ";
			cin >> temp;
			n.setAddress(temp);
			cout << "-----------------------" << endl;

			cout << "Submit New Mileage : ";
			cin >> temporary;
			cout << "-----------------------" << endl;

			if (errorflag) {
				cout << "error occured!" << endl;
				return 0;
			}
			if (strlen(temporary) != 10) {
				cout << "Invalid Mileage Number!!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			n.setMileage(temporary);

			memberArr[index] = n;
			index = index + 1;

			MemberFile.Close();
			MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
			int recaddr;
			int i = 0;
			while(i < index) {
				if ((recaddr = MemberFile.Write(memberArr[i])) == -1) {
					cout << "Write Error Occured!" << endl;
					cout << "-----------------------" << endl;
				}
				i++;
			}

			if (errorflag) {
				cout << "Write Error Occured!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}

			MemberFile.Close();
			ifs.close();


		}
		else if (!filename.compare("fileOfLecture.dat")) {
			index = 0;
			ifstream ifs("fileOfLecture.dat");
			if (ifs.fail() == 1) {
				cout << "fileOfLecture.dat open error!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			ifs.ignore(streamMax, '\n');

			Lecture m;
			int ifs_last;
			
			if (errorflag) {
				cout << "error!" << endl;
				return 0;
			}

			DelimFieldBuffer buffer(delimiter, bufferSize);
			RecordFile <Lecture> LectureFile(buffer);
			LectureFile.Open("fileOfLecture.dat", ios::in);
			
			ifs.clear();	
			ifs.seekg(reset, ifs.end);
			
			ifs_last = ifs.tellg();
			ifs.seekg(reset, ifs.beg);
			Lecture m_temp;

			while (ifs.tellg() < ifs_last) {
				LectureFile.Read(m);
				if (strcmp(m_temp.getLectureID(), m.getLectureID()) == 0) {
					break;
				}
				lectureArr[index] = m;
				m_temp = m;
				index = index + 1;
				ifs.seekg(m.getLength(), ifs.cur);
			}
			Lecture n;

			if (errorflag) {
				cout << "error occured!" << endl;
				return 0;
			}
			string temp;
			char* temporary = new char(100);
			int temp_i;

			if (strlen(want_ID.c_str()) != 12) {
				cout << "Invalid Lecture length!!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			n.setLectureID(want_ID.c_str());

			cout << "Submit New Subject : ";
			cin >> temporary;
			cout << "-----------------------" << endl;
			n.setSubject(temporary);

			cout << "Submit New Level : ";
			cin >> temporary;
			cout << "-----------------------" << endl;
			if (strlen(temporary) != 1) {
				cout << "Invalid Level length!!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			n.setLevel(temp.c_str());

			cout << "Submit New Price : ";
			cin >> temp_i;
			cout << "-----------------------" << endl;
			n.setPrice(temp_i);

			cout << "Submit New Extension : ";
			cin >> temporary;
			cout << "-----------------------" << endl;
			if (strlen(temporary) != 1) {
				cout << "Invalid Extension length!!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			n.setExtension(temporary);

			cout << "Submit New DueDate : ";
			cin >> temp_i;
			cout << "-----------------------" << endl;
			n.setDueDate(temp_i);

			cout << "Submit New NameOfTeacher : ";
			cin >> temporary;
			cout << "-----------------------" << endl;
			n.setNameOfTeacher(temporary);

			cout << "Submit New TextBook : ";
			cin >> temporary;
			cout << "-----------------------" << endl;
			n.setTextBook(temporary);

			lectureArr[index] = n;
			index = index + 1;

			LectureFile.Close();

			LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);
			int recaddr;
			int i = 0;

			if (errorflag) {
				cout << "write error occured!" << endl;
			}
			while(i < index) {
				if ((recaddr = LectureFile.Write(lectureArr[i])) == -1) {
					cout << "Write Error Occured!" << endl;
					cout << "-----------------------" << endl;
				}
				i++;
			}
			LectureFile.Close();

			ifs.close();
		}
		else if (!filename.compare("fileOfPurchase.dat")) {
			index = 0;
			ifstream ifs("fileOfPurchase.dat");
			if (ifs.fail() == 1) {
				cout << "fileOfPurchase.dat open error!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			ifs.ignore(streamMax, '\n');

			Purchase m;
			int ifs_last;

			DelimFieldBuffer buffer(delimiter, bufferSize * 10);
			RecordFile <Purchase> PurchaseFile(buffer);
			PurchaseFile.Open("fileOfPurchase.dat", ios::in);
			
			ifs.clear();
			ifs.seekg(reset, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(reset, ifs.beg);
			Purchase m_temp;
			while (ifs.tellg() < ifs_last) {
				PurchaseFile.Read(m);
				if (strcmp(m_temp.getPurchaseID(), m.getPurchaseID()) == 0) {
					break;
				}
				m_temp = m;
				purchaseArr[index] = m;
				index = index + 1;
				ifs.seekg(m.getLength(), ifs.cur);
			}

			Purchase p;
			char* temporary = new char(100);
			string temp;
			if (errorflag) {
				cout << "error occured!" << endl;
			}

			if (strlen(want_ID.c_str()) != 16) {
				cout << "INVALID PID length!!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			p.setPurchaseID(want_ID.c_str());

			cout << "New Ticket ID : ";
			cin >> temp;
			cout << "-----------------------" << endl;
			if (strlen(temp.c_str()) != 12) {
				cout << "Wrong TID length" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			int find_flag = SearchingByID(0, "fileOfTicket.dat", temp);
			if (find_flag == 0) {
				cout << "No Match exist!!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			p.setPurchaseID(temp.c_str());

			cout << "New Member ID : ";
			cin >> temp;
			cout << "-----------------------" << endl;
			find_flag = SearchingByID(0, "fileOfMember.dat", temp);
			if (find_flag == 0) {
				cout << "No Match exist!!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			p.setMemberID(temp);

			cout << "New Mileage : ";
			cin >> temporary;
			cout << "-----------------------" << endl;
			if (strlen(temporary) != 10) {
				cout << "Invalid Mileage Length!!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			p.setMileage(temporary);

			purchaseArr[index] = p;

			index = index + 1;

			PurchaseFile.Close();

			PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
			int recaddr;
			int i = 0;
			while(i < index) {
				if ((recaddr = PurchaseFile.Write(purchaseArr[i])) == -1) {
					cout << "Write Error Occured!" << endl;
					cout << "-----------------------" << endl;
				}
				i++;
			}
			PurchaseFile.Close();

			ifs.close();

		}
		cout << endl << "Insert Succeeded!" << endl << endl;
	}

	return 0;
}

int DeletingByID(void) {
	string wantedID;
	cout << "Submit ID to Delete: ";

	cin >> wantedID;
	cout << "-----------------------" << endl;
	DeleteMember(wantedID);
	DeleteLecture(wantedID);
	DeletePurchase(wantedID);

	return 0;
}

int DeleteMember(string want_ID) {
	index = 0;
	long long streamMax = numeric_limits<streamsize>::max();
	char delimiter = '|';
	int bufferSize = 1000;
	int reset = 0;
	ifstream ifs("fileOfMember.dat");
	if (ifs.fail() == 1) {
		cout << "fileOfMember.dat open error!" << endl;
		cout << "-----------------------" << endl;
		return 0;
	}
	ifs.ignore(streamMax, '\n');

	
	int ifs_last;
	int find_ID = 0;
	Member m;


	DelimFieldBuffer buffer(delimiter, bufferSize);
	RecordFile <Member> MemberFile(buffer);
	MemberFile.Open("fileOfMember.dat", ios::in);


	ifs.clear();
	ifs.seekg(reset, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(reset, ifs.beg);


	while (ifs.tellg() < ifs_last) {
		MemberFile.Read(m);
		if (m.getID().compare(want_ID) == 0) {
			find_ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
		}

		else {
			memberArr[index] = m;
			index = index + 1;
		}
		ifs.seekg(m.getLength(), ifs.cur);
	}


	MemberFile.Close();

	if (find_ID == 1) {
		MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
		int recaddr;
		int i = 0;
		while(i < index) {
			if ((recaddr = MemberFile.Write(memberArr[i])) == -1) {
				cout << "Write Error!" << endl;
				cout << "-----------------------" << endl;
			}
			i++;
		}
		MemberFile.Close();
		cout << "Delete Process Completed from fileOfMember.dat" << endl;
		cout << "-----------------------" << endl;
	}
	ifs.close();

	return 0;
}

int DeleteLecture(string want_ID) {
	long long streamMax = numeric_limits<streamsize>::max();
	char delimiter = '|';
	int bufferSize = 1000;
	int reset = 0;
	index = 0;
	ifstream ifs("fileOfLecture.dat");
	if (ifs.fail()) {
		cout << "fileOfLecture.dat open error!" << endl;
		cout << "-----------------------" << endl;
		return 0;
	}
	ifs.ignore(streamMax, '\n');

	Lecture m;
	int ifs_last;
	int find_ID = 0;
	DelimFieldBuffer buffer(delimiter, bufferSize);

	RecordFile <Lecture> LectureFile(buffer);
	LectureFile.Open("fileOfLecture.dat", ios::in);
	
	ifs.clear();
	ifs.seekg(reset, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(reset, ifs.beg);
	while (ifs.tellg() < ifs_last) {
		LectureFile.Read(m);
		if (memcmp(m.getLectureID(), want_ID.c_str(), strlen(m.getLectureID())) == 0) {
			find_ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
		}
		else {
			lectureArr[index] = m;
			index = index + 1;
		}
		ifs.seekg(m.getLength(), ifs.cur);
	}
	LectureFile.Close();


	if (find_ID == 1) {
		LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);
		int recaddr;
		int i = 0;
		while(i < index) {
			if ((recaddr = LectureFile.Write(lectureArr[i])) == -1) {
				cout << "Write Error!" << endl;
				cout << "-----------------------" << endl;
			}
			i++;
		}
		LectureFile.Close();
		cout << "Delete Process Completed from fileOfLecture.dat" << endl;
		cout << "-----------------------" << endl;
	}
	ifs.close();

	return 0;
}

int DeletePurchase(string want_ID) {
	long long streamMax = numeric_limits<streamsize>::max();
	char delimiter = '|';
	int bufferSize = 1000;
	int reset = 0;
	index = 0;
	ifstream ifs("fileOfPurchase.dat");


	if (ifs.fail() == 1) {
		cout << "fileOfPurchase.dat open error!" << endl;
		cout << "-----------------------" << endl;
		return 0;
	}
	ifs.ignore(streamMax, '\n');

	
	int ifs_last;
	int find_ID = 0;

	Purchase m;


	DelimFieldBuffer buffer(delimiter, bufferSize);
	RecordFile <Purchase> PurchaseFile(buffer);
	
	PurchaseFile.Open("fileOfPurchase.dat", ios::in);
	
	ifs.clear();
	ifs.seekg(reset, ifs.end);
	ifs_last = ifs.tellg();
	ifs.seekg(reset, ifs.beg);
	
	
	while (ifs.tellg() < ifs_last) {
		PurchaseFile.Read(m);
		if (strcmp(m.getPurchaseID(), want_ID.c_str()) == 0) {
			find_ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
		}
		else if (strcmp(m.getLectureID(), want_ID.c_str()) == 0) {
			find_ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
		}
		else if (m.getMemberID().compare(want_ID) == 0) {
			find_ID = 1;
			ifs.seekg(m.getLength(), ifs.cur);
		}
		else {
			purchaseArr[index] = m;
			index = index + 1;
		}
		ifs.seekg(m.getLength(), ifs.cur);
	}
	PurchaseFile.Close();


	if (find_ID == 1) {
		PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
		int recaddr;
		int i = 0;
		while(i < index) {
			if ((recaddr = PurchaseFile.Write(purchaseArr[i])) == -1) {
				cout << "Write Error!" << endl;
				cout << "-----------------------" << endl;
			}
			i++;
		}
		PurchaseFile.Close();
		cout << "Delete Process Completed from fileOfPurchase.dat" << endl;
		cout << "-----------------------" << endl;
	}
	ifs.close();

	return 0;
}

int ModifyingByID() {

	string want_ID;
	long long streamMax = numeric_limits<streamsize>::max();
	string filename;
	char delimiter = '|';
	int reset = 0;
	int errorflag = 0;
	int bufferSize = 1000;
	int find;

	cout << "Submit ID : ";
	cin >> want_ID;
	cout << "-----------------------" << endl;
	cout << "Submit file name : ";
	cin >> filename;
	cout << "-----------------------" << endl;
	find = SearchingByID(0, filename, want_ID);
	if (find) {
		if (!filename.compare("fileOfMember.dat")) {

			if (errorflag) {
				return 0;
			}
			index = 0;
			ifstream ifs("fileOfMember.dat");
			if (ifs.fail() == 1) {
				cout << "fileOfMember.dat open error!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}
			ifs.ignore(streamMax, '\n');

			
			int ifs_last;
			int find_ID = 0;

			Member m;
			DelimFieldBuffer buffer(delimiter, bufferSize);


			RecordFile <Member> MemberFile(buffer);
			MemberFile.Open("fileOfMember.dat", ios::in);

			ifs.clear();
			ifs.seekg(reset, ifs.end);
			ifs_last = ifs.tellg();

			ifs.seekg(reset, ifs.beg);
			while (ifs.tellg() < ifs_last) {
				MemberFile.Read(m);
				if (m.getID().compare(want_ID) == 0) {
					find_ID = 1;
					string temp;
					char* update_temp = new char(100);

					if (errorflag) {
						cout << "error occured!" << endl;
						cout << "-----------------------" << endl;
						return 0;
					}

					cout << "Submit New Password : ";
					cin >> temp;
					cout << "-----------------------" << endl;

					m.setPassword(temp);

					cout << "Submit New Name : ";
					cin >> temp;
					cout << "-----------------------" << endl;
					
					m.setName(temp);

					cout << "Submit New Phone-Number : ";
					cin >> temp;
					cout << "-----------------------" << endl;

					m.setPhoneNumber(temp);

					cout << "Submit New Address : ";
					cin >> temp;
					cout << "-----------------------" << endl;

					m.setAddress(temp);

					cout << "Submit New Mileage : ";
					cin >> update_temp;
					cout << "-----------------------" << endl;

					if (strlen(update_temp) != 10) {
						cout << "Invalid Mileage length!!" << endl;
						cout << "-----------------------" << endl;
						return 0;
					}

					m.setMileage(update_temp);

					ifs.seekg(m.getLength(), ifs.cur);
					
					cout << endl << endl;

					if (errorflag) {
						cout << "error occured!" << endl;
						cout << "-----------------------" << endl;
						return 0;
					}


					cout << "updated successfully!" << endl;
					cout << "-----------------------" << endl;
					
					cout << m;
				}
				memberArr[index] = m;
				index = index + 1;

				ifs.seekg(m.getLength(), ifs.cur);
			}

			MemberFile.Close();

			if (find_ID == 1) {
				MemberFile.Create("fileOfMember.dat", ios::out | ios::trunc);
				int recaddr;
				int i = 0;

				while(i < index) {
					if ((recaddr = MemberFile.Write(memberArr[i])) == -1) {
						cout << "Write Error!" << endl;
						cout << "-----------------------" << endl;
					}
					i++;
				}
				MemberFile.Close();
			}
			ifs.close();
		}

		if (!filename.compare("fileOfLecture.dat")) {
			index = 0;
			ifstream ifs("fileOfLecture.dat");
			if (ifs.fail() == 1) {

				cout << "fileOfLecture.dat open error!" << endl;
				cout << "-----------------------" << endl;
				return 0;
			}

			ifs.ignore(streamMax, '\n');

			
			int ifs_last;
			int find_ID = 0;

			Lecture m;

			DelimFieldBuffer buffer(delimiter, bufferSize);
			RecordFile <Lecture> LectureFile(buffer);
			LectureFile.Open("fileOfLecture.dat", ios::in);

			ifs.clear();
			ifs.seekg(reset, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(reset, ifs.beg);
			while (ifs.tellg() < ifs_last) {
				LectureFile.Read(m);
				if (memcmp(m.getLectureID(), want_ID.c_str(), strlen(m.getLectureID())) == 0) {
					find_ID = 1;

					string temp;
					char* temporary = new char(100);
					int temp_i;
					if (errorflag) {
						cout << "error occured!" << endl;
						return 0;
					}
					cout << "Submit New Subject : ";
					cin >> temp;
					m.setSubject(temp);
					cout << "-----------------------" << endl;
					cout << "Submit New Level : ";
					cin >> temporary;
					cout << "-----------------------" << endl;
					if (strlen(temporary) != 1) {

						cout << "Invalid Level length!!" << endl;
						cout << "-----------------------" << endl;
						return 0;
					}
					m.setLevel(temporary);

					cout << "Submit New Price : ";
					cin >> temp_i;
					m.setPrice(temp_i);
					cout << "-----------------------" << endl;

					cout << "Submit New Extension : ";
					cin >> temporary;
					cout << "-----------------------" << endl;

					if (strlen(temporary) != 1) {
						cout << "Invalid Extension length!!" << endl;
						cout << "-----------------------" << endl;
						return 0;
					}

					if (errorflag) {
						cout << "error occured!" << endl;
						cout << "-----------------------" << endl;
					}
					m.setExtension(temporary);

					cout << "Submit New Due Date : ";
					cin >> temp_i;
					cout << "-----------------------" << endl;

					m.setDueDate(temp_i);

					cout << "Submit New NameOfTeacher : ";
					cin >> temp;
					cout << "-----------------------" << endl;

					m.setNameOfTeacher(temp);

					cout << "Submit New TextBook : ";
					cin >> temp;
					cout << "-----------------------" << endl;

					m.setTextBook(temp);

					ifs.seekg(m.getLength(), ifs.cur);

					cout << endl << endl;

					if (errorflag) {
						cout << "error occured!" << endl;
						return 0;
					}
					cout << "-----------------------" << endl;
					cout << "updated successlly!" << endl;
					cout << "-----------------------" << endl;
					cout << "" << endl;
					cout << m;
				}
				lectureArr[index] = m;
				index = index + 1;

				ifs.seekg(m.getLength(), ifs.cur);
			}
			LectureFile.Close();


			if (find_ID == 1) {
				LectureFile.Create("fileOfLecture.dat", ios::out | ios::trunc);
				int recaddr;
				int i = 0;
				while(i < index) {
					if ((recaddr = LectureFile.Write(lectureArr[i])) == -1) {
						cout << "Write Error Occured!" << endl;
					}
					i++;
				}
				LectureFile.Close();
			}
			ifs.close();
		}
		if (filename.compare("fileOfPurchase.dat") == 0) {
			index = 0;
			ifstream ifs("fileOfPurchase.dat");
			if (ifs.fail() == 1) {
				cout << "fileOfPurchase.dat open error!" << endl;
				return 0;
			}
			ifs.ignore(streamMax, '\n');

			
			int ifs_last;
			int find_ID = 0;

			Purchase m;

			DelimFieldBuffer buffer(delimiter, bufferSize * 10);

			RecordFile <Purchase> PurchaseFile(buffer);
			PurchaseFile.Open("fileOfPurchase.dat", ios::in);

			ifs.clear();
			ifs.seekg(reset, ifs.end);
			ifs_last = ifs.tellg();
			ifs.seekg(reset, ifs.beg);

			while (ifs.tellg() < ifs_last) {
				PurchaseFile.Read(m);

				if (strcmp(m.getPurchaseID(), want_ID.c_str()) || !strcmp(m.getLectureID(), want_ID.c_str()) || !m.getMemberID().compare(want_ID) == 0) {
					find_ID = 1;

					int tmpbuffer = 100;
					char* temporary = new char(tmpbuffer);

					cout << "Submit New Mileage : ";
					cin >> temporary;
					cout << "-----------------------" << endl;
					if (strlen(temporary) != 10) {
						cout << "Invalid Mileage length!" << endl;
						cout << "-----------------------" << endl;
						return 0;
					}
					m.setMileage(temporary);


					ifs.seekg(m.getLength(), ifs.cur);

					cout << "-----------------------------" << endl;

					if (errorflag) {
						cout << "error occured!" << endl;
						return 0;
					}
					cout << "updated successfully!" << endl;
					cout << "-----------------------" << endl;
					cout << "" << endl;
					cout << m;
				}
				purchaseArr[index] = m;
				index = index + 1;

				ifs.seekg(m.getLength(), ifs.cur);
			}
			PurchaseFile.Close();
			if (find_ID == 1) {
				PurchaseFile.Create("fileOfPurchase.dat", ios::out | ios::trunc);
				int recaddr;
				int i = 0;

				while(i < index) {
					if (errorflag) {
						cout << "error!" << endl;
						return 0;
					}

					if ((recaddr = PurchaseFile.Write(purchaseArr[i])) == -1) {

						cout << "Write Error Occured!" << endl;
						cout << "-------------------------------" << endl;
					}
				}
				PurchaseFile.Close();
			}
			ifs.close();
		}
		cout << "\nModifying Process Completed\n" << endl;

	}
	else {
		cout << "No Match exist.\n" << endl;
		cout << "****************************" << endl;
	}
	return 0;
}