/*
Nur Suhaira 5841549 (CSCI203 Assignment 3)
Write a program to schedule final examination for the examination 
department so that no student has two examinations at the same time. 
The goal of this assignment is to expose you to the implementation 
of greedy algorithms that solves a problem with constraints. 

You will use a greedy algorithm to determine an assignment of classes 
to examination slots (schedules) such that: 
1. No student, enrolled in two subjects, is assigned 
to the same examination slot (schedule.) 
2. Any attempt to combine two slots into one would violate rule 1.
  
Input to the program will consist of the name of a data file. 
This file will contain the following data: 
• The number of students enrolled in the current semester 
• Repeated rows of the following: 
o Name of the student 
and the total number of subjects enrolled 
o The subject code the student is enrolled in
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX = 20;
const int TOTALSUB = 7;
const char MODULES [TOTALSUB][TOTALSUB+1] = {"CSCI212", "CSCI235", "CSCI222", "CSCI203", "CSCI205", "CSCI204", "CSCI213"};
	

struct StudentInfo 
{
	char name [MAX];
	int noOfSubjects;
	char subjects [MAX][MAX];
	bool examOK;
};

int readFile (fstream&, StudentInfo []);
void printInfo (StudentInfo [], int);
void printEnrolment (const char [][TOTALSUB+1], int [][TOTALSUB]);
void enrolStudents (StudentInfo [], int, char [][TOTALSUB+1], int [][TOTALSUB]);
void countNoEnrolment (int [], int [][TOTALSUB]);
void sortEnrolment (char [][TOTALSUB+1], int []);
void createSlot (char [][TOTALSUB+1], char [][TOTALSUB+1], const char [][TOTALSUB+1], int [][TOTALSUB]);
bool checkSlot (char [][TOTALSUB+1], char [][TOTALSUB+1], int, StudentInfo []);

int main ()
{
	fstream infile;
	
	StudentInfo s [MAX];
	
	int noOfStudents = readFile (infile, s);
	
	printInfo (s, noOfStudents);
	
	char subjectTitle [TOTALSUB][TOTALSUB+1] = {"CSCI212", "CSCI235", "CSCI222", "CSCI203", "CSCI205", "CSCI204", "CSCI213"};
	
	int studentEnrolment [TOTALSUB][TOTALSUB];
	
	for (int i = 0; i < TOTALSUB; i++)
	{	 
		for (int j = 0; j < TOTALSUB; j++)
		{
			studentEnrolment [i][j] = 0;
		}
		
	}
	
	printEnrolment (MODULES, studentEnrolment);
	
	enrolStudents (s, noOfStudents, subjectTitle, studentEnrolment);
	
	printEnrolment (MODULES, studentEnrolment);
			
	int counter [TOTALSUB];
	
	countNoEnrolment (counter, studentEnrolment);
	
	sortEnrolment (subjectTitle, counter);

	char slot [TOTALSUB+1][TOTALSUB+1]; 
	
	createSlot (slot, subjectTitle, MODULES, studentEnrolment);

	bool ok = checkSlot (slot, subjectTitle, noOfStudents, s); 
	
	cout << endl;
	if (ok == true)
	{
		cout << "All students are successfully assigned to examination slots..." << endl;
	}
}

int readFile (fstream& infile, StudentInfo s [])
{
	int noOfStudents;
	
	char input;
	
	infile.open ("A3Data.txt");
	
	if (! infile)
	{
		cout << "File failed to open!" << endl;
	
	}
	
	infile >> noOfStudents;
		
	for (int a = 0; a < noOfStudents; a++)
	{
		int b = 0;
		
		do
		{
			input = infile.get ();
			
			if (input != ',')
			{
				s[a].name[b] = input;
			}
				
			++b;
				
		} while (input != ',');
			
		infile >> s[a].noOfSubjects;
		
		for (int c = 0; c < s[a].noOfSubjects; c++)
		{
			infile >> s[a].subjects[c];
		}
	}
	
	infile.close ();	 
	  
	return noOfStudents;
}

void printInfo (StudentInfo s [], int noOfStudents)
{
	cout << "Subjects enrolled by students:" << endl;
	for (int i = 0; i < noOfStudents; i++)
	{
		cout << s[i].name << "\t [ ";
				
		for (int j = 0; j < s[i].noOfSubjects; j++)
		{
			cout << s[i].subjects[j] << " ";
		}
		
		cout << "]" << endl;
	}
}

void printEnrolment (const char MODULES [][TOTALSUB+1], int studentEnrolment [][TOTALSUB])
{
	cout << endl
		 << "Matrix of subjects enrolled by students" 
		 << endl
		 << "---------------------------------------"
		 << endl << endl;
	
	for (int i = 0; i < TOTALSUB; i++)
	{
		cout << "\t" << MODULES [i];
	}
	
	cout << endl;
	
	for (int i = 0; i < TOTALSUB; i++)
	{
		cout << MODULES [i] << "\t";
		
		for (int j = 0; j < TOTALSUB; j++)
		{
			cout << "\t" << studentEnrolment [i][j];
		}
		
		cout << endl;
	}
}

void enrolStudents (StudentInfo s [], int noOfStudents, char subjectTitle [][TOTALSUB+1], int studentEnrolment [][TOTALSUB])
{
	cout << endl << "Enrolling students' subjects into matrix....." 
		 << endl;
	
	for (int i = 0; i < noOfStudents; i++)
	{	 	 	 
		for (int j = 0; j < s[i].noOfSubjects; j++)
		{
			for (int k = 0; k < TOTALSUB; k++)
			{
				if (strcmp (s[i].subjects[j], subjectTitle[k]) == 0)
				{
					for (int m = 0; m < TOTALSUB; m++)
					{
						for (int n = 0; n < s[i].noOfSubjects; n++)
						{
							if (strcmp (s[i].subjects[n], subjectTitle[m]) == 0)
							{
								studentEnrolment [k][m] += 1;
							}
						}
					}
				}
			}
		}
	}
}

void countNoEnrolment (int counter [], int studentEnrolment [][TOTALSUB])
{
	int count;
	
	for (int i = 0; i < TOTALSUB; i++)
	{
		count = 0;
		
		for (int j = 0; j < TOTALSUB; j++)
		{
			if (studentEnrolment [i][j] == 0)
			{
				count++;
			}
		}
		
		counter[i] = count;
	}
}

void sortEnrolment (char subjectTitle [][TOTALSUB+1], int counter [])
{	 	 
	int tempInt;
	char tempChar [8];
	
	cout << endl << "No. of Candidates Subject List:" << endl;
	
	for (int i = 0; i < TOTALSUB; i++)
	{
		for (int j = i+1; j < TOTALSUB; j++)
		{
			if (counter[i] < counter[j])
			{
				tempInt = counter[i];
				counter[i] = counter[j];
				counter[j] = tempInt;
				
				strcpy (tempChar, subjectTitle[i]);
				strcpy (subjectTitle[i], subjectTitle[j]);
				strcpy (subjectTitle[j], tempChar);
			}
		}

		cout << subjectTitle [i] << " ";
		cout << counter[i] << endl;
	}
}

void createSlot (char slot [][TOTALSUB+1], char subjectTitle [][TOTALSUB+1], const char MODULES [][TOTALSUB+1], int studentEnrolment [][TOTALSUB])
{	 
	static int i = 0;
	static int used1 = 0;
	static int used2 = 0;
	static int used3 = 0;
	static int used4 = 0;
	static int used5 = 0;
	static int used6 = 0;
	bool slot1ok = false;
	bool slot2ok = false;
	bool slot3ok = false;
	bool slot4ok = false;
	
	cout << endl << "Creating exam slots:" << endl;
	
	for (int h = 0; h <= TOTALSUB/2; h++)
	{
		for (int j = 0; j < TOTALSUB; j++)
		{
			for (int k = 0; k < TOTALSUB; k++)
			{
				if (slot1ok == false)
				{
					if (strcmp (subjectTitle [j], MODULES[k]) == 0)
					{
						for (int m = 0; m < TOTALSUB; m++)
						{
							if (slot1ok == false)
							{
								if (studentEnrolment[k][m] == 0)
								{
									strcpy (slot[i], MODULES[k]);
									i++;
									used1 = k;
									strcpy (slot[i], MODULES[m]);
									i++;
									used2 = m;
									slot1ok = true;
								}
							}
						}
					}
				}
				else if (slot1ok == true && slot2ok == false)
				{
					bool ok = false;
					for (int s = 0; s < i; s++)
					{
						if (strcmp (subjectTitle [j], slot[s]) == 1)
						{
							ok = true;
						}
					}
					
					if (ok == true)
					{
						if (strcmp (subjectTitle [j], MODULES[k]) == 0)
						{
							for (int m = 0; m < TOTALSUB; m++)
							{
								if (studentEnrolment[k][m] == 0)
								{
									if (m != used1 && m != used2)
									{
										strcpy (slot[i], MODULES[k]);
										i++;
										used3 = k;
										strcpy (slot[i], MODULES[m]);
										i++;
										used4 = m;
										slot2ok = true;
									}
								}
							}
						}
					}
				}
				else if (slot2ok == true && slot3ok == false)
				{
					bool ok = false;
					for (int s = 0; s < i; s++)
					{
						if (strcmp (subjectTitle [j], slot[s]) == 1)
						{
							ok = true;
						}
					}
					
					if (ok == true)
					{
						if (strcmp (subjectTitle [j], MODULES[k]) == 0)
						{
							for (int m = 0; m < TOTALSUB; m++)
							{
								if (studentEnrolment[k][m] == 0)
								{
									if (m != used1 && m != used2 && 
										m != used3 && m != used4)
									{
										strcpy (slot[i], MODULES[k]);
										i++;
										used5 = k;
										strcpy (slot[i], MODULES[m]);
										i++;
										used6 = m;
										slot3ok = true;
									}
								}
							}
						}
					}
				}
				else if (slot3ok == true && slot4ok == false)
				{
					for (int m = 0; m < TOTALSUB; m++)
					{
						if (m != used1 && m != used2 && 
							m != used3 && m != used4 &&
							m != used5 && m != used6)
						{
							strcpy (slot[i], MODULES[m]);
							slot4ok = true;
						}
					}
				}
			}		  
		}
	}   
	
	for (int s = 0; s < TOTALSUB; s++)
	{
		switch (s)
		{
			case 0: cout << "Slot 1: " << slot[s];
				    break;
			case 1: cout << "\t" << slot[s] << endl;
					break;
			case 2: cout << "Slot 2: " << slot[s];
					break;
			case 3: cout << "\t" << slot[s] << endl;
					break;
			case 4: cout << "Slot 3: " << slot[s];
					break;
			case 5: cout << "\t" << slot[s] << endl;
					break;
			default: cout << "Slot 4: " << slot[s] << endl;
		}
	}
}

bool checkSlot (char slot [][TOTALSUB+1], char subjectTitle [][8], int noOfStudents, StudentInfo s [])
{
	int count = 0;
	bool allslotOK = false;
	int slot1no = 0;
	int slot2no = 0;
	int slot3no = 0;
	int slot4no = 0;
	
	cout << endl << "Checking slots with students' enrolment.....";
	
	for (int i = 0; i < noOfStudents; i++)
	{	 	 	 
		for (int index = 0; index < TOTALSUB; index++)
		{
			bool sub1ok = false;
			bool sub2ok = false;
			bool slot1ok = false;
			bool slot2ok = false;
			bool slot3ok = false;
			bool slot4ok = false;
			
			for (int j = 0; j < s[i].noOfSubjects; j++)
			{
				switch (index)
				{
					case 0: if (strcmp (slot[index], s[i].subjects[j]) == 0)
							{
								sub1ok = true;
							}
							break;
					case 1:	if (strcmp (slot[index], s[i].subjects[j]) == 0)
							{
								sub2ok = true;
							}
							break;
				 	case 2: if (strcmp (slot[index], s[i].subjects[j]) == 0)
							{
								sub1ok = true;
							}
							break;
					case 3: if (strcmp (slot[index], s[i].subjects[j]) == 0)
							{
								sub2ok = true;
							}
							break;
					case 4: if (strcmp (slot[index], s[i].subjects[j]) == 0)
							{
								sub1ok = true;
							}
							break;
					case 5: if (strcmp (slot[index], s[i].subjects[j]) == 0)
							{
								sub2ok = true;
							}
							break;
					default:if (strcmp (slot[index], s[i].subjects[j]) == 0)
							{
								sub1ok = true;
							}
					
				}
			}
			
			switch (index)
				{
					case 0: 
					case 1: if ((sub1ok == true && sub2ok == false) ||
								(sub1ok == false && sub2ok == true))	
							{
								cout << s[i].name << " is ok with slot 1...";
								++count;
								++slot1no;
								slot1ok = true;
							}
							break;
					case 2:
					case 3: if ((sub1ok == true && sub2ok == false) ||
								(sub1ok == false && sub2ok == true))	
							{
								cout << s[i].name << " is ok with slot 2..";
								++count;
								++slot2no;
								slot2ok = true;
							}
							break;
					case 4:
					case 5: if ((sub1ok == true && sub2ok == false) ||
								(sub1ok == false && sub2ok == true))	
							{
								cout << s[i].name << " is ok with slot 3..";
								++count;
								++slot3no;
								slot3ok = true;
							}
							break;
					default: if ((sub1ok == true && sub2ok == false) ||
								(sub1ok == false && sub2ok == true))	
							{	 
								cout << s[i].name << " is ok with slot 4..";
								++count;
								++slot4no;
								slot4ok = true;
							}
						
				}
		}
		
		if (count == s[i].noOfSubjects)
		{
			s[i].examOK = true;	   
		}
	
		count = 0;  
	}
	
	cout << endl << endl
		 << "No. of Candidates attending each exam slot:"
		 << endl;
	for (int h = 0; h < TOTALSUB; h++)
	{
		switch (h)
		{	 	 
			case 0:	cout << "1. " << slot[h];
					break;
			case 1: cout << "\t" << slot[h] <<"\t" << slot1no << endl;
					break;
			case 2: cout << "2. " << slot[h];
					break;
			case 3:	cout << "\t" << slot[h] << "\t" << slot2no << endl;
					break;
			case 4: cout << "3. " << slot[h];
					break;
			case 5: cout << "\t" << slot[h] << "\t" << slot3no << endl;
					break;
			default: cout << "4. " << slot[h] << "\t\t" << slot4no << endl;	   
		} 
	}   
	
	for (int student = 0; student < noOfStudents; student++)
	{
		if (s[student].examOK == true)
		{
			++count;
		}	 
	}
	
	int total = slot1no + slot2no + slot3no + slot4no;
	
	cout << "Total no. of exam attendees: " << total << endl;
	
	if (count == noOfStudents)
	{
		allslotOK = true;
	}
	
	return allslotOK;
}

