#include <iostream>
#include <cstdio>
#include <cstdlib>
#include<ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include<map>
#include <iomanip>
#define HASHING_H
using namespace std;
class person
{
private:
    string name;
    string password;
    string gender;
    int age;
    string city;
    string college;
    vector<person*> friends;
    vector< string> status;
    map<string, vector<string> > text;
    bool deactivate;
public:
    person();
    person ( string name, string password, string gender, int age,  string city,  string college);
    void  setName( string item);
    void  setPassword(string password);
    void  setGender(string gender);
    void  setAge(int age);
    void  setCity(string city);
    void  setCollege( string college);
    void  setStatus( string newStatus);
    void  deactivateAccount( bool deactivate);
    void  addFriend(person &friendName);
    void deleteFriend(person &friendName);
    void  receiveMessage(person &friendName ,string message);
    void  sendMessage(person &friendName,  string message);
    string getName() const;
    string getPassword() const;
    string getPwd() const;
    string  getGender() const;
    int  getAge() const;
    string  getCity() const;
    string  getCollege() const;
    bool getStatus() const;
    string getDate();
    vector<person *>  getFriends() const;
    void  printFriends() const;
    void  printStatus() const;
    void  printMessages() const;
    void  printPerson() const;
    bool operator < (const person &otherObject)
    {
        return name < otherObject.getName();
    }
    bool operator > (const person &otherObject)
    {
        return name > otherObject.getName();
    }
   bool operator == (const person &otherObject) {
        return this->name == otherObject.getName();
    }
    bool operator != (const person &otherObject)
    {
        return name != otherObject.getName();
    }
   friend ostream &operator<<( ostream &output,  const person &P )
    {
        output << setw(20) << P.getName()<< "  "
			   << setw(10) << P.getGender()
			   << "     "<< P.getAge() << "      "
               << setw(20) << P.getCity() << "       "  << P.getCollege();
        return output;
    }
};
person::person ( )
{
    name = " ";
    password = " ";
    gender = " ";
    age = 0;
    city = " ";
    college = " ";
    deactivate = false;
};
person::person ( string name, string password, string gender, int age,  string city,  string college)
{
    this->name = name;
    this->password = password;
    this->gender = gender;
    this->age = age;
    this->city = city;
    this->college = college;
    deactivate = false;
};
void person::setName( string name)
{
    this->name = name;
}
void person::setPassword( string password)
{
    this->password = password;
}
void  person::setGender(string gender)
{
    this->gender = gender;
}
void  person::setAge(int age)
{
    this->age = age;
}
void  person::setCity(string city)
{
    this->city = city;
}
void  person::setCollege( string college)
{
    this->college = college;
}
void  person::setStatus(string newStatus) {
    string timeNow  = getDate()+newStatus;
    status.push_back(timeNow + "\n");
}
void  person::deactivateAccount( bool deactivate) {
    this->deactivate = deactivate;
}
void  person::receiveMessage(person&friendName ,string message)
{
    friendName.text[this->name].push_back(message);
};

void  person::sendMessage(person &friendName,  string message)
{
    bool found = false;
    if (&friendName == this)
    {
        cout << "You cannot send a message to yourself." <<  endl;
        return;
    }
    if (friends.size() == 0) {
        cout << "In order to send a message, you need to be friends with this person";
        return;
    }

    for (int i = 0; i < friends.size(); i++ ) {
        if (friends[i]->name == friendName.name) {
            found = true;
        }
            }
    if(found) {
        string messageName =  getDate() + "\n" + this->name + "  " + message + "\n";
        string firstName = friendName.getName();
        text[firstName].push_back(messageName);
        friendName.receiveMessage(friendName, messageName);
    }
    else
    {
        cout << "In order to send a message, you need to be friends with this person";
    }
    };
void  person::addFriend(person &friendName)
{
    if (&friendName == this)
    {
        cout << "You cannot add yourself." <<  endl;
        return;
    }
    for (int i = 0; i < friends.size(); i++ ) {
        if (friends[i]->name == friendName.name) {
            cout << "You cannot add the same friend twice." <<  endl;
            return  ;
        }
    }
    friends.push_back(&friendName);
    friendName.friends.push_back(this);
    cout << name << " and " << friendName.name << " are now friend " <<  endl;
    setStatus(name + " and " + friendName.name + " are now friend ");
}
void  person::deleteFriend(person &friendName)
{
    if (&friendName == this)
    {
        cout << "You cannot delete yourself." <<  endl;
        return;
    }
    for (int i = 0; i < friends.size(); i++ ) {
        if (friends[i]->name == friendName.name) {
            friends.erase(friends.begin() + i);
            friendName.deleteFriend(*this);
            return  ;
        }
    }
    cout << name << " and " << friendName.name << " are no longer friends." <<  endl;
}
string person::getName() const {
    return name;
}
string person::getPassword() const {
    int a = (int)password.length();

    string newPassword;
    for (int i = 0; i < a; i++) {
        newPassword += "*";
    }
    return newPassword;
}
string person::getPwd() const {
    return password;
}

string  person::getGender() const {
    return gender;
}
int  person::getAge() const {
    return age;

}
string person:: getCity() const {
    return city;
}
string  person::getCollege() const {
    return college;
}

bool  person::getStatus() const {
    return deactivate;
}
vector<person*>  person::getFriends() const {
    return friends;
}
void  person::printFriends() const {
    if( friends.size() == 0 ) {
        cout << name << " has no friends." <<  endl;
    }
    else
    {
        cout << "Friends of " << name <<  endl;
        for (int i=0; i<friends.size();i++){
            cout << friends[i]->name <<  endl;
        }
    }
};
void  person::printStatus() const {
    if( status.size() == 0 ) {
        cout << name << " has no status updates." <<  endl;
    }
    else
    {
        cout << "Status updates of " << name <<  endl << "----------------------------------------------" << endl;
        for (int i=0; i<status.size();i++){
            cout << status[i] <<  endl;
        }
    }
};
void person:: printMessages() const {
    if( text.size() == 0 ) {
        cout << name << " no messages so far." <<  endl;
    }
    else
    {
        cout << "Private Messages of " << name  <<  endl << "----------------------------------------------" << endl;
        typedef map<string, vector<string> >::const_iterator MapIterator;
        for (MapIterator iter = text.begin(); iter != text.end(); iter++)
        {
            cout << iter->first << endl << endl;
            typedef vector<string>::const_iterator ListIterator;
            for (ListIterator list_iter = iter->second.begin(); list_iter != iter->second.end(); list_iter++)
                cout << " " << *list_iter << endl;
        }
    }
}
string person::getDate() {
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);

    int day = aTime->tm_mday;
    int month = aTime->tm_mon ;
    int year = aTime->tm_year + 1900;
    string months[] = {"January", "February", "March", "April",
        "May", "June", "July", "August", "September", "October",
        "November", "December"};
    string DAY;
    {
        stringstream ss;
        ss << day;
        DAY = ss.str();
    }
    string YEAR;
    {
        stringstream ss;
        ss << year;
        YEAR = ss.str();
    }
    string fullDate = DAY+ " " + months[month] +" " + YEAR + "\n";
    return fullDate;
}
template <class itemType>
class BinarySearchTree
{

    struct node
    {
    itemType *data;
    node* left;
    node* right;
    };
    node *root;
  public:
    BinarySearchTree() {root = NULL;}
    bool isEmpty() const {return root == NULL;}
    typename BinarySearchTree<itemType>::node* _insert(node*&, itemType &d);
    void _insert(itemType &d);
    void remove(itemType &data);
    void _remove(node*p ,itemType &data);
    int getBalance(node* N);
    void delete_BST(node*);
    void inOrder(node*);
    void print_inOrder();
    void printIndent();
    void indented(node* p, int indent );
    itemType* _search(node*   ,itemType const &d);
    itemType* search(itemType const &d);
    int Height(node*);
    void rotateLeftOnce(node*&);
    void rotateLeftTwice(node*&);
    void rotateRightOnce(node*&);
    void rotateRightTwice(node*&);
};
template <class itemType>
typename BinarySearchTree<itemType>::node* BinarySearchTree<itemType>::_insert(node*& i, itemType &d){
    if(i == NULL)
    {
        node* n = new node;
        n->data = &d;
        n->left = n->right = NULL;
        i = n;
    }
    else if(d < *i->data)
        {
        _insert(i->left, d);
        if(Height(i->left) - Height(i->right) == 2){
            if(d < *i->left->data)
                rotateLeftOnce(i);
            else
                rotateLeftTwice(i);
        }
    }
    else if(d > *i->data)
    {
        _insert(i->right, d);
        if(Height(i->right) - Height(i->left) == 2){
            if(d > *i->right->data)
                rotateRightOnce(i);
            else
                rotateRightTwice(i);
        }
    }
    return i;
}
template <class itemType>
void BinarySearchTree<itemType>::_insert(itemType &data)
{

    _insert(root, data);
}
template <class itemType>
void BinarySearchTree<itemType>::remove(itemType &d)
{
    node* current = root;
    node* parent =NULL;
    bool found = 0;
    if(isEmpty())
    {
        cout<<"BST is empty"<<endl;
        return;
    }
    while(current != NULL)
    {
        if(*current->data == d)
        {
            found = true;
            break;
        }
        else
        {
            parent = current;
            if(*current->data < d)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
    }
    if(!found)
    {
        cout<<"data is not found"<<endl;
        return;
    }
    if(current->left == NULL && current->right == NULL)
    {
        if(parent->left == current)
        {
            parent->left = NULL;
        }
        else
        {
            parent->right = NULL;
        }

        delete current;
        return;
    }
    if((current->left == NULL && current->right != NULL) || (current->left != NULL && current->right == NULL))
    {
        if(current->left == NULL && current->right != NULL)
        {
            if(parent->left == current)
            {
                parent->left = current->right;
                delete current;
            }
            else
            {
                parent->right = current->right;
                delete current;
            }
        }
        else
        {
            if(parent->left == current)
            {
                parent->left = current->left;
                delete current;
            }
            else
            {
                parent->right = current->left;
                delete current;
            }
        }
        return;
    }
    if (current->left != NULL && current->right != NULL)
    {
        node* checker;
        checker = current->right;
        if((checker->left == NULL) && (checker->right == NULL))
        {
            current = checker;
            delete checker;
            current->right = NULL;
        }
        else
        {
            if((current->right)->left != NULL)
            {
                node* leftCurrent;
                node* leftCurrentPred;
                leftCurrentPred = current->right;
                leftCurrent = (current->right)->left;
                while(leftCurrent->left != NULL)
                {
                    leftCurrentPred = leftCurrent;
                    leftCurrent = leftCurrent->left;
                }
                *current->data = *leftCurrent->data;
                delete leftCurrent;
                leftCurrentPred->left = NULL;
            }
            else
            {
                node* input1;
                input1 = current->right;
                *current->data = *input1->data;
                current->right = input1->right;
                delete input1;
            }
        }
        return;
    }
}
template <class itemType>
void BinarySearchTree<itemType>::print_inOrder()
{
    cout << "****** PRINTING BINARY SEARCH TREE *******" << endl;
    inOrder(root);
}
template <class itemType>
void BinarySearchTree<itemType>::inOrder(node* i)
{
    if(i != NULL)
    {
        cout<< *i->data << endl;

        if(i->left)
        {
            inOrder(i->left);
        }
        if(i->right)
        {
            inOrder(i->right);
        }

    }
    else return;
}
template <class itemType>
void BinarySearchTree<itemType>::printIndent()
{
    cout << "****** PRINTING BINARY SEARCH TREE *******" << endl;
    indented( root, 0 );
}
template <class itemType>
void BinarySearchTree<itemType>::indented ( node* tp, int spaces )
{
    int i;
    if( tp != NULL )
    {
        indented( tp->right, spaces + 13 );
        for( i = 0; i < spaces; i++ )
            cout <<' ';
        person *ptr = tp->data;
        cout << ptr->getName() << endl;
        indented( tp->left, spaces + 13);
    }
}
template <class itemType>
itemType* BinarySearchTree<itemType>::_search(node* i ,itemType const &key)
{
   	if(i == NULL) return NULL;
    if(*i->data == key) return i->data;
    else {
        if(*i->data < key)
            return _search(i->right, key) ;
        else
            return _search(i->left, key);
    }
}
template <class itemType>
itemType* BinarySearchTree<itemType>::search(itemType const &key) {
    return _search(root, key);
}
template <class itemType>
int BinarySearchTree<itemType>::Height(node* node){
    int  left , right;
    if(node==NULL){
        return false;
        }
   left = Height(node->left);
    right = Height(node->right);
    if(left > right)
        return left+1;
    else
        return right+1;
}
template <class itemType>
void BinarySearchTree<itemType>::rotateLeftOnce(node*& i){
    node *otherNode;
    otherNode = i->left;
    i->left = otherNode->right;
    otherNode->right = i;
    i = otherNode;
}
template <class itemType>
void BinarySearchTree<itemType>::rotateLeftTwice(node*& i){

    rotateRightOnce(i->left);
    rotateLeftOnce(i);
}
template <class itemType>
void BinarySearchTree<itemType>::rotateRightOnce(node*& i){
    node * otherNode;
    otherNode = i->right;
    i->right = otherNode->left;
    otherNode->left = i;
    i = otherNode;
}
template <class itemType>
void BinarySearchTree<itemType>::rotateRightTwice(node*& i){
    rotateLeftOnce(i->right);
    rotateRightOnce(i);
}
class hashing
{
private:
    int tableSize;
    int numberofentries;
	int largestbucket;
	int numberofcollisions;
   struct item
    {
        person *hashedPerson ;
        item* next;
        item() { next = NULL; hashedPerson = NULL; };
    };
    item **HashTable;
public:
    hashing() { tableSize = 0; }
    hashing(int size);
    int Hash(string key);
    void addObject(person &personObj);
    int NumberOfItemsInIndex(int index);
    void PrintTable();
    void removeObject(person &personObj);
    void getPrime(int &num);
   void deleteentry(){numberofentries--;}
    double getLoadingfactor(){return (double)numberofentries/(double)tableSize;}
    int getNumberofentries(){return numberofentries;}
    int getTablesize(){ return tableSize;}
    void reHash();
	int getNumberofcollisions(){return numberofcollisions;}
};
hashing::hashing(int size)
{
	numberofcollisions =0;
	largestbucket =0;
    size = size *2;
    getPrime(size);
    tableSize = size;
	numberofentries =0;
    HashTable = new item*[tableSize];
	for(int i=0; i<tableSize; i++){
		HashTable[i] = NULL;
	}
}
int hashing::Hash(string key)
{
    int hash = 0;
    int index;
   index = (int)key.length();
    for(int i = 0; i < key.length(); i++ )
    {
        hash = hash + (int)key[i];

    }
    index = hash % tableSize;
	cout << endl;
     cout << "[tableSize] : " << tableSize << endl;
     cout << "[hash] : " << hash << endl;
     cout << "[NAME] : " << key << endl;
     cout << "[INDEX] : " << index << endl;
    return index;
}
void hashing::addObject(person &personObj)
{
    int tempCollision = 0;
    int index = Hash(personObj.getName());
	cout << personObj.getName() << ": [" << index << "]\n" ;
    if(HashTable[index] == NULL)
    {
        HashTable[index] = new item;
        HashTable[index]->hashedPerson = &personObj;
        HashTable[index]->next =0;
		cout << personObj.getName() << " is added!\n";
    }
    else
    {
		item* Ptr = new item;
		Ptr->hashedPerson = HashTable[index]->hashedPerson;
		Ptr->next = HashTable[index]->next;
		HashTable[index]->hashedPerson = &personObj;
		HashTable[index]->next = Ptr;
		cout << personObj.getName() << " is added!" << endl;
        numberofcollisions = numberofcollisions +1;
		cout << numberofcollisions << endl;
	}
    numberofentries++;
    if(getLoadingfactor() > 0.75) {
        reHash();
    }
}
int hashing::NumberOfItemsInIndex(int index)
{
    int count = 0;

    if(HashTable[index] ==  NULL)
    {
        return count;
    }
    else
    {
        item* Ptr = HashTable[index];
        while(Ptr != 0)
        {
            count++;
            Ptr = Ptr->next;
        }
    }
	if(count > largestbucket)
	{
		largestbucket = count;
	}
    return count;
}
void hashing::PrintTable()
{
   cout << "****** PRINTING HASH TABLE *******" << endl;
    int number = 0;
    for(int i = 0; i < tableSize; i++)
    {
        if(HashTable[i] != NULL)
        {

			number = NumberOfItemsInIndex(i);
            cout << "Index = " << i <<endl;
            cout << "There are " << number << " people in this bucket.\n";
            item* Ptr = HashTable[i];

            while( Ptr != NULL)
            {
                cout << *Ptr->hashedPerson << endl;
                Ptr = Ptr->next;
            }
        }
    }
    cout << "The largest collision chain is " << largestbucket << endl;
    cout << "Number of collisions = " << getNumberofcollisions() <<endl;
    cout << "Number of elements = " << numberofentries << endl;
    cout << "Loading factor = " << getLoadingfactor() << endl;
}
void hashing::removeObject(person &personObj)
{
    int index = Hash(personObj.getName());

    item* delPtr;
    item* p1;
    item* p2;
    if(HashTable[index] == NULL)
        cout << "Person not found in the hash table!\n";
    else if( HashTable[index]->hashedPerson == &personObj && HashTable[index]->next == 0)
    {
        HashTable[index] = NULL;
        cout << personObj.getName() << " item not found!\n";
    }
    else if(HashTable[index]->hashedPerson == &personObj)
    {
        delPtr = HashTable[index];
        HashTable[index] = HashTable[index]->next;
        delete delPtr;
        delPtr = 0;
        cout << personObj.getName() << " is removed from the hash table!\n";
        numberofentries--;
    }
    else
    {
        p1 = HashTable[index]->next;
        p2 = HashTable[index];

        while(p1 != 0 && p1->hashedPerson != &personObj)
        {
            p2 = p1;
            p1 = p1->next;
        }
        if(p1 == 0)
        {
            cout << "Person not found in the hash table!\n";
        }
        else
        {
            delPtr = p1;
            p1 = p1->next;
            p2->next = p1;
            delete delPtr;
            delPtr = 0;
            cout << personObj.getName() << " is removed from the hash table!\n";
            numberofentries--;
        }
    }
}
void hashing::getPrime(int &num) {
    int i, j;
    for ( i = num; i < num+40; ++i)
    {
        for ( j = 2; j <= i/2; j++ )
        {
            if ( ! ( i % j ) ) break;
        }

        if ( j > i / 2 )
        {
            num = i;
            break;
        }
    }
}
void hashing::reHash() {
    int newSize = tableSize * 2;
    getPrime(newSize);
    cout << "Old Table Size = " << tableSize << endl;
    cout << "New Table Size = " << newSize << endl;

    item* newArr = new item[newSize];
    int count = 0;
    for(int i = 0; i < tableSize; i++)
    {
        if(HashTable[i] != NULL)
        {
            item* Ptr = HashTable[i];
            while( Ptr != NULL)
            {
                cout <<"Adding to temp Array" << endl;
                cout << *Ptr->hashedPerson;
                newArr[count] = *Ptr;
                count++;
                Ptr = Ptr->next;
            }
        }
    }
    delete [] HashTable;
    tableSize = newSize;
    HashTable = new item*[tableSize];
    numberofentries = 0;
    for(int i=0; i<tableSize; i++){
		HashTable[i] = NULL;
	}
    for(int i = 0; i < count; i++)
    {

                cout <<"Adding to new  Hashed Array" << endl;
                cout << *newArr[i].hashedPerson;
                addObject(*newArr[i].hashedPerson);
        }
    delete[] newArr;
}
class user{
public:
    BinarySearchTree<person> tree;
    person personArray[100];
    int count;
    user()
    {
    count=0;
    }
    void readFile(string textname)
    {
        string  name;
        string password;
        string gender;
        string age;
        string city;
        string college;
        string wasteSpace;
        ifstream infile;
        infile.open("name.txt");
        while(!infile.eof())
        {
            getline(infile, name);
            getline(infile, password);
             getline(infile, gender);
            getline(infile, age);
            getline(infile, city);
            getline(infile, college);
            getline(infile, wasteSpace);
            int Age = atoi(age.c_str());

            person tempPerson(name, password, gender, Age, city, college);
            personArray[count] = tempPerson;
            tree._insert(personArray[count]);
            count++;


        }
    }


    void userMenu(string name, string password) {
        bool options = true;
        person *temp;  person *other; person temporary; vector<person *> tempFriends;

        temporary.setName(name);
        temp = tree.search(temporary);
        if(temp == NULL ){
            cout << "Incorrect Username and Password";
            return;
        }
        if(temp->getPwd() != password){
            cout << "Incorrect Username and Password";
            return;
        }
        if(temp->getStatus() != false)
                {
                    int status;
                    cout << "Your account is not active" << endl;
                    cout << "Please reactivate your account in order to access it" <<endl;
                    cout << "Press [1] to Reactivate or [2] to Exit" <<endl;
                    cin >> status;
                    if (status == 1)
                        temp->deactivateAccount(false);
                    else
                        return;
                }
                while(options == true) {
                    cout << endl<< "-------------"<< temp->getName() << " Profile --------------" << endl;;
                    cout << "Choose an option from below" << endl;
                    cout << "1. Add a friend" << endl
                    << "2. Write a new Status Message" << endl
                    << "3. Send a message" << endl
                    << "4. Show your friends" << endl
                    << "5. Show newsfeed" << endl
                    << "6. Print your status messages" <<endl
                    << "7. Print your private messages" << endl
                    << "8. Account Settings" << endl
                    << "9. Logout"  << endl << "[Choose Your Option] : " ;

                    int option;
                    string friendName;
                    string message;
                    string pressKey;
                    bool friendFound = false;
                    string status = " ";
                    cin >> option;
                    switch(option) {
                        case 1 : cout << "Which friend would you like to add" << endl;
                            cin.ignore();
                            getline(cin, friendName);
                            temporary.setName(friendName);
                            other = tree.search(temporary);
                            if(other == NULL)
                            { cout << "Person does not exist in the database";
                                continue;
                            } else {
                                    temp->addFriend(*other);
                                    friendFound = true;
                                }
                            break;

                        case 2 : cout << "What's on your mind?" << endl;
                            cin.ignore();
                            getline(cin, status);
                            cout << " " << endl;
                            temp->setStatus(status);
                            break;

                        case 3 :
                            cout << "Which friend would you like to send a message" << endl;
                            cin.ignore();
                            getline(cin, friendName);
                            cout << "What message would you like to send : " << endl;
                            getline(cin, message);
                            temporary.setName(friendName);
                            other = tree.search(temporary);
                            if(other == NULL)
                            { cout << "Person does not exist in the database";
                                break;
                            }
                            else
                                temp->sendMessage(*other, message);
                            break;
                        case 4 :
                            temp->printFriends();
                            break;
                        case 5 :
                            tempFriends = temp->getFriends();
                            for(int i = 0; i < tempFriends.size(); i++) {
                                tempFriends[i]->printStatus();
                            }
                            break;
                        case 6 :
                             temp->printStatus();
                            break;
                        case 7 :
                            temp->printMessages();
                            break;
                        case 8:
                            userAdminMenu(*temp);
                            break;
                        case 9 :
                            options = false;
                            break;
                        default:
                            cout << "select the right option";

                    }
                    cout <<endl << "Press z to continue : ";
                    cin>> pressKey;

                }


        if(options == false){
            cout << "You've been logged out." << endl;
            return;
        }

    }

    void userAdminMenu(person &personName) {
        person temporary;
        person *other;
        bool options = true;
        while( options == true ) {
            int option;
            string temp;
            cout << "-------------"<< personName.getName() << " Settings --------------" << endl;;
            cout << "Choose an option from below" << endl;
            cout << "1. Change Password" << endl
            << "2. Change City " << endl
            << "3. Change University" << endl
            << "4. Delete a Friend" << endl
            << "5. Deactivate Profile " << endl
            << "6. Back to your Profile" << endl
            <<"[Choose Your Option] : ";
            cin >> option;
            switch(option) {
                case 1 :
                    cout << "New Password : ";
                    cin>>temp;
                    personName.setPassword(temp);
                    cout << "Your Password has been changed";
                    break;
                case 2 :
                    cout << "New City : ";
                    cin>>temp;
                    personName.setCity(temp);
                    cout << "Your City has been changed";
                    break;
                case 3 :
                    cout << "New University : ";
                    cin>>temp;
                    personName.setCollege(temp);
                    cout << "\nYour University has been changed";
                    break;
                case 4:
                    cout << "Enter the name of the friend you want to Delete : ";
                    cin.ignore();
                    getline(cin, temp);
                    temporary.setName(temp);
                    other = tree.search(temporary);
                    if(other == NULL)
                    { cout << "The person does not exist in the database.";
                        break;
                    }
                    personName.deleteFriend(*other);
                    break;
                case 5 :
                    cout << "Are you sure you want to deactivate your account?" <<endl
                    <<"Choose [1] for Yes \n [2] for No  : ";
                    cin >> temp;
                    if (temp == "1"){
                        personName.deactivateAccount(true);
                        cout <<"Your account has been deactivated, however you can still access your account until you logout";
                    }
                    else {
                        cout << "Your account has not been deactivated" << endl;
                    }
                    break;
                case 6:
                    options = false;
                    break;
                default:
                    cout << "please select the right option";

            }
        }


    }


    void adminMenu(user &obj, string password) {
        hashing hashfunc(count);
        for (int i = 0 ; i < count ; i++ ) {
            hashfunc.addObject(personArray[i]);
        }
        person *temp; person temporary; string name;


        if (password != "pass")
        {
            cout << "incorrect username or password";
            return;
        }

        bool options = true;
        while(options == true) {
            cout <<  "-------------------- ADMINISTRATOR  --------------" << endl;;
            cout << "Choose an option from below" << endl;
            cout << "1.Delete a Person" << endl
            << "2. Print the Hash Table" << endl
            << "3. Print the Binary Tree" << endl
            << "4. Print Indented Tree" <<endl
            << "5. Logout" << endl
            << "[Choose Your Option] : " ;
            int option;
            cin >> option;

            switch(option) {
                case 1:
                    cout << "Name of the person to be deleted : " <<endl;
                    cin.ignore();
                    getline(cin, name);
                    temporary.setName(name);
                    tree.remove(temporary);
                    hashfunc.removeObject(temporary);
                    break;

                case 2 :
                    hashfunc.PrintTable();
                    break;

                case 3 :
                    tree.print_inOrder();
                    break;

                case 4:
                    tree.printIndent();
                    break;

                case 5:
                    options = false;
                    break;
                default :
                    cout << "Please enter the correct choice:" ;
            }

        }
        if(options == false) {
            cout << "You have been logged out" <<endl;
            return;
        }
    }
};
int main()
{

    user u;
    u.readFile("name.txt");
    int input = 0;
    while(input == 0) {
        cout << "\n-------------------Welcome to the Social Network---------------------\n\n\n";
        string name;
        string password;
        cout << "Username: ";
        cin.ignore(1,'\n');
        getline(cin, name);
        cout << "Password: ";
        cin>>password;
        if(name != "admin")
            u.userMenu(name, password);
        else
            u.adminMenu(u, password);
    }

}

