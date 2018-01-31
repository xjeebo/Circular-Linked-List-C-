
//--Jeeno Doria
#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <assert.h>
using namespace std;

struct node{
  int id;
  string data;
  node *next;
  node *prev;
};
class CList{
public:
  void disp();
  void shiftRight();
  void shiftLeft();
  void addelement();
  void removeelement();
  CList(){ 
           counter = 0; current = NULL; alwaysfirst = NULL; newnode = NULL; last=NULL;
} 
  ~CList(){ 
          delete current; delete alwaysfirst; delete newnode; delete last;
  }
  int counter;
private:
  node *current;
  node *alwaysfirst;
  node *newnode;
  node *last;
};
//EXCEPTION CLASS-------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
class except{
public: 
  except(){ message = "Invalid value, restarting program... "; }
  except(int x){
    cout << "List is empty: program will now abort, Please execute again..." << endl;  x=0; cout << "Program has now "; abort();
    cout << endl;
  }
  string what(){ return message; }

private:
  string message;
};
//ADDING AN ELEMENT-----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void CList::addelement(){
  counter++;
  if(counter>1){
  current->prev = newnode;
  newnode = new node;
  cout << "Enter data: "; cin >> newnode->data;
  newnode->id=counter;
  current->next = newnode;
  current = newnode;
  current->next = NULL;
  last = current;
}
  else if(counter==1){//-------I've incorporated for the very first run; the first node is tracked down
  newnode = new node;
  cout << "Enter data: "; cin >> newnode->data; 
  current = newnode; 
  newnode->id = counter;
  current->prev = NULL;
  alwaysfirst = newnode;
  alwaysfirst->prev = NULL;
  last = current;
  }
}
//SHIFTING RIGHT--------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void CList::shiftRight(){
  node *getlast; // Simply making sure the last and second to last node is acquired to avoid errors
  node *shifter;  // Connects the last node to the first node
  node *secondfromlast; // Becomes the new last node
  
  if(alwaysfirst==NULL){
    cout << "The list is empty!" << endl;
    cout << "Restarting..." << endl;
  }
    else{
      if(alwaysfirst->next==NULL){ //------------Pretty obvious what these mean..
    cout << "Cannot shift because there is only one node in the list!" << endl;
    cout << "Restarting..." << endl;
  }
  else{
    getlast = alwaysfirst;  //------This is how I make sure the last node..is really..the last node...
  while(getlast!=NULL){
    last = getlast;
    getlast=getlast->next;
  }
  getlast=alwaysfirst;
  while(getlast->next!=NULL){ //-----This is used to get the SECOND to the last node
    secondfromlast=getlast;
    getlast=getlast->next;
  }
  shifter=last;
  shifter->next=alwaysfirst;
  alwaysfirst->prev=shifter;
  alwaysfirst=shifter;
  alwaysfirst->prev=NULL;
  secondfromlast->next=NULL;
  current=secondfromlast; // Current becomes the last node incase we want to add more remove nodes
  last=secondfromlast;
  }
    }
}
//SHIFTING LEFT---------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void CList::shiftLeft(){
  node *shifter;  // Connects the last node to the first node                                                          
  node *secondfromfirst; // Becomes the new first node                              
                            
  if(alwaysfirst==NULL){ //------------If list is empty..
    cout << "The list is empty!" << endl;
    cout << "Restarting..." << endl;
  } 
   else{
     if(alwaysfirst->next==NULL){ //---------------If there is only one node..
    cout << "Cannot shift because there is only one node in the list!" << endl;
    cout << "Restarting..." << endl;
  }    
  else{
    secondfromfirst=alwaysfirst->next; //-----We do the opposite of shifting right by having the second from first node

  shifter=last;
  shifter->next=alwaysfirst;
  alwaysfirst->prev=shifter;
  shifter=alwaysfirst;
  shifter->next=NULL; //--------this becomes the last node; it cuts a tie avoiding a circularly linked list
  last=shifter;
  alwaysfirst=secondfromfirst;
  alwaysfirst->prev=NULL;
  }
    }
}
//REMOVING AN ELEMENT---------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void CList::removeelement(){
  bool match=false;
  node *remove;  node *traveler; node *ahead;
  int idinput;
  
  if(alwaysfirst==NULL){ //----------if the list is empty
    cout << "Nothing to remove!" << endl << "Restarting..." << endl;
  }
  else{

    traveler = alwaysfirst;
    ahead = traveler->next;

  cout << "Enter placement(int): ";
  try{
  cin >> idinput;
  //-----------This checks to make sure that the certain Id chosen to be deleted actually exists
  traveler=alwaysfirst;
  while(traveler!=NULL){
    if(idinput==traveler->id)
      match=true;
    traveler=traveler->next;
  }//------------------------if it did exist match is set to true to continue the process of deletion
   if(match==true){

     if(alwaysfirst->id==idinput&&alwaysfirst->next==NULL){ // -----If there is one node in the list
      remove=alwaysfirst;
      remove->next=NULL;
      remove->prev=NULL;
      delete remove; 
     throw except(1);
     }

    if(alwaysfirst->id==idinput){ //------------if the first node is the chosen one to be deleted
    remove=alwaysfirst;
    alwaysfirst=alwaysfirst->next;
    remove->next=NULL; //-----------make sure the node has no ties with any other nodes
    remove->prev=NULL;
    alwaysfirst->prev=NULL;
    delete remove;
    traveler=alwaysfirst;

    while(traveler!=NULL){ //-----This was to make sure that these pointers corresponded correctly 
      last=traveler;
      current=traveler;
      traveler=traveler->next;
    }   
    }
    traveler=alwaysfirst;
 while(traveler!=NULL){
   if(ahead->id==idinput){ //------------the pointer will find a step ahead; the note before it will be deleted
      remove=traveler->next;
      traveler->next=traveler->next->next; //---------the node goes on to the next next node 
      delete remove;
      if(traveler->next==NULL){
      current=last;
      current->next=traveler;
      current=traveler;
      current->next=NULL;      
      }
    }
    ahead=ahead->next;
    traveler=traveler->next;
 }
  }
  else
    throw except();
  }
  
  catch(except anError){ //---------------exception handling to display a message because of the error
    cout << anError.what() << endl;
  }
  }  
}
//DISPLAYING ALL ELEMENTS-----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
void CList::disp(){
  node *traveler;

  traveler=alwaysfirst;
  cout << endl <<"List:" << endl;
  while(traveler!=NULL){
    cout << left << traveler->id << setw(2) << ". " << traveler->data << endl;
      traveler=traveler->next;
  }
  cout << "-------------------" << endl;
      cout << "1. add element" << endl;
      cout << "2. remove element" << endl;
      cout << "3. shift right" << endl;
      cout << "4. shift left" << endl;
      cout << "5.exit" << endl;
}
//NOW TO MAIN FUNCTION___________________________________________________________________________________________
//---------------------------------------------------------------------------------------------------------------
int main(){
  system("clear");
  CList list; int option;
  cout << setw(40) << " " << "~~~~~~~~~~~~~~~~~~~" << endl;
  cout << setw(40) << " " << "~~EXTRA CREDIT!!!~~" << endl;
  cout << setw(40) << " " << "~~~~~~~~~~~~~~~~~~~" << endl;  
  cout << "List:" << endl;
  cout << "1. add element" << endl;
  cout << "2. remove element" << endl;
  cout << "3. shift right" << endl;
  cout << "4. shift left" << endl;
  cout << "5. exit" << endl;


  cout << "Enter choice: "; cin >> option;
  while(option>5||option<1){
    cout << "Invalid value, Please try again: ";
    cin >> option;
  }
  while(option==1||option==2||option==3||option==4){ 
 switch(option){
  case 1:list.addelement(); list.disp();break;
  case 2:list.removeelement(); list.disp();break;
  case 3:list.shiftRight(); list.disp();break;
  case 4:list.shiftLeft(); list.disp();break;
  }
 cout << "Enter choice: ";
 cin >> option;
 while(option>5||option<1){
   cout << "Invalid value, Please try again: ";
   cin >> option;
 }
  }
}




