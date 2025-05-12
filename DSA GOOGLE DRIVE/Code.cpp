#include <iostream > 
#include <string>
#include <ctime>
using namespace std;
//THIS IS THE FILES CALSS WHERE WE STORE ITS META DATA 

int  Input(int& input, int min = INT_MIN, int max = INT_MAX)
{

    cin >> input;
    if (input >= min && input <= max && !cin.fail())
        return input;
    else
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << endl << "ENTER A NUMBER  BETWEEN " << min << "-" << max << endl;
        Input(input, min, max);
    }
}
class file
{
    int size;
    string data; //THIS IS THE CONTENT OF FILE  
    string type;
    string owner;
    int id;
public:
    file()
    {
        id = 0;
        size = 0;
    }
    int getId()
    {
        return id;
    }
    void setValues(int s, string dat, string typ, string ow, int id)
    {
        size = s;
        data = dat;
        type = typ;
        owner = ow;
        this->id = id;
        RLE_Compress(); //USING THE RLE ALGORITM TO CHANGE THE FORMAT OF DATA VARIBEL
    }
    void display()
    {
        cout << "-----------------------------\n\n";
        cout << "ID : " << id << endl;
        cout << "SIZE : " << size << endl;
        cout << "TYPE : " << type << endl;
        cout << "OWNER : " << owner << endl;
        cout << "CONTENT  : \n" << RLE_Decompress() << endl;
        cout << "CONENT IN RLE FORMAT : \n" << data << endl;
        cout << "-----------------------------\n\n";
    }
    void del()
    {
        id = 0;
        size = 0;
        type = "";
        data = "";
    }
    void Update()
    {
        cout << "ENTER NEW SIZE : ";
        cin >> size;
        cin.ignore();
        cout << "ENTER NEW DATA : ";
        getline(cin, data);
        cin.ignore();
    }
    void RLE_Compress()
    {
        string result = "";
        int n = data.length();

        for (int i = 0; i < n; ) {
            char current = data[i];
            int count = 1;

            while (i + 1 < n && data[i + 1] == current) {
                count++;
                i++;
            }
            result += to_string(count) + current;
            i++;
        }

        data = result;
    }


    string RLE_Decompress()
    {
        string result = "";
        int n = data.length();

        for (int i = 0; i < n; ) {
            int count = 0;

            while (i < n && isdigit(data[i])) {
                count = count * 10 + (data[i] - '0');
                i++;
            }

            if (i < n) {
                char ch = data[i++];
                result.append(count, ch);
            }
        }

        return result;
    }

};
//THIS IS THE HASH TABLE OF FILES : 

class Stackfiles
{
    int top;
    file arr[50];
public:
    Stackfiles()
    {
        top = 0;
    }
    void push(file f)
    {
        arr[top] = f;
        top++;
    }
    file pop()
    {
        return arr[top - 1];
        top--;
    }
    bool isempty()
    {
        return top;
    }
    void display()
    {
        for (int i = 0; i < top; i++)
            arr[i].display();
    }
};
class FilesQeueu
{
    int top;
    int bottom;
    file arr[50];
public:
    FilesQeueu()
    {
        top = -1;
        bottom = -1;
    }
    void enqeue(file temp)
    {
        if (top < 50)
        {
            top = (top + 1) % 50;
            arr[top] = temp;
        }
        else
            cout << "QEUE IS FULL! ";
    }
    file deqeue()
    {
        if (top != bottom)
        {
            bottom = (bottom + 1) % 50;
            return arr[bottom];
        }
        else
        {
            cout << "QUEUE IS EMPTY ";
            file garbage;
            return garbage;
        }
    }
    bool isempt()
    {
        return top == bottom;
    }
    file peek()
    {
        if (top != bottom)
            return arr[(bottom + 1) % 50];
        else
        {
            cout << "Queue is empty\n";
            file garbage;
            return garbage;
        }
    }
    void display()
    {
        int i = (bottom + 1) % 50;
        while (i != (top + 1) % 50)
        {
            arr[i].display();
            i = (i + 1) % 50;
        }
    }
};
template <typename T>
struct node
{
    T data;
    node* next;
    node* prev;
    node(T dat)
    {
        data = dat;
        next = NULL;
        prev = NULL;
    }
};
template <typename T>
class list
{
    node<T>* root;
public:
    list()
    {
        root = NULL;
    }
    void insert(T data)
    {
        node<T>* newNode = new node<T>(data);
        if (!root)
            root = newNode;
        else
        {
            node<T>* temp = root;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
            newNode->prev = temp;
        }
    }
    T* getHead()
    {
        if (root)
            return &root->data;
        else
            return NULL;
    }
    node<T>* getRoot()
    {
        return root;
    }
    void printP()
    {
        node<T>* temp = root;
        while (temp)
        {
            cout << temp->data.getName() << " ";
            temp = temp->next;
        }
    }
    void printF()
    {
        int i = 1;
        node<T>* temp = root;
        while (temp)
        {
            cout << " -----(" << i << ")-----\n";
            temp->data.display();
            cout << "----------------------\n ";
            temp = temp->next;
            i++;
        }
    }
    T* searchByIndex(int index)
    {
        if (index < 1)
            return NULL;
        if (index == 1)
            return &root->data;
        node<T>* temp = root;
        int count = 1;

        while (temp && count < index)
        {
            temp = temp->next;
            count++;
        }
        if (temp && count == index)
            return &temp->data;
        else
            return NULL;
    }

};
class  HashTableFiles
{
    int size;
    int key;
    file* arr;
    list<file>* Versions;
public:
    HashTableFiles()
    {
        key = 0;
        size = 10;
        arr = new file[size];
        Versions = new list<file>[size];
    }
    void update()
    {
        display();

        int id;
        cout << "ENTER ID OF FILE YOU WANT TO UPDATE : ";
        cin >> id;
        Versions[id].insert(arr[id]);
        arr[id].Update();
    }
    void previousVersions()
    {
        int id;
        cout << "ENTER ID OF FILE YOU WANT TO UPDATE : ";
        cin >> id;
        if (Versions[id].getRoot())
        {

            Versions[id].printF();
            cout << "\nSELECT   WHICH VERSION TO REVERS TO  : ";
            cin >> id;
            arr[id] = *Versions[id].searchByIndex(id);
        }
        else
            cout << "NO PREVIOUS VERSIONS ! ";

    }
    int hashFuntion(int key)
    {
        return key % size;
    }
    void resize()
    {
        file* temp = new file[size];
        list<file>* temparr = new list<file>[size];
        for (int i = 0; i < size; i++)
        {
            temparr[i] = Versions[i];
            temp[i] = arr[i];
        }
        delete[] arr;
        delete[] Versions;
        size *= 2;
        size++;
        arr = new file[size];
        for (int i = 0; i < size / 2; i++)
        {
            arr[i] = temp[i];
            Versions[i] = temparr[i];
        }
        delete[] temparr;
        delete[] temp;
        temparr = NULL;
        temp = NULL;
    }
    void insert(file obj)
    {
        int original = hashFuntion(obj.getId());
        int idx = original;

        while (arr[idx].getId() != 0 && arr[idx].getId() != obj.getId())
        {
            idx = (idx + 1) % size;
            if (idx == original)  //THSI MEANS THAT THE LOOP HAS REPEATED MEANING THE HASH TABLE IS FULL 
            {
                resize();
                original = hashFuntion(obj.getId());
                idx = original;
            }
        }
        arr[idx] = obj;
    }
    file deleteFile(int id)
    {
        file temp;
        for (int i = 0; i < size; i++)
        {
            if (arr[i].getId() == id)
            {
                temp = arr[i];//I AM STRONG THIS FILE SO I CAN RETURN IT TO PUT IT INTO THE STACK 
                arr[i].del(); //THIS WILL DELTE THE FILE FROM HASH TABLE  
                return temp;
            }
        }
        cout << "ID NOT FOUND !";
        return temp;
    }
    file* search(int id)
    {
        int orignal;
        key = hashFuntion(id);
        orignal = key; //TO AVOID INFINTE LOOP ;
        while (arr[key].getId() == id)
        {
            key = hashFuntion(key + 1);
            if (key == orignal)
            {
                cout << "\nFILE DOESNT EXSIST !";
                return NULL;
            }
        }
        return &arr[key];
    }
    void display()
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i].getId() != 0)
                arr[i].display();
        }
    }
};

//THIS IS THE CLASS OF FOLDER   

class folder
{
    HashTableFiles  Files;

    Stackfiles st;
    FilesQeueu que;
    string name;
    string ownerName;
    int id;
    int count;
public:
    void setValuse(string n, int i, string owner)
    {
        ownerName = owner;
        id = i;
        name = n;
        count = 0;
    }
    int getId()
    {
        return id;
    }
    string getName()
    {
        return name;
    }

    void insert()
    {
        int size;
        string data;
        string type;
        file obj;
        count++;
        cout << "ENTER SIZE : ";
        cin >> size;
        cout << "ENTER FILE TYPE : ";
        cin >> type;
        cin.ignore();
        cout << "ENTER DATA FOR FILE : ";
        getline(cin, data);
        cin.ignore();
        obj.setValues(size, data, type, ownerName, count);
        Files.insert(obj);
    }
    void search()
    {
        int id;
        cout << "ENTER ID YOU WANT TO SEARCH  1 - " << count << " : ";
        Input(id, 1, count);
        Files.search(id - 1)->display();
        que.enqeue(*Files.search(id - 1));
    }
    void displayAllFiles()
    {
        cout << "FOLDER NAME : " << name << endl;
        Files.display();
    }
    void menu()
    {
        bool flag = true;
        int choice = 0;
        while (flag)
        {
            system("pause");
            system("cls");
            cout << "1.INSERT NEW FILE \n2.SEARCH NEW FILE\n3.DISPLAY ALL FILES\n4.DELETE FILE\n5.DISPLAY DELETED FILES \n6.RECOVER RECENTLY DELETED FILE\n7.VEIW RECETLY VIEWED FILE \n8.UPDATE FILE\n9.VIEW PREVIOUS VERSIONS \n10.EXIT\n";
            Input(choice, 1, 10);
            switch (choice)
            {
            case 1:
                insert();
                break;
            case 2:
                search();
                break;
            case 3:
                displayAllFiles();
                break;
            case 4:

                displayAllFiles();
                cout << "GIVE ID OF FILE YOU WANT TO DELETE : ";
                cin >> choice;
                st.push(Files.deleteFile(choice));
                break;
            case 5:
                st.display();
                break;
            case 6:
                Files.insert(st.pop());
                break;
            case 7:
                if (!que.isempt())
                {
                    cout << "THIS  IS THE MOST RECENT FILE : ";
                    que.peek().display();
                    cout << "\n\nTHESE ARE ALL THE FILES WHICH ARE VIEW IN ORDER :\n";
                    que.display();
                }
                break;
            case 8:
                Files.update();
                break;
            case 9:
                Files.previousVersions();
                break;
            case 10:
                flag = false;
            default:
                cout << "EXITED ! ";
            }
        }
    }
};

class TreeNode
{
public:
    folder data;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(folder f)
    {
        data = f;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

class AVLTree
{
    TreeNode* root;

    int height(TreeNode* n)
    {
        return n ? n->height : 0;
    }

    int balanceFactor(TreeNode* n)
    {
        return height(n->left) - height(n->right);
    }

    TreeNode* rotateRight(TreeNode* y)
    {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        return x;
    }

    TreeNode* rotateLeft(TreeNode* x)
    {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }

    TreeNode* insert(TreeNode* node, folder f, int id)
    {
        if (!node)
            return new TreeNode(f);
        if (id < node->data.getId())
            node->left = insert(node->left, f, id);
        else if (id > node->data.getId())
            node->right = insert(node->right, f, id);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int bf = balanceFactor(node);

        if (bf > 1 && id < node->left->data.getId())
            return rotateRight(node);
        if (bf < -1 && id > node->right->data.getId())
            return rotateLeft(node);
        if (bf > 1 && id > node->left->data.getId())
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1 && id < node->right->data.getId())
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }
    void displayAllHelper(TreeNode* node)
    {
        if (!node)
            return;
        displayAllHelper(node->left);
        cout << "Folder: " << node->data.getName() << "\n";
        node->data.displayAllFiles();
        displayAllHelper(node->right);
    }
    void inorder(TreeNode* node)
    {
        if (!node)
            return;
        inorder(node->left);
        node->data.getName();
        inorder(node->right);
    }
    folder* search(TreeNode* node, int id)
    {
        if (!node)
            return NULL;
        if (id == node->data.getId())
            return &(node->data);
        else if (id < node->data.getId())
            return search(node->left, id);
        else
            return search(node->right, id);
    }

public:
    AVLTree()
    {
        root = NULL;

    }

    void insert(folder f, int id)
    {
        root = insert(root, f, id);
    }
    void displayAllFoldersWithFiles()
    {
        displayAllHelper(root);
    }
    void display()
    {
        inorder(root);
    }

    folder* search(int id)
    {
        return search(root, id);
    }
};

class User
{
    AVLTree folders;
    string name;
    string password;
    string question;
    string answer;
    string date;
    list<User> u;
    int count;
    int id;
public:
    User()
    {
        count = 1;
    }
    string getPass()
    {
        return password;
    }
    string getName()
    {
        return name;
    }
    void logout()
    {
        time_t t = time(0);
        tm ltm;
        localtime_s(&ltm, &t);

        date = to_string(1900 + ltm.tm_year) + "-" +
            to_string(1 + ltm.tm_mon) + "-" +
            to_string(ltm.tm_mday) + " " +
            to_string(ltm.tm_hour) + ":" +
            to_string(ltm.tm_min) + ":" +
            to_string(ltm.tm_sec);
    }
    void insertFolder()
    {
        folder f;
        string namef;
        cout << "ENTER FOLDER NAME : ";
        cin >> namef;
        f.setValuse(namef, count, name);
        folders.insert(f, count++);
    }
    void signUp()
    {
        cin.ignore();
        cout << "ENTER NAME : ";
        getline(cin, name);
        cout << "IF YOU FORGOT YOUR PASSWORD WHAT QUESION SHOULD BE ASKED : ";
        getline(cin, question);
        cout << "GIVE ANSWER : ";
        getline(cin, answer);
        cin.ignore();
        cout << "ENTER PASSWORD : ";
        cin >> password;
        cout << "ENTER ID : ";
        cin >> id;
    }
    void forgetPassword()
    {
        string que;
        cin.ignore();
        cout << question << " \nGIVE ANSWER : ";
        getline(cin, que);
        cin.ignore();
        if (que == answer)
        {
            cout << "ENTER NEW PASSWORD : ";
            cin >> password;
        }
        else
            cout << "INVALID ANSWER ! ";
    }
    void displayFoldersAndFiles()
    {
        cout << "\n=== Files of " << name << " ===\n";
        folders.displayAllFoldersWithFiles();
    }
    void menu()
    {
        bool flag = true;
        int choice = 0;

        while (flag)
        {
            system("pause");
            system("cls");
            cout << "\n1.ADD FOLDER \n2.SEE ALL FOLDERS \n3.SELECT A FOLDER\n4.LOGOUT\n";
            Input(choice, 1, 4);
            switch (choice)
            {
            case 1:
                insertFolder();
                break;
            case 2:
                folders.displayAllFoldersWithFiles();
                break;
            case 3:
                cout << "SELECT FROM 1 - " << count - 1 << " : ";
                cin >> choice;
                folders.search(choice)->menu();
                break;
            case 4:
                logout();
                cout << "LOGGED OUT AT : " << date << endl;
                flag = false;
            default:
                break;
            }
        }
    }
};
class GraphUsers
{
    list<User*>* arr;
    User* ptr;
    int count;
    int size;

public:
    GraphUsers()
    {
        count = 0;
        size = 10;
        arr = new list<User*>[size];
    }

    ~GraphUsers()
    {
        for (int i = 0; i < count; ++i)
        {
            delete* arr[i].getHead();
        }
        delete[] arr;
    }

    void resize()
    {
        int oldSize = size;
        list<User*>* temp = new list<User*>[oldSize];
        for (int i = 0; i < oldSize; i++)
            temp[i] = arr[i];
        delete[] arr;

        size *= 2;
        size++;
        arr = new list<User*>[size];
        for (int i = 0; i < oldSize; i++)
            arr[i] = temp[i];
        delete[] temp;
    }

    void addUser()
    {
        if (count >= size)
            resize();
        User* a = new User();
        a->signUp();
        arr[count].insert(a);
        count++;
    }

    void login()
    {
        string n, p;
        ptr = nullptr;
        int index = -1;

        cin.ignore();
        cout << "ENTER NAME : ";
        getline(cin, n);
        cout << "ENTER PASSWORD : ";
        cin >> p;

        for (int i = 0; i < count; i++)
        {
            User* head = *arr[i].getHead();
            if (n == head->getName() && p == head->getPass())
            {
                index = i;
                ptr = head;
                break;
            }
        }
        if (!ptr)
        {
            cout << "NO USER NAME AND PASSWORD FOUND!\n";
            return;
        }

        cout << "YOU ARE NOW LOGGED IN!\n";
        ptr->menu();

        node<User*>* cur = arr[index].getRoot()->next;
        if (!cur)
        {
            cout << "\nYOU HAVE NO CONNECTIONS.\n";
            return;
        }
        cout << "\n--- YOUR CONNECTIONS' FOLDERS AND FILES ---\n";
        while (cur)
        {
            cout << "\n>> " << cur->data->getName() << ":\n";
            cur->data->displayFoldersAndFiles();
            cur = cur->next;
        }
    }

    void menu()
    {
        bool flag = true;
        while (flag)
        {
            system("pause");
            system("cls");
            int choice;
            cout << "\n1. LOGIN\n2. SIGN UP\n3. FORGET PASSWORD\n4. MAKE CONNECTION\n5. EXIT\n";
            Input(choice, 1, 5);

            switch (choice)
            {
            case 1:
                login();
                break;

            case 2:
                addUser();
                break;

            case 3:
            {
                cout << "ENTER USER NAME: ";
                string n;
                cin >> n;
                for (int i = 0; i < count; i++)
                {
                    User* head = *arr[i].getHead();
                    if (head->getName() == n)
                        head->forgetPassword();
                }
            }
            break;

            case 4:
            {
                cout << "ENTER NAME OF USER 1: ";
                string n1, n2;
                cin >> n1;
                cout << "ENTER NAME OF USER 2: ";
                cin >> n2;

                int idx1 = -1, idx2 = -1;
                for (int i = 0; i < count; i++)
                {
                    User* head = *arr[i].getHead();
                    if (head->getName() == n1)
                        idx1 = i;
                    if (head->getName() == n2)
                        idx2 = i;
                }

                if (idx1 >= 0 && idx2 >= 0 && idx1 != idx2)
                {
                    arr[idx1].insert(*arr[idx2].getHead());
                    arr[idx2].insert(*arr[idx1].getHead());
                    cout << "CONNECTION MADE BETWEEN " << n1 << " AND " << n2 << "\n";
                }
                else
                    cout << "INVALID OR SELF CONNECTION!\n";
            }
            break;

            case 5:
                flag = false;
                break;

            default:
                break;
            }
        }
    }
};

int main()
{
    GraphUsers  g;
    g.menu();
}
