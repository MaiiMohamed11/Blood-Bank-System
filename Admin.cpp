#include "Admin.h"
#include <iostream>
#include <string>
#include <vector>
#include "Donor.h"
#include "Recipient.h"
#include <queue>
#include "Blood.h"
#include "Files.h"

using namespace std;

Files fileA;
Date c_date;

Admin::Admin()
{

}
Admin::Admin(string name, int age, char gender, string email, string password, int& aID) :User(name, age, gender, email, password)
{
	ID = aID;
	aID++;
}

void Admin::Admin_page(int userIndex, vector <Admin>& adminsList, vector <Donor>& donorsList, vector <Recipient>& recipientsList, queue<int>& Donor_Requests, queue<Blood>& dataA, queue<Blood>& dataB, queue<Blood>& dataO, queue<Blood>& dataAB, int& aID, int& rID, int& dID)
{
	while (true)
	{
		cout << "\t\t Enter 1 to display & validate donor's requests." << endl;
		cout << "\t\t Enter 2 to Insert/Delete the quantity of blood." << endl;
		cout << "\t\t Enter 3 to Insert/Update/Delete data of users." << endl;
		cout << "\t\t Enter 4 to search for users." << endl;
		cout << "\t\t Enter 5 to display blood data." << endl;
		cout << "\t\t Enter 6 to log out." << endl;
		int choice;

		cin >> choice;
		if (choice == 1)
		{
			Display_requests(donorsList, Donor_Requests, dID, dataA, dataB, dataO, dataAB);
			continue;
		}
		else if (choice == 2)
		{
			while (true)
			{
				cout << "Enter the number of your choice:" << endl;
				cout << "1-Insert" << endl;
				cout << "2-Delete" << endl;
				int choice2;
				cin >> choice2;
				if (choice2 == 1)
				{
					insertBlood(dataA, dataB, dataO, dataAB);
					break;
				}
				else if (choice2 == 2)
				{
					deleteBlood(dataA, dataB, dataO, dataAB);
					break;
				}
				else
				{
					cout << "Invalid Choice, Please Enter a number(1 or 2)\n";
					cin >> choice2;
				}
			}
			continue;

		}

		else if (choice == 3)
		{
			while (true)
			{
				cout << "Enter the number of your choice:" << endl;
				cout << "1-Insert" << endl;
				cout << "2-Update" << endl;
				cout << "3-Delete" << endl;
				int choice2;
				cin >> choice2;
				if (choice2 == 1)
				{
					insertUser(adminsList, donorsList, recipientsList, Donor_Requests, dataA, dataB, dataO, dataAB, aID, rID, dID);
					break;
				}
				else if (choice2 == 2)
				{
					updateUser(adminsList, donorsList, recipientsList);
					break;
				}
				else if (choice2 == 3)
				{
					deleteUser(adminsList, donorsList, recipientsList);
					break;
				}
				else
				{
					cout << "Invalid Choice, Please Enter a number(1, 2 or 3)\n";
					cin >> choice2;
				}
			}
			continue;
		}
		else if (choice == 4)
		{
			do
			{
				cout << "Please enter user ID and their type (Admin, Donor or Recipient)\n";
				int id, userIndex; string userType; char user;
				cin >> id >> userType;
				for_each(userType.begin(), userType.end(), [](char & c) {
					c = ::tolower(c);
				});
				if (userType == "admin")
					user = 'a';
				else if (userType == "donor")
					user = 'd';
				else
					user = 'r';

				userIndex = searchForUser(id, adminsList, donorsList, recipientsList, user);
				if (userIndex == -1)
					cout << "Invalid ID or user type. Try again.\n";
				else
				{
					displayData(userIndex, adminsList, donorsList, recipientsList, user);
					break;
				}
			} while (true);

			continue;
		}
		else if (choice == 5)
		{
			displayBloodData(dataA, dataB, dataO, dataAB);
			continue;
		}
		else if (choice == 6)
		{
			break;
		}
		else
		{
			cout << "Invalid Choice, Please Enter a number(1, 2, 3 or 4)\n";
		}
	}
}

void Admin::Admin_Register(vector <Admin>& adminsList, vector <Donor>& donorsList, vector <Recipient>& recipientsList, queue<int>& Donor_Requests, queue<Blood>& dataA, queue<Blood>& dataB, queue<Blood>& dataO, queue<Blood>& dataAB, int& aID)
{
	cout << "Please enter Admin's code: ";
	string input_code;
	cin.ignore();
	getline(cin, input_code);
	if (input_code != code)
	{
		cout << "\nInvalid code. You can't be an admin.\n";
		return;
	}
	int age;
	string name, email, pass;
	char gender;
	cout << "Please enter your name, age and gender (M/F).\n";
	cin >> name >> age >> gender;
	cout << "Please enter your Email and Password.\n";
	cin >> email >> pass;
	Admin reg(name, age, gender, email, pass, aID);
	adminsList.push_back(reg);
	fileA.adminUpdate(adminsList);
}

void Admin::insertUser(vector <Admin>& adminsList, vector <Donor>& donorsList, vector <Recipient>& recipientsList, queue<int>& Donor_Requests, queue<Blood>& dataA, queue<Blood>& dataB, queue<Blood>& dataO, queue<Blood>& dataAB, int& aID, int& rID, int& dID)
{
	cout << "Enter the number of your choice:\n" << endl;
	cout << "1-Insert admin." << endl;
	cout << "2-Insert donor." << endl;
	cout << "3-Insert recipient." << endl;
	int choice;
	cin >> choice;
	while (true)
	{
		if (choice == 1)
		{
			Admin reg;
			reg.Admin_Register(adminsList, donorsList, recipientsList, Donor_Requests, dataA, dataB, dataO, dataAB, aID);
			cout << "Insertion is successfully done." << endl;
			cout << "_________________________________" << endl;
			break;
		}
		else if (choice == 2)
		{
			Donor reg;
			reg.Donor_Registeration(donorsList, Donor_Requests, dID);
			cout << "Insertion is successfully done." << endl;
			cout << "_________________________________" << endl;
			break;
		}
		else if (choice == 3)
		{
			Recipient reg;
			reg.Recipient_Registeration_Page(recipientsList, dataA, dataB, dataO, dataAB, rID);
			cout << "Insertion is successfully done." << endl;
			cout << "_________________________________" << endl;
			break;
		}
		else
		{
			cout << "Invalid Choice, Please Enter a number(1, 2 or 3)\n";
			cin >> choice;
		}
	}

}
void Admin::deleteUser(vector <Admin>& adminsList, vector <Donor>& donorsList, vector <Recipient>& recipientsList)
{
	cout << "Enter the number of your choice:" << endl;
	cout << "1-Delete admin." << endl;
	cout << "2-Delete donor." << endl;
	cout << "3-Delete recipient." << endl;
	int choice;
	cin >> choice;
	cout << "Please enter user's ID.\n";
	int id;
	cin >> id;
	bool isFound = false;
	while (true)
	{
		if (choice == 1)
		{
			for (int i = 0; i < adminsList.size(); i++)
			{
				if (id == adminsList[i].ID)
				{
					adminsList.erase(next(adminsList.begin(), i));
					fileA.adminUpdate(adminsList);
					isFound = true;
					cout << "Deletion is successfully done." << endl;
					cout << "_________________________________" << endl;
					break;
				}
			}
			if (isFound)
			{
				break;
			}
		}
		else if (choice == 2)
		{
			for (int i = 0; i < donorsList.size(); i++)
			{
				if (id == donorsList[i].ID)
				{
					donorsList.erase(next(donorsList.begin(), i));
					fileA.donorUpdate(donorsList);
					isFound = true;
					cout << "Deletion is successfully done." << endl;
					cout << "_________________________________" << endl;
					break;
				}
			}
			if (isFound)
			{
				break;
			}
		}
		else if (choice == 3)
		{
			for (int i = 0; i < recipientsList.size(); i++)
			{
				if (id == recipientsList[i].ID)
				{
					recipientsList.erase(next(recipientsList.begin(), i));
					fileA.recipientUpdate(recipientsList);
					isFound = true;
					cout << "Deletion is successfully done." << endl;
					cout << "_________________________________" << endl;
					break;
				}
			}
			if (isFound)
			{
				break;
			}
		}
		else
		{
			cout << "Invalid Choice, Please Enter a number(1, 2 or 3)\n";
			cin >> choice;
			continue;
		}

		if (!isFound)
		{
			cout << "Incorrect ID, Please try again." << endl;
			cin >> id;
		}
	}

}
void Admin::updateUser(vector <Admin>& adminsList, vector <Donor>& donorsList, vector <Recipient>& recipientsList)
{
	cout << "Enter the number of your choice:" << endl;
	cout << "1-Update data of an admin." << endl;
	cout << "2-Update data of a donor." << endl;
	cout << "3-Update data of a recipient." << endl;
	int choice, choice2;
	char answer;
	cin >> choice;
	cout << "Please enter user's ID.\n";
	int id;
	cin >> id;
	int age;
	string name, pass;
	bool isFound = false;
	if (choice == 1)
	{

		for (int i = 0; i < adminsList.size(); i++)
		{
			if (id == adminsList[i].ID)
			{
				isFound = true;
				while (true)
				{
					cout << "press 1 to update the name." << endl;
					cout << "press 2 to update the age." << endl;
					cout << "press 3 to update the password." << endl;
					cin >> choice2;
					if (choice2 == 1)
					{
						cout << "enter the new name: "; cin >> name;
						adminsList[i].Name = name;
					}
					else if (choice2 == 2)
					{
						cout << "enter the new age: "; cin >> age;
						adminsList[i].Age = age;
					}
					else if (choice2 == 3)
					{
						cout << "enter the new password: "; cin >> pass;
						adminsList[i].Password = pass;

					}
					else
					{
						cout << "Invalid Choice, Please Enter a number(1, 2 or 3)\n";
						continue;
					}
					cout << "Do you want to continue updating data of this admin? (y/n) "; cin >> answer;
					if (answer == 'N' || answer == 'n')
					{
						break;
					}
				}

			}

			if (isFound)
				break;
		}
		if (!isFound)
		{
			cout << "Incorrect ID, Please try again." << endl;
			cin >> id;
		}

		fileA.adminUpdate(adminsList);
	}
	if (choice == 2)
	{
		for (int i = 0; i < donorsList.size(); i++)
		{
			if (id == donorsList[i].ID)
			{
				isFound = true;
				while (true)
				{
					cout << "press 1 to update the name." << endl;
					cout << "press 2 to update the age." << endl;
					cout << "press 3 to update the password." << endl;
					cin >> choice2;
					if (choice2 == 1)
					{
						cout << "enter the new name: "; cin >> name;
						donorsList[i].Name = name;
					}
					else if (choice2 == 2)
					{
						cout << "enter the new age: "; cin >> age;
						donorsList[i].Age = age;
					}
					else if (choice2 == 3)
					{
						cout << "enter the new password: "; cin >> pass;
						donorsList[i].Password = pass;
					}
					else
					{
						cout << "Invalid Choice, Please Enter a number(1, 2 or 3)\n";
						continue;
					}

					cout << "Do you want to continue updating data of this donor? (y/n) "; cin >> answer;
					if (answer == 'N' || answer == 'n')
					{
						break;
					}
				}

			}
			if (isFound)
				break;
		}
		if (!isFound)
		{
			cout << "Incorrect ID, Please try again." << endl;
			cin >> id;
		}
		fileA.donorUpdate(donorsList);
	}
	if (choice == 2)
	{
		for (int i = 0; i < recipientsList.size(); i++)
		{
			if (id == recipientsList[i].ID)
			{
				isFound = true;
				while (true)
				{
					cout << "press 1 to update the name." << endl;
					cout << "press 2 to update the age." << endl;
					cout << "press 3 to update the password." << endl;
					cin >> choice2;
					if (choice2 == 1)
					{
						cout << "enter the new name: "; cin >> name;
						recipientsList[i].Name = name;
					}
					else if (choice2 == 2)
					{
						cout << "enter the new age: "; cin >> age;
						recipientsList[i].Age = age;
					}
					else if (choice2 == 3)
					{
						cout << "enter the new password: "; cin >> pass;
						recipientsList[i].Password = pass;
					}
					else
					{
						cout << "Invalid Choice, Please Enter a number(1, 2 or 3)\n";
						continue;
					}
					cout << "Do you want to continue updating data of this recipient? (y/n) "; cin >> answer;
					if (answer == 'N' || answer == 'n')
					{
						break;
					}
				}
			}

			if (isFound)
				break;
		}
		if (!isFound)
		{
			cout << "Incorrect ID, Please try again." << endl;
			cin >> id;
		}
		fileA.recipientUpdate(recipientsList);
	}
}
void Admin::insertBlood(queue<Blood>& dataA, queue<Blood>& dataB, queue<Blood>& dataO, queue<Blood>& dataAB)
{
	int choice;
	cout << "Enter the number of the type of blood you want to insert:" << endl;
	cout << "1-A" << endl;
	cout << "2-B" << endl;
	cout << "3-AB" << endl;
	cout << "4-O" << endl;
	cin >> choice;
	int numOfBags, index;
	cout << "Enter the number of bags you want to insert: "; cin >> numOfBags;
	Blood blood;
	if (choice == 1)
	{
		for (int i = 0; i < numOfBags; i++)
		{
			dataA.push(blood);
		}
	}
	if (choice == 2)
	{
		for (int i = 0; i < numOfBags; i++)
		{
			dataB.push(blood);
		}
	}
	if (choice == 3)
	{
		for (int i = 0; i < numOfBags; i++)
		{
			dataAB.push(blood);
		}
	}
	if (choice == 4)
	{
		for (int i = 0; i < numOfBags; i++)
		{
			dataO.push(blood);
		}
	}
	fileA.bloodUpdate(dataA, dataB, dataO, dataAB);
	cout << "Insertion is successfully done." << endl;
	cout << "_________________________________" << endl;
}
void Admin::deleteBlood(queue<Blood>& dataA, queue<Blood>& dataB, queue<Blood>& dataO, queue<Blood>& dataAB)
{
	do
	{
		int choice;
		char ans;
		cout << "Enter the number of the type of blood you want to check/delete: (Press 0 to exit)" << endl;
		cout << "1-A" << endl;
		cout << "2-B" << endl;
		cout << "3-AB" << endl;
		cout << "4-O" << endl;
		cin >> choice;

		if (choice == 1)
		{
			cout << "Blood type A: " << endl;
			cout << "Blood quantity is: " << dataA.size() << " bags (1 Liter\\bag)" << endl << endl;
			for (int i = 0; i < dataA.size(); i++)
			{
				cout << "\t\tBag number " << i + 1 << ": " << endl;
				cout << "\t\tReceived date: " << dataA._Get_container()[i].received.tm_mday << "/" << dataA._Get_container()[i].received.tm_mon;
				cout << "/" << dataA._Get_container()[i].received.tm_year << endl;
				cout << "\t\tExpiry date: " << dataA._Get_container()[i].expiry.tm_mday << "/" << dataA._Get_container()[i].expiry.tm_mon;
				cout << "/" << dataA._Get_container()[i].expiry.tm_year << endl;

				cout << "Do you want to remove this bag from the system? (y/n)";
				cin >> ans;
				if (ans == 'y' | ans == 'Y')
				{
					dataA.pop();
					fileA.bloodUpdate(dataA, dataB, dataO, dataAB);
					cout << "----- Bag removed successfuly from the system -----" << endl;
					cout << "Do you want to continue checking other A-Blood Type bags? (y/n)";
					cin >> ans;
					if (ans == 'n' | ans == 'N')
						break;
				}
			}
		}
		else if (choice == 2)
		{
			cout << "Blood type B: " << endl;
			cout << "Blood quantity is: " << dataB.size() << " bags (1 Liter\\bag) " << endl << endl;
			for (int i = 0; i < dataB.size(); i++)
			{
				cout << "\t\tBag number " << i + 1 << ": " << endl;
				cout << "\t\tReceived date: " << dataB._Get_container()[i].received.tm_mday << "/";
				cout << dataB._Get_container()[i].received.tm_mon << "/" << dataB._Get_container()[i].received.tm_year << endl;
				cout << "\t\tExpiry date: " << dataB._Get_container()[i].expiry.tm_mday << "/" << dataB._Get_container()[i].expiry.tm_mon;
				cout << "/" << dataB._Get_container()[i].expiry.tm_year << endl;

				cout << "Do you want to remove this bag from the system? (y/n)";
				cin >> ans;
				if (ans == 'y' | ans == 'Y')
				{
					dataB.pop();
					fileA.bloodUpdate(dataA, dataB, dataO, dataAB);
					cout << "----- Bag removed successfuly from the system -----" << endl;
					cout << "Do you want to continue checking other B-Blood Type bags? (y/n)";
					cin >> ans;
					if (ans == 'n' | ans == 'N')
						break;
				}
			}
		}
		else if (choice == 3)
		{
			cout << "Blood type AB : " << endl;
			cout << "Blood quantity is : " << dataAB.size() << " bags (1 Liter\\bag)" << endl << endl;
			for (int i = 0; i < dataAB.size(); i++)
			{
				cout << "\t\tBag number " << i + 1 << ": " << endl;
				cout << "\t\tReceived date: " << dataAB._Get_container()[i].received.tm_mday << "/" << dataAB._Get_container()[i].received.tm_mon;
				cout << "/" << dataAB._Get_container()[i].received.tm_year << endl;
				cout << "\t\tExpiry date: " << dataAB._Get_container()[i].expiry.tm_mday << "/" << dataAB._Get_container()[i].expiry.tm_mon << "/";
				cout << dataAB._Get_container()[i].expiry.tm_year << endl;

				cout << "Do you want to remove this bag from the system? (y/n)";
				cin >> ans;
				if (ans == 'y' | ans == 'Y')
				{
					dataAB.pop();
					fileA.bloodUpdate(dataA, dataB, dataO, dataAB);
					cout << "----- Bag removed successfuly from the system -----" << endl;
					cout << "Do you want to continue checking other AB-Blood Type bags? (y/n)";
					cin >> ans;
					if (ans == 'n' | ans == 'N')
						break;
				}
			}
		}
		else if (choice == 4)
		{
			cout << "Blood type O : " << endl;
			cout << "Blood quantity is : " << dataO.size() << " bags (1 Liter\\bag)" << endl << endl;
			for (int i = 0; i < dataO.size(); i++)
			{
				cout << "Bag number " << i + 1 << ": " << endl;
				cout << "Received date: " << dataO._Get_container()[i].received.tm_mday << "/" << dataO._Get_container()[i].received.tm_mon;
				cout << "/" << dataO._Get_container()[i].received.tm_year << endl;
				cout << "Expiry date: " << dataO._Get_container()[i].expiry.tm_mday << "/" << dataO._Get_container()[i].expiry.tm_mon << "/";
				cout << dataO._Get_container()[i].expiry.tm_year << endl;

				cout << "Do you want to remove this bag from the system? (y/n)";
				cin >> ans;
				if (ans == 'y' | ans == 'Y')
				{
					dataO.pop();
					fileA.bloodUpdate(dataA, dataB, dataO, dataAB);
					cout << "----- Bag removed successfuly from the system -----" << endl;
					cout << "Do you want to continue checking other O-Blood Type bags? (y/n)";
					cin >> ans;
					if (ans == 'n' | ans == 'N')
						break;
				}
			}
		}
		else
		{
			return;
		}

	} while (true);
}

void Admin::Current_Date()
{
	tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);
	c_date.day = newtime.tm_mday;

	c_date.month = 1 + newtime.tm_mon;

	c_date.year = 1900 + newtime.tm_year;
}
void Admin::Set_DonationDate(vector <Donor>& donorsList, int userIndx)
{

	donorsList[userIndx].Latest_Donation_Date.day = c_date.day;

	donorsList[userIndx].Latest_Donation_Date.month = c_date.month;

	donorsList[userIndx].Latest_Donation_Date.year = c_date.year;
}
void Admin::Set_Nxt_DonationDate(vector <Donor>& donorsList, int userIndx)
{
	if (donorsList[userIndx].Nxt_Donation_Date.month == 12)
	{
		donorsList[userIndx].Nxt_Donation_Date.month = 3;
		donorsList[userIndx].Nxt_Donation_Date.year = donorsList[userIndx].Latest_Donation_Date.year++;

	}
	else if (donorsList[userIndx].Nxt_Donation_Date.month == 11)
	{

		donorsList[userIndx].Nxt_Donation_Date.month = 2;
		donorsList[userIndx].Nxt_Donation_Date.year = donorsList[userIndx].Latest_Donation_Date.year++;
	}
	else if (donorsList[userIndx].Nxt_Donation_Date.month == 10)
	{
		donorsList[userIndx].Nxt_Donation_Date.month = 1;
		donorsList[userIndx].Nxt_Donation_Date.year = donorsList[userIndx].Latest_Donation_Date.year++;
	}
	else
	{
		donorsList[userIndx].Nxt_Donation_Date.month = donorsList[userIndx].Latest_Donation_Date.month + 3;
		donorsList[userIndx].Nxt_Donation_Date.year = donorsList[userIndx].Latest_Donation_Date.year;
	}
	donorsList[userIndx].Nxt_Donation_Date.day = donorsList[userIndx].Latest_Donation_Date.day;
}
bool Admin::comparingDates(vector <Donor>& donorsList, int userIndx)
{

	int date1 = c_date.day + (c_date.month * 30) + (c_date.year * 30 * 12);
	int date2 = donorsList[userIndx].Nxt_Donation_Date.day + (donorsList[userIndx].Nxt_Donation_Date.month * 30) + (donorsList[userIndx].Nxt_Donation_Date.year * 30 * 12);
	if (date2 < date1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void Admin::validateRequests(vector <Donor>& donorsList, queue <int>& Donor_Requests, int& dID, queue<Blood>& dataA, queue<Blood>& dataB, queue<Blood>& dataO, queue<Blood>& dataAB)
{
	int indx = -1;
	char ch;
	bool flag = 0;
	cout << "Do you want to validate the requests?(y/n)\n";
	cin >> ch;
	if (ch == 'y' || ch == 'Y')
	{
		while (!Donor_Requests.empty())
		{
			int id = Donor_Requests.front();
			for (int i = 0; i < donorsList.size(); i++)
			{
				if (donorsList[i].ID == id)
				{
					indx = i;
					break;
				}
			}
			if (indx == -1)
				cout << "User not found. The account must have been removed!\n";
			else if (donorsList[indx].Age >= 17 && donorsList[indx].Age <= 60 && donorsList[indx].isDisease == false)
			{
				Current_Date();
				flag = comparingDates(donorsList, indx);
				if (flag == 1)
				{
					Set_DonationDate(donorsList, indx);
					Set_Nxt_DonationDate(donorsList, indx);
					donorsList[indx].Validated_Donor = true;
				}

			}
			else
			{
				donorsList[indx].Validated_Donor = false;
			}
			fileA.donorUpdate(donorsList);
			Donor_Requests.pop();
			fileA.requestsUpdate(Donor_Requests);

			if (flag)
			{
				Blood b;
				tm newtime;
				time_t now = time(0);
				localtime_s(&newtime, &now);
				b.received.tm_mday = newtime.tm_mday;
				b.received.tm_mon = 1 + newtime.tm_mon;
				b.received.tm_year = 1900 + newtime.tm_year;

				if (donorsList[indx].Blood_type == "A")
					dataA.push(b);
				else if (donorsList[indx].Blood_type == "B")
					dataB.push(b);
				else if (donorsList[indx].Blood_type == "O")
					dataO.push(b);
				else
					dataAB.push(b);
				fileA.bloodUpdate(dataA, dataB, dataO, dataAB);
				if (b.received.tm_mon == 12)
				{
					b.expiry.tm_mday = b.received.tm_mday;
					b.expiry.tm_mon = 1;
					b.expiry.tm_year = b.received.tm_year + 1;

				}
				else
				{
					b.expiry.tm_mday = b.received.tm_mday;
					b.expiry.tm_mon = b.received.tm_mon + 1;
					b.expiry.tm_year = b.received.tm_year;
				}
			}
		}
		cout << "All requests are successfully validated!" << endl;
	}
}
void Admin::Display_requests(vector <Donor>& donorsList, queue <int>& Donor_Requests, int& dID, queue<Blood>& dataA, queue<Blood>& dataB, queue<Blood>& dataO, queue<Blood>& dataAB)
{
	if (Donor_Requests.size() == 0)
	{
		cout << "There is no request available now\n";
	}
	else
	{

		for (int i = 0; i < Donor_Requests.size(); i++)
		{

			for (int j = 0; j < donorsList.size(); j++)
			{
				if (Donor_Requests._Get_container()[i] == donorsList[j].ID)
				{
					if (donorsList[j].isDisease == false && (donorsList[j].Age >= 17 && donorsList[j].Age <= 60))
					{
						Current_Date();
						bool flag = comparingDates(donorsList, j);
						if (flag == 1) {
							cout << "Donor's ID : " << donorsList[j].ID << "\t" << "The User satisfies Donation rules \n";
							break;
						}
						else {
							cout << "Donor's ID : " << donorsList[j].ID << "\t" << "The User Doesn't satisfy Donation Date rules \n";
							break;
						}
					}
					else if (donorsList[j].isDisease == true)
					{
						cout << "Donor's ID : " << donorsList[j].ID << "\t" << "The User Doesn't satisfy Disease rules\n";
						break;
					}
					else if (donorsList[j].Age < 17 || donorsList[j].Age > 60) {
						cout << "Donor's ID : " << donorsList[j].ID << "\t" << "The User Doesn't satisfy Age rules\n";
						break;
					}

				}

			}
		}
		validateRequests(donorsList, Donor_Requests, dID, dataA, dataB, dataO, dataAB);
	}

}
int Admin::searchForUser(int id, vector <Admin>& adminsList, vector <Donor>& donorsList, vector <Recipient>& recipientsList, char userType)
{
	int userIndex = -1;
	if (tolower(userType) == 'a')
	{
		for (int i = 0; i < adminsList.size(); i++)
			if (adminsList[i].ID == id)
			{
				userIndex = i;
				break;
			}
	}
	else if (tolower(userType) == 'd')
	{
		for (int i = 0; i < donorsList.size(); i++)
			if (donorsList[i].ID == id)
			{
				userIndex = i;
				break;
			}
	}
	else
	{
		for (int i = 0; i < recipientsList.size(); i++)
			if (recipientsList[i].ID == id)
			{
				userIndex = i;
				break;
			}
	}
	return userIndex;
}
void Admin::displayData(int userIndex, vector <Admin>& adminsList, vector <Donor>& donorList, vector <Recipient>& recipientList, char userType)
{
	cout << "All data of user with ID: ";
	if (tolower(userType) == 'a')
	{
		cout << adminsList[userIndex].ID << endl;
		cout << "Name: " << adminsList[userIndex].Name << endl;
		cout << "Age: " << adminsList[userIndex].Age << endl;
		cout << "Gender: " << adminsList[userIndex].Gender << endl;
		cout << "Email: " << adminsList[userIndex].Email << endl;
		cout << "Password: " << adminsList[userIndex].Password << endl;
	}
	else if (tolower(userType) == 'd')
	{
		cout << donorList[userIndex].ID << endl;
		cout << "Name: " << donorList[userIndex].Name << endl;
		cout << "Age: " << donorList[userIndex].Age << endl;
		cout << "Gender: " << donorList[userIndex].Gender << endl;
		cout << "Email: " << donorList[userIndex].Email << endl;
		cout << "Password: " << donorList[userIndex].Password << endl;
		cout << "Blood Type: " << donorList[userIndex].Blood_type << endl;
		cout << "If she/he suffers from any disease(blood pressure disorders, thyroid disease, diabetes, cancer, heart disorders, hepatitis): " << donorList[userIndex].isDisease << endl;
		cout << "If she/he suffers from any other disease or take any medicine: " << donorList[userIndex].Other_Disease << endl;
		cout << "Latest Donation Date: " << donorList[userIndex].Latest_Donation_Date.day << "/" << donorList[userIndex].Latest_Donation_Date.month << "/" << donorList[userIndex].Latest_Donation_Date.year << endl;
	}
	else
	{
		cout << recipientList[userIndex].ID << endl;
		cout << "Name: " << recipientList[userIndex].Name << endl;
		cout << "Age: " << recipientList[userIndex].Age << endl;
		cout << "Gender: " << recipientList[userIndex].Gender << endl;
		cout << "Email: " << recipientList[userIndex].Email << endl;
		cout << "Password: " << recipientList[userIndex].Password << endl;
		cout << "Blood Type: " << recipientList[userIndex].Blood_type << endl;
		cout << "Hospital: " << recipientList[userIndex].Hospital << endl;
		cout << "Doctor of the Case: " << recipientList[userIndex].DoctorofTheCase << endl;
	}
}
void Admin::displayBloodData(queue<Blood>& dataA, queue<Blood>& dataB, queue<Blood>& dataO, queue<Blood>& dataAB)
{
	Recipient r;
	r.display_all_blood_data(dataA, dataB, dataO, dataAB);
}
