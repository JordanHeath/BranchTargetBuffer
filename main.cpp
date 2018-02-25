#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <tgmath.h>
#include <vector>
#include <unordered_map>

using namespace std;

typedef struct table
{
    int currentPC;
    int nextPC;
    int twobitpred;// 0-1-2-3
    bool busy;
    int btb_right;
    int btb_wrong;
    
    table(int cur, int next)//constructs table
    {
        currentPC = cur;
        nextPC = next;
        twobitpred = 0;///apparently we have to start at 0 according to state machine
        busy = false;
        btb_right = 0;
        btb_wrong = 0;
        
    }
    
    void changepred(int to)
    {
        ///twobitpred = to;
        
        if(twobitpred == 3 && to == 1)
        {
            
        }
        else if(twobitpred == 0 && to == -1)
        {
            
        }
        else
        {
            twobitpred += to;
        }
    }
    
    void changenext(int newpred)
    {
        nextPC = newpred;
    }
    
    void addright()
    {
        btb_right += 1;
    }
    
    void addwrong()
    {
        btb_wrong +=1;
    }
    
}Table;

class BTB
{
    
    
public:
    
    BTB()
    {
        
        
    }
    
    BTB(const BTB &copy)
    {
   
        
    }
    
    
    ~BTB()
    {
        
    }
    
    void findme(int currentPC, int next)/// adress in PC
    {
        std::unordered_map<int ,Table>::const_iterator find = ourtalble.find (currentPC);
        
        if(find == ourtalble.end())// this means it hasnt been found
        {
            addtoBTB(currentPC, next);
        }
        else//this means it has and we need to check the object
        {
            ///check the next PC and compare to next in the table
            ///compar
        }
        
    }
    
    
    
    ///this processes when we have the current and next
    void compare(int current, int next)
    {
      
    if(next != current + 4)
    {// we've hit a branch
        // now we have to add to the bTB
        
        unordered_map<int, Table>::iterator findme = ourtalble.find(current);
        
        if(findme == ourtalble.end())//its not yet in the buffer
        {
            addtoBTB(current, next);
        }
        else
        {//we updatte the 2-bit prediction if it exists already as well as the new prediction
            
            ///now we have to check if the prediction is taken
            
            if (findme->second.nextPC == next)//prediction is right
            {
                findme->second.addright();
                findme->second.changepred(0);
            }
            else
            {
                findme->second.addwrong();
                findme->second.changepred(1);//move up in state machine
                
            }
            
            
        }
    }
    else
    {
        unordered_map<int, Table>::iterator findme = ourtalble.find(current);///finds the object in the table
        
        if(findme != ourtalble.end())///this means the branch isnt taken so we update the prediction
        {
            findme->second.changepred(1);//wasnt taken
            findme->second.addright();//look in the slides
        }
    }
        
        
        
    }
    
    
    
    
    
    
    void addtoBTB(int current, int pred)
    {/// create a table object
        Table addto = Table(current, pred);
        pair<int, Table> createdobject (current, addto);
        ourtalble.insert(createdobject);
    }
    
    
    
    
    
private:

    
    unordered_map<int, Table> ourtalble;
    
    
    
    
    
};




int main(int argc, const char *argv[])
{
    ifstream myfile ("input.txt");
    ofstream outfile ("output.txt");
    string line;
    int end;
    int hexVal = 0;
    int prev = -1;
    int current = 0;
    int power = 1;
    int endFor = 0;
    string table = "0123456789abcdef";
    string oldLine;
    
    BTB ourbuffer;
    
    
    
    
    
    
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            
            
            ///check in BRB for current PC
            /// if no,
            //current = stoul(line, NULL, 16);
            end = line.size();
            end = end - 2;
            endFor = end;
            for (int i=0;i<=endFor;i++)
            {
                for (int j=0;j<=15;j++)
                {
                    if(line[i] == table[j])
                    {
                        hexVal = j;
                        
                    }
                    
                }
                for (int k= end; k > 0;k--)
                {
                    if (i == endFor)
                    {
                        power = 1;
                    }
                    else
                    {
                        power = power * 16;
                    }
                }
                end--;
                
                current = current + (hexVal * power);
                power = 1;
            }
            //outfile<< "Actual current" << line;
            
            
            
           
            if(prev != -1)
            {
                ourbuffer.compare(prev, current);
            }
            
            prev = current;
        }
        myfile.close();
        outfile.close();
        
    }
    else cout << "File failed to open";
    
    
    ourbuffer.~BTB();//destrcution
    
    
    
    return 0;
}