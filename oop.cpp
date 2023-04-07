#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;
int numPublisher = 1;
int numLibrary = 1;
enum BookType
{
    SCIENTIFIC,
    CRIME,
    FANTASY,
    HORROR,
    CLASSICS
};
class Publisher
{
    int id;
    string name;
    string location;

public:
    Publisher(string name, string location)
    {
        this->name = name;
        this->location = location;
        id = numPublisher;
        numPublisher++;
    };
    Publisher()
    {
    }
    int getId()
    {
        return id;
    }
};
class Book
{
    int id;
    string name;
    BookType type;
    Publisher publisher;
    bool borrowed;

public:
    Book(string name, Publisher publisher(), BookType type)
    {
        this->name = name;
        this->publisher = publisher();
        this->type = type;
        borrowed = 0;
    }
    void showInfo()
    {
        cout << id << "." << name;
    }
    string getName()
    {
        return name;
    }
    int getId()
    {
        return id;
    }
    BookType getBookType()
    {
        return type;
    }
    bool getBorrow()
    {
        return borrowed;
    }
    void changeBorrow(){
        borrowed=!borrowed;
    }
};
class Member
{
    string id;
    string name;
    vector<Book> books;

public:
    vector<Book> getBooks()
    {
        return books;
    }
    Member(string id, string name)
    {
        this->id = id;
        this->name = name;
    }
    string getId()
    {
        return id;
    }
    string getName()
    {
        return name;
    }
};
class Library
{
    int id;
    string name;
    vector<Book> books;
    int position;

public:
    Library(string name, int position)
    {
        this->name = name;
        this->position = position;
        id = numLibrary;
        numLibrary++;
    }
    string getName()
    {
        return name;
    }
    int getPosition()
    {
        return position;
    }
    int GetId()
    {
        return id;
    }
    Book search(string name)
    {
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getName() == name)
            {
                return books[i];
            }
        }
    }
    vector<Book> listOfBooks()
    {
        return books;
    }
    void AddBook(Book book)
    {
        books.push_back(book);
    }
    vector<Book> BooksByType(BookType type)
    {
        vector<Book> v;
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].getBookType() == type)
            {
                v.push_back(books[i]);
            }
        }
        return v;
    }
};
class LibrariesHandler
{
    vector<Library> ShahedLibraries;
    vector<Member> ShahedMembers;

public:
    void createLibrary(string name, int position)
    {
        bool interference = 0;
        for (int i = 0; i < ShahedLibraries.size(); i++)
        {
            if (ShahedLibraries[i].getName() == name)
            {
                cout << "A library with this name already exists";
                interference = 1;
                break;
            }
            if (ShahedLibraries[i].getPosition() == position)
            {
                cout << "There is now a library in this place";
                interference = 1;
                break;
            }
        }
        if (interference == false)
        {
            Library NewLibrary(name, position);
            ShahedLibraries.push_back(NewLibrary);
        }
    }
    void addBook(int libId, string name, Publisher publisher(), BookType type)
    {
        for (int i = 0; i < ShahedLibraries.size(); i++)
        {
            if (ShahedLibraries[i].GetId() == libId)
            {
                Book NewBook(name, publisher,  type);
                ShahedLibraries[i].AddBook(NewBook);
                return;
            }
        }
        cout << "NO SUCH LIBRARY EXISTS";
    }
    void addBook(int libId, Book book)
    {
        for (int i = 0; i < ShahedLibraries.size(); i++)
        {
            if (ShahedLibraries[i].GetId() == libId)
            {
                ShahedLibraries[i].AddBook(book);
                return;
            }
        }
        cout << "NO SUCH LIBRARY EXISTS";
    }
    void addMember(string name, string id)
    {
        for (int i = 0; i < ShahedMembers.size(); i++)
        {
            if (name == ShahedMembers[i].getName())
            {
                cout << "A Member with this id already exists\n";
                return;
            }
        }
        Member newMember(id, name);
        ShahedMembers.push_back(newMember);
    }
    vector<Book> getAllBooks(int libId)
    {
        for (int i = 0; i < ShahedLibraries.size(); i++)
        {
            if (ShahedLibraries[i].GetId() == libId)
            {
                return ShahedLibraries[i].listOfBooks();
            }
        }
        vector<Book> v;
        return v;
    }
    string getAllBooksInfo(int libId)
    {
        string s;
        for (int i = 0; i < ShahedLibraries.size(); i++)
        {
            if (ShahedLibraries[i].GetId() == libId)
            {
                for (int j = 0; j < ShahedLibraries[i].listOfBooks().size(); j++)
                {
                    s += to_string(j + 1);
                    s += ". ";
                    s += ShahedLibraries[i].listOfBooks()[j].getName();
                    s += "\n";
                }
            }
        }
        return s;
    }
    vector<Book> filterByType(int libId, BookType type)
    {
        vector<Book> v;
        for (int i = 0; i < ShahedLibraries.size(); i++)
        {
            if (ShahedLibraries[i].GetId() == libId)
            {
                for (int j = 0; j < ShahedLibraries[i].listOfBooks().size(); j++)
                {
                    if (ShahedLibraries[i].listOfBooks()[j].getBookType() == type)
                    {
                        v.push_back(ShahedLibraries[i].listOfBooks()[j]);
                    }
                }
            }
        }
        return v;
    }
    string filterByTypeAndShowInfo(int libId, BookType type)
    {
        vector<Book> v = ShahedLibraries.filterByType(int libId, BookType type);
        string s;
        for (int i = 0; i < v.size(); i++)
        {
            s += to_string(i + 1);
            s += ". ";
            s += v[i].getName();
            s += "\n";
        }
        return s;
    }
    void borrow(string memberId, int libraryId, string name)
    {
        for (int i = 0; i < ShahedLibraries.size(); i++)
        {
            if (ShahedLibraries[i].GetId() == libraryId)
            {
                for (int j = 0; j < ShahedLibraries[i].listOfBooks().size(); j++)
                {
                    if (ShahedLibraries[i].listOfBooks()[j].getName() == name)
                    {
                        if (ShahedLibraries[i].listOfBooks()[j].getBorrow())
                        {
                            cout << "THIS BOOK IS UNAVAILABLE";
                            return;
                        }
                        for (int k = 0; k < ShahedMembers.size(); k++)
                        {
                            if (ShahedMembers[k].getId() == memberId)
                            {
                                if (ShahedMembers[k].getBooks().size() == 5)
                                {
                                    cout << "YOU HAVE BORROWED 5 BOOKS .YOU CANT BORROE MORE THAN 5 BOOKS";
                                     return;
                                }
                                ShahedMembers[k].getBooks().push_back(ShahedLibraries[i].listOfBooks()[j]);
                                ShahedLibraries[i].listOfBooks()[j].changeBorrow();
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
    void returnBook(string memberId, int libraryid, string name)
    {
        for (int i = 0; i < ShahedLibraries.size(); i++)
        {
            if (ShahedLibraries[i].GetId() == libraryid)
            {
                for (int j = 0; j < ShahedMembers.size(); j++)
                {
                    if (ShahedMembers[j].getId() == memberId)
                    {
                        for (int k = 0; k < ShahedMembers[j].getBooks().size(); k++)
                        {
                            if (ShahedMembers[j].getBooks()[k].getName() == name)
                            {
                                ShahedMembers[j].getBooks()[k].changeBorrow();
                                ShahedMembers[j].getBooks().erase(ShahedMembers[j].getBooks().begin() + k);
                            }
                        }
                    }
                }
            }
        }
    }

public:
    int size()
    {
        int x = 0;
        for (int i = 0; i < ShahedLibraries.size(); i++)
        {
            x += ShahedLibraries[i].listOfBooks().size();
        }
        return x;
    }
    Library findNearestLibraryByPosition(string name, int position)
    {
        vector<Library> v;
        for (int i = 0; i < ShahedLibraries.size(); i++)
        {
            for (int j = 0; j < ShahedLibraries[i].listOfBooks().size(); j++)
            {
                if (ShahedLibraries[i].listOfBooks()[j].getName() == name)
                {
                    v.push_back(ShahedLibraries[i]);
                    break;
                }
            }
        }
        int index = 0;
        int curPos = abs(position - v[0].getPosition());
        string curName = v[0].getName();
        for (int i = 1; i < v.size(); i++)
        {
            if (abs(position - v[i].getPosition()) < curPos || (abs(position - v[i].getPosition()) == curPos && curName > v[i].getName()))
            {
                curPos = abs(position - v[i].getPosition());
                curName = v[i].getName();
                index = i;
            }
        }
        return v[index];
    }
    string findLibrariesHaveBook(string name, int position)
    {
        vector<Library> v;
        for (int i = 0; i < ShahedLibraries.size(); i++)
        {
            for (int j = 0; j < ShahedLibraries[i].listOfBooks().size(); j++)
            {
                if (ShahedLibraries[i].listOfBooks()[j].getName() == name)
                {
                    v.push_back(ShahedLibraries[i]);
                    break;
                }
            }
        }
        for (int i = 0; i < v.size() - 1; i++)
        {
            for (int j = i + 1; j < v.size(); j++)
            {
                if (abs(v[j].getPosition() - position) < abs(v[i].getPosition() - position) || ((abs(v[j].getPosition() - position) == abs(v[i].getPosition() - position)) && v[j].getName() < v[i].getName()))
                {
                    swap(v[i], v[j]);
                }
            }
        }
        string s;
        for (int i = 0; i < v.size(); i++)
        {
            s += to_string(i + 1);
            s += ". ";
            s += ShahedLibraries[i].getName();
            s += " ";
            s += to_string(abs(ShahedLibraries[i].getPosition() - position));
            s += "\n";
        }
        return s;
    }
};