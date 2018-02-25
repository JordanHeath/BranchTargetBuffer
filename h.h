//
//  h.h
//  Homework4
//
//  Created by Jordan Heath on 2/8/16.
//  Copyright © 2016 Jordan Heath. All rights reserved.
//

#ifndef h_h
#define h_h
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
using namespace std;


typedef struct itemarray
{
    int value;
    int index;
    
}ItemArray;


char *getstring(const char *buffer, int index, char lookfor);

class MyString
{
    friend bool operator ==(const MyString &lhs, const MyString &rhs);// checks if 2 strings are anagrams
    ///friend ostream &operator <<(const ostream &stream, const MyString &rhs);
    
public:
    MyString();
    MyString(const char *str_cpy); // copy constructor
    ~MyString();
    
    //we want to add
    //delete
    
    void set(const char * newstring);///1
    ///does not display
    MyString Substring(int startIndex, int length) const;///2
    ///displays a substring
    void Split(char c, vector<MyString>& outputVector) const;///3
    ///displays the split
    int indexof(int start, const char *findme);///4
    ///gets the index of
    int *badchartable();///5
    int GetAnagrams(std::vector<MyString>& candidates,///6
                    std::vector<MyString>& output);
    
    MyString &operator = (const MyString &rhs); // this is the assignment operator
    
    
    
    void createfrequencytable();
    int getlength()const;
    bool startwith(char *findme);
    
    void Write(ostream& stream) const;
    void DisplayBadChar(ostream &stream)const;
    bool isint();
    
    char *getstring()
    {
        return StringInUse;
    }
    
    
    int toint()
    {
        return atoi(StringInUse);
    }
    
    double todouble()
    {
        return atof(StringInUse);
    }
    
    
private:
    char *StringInUse;
    int BadCharTable [256];//56 doesn't have a null terminator
    // it's an array of ints pointing to the location of the last char occyrance
    //int FrequencyTable
    int FrequencyTable[256];// this holds the classes quicksorted variable
};

bool operator ==(const MyString &lhs, const MyString &rhs) // this is compartig the two frequency tables
{
    /// bool temp = true;
    ///stringcompare the two, if equal then we can say they are equal and output a 0
    int i =0;
    while(i < 256)
    {
        if((lhs.FrequencyTable)[i] != (rhs.FrequencyTable)[i])
        {
            return false;
        }
        i++;
    }
    
    
    return true;
    
    
}


int MyString::getlength()const // gets the lenth of the string
{
    int i = 0;
    while(StringInUse[i])
    {
        i++;
    }
    return i;
}


MyString & MyString::operator = (const MyString &rhs)
{
    if(this != &rhs)
    {
        this->StringInUse = rhs.StringInUse;///copying a value
    }
    return *this;
    
}


MyString::MyString()
{
    StringInUse = new char [250];
    
}
MyString::MyString(const char *str_cpy)
{
    //create a deep copy
    int str_len = strlen(str_cpy);
    StringInUse = new char [str_len + 1];
    strcpy(StringInUse, str_cpy);
    
}
MyString::~MyString()
{
}

void MyString::set(const char *newstring)
{//check for problems
    int len = strlen(newstring);
    StringInUse = new char [len + 1]; // allocating just enough space to fill it
    strcpy(StringInUse, newstring); // for memory purposes
    int j = 0;
   
}

int MyString::indexof(int start, const char *findme)
{
    bool isend = false; // indicates the terminating of the end
    int fi = 0;//find index
    int si = 0;
    int i = 0; //index for counting
    if(start < getlength()) //preventing glitch maybe?
    {///IF PROBLEMS WITH INDEX COME HERE
        ////check here
        while(StringInUse[start]) //while the compare value
        {
            
            //check if first character matches
            if(findme[fi] == StringInUse[start])
            {
                //i++;
                while(findme[fi++] == StringInUse[start++])
                {
                    i++;
                    if(!StringInUse[start])///had to put it there to
                    {
                        isend = true;
                        break;
                    }
                    
                }
                if(i == strlen(findme))
                {
                    if(strlen(findme) == 3)/// for some reason n = 3 was giving me a problem
                    {//if its an even number
                        si = start - strlen(findme);
                    }
                    else if((start == getlength()) && (isend == true))
                    {
                        si = start - strlen(findme);/// THis is found at the end and shouldn't experiance the -1
                    }
                    else{
                        si = start - strlen(findme) - 1;// want to leave this statement after it's found]
                    }
                    break;//leavs the statement if the
                    
                }
                
            }
            else
            {
                si = -1; //if its not found,
            }
            start++;
            
        }
    }
    return si;
    
    
    
}




MyString MyString::Substring(int startIndex, int length) const
{/// I THINK THIS IS OKAY
    MyString Substring;
    char toset[100];
    int i = 0;
    if(startIndex < strlen(StringInUse))
    {
        while((i) <= length)
        {
            if(StringInUse[startIndex])
            {
                toset[i] = StringInUse[startIndex];
                startIndex++;
            }
            else
            {
                toset[i] = '\0'; // makes the last char a null ch @ end
                //i = length; //pushes the index past the while threshold
                break;
            }
            i++;
        }
        if(i == (length +1)) // this is if we havet to have a teminating
        {
            toset[i] = '\0';
        }
        Substring.set(toset);
    }
    return Substring;
}





void MyString::Split(char c, vector<MyString>& outputVector) const
{
    //copy all characters unti we reach the splitter
    //place a comma then continue to read
    
    int index_1 = 0;
    int index_2 = 0;
    char *temp = new char [100];
    MyString stringtoadd; // creates a new object
    
    while(StringInUse[index_1])
    {
        if(StringInUse[index_1] == c)
        {// we want to push the last string onto the vector and reset temp and index after
            temp[index_2] = '\0';
            stringtoadd.set(temp); //adds the string to the object
            outputVector.push_back(stringtoadd); // pushes the string to the vector
            index_2 = 0;
            temp = new char[100];
            ///add something for the last one
            
            if(StringInUse[index_1 + 1] == '\0') // if the last character is the split character add another (blank
            {
                stringtoadd.set("");
                outputVector.push_back(stringtoadd);
            }
            
        }
        else if(StringInUse[index_1 + 1] == '\0') //for if the terminating character isnt at the end
        {
            
            temp[index_2] = StringInUse[index_1];//set that last one
            temp[index_2 + 1 ] = '\0';//null terminator
            stringtoadd.set(temp); // add string to object
            outputVector.push_back(stringtoadd); // push object onto vector
            
            
        }
        else
        {//when we dont reach the
            temp[index_2] = StringInUse[index_1];
            index_2++;
            
        }
        index_1++;
    }
}





int *MyString::badchartable()
{
    ///int length = strlen(StringInUse);
    int index = 0;// index through the loop
    
    /// we have to step through stringinuse and at every point from [0] and record
    // if a value occcurs twice, the right most one will overlap it
    
    for (int i =  0; i < 256; i++) {
        BadCharTable[i] = -1;
    }
    
    ////if p
    while(index <= strlen(StringInUse))//index is less than string
    {// step thru 1-by-1
        //get the ascii value to the first letter
        int ascivaal = (int) StringInUse[index];
        BadCharTable[ascivaal] = index;
        index++;
        
    }
    
    
    
    
    return BadCharTable;
    
}


int MyString::GetAnagrams(vector<MyString>& candidates,
                          vector<MyString>& output)
{
    //first compare the lengths
    //for the ones that match in length, move to next step with them
    
    int t = 0;
    int sizetocmp = getlength();
    createfrequencytable();///creates the table for the StringInUse
    //sort the letters by value from a to z (or ascii valie)
    int i = 0;
    int q = candidates.size();
    
    
    i = 0;
    while(i < q)
    {
        //nt who = tocmp.getlength();
        if(sizetocmp == (candidates.at(i)).getlength())// the lengths match
        {
            
            ///m     ||  KEEPS DEALLOCATING THE NEXT STRING IN ORBIT
            ///      \/
            ///candidates.at(i).createfrequencytable();//creates freq table for that current String
            //compare frequency tables
            candidates.at(i).createfrequencytable();
            if(*this == (candidates.at(i)))
            {
                output.push_back(candidates.at(i));
            }
            
        }
        i++;
        
    }
    
    
    return t;
    
}

void MyString::createfrequencytable()
{
    
    int index = 0;
    while(index <= getlength())
    {
        
        FrequencyTable[(int)StringInUse[index]]++;//takes ascii value from the current letter and adds 1 to current value
        index++;
    }
    
}


void MyString::Write(ostream& stream) const
{
    
    stream << StringInUse;
    
}

void MyString::DisplayBadChar(ostream &stream)const
{
    for(int i = 0; i < 256; i++)
    {
        stream << BadCharTable[i] << ',';
    }
    stream << endl;
    
}


bool  MyString::startwith(char *findme)
{
    bool a = false;
    for(int i = 0; i < strlen(findme); i++)///omit the NULL char at the end
    {
        if(StringInUse[i] != findme[i])
        {
            return false;
        }
        else{
            a=true;
        }
    }
    return a;
}



bool MyString::isint()
{
    int i = 0;
    while(StringInUse[i])
    {///48-57
        if((StringInUse[i] >= 48) && (StringInUse[i] <= 57))
        {
            
        }
        else
        {
            return false;///if oone char isn't an int, it will return a false bool
        }
        i++;
    }
    return true;///check this one
}



#endif /* h_h */
