#include "sequence.h"
#include <iostream>

namespace tests
{
    bool test1() // testing addictive functional and operator
    {
        bool flag = true;
        int* ar = new int[7]{100, 13, 1, 2, 3, 34, 45};
        SequenceArray<int>* sa = new SequenceArray<int>(new int[3]{1, 2, 3}, 3);
        SequenceList<int>* sl = new SequenceList<int>(new int[3]{1, 2, 3}, 3);
        sa->append(34);
        sl->append(34);
        sa->prepend(13);
        sl->prepend(13);
        sa->append(45);
        sl->append(45);
        sa->prepend(100);
        sl->prepend(100);
        for (int i = 0; i < (sl->getLength() & sa->getLength()); i++)
        {
            if (((*sa)[i] & (*sl)[i]) != ar[i])
                flag = false;
        }
        delete sa;
        delete sl;
        delete[] ar;
        return flag;
    }

    bool test2() // testing concates, substrs and get()
    {
        bool flag = true;
        char* ar = new char[4]{'a', 'b', 'c', 'd'};
        SequenceArray<char>* sa = new SequenceArray<char>();
        SequenceList<char>* sl = new SequenceList<char>();
        sa->insertAt('t', 6); // must throw "Empty" error
        sl->insertAt('t', 6); // must throw the same error
        sa->append('c');
        sl->append('c');
        sa->prepend('b');
        sa->prepend('a');
        sl->prepend('b');
        sl->prepend('a');
        sa->append('d');
        sl->append('d');
        SequenceArray<char> *concSa = sa->getSubsequence(0, 1)->concat(sa->getSubsequence(2, 3));
        SequenceList<char> *fp = sl->getSubsequence(0, 1);
        SequenceList<char> *sp = sl->getSubsequence(2, 3);
        SequenceList<char> *concSl = fp->concat(sp);
        int size = sa->getLength() & sl->getLength() & concSa->getLength() & concSl->getLength();
        flag = size == 4;
        for (int i = 0; i < size; i++)
        {
            if (sa->get(i) & sl->get(i) & concSa->get(i) & concSl->get(i) != ar[i])
                flag = false;
        }
        delete sa;
        delete sl;
        delete concSa;
        delete concSl;
        delete[] ar;
        return flag;
    }

    bool test3() // testing constructors and operators
    {
        bool flag = true;
        int n = 3;
        int* testAr = new int[3]{0, -1, 2};
        
        SequenceList<int>* sl1 = new SequenceList<int>();
        SequenceList<int>* sl2 = new SequenceList<int>(testAr, n);
        SequenceList<int>* sl3 = new SequenceList<int>(*(new LinkedList<int>(testAr, n)));
        SequenceArray<int>* sa1 = new SequenceArray<int>();
        SequenceArray<int>* sa2 = new SequenceArray<int>(testAr, n);
        SequenceArray<int>* sa3 = new SequenceArray<int>(*(new DynamicArray<int>(testAr, n)));
        flag = (sl1->getLength() == 0) && (sl2->getLength() == 3) && (sl3->getLength() == 3);
        flag = flag && (sa1->getLength() == 0) && (sa2->getLength() == 3) && (sa3->getLength() == 3);
        sl1->append(2);
        sl1->prepend(0);
        sl1->insertAt(-1, 1);
        sa1->append(2);
        sa1->prepend(0);
        sa1->insertAt(-1, 1);
        for (int i = 0; i < n; i++)
        {
//            cout << (*sl1)[i] << " " << (*sl2)[i] << " " << (*sl3)[i] << endl;
            if ((*sl1)[i] & (*sl2)[i] & (*sl3)[i] & (*sa1)[i] & (*sa2)[i] & (*sa3)[i] != testAr[i])
                flag = false;
        }
        
        delete sl1;
        delete sl2;
        delete sl3;
        delete sa1;
        delete sa2;
        delete sa3;
        delete[] testAr;
        return flag;
    }

    bool test4() // testing DynamicArray's set and resize
    {
        bool flag = true;
        DynamicArray<char>* sl = new DynamicArray<char>(new char[5]{'!', '@', 'r', 't', 'q'}, 5);
        sl->resize(3);
        flag = flag && (sl->getSize() == 3);
        sl->set(1, 'e');
        sl->set(0, 'p');
        sl->set(2, 'i');
        flag = flag && (sl->get(0) == 'p') && (sl->get(1) == 'e') && (sl->get(2) == 'i');
        sl->resize(5);
        flag = flag && (sl->getSize() == 5);
        flag = flag && (sl->get(0) == 'p') && (sl->get(1) == 'e') && (sl->get(2) == 'i');
        delete sl;
        return flag;
    }

    bool test5() // examples with exceptions
    {
        bool flag = true;
        
        SequenceList<float>* sl = new SequenceList<float>();
        sl->getLast(); // throws "Empty" exception
        sl->getFirst(); // throws "Empty" exception
        sl->append(6.0);
        sl->append(7.0);
        sl->get(7.0); // throws "Invalid" exception
        sl->get(-1.0); // throws "Invalid" exception
        flag = flag && (sl->getFirst() == 6.0) && (sl->getLast() == 7.0);
        
        SequenceArray<float>* sa = new SequenceArray<float>();
        sa->getLast(); // throws "Empty" exception
        sa->getFirst(); // throws "Empty" exception
        sa->append(6.0);
        sa->append(7.0);
        sa->get(7.0); // throws "Invalid" exception
        sa->get(-1.0); // throws "Invalid" exception
        flag = flag && (sa->getFirst() == 6.0) && (sa->getLast() == 7.0);
        
        delete sl;
        delete sa;
        return flag;
    }

    void log(int num)
    {
        std::cout << "Test №" << num << " passed\n";
    }

    void startTesting()
    {
        std::cout << "---TESTS WITHOUT STD---\n";
        assert(test1());
        log(1);
        assert(test2());
        log(2);
        assert(test3());
        log(3);
        assert(test4());
        log(4);
        assert(test5());
        log(5);
        std::cout << "---END OF TESTS WITHOUT STD---\n";
    }
}

//Tests with std
#include <deque>
#include <random>
#include <vector>
namespace testsSTD
{
    using namespace std;

    bool test1() // testing addictive functional and operator
    {
        int el = rand();
//        cout << "el: " << el << endl;
        bool flag = true;
        SequenceArray<int>* sa = new SequenceArray<int>(new int[3]{1, 2, 3}, 3);
        SequenceList<int>* sl = new SequenceList<int>(new int[3]{1, 2, 3}, 3);
        deque<int>* ans = new deque<int>({1, 2, 3});
        sa->append(el);
        sl->append(el);
        ans->push_back(el);
        el = rand();
//        cout << "el: " << el << endl;
        sa->prepend(el);
        sl->prepend(el);
        ans->push_front(el);
        el = rand();
//        cout << "el: " << el << endl;
        sa->append(el);
        sl->append(el);
        ans->push_back(el);
        el = rand();
//        cout << "el: " << el << endl;
        sa->prepend(el);
        sl->prepend(el);
        ans->push_front(el);
        flag = (sl->getLength() & sa->getLength()) == ans->size();
        for (int i = 0; i < (sl->getLength() & sa->getLength() & ans->size()); i++)
        {
            if ((((*sa)[i] & (*sl)[i])) != ans->front())
                flag = false;
            ans->pop_front();
        }
        delete sa;
        delete sl;
        delete ans;
        return flag;
    }

    bool test2() // testing concates, substrs and get()
    {
        bool flag = true;
        char tmpItem;
//        char* ar = new char[4]{'a', 'b', 'c', 'd'};
        SequenceArray<char>* sa = new SequenceArray<char>();
        SequenceList<char>* sl = new SequenceList<char>();
        deque<char> ar = deque<char>();
        tmpItem = (char)(rand()%150);
        sa->append(tmpItem);
        sl->append(tmpItem);
        ar.push_back(tmpItem);
        tmpItem = (char)(rand()%150);
        sa->prepend(tmpItem);
        ar.push_front(tmpItem);
        sl->prepend(tmpItem);
        tmpItem = (char)(rand()%150);
        sa->prepend(tmpItem);
        ar.push_front(tmpItem);
        sl->prepend(tmpItem);
        tmpItem = (char)(rand()%150);
        sa->append(tmpItem);
        sl->append(tmpItem);
        ar.push_back(tmpItem);
        SequenceArray<char> *concSa = sa->getSubsequence(0, 1)->concat(sa->getSubsequence(2, 3));
        SequenceList<char> *fp = sl->getSubsequence(0, 1);
        SequenceList<char> *sp = sl->getSubsequence(2, 3);
        SequenceList<char> *concSl = fp->concat(sp);
        int size = sa->getLength() & sl->getLength() & concSa->getLength() & concSl->getLength();
        flag = size == ar.size();
//        cout << "start\n";
        for (int i = 0; i < size; i++)
        {
//            cout << sa->get(i) << " " << sl->get(i) << endl;
            if ((sa->get(i) & sl->get(i) & concSa->get(i) & concSl->get(i)) != ar[i])
                flag = false;
        }
//        cout << "end\n";
        delete sa;
        delete sl;
        delete concSa;
        delete concSl;
        return flag;
    }

    bool test3() // testing concates, getSubs
    {
        bool flag = true;
        SequenceList<int>* sl = new SequenceList<int>();
        SequenceArray<int>* sa = new SequenceArray<int>();
        vector<int>* d = new vector<int>();
        int size = rand() % 50;
        
        for (int i = 0; i < size; i++)
        {
            int val = rand() % 3000;
            sl->append(val);
            sa->append(val);
            d->push_back(val);
        }
        
        for (int i = 0; i < 50; i++) // testing getSubs
        {
            int stIndex = rand() % size;
            int finIndex = stIndex + rand() % (size - stIndex);
            SequenceList<int>* slSub = sl->getSubsequence(stIndex, finIndex);
            SequenceArray<int>* saSub = sa->getSubsequence(stIndex, finIndex);
            
            for (int j = stIndex; j <= finIndex; j++)
                if (((*slSub)[j - stIndex] & (*saSub)[j - stIndex]) != (*d)[j])
                    flag = false;
            
            delete slSub;
            delete saSub;
        }
        
        for (int i = 0; i < 50; i++) // testing concates
        {
            int stIndex = rand() % size;
            int finIndex = stIndex + rand() % (size - stIndex);
            SequenceList<int>* slSub = sl->getSubsequence(stIndex, finIndex);
            SequenceArray<int>* saSub = sa->getSubsequence(stIndex, finIndex);
            SequenceList<int>* slConc = sl->concat(slSub);
            SequenceArray<int>* saConc = sa->concat(saSub);
            
            vector<int>* dConc = new vector<int>();
            for (int j = 0; j < d->size(); j++)
            {
                dConc->push_back((*d)[j]);
            }
            for (int j = stIndex; j <= finIndex; j++)
            {
                dConc->push_back((*d)[j]);
            }
            
            for (int j = 0; j < dConc->size(); j++)
                if (((*slConc)[j] & (*saConc)[j]) != (*dConc)[j])
                    flag = false;
            
            delete dConc;
            delete slConc;
            delete saConc;
            delete slSub;
            delete saSub;
        }
        
        delete sl;
        delete sa;
        delete d;
        return flag;
    }

    void log(int num)
    {
        std::cout << "Test №" << num << " passed\n";
    }

    void startTesting()
    {
        cout << "---TESTS WITH STD---\n";
        assert(test1());
        log(1);
        assert(test2());
        log(2);
        assert(test3());
        log(3);
        cout << "---END OF TESTS WITH STD---\n";
    }
}

using namespace std;

template<class T>
void printSequenceArray(SequenceArray<T>& sa)
{
    cout << "SequenceArray now: ";
    for (int i = 0; i < sa.getLength(); i++)
    {
        cout << sa.get(i) << " ";
    }
    cout << endl;
}

template<class T>
void printSequenceList(SequenceList<T>& sl)
{
    cout << "SequenceList now: ";
    for (int i = 0; i < sl.getLength(); i++)
    {
        cout << sl.get(i) << " ";
    }
    cout << endl;
}

template<class T>
void testingArray()
{
    int constr;
    cout << "How do you want initialize your SequenceArray?\n";
    cout << "1 - create empty\n2 - create from array\n";
    cin >> constr;
    SequenceArray<T>* sa;
    switch (constr) {
        case 1:
            sa = new SequenceArray<T>();
            break;
            
        case 2:
            {
                int n;
                cout << "Enter size: ";
                cin >> n;
                T* temp = new T[n];
                cout << "Enter n elements: ";
                for (int i = 0; i < n; i++)
                    cin >> temp[i];
                sa = new SequenceArray<T>(temp, n);
                delete[] temp;
            }
            break;
            
        default:
            cout << "Handling error.\n";
            break;
    }
    int com = 0;
    while (com!=14)
    {
        cout << "1 - getFirst()\n2 - getLast()\n3 - get(ind)\n";
        cout << "4 - getSub(startInd, endInd)\n5 - getLength()\n6 - append(item)\n7 - prepend(item)\n";
        cout << "8 - insertAt(item, index)\n9 - concat(array)\n10 - printAll()\n11 - deleteIndex(index)\n";
        cout << "12 - resize(newSize)\n13 - set(index, value)\n14 - exit\n";
        cout << "Choose action: ";
        cin >> com;
        switch (com) {
            case 1:
                cout << "First element: " << sa->getFirst() << endl;
                break;
                
            case 2:
                cout << "Last element: " << sa->getLast() << endl;
                break;
            
            case 3:
                {
                    int ind;
                    cout << "Enter index: ";
                    cin >> ind;
                    cout << "Element: " << sa->get(ind) << endl;
                }
                break;
            
            case 4:
                {
                    int start, fin;
                    cout << "Enter start, fin: ";
                    cin >> start >> fin;
                    SequenceArray<T>* tmpseq = sa->getSubsequence(start, fin);
                    cout << "SubSequence: ";
                    for (int i = 0; i < tmpseq->getLength(); i++)
                    {
                        cout << tmpseq->get(i) << " ";
                    }
                    cout << endl;
                    delete tmpseq;
                }
                break;
                
            case 5:
                cout << "Length: " << sa->getLength() << endl;
                break;
                
            case 6:
                {
                    T item;
                    cout << "Enter item: ";
                    cin >> item;
                    sa->append(item);
                    printSequenceArray(*sa);
                }
                break;
                
            case 7:
                {
                    T item;
                    cout << "Enter item: ";
                    cin >> item;
                    sa->prepend(item);
                    printSequenceArray(*sa);
                }
                break;
            
            case 8:
                {
                    int ind;
                    T item;
                    cout << "Enter item, index: ";
                    cin >> item >> ind;
                    sa->insertAt(item, ind);
                    printSequenceArray(*sa);
                }
                break;
                
            case 9:
                {
                    int n;
                    cout << "Enter n (count) elements: ";
                    cin >> n;
                    T* tmp1 = new T[n];
                    cout << "Enter n elements: ";
                    for (int i = 0; i < n; i++)
                    {
                        cin >> tmp1[i];
                    }
                    SequenceArray<T>* helpSeq = new SequenceArray<T>(tmp1, n);
                    delete[] tmp1;
                    SequenceArray<T>* tmpseq = sa->concat(helpSeq);
                    cout << "New Sequence: ";
                    for (int i = 0; i < tmpseq->getLength(); i++)
                    {
                        cout << tmpseq->get(i) << " ";
                    }
                    cout << endl;
                    delete tmpseq;
                    
                }
                break;
                
            case 10:
                {
                    cout << "Sequence array now: ";
                    for (int i = 0; i < sa->getLength(); i++)
                    {
                        cout << sa->get(i) << " ";
                    }
                    cout << endl;
                }
                break;
                
            case 11:
                {
                    int ind;
                    cout << "Enter index: ";
                    cin >> ind;
                    sa->deleteAt(ind);
                    printSequenceArray(*sa);
                }
                break;
                
            case 12:
                {
                    T newSize;
                    cout << "Enter new size: ";
                    cin >> newSize;
                    sa->resize(newSize);
                }
                break;
                
            case 13:
                {
                    int ind;
                    T item;
                    cout << "Enter index, item: ";
                    cin >> ind >> item;
                    sa->set(ind, item);
                    printSequenceArray(*sa);
                }
                break;
        }
    }
    delete sa;
};

template <class T>
void testingList()
{
    int constr;
    cout << "How do you want initialize your SequenceList?\n";
    cout << "1 - create empty\n2 - create from array\n";
    cin >> constr;
    SequenceList<T>* sa;
    switch (constr) {
        case 1:
            sa = new SequenceList<T>();
            break;
            
        case 2:
            {
                int n;
                cout << "Enter size: ";
                cin >> n;
                T* temp = new T[n];
                cout << "Enter n elements: ";
                for (int i = 0; i < n; i++)
                    cin >> temp[i];
                sa = new SequenceList<T>(temp, n);
                delete[] temp;
            }
            break;
            
        default:
            cout << "Handling error.\n";
            break;
    }
    int com = 0;
    while (com!=11)
    {
        cout << "1 - getFirst()\n2 - getLast()\n3 - get(ind)\n";
        cout << "4 - getSub(startInd, endInd)\n5 - getLength()\n6 - append(item)\n7 - prepend(item)\n";
        cout << "8 - insertAt(item, index)\n9 - concat(array)\n10 - printAll()\n11 - exit\n12 - deleteIndex(index)\n";
        cout << "13 - set(index, value)\n";
        cout << "Choose action: ";
        cin >> com;
        switch (com) {
            case 1:
                cout << "First element: " << sa->getFirst() << endl;
                break;
                
            case 2:
                cout << "Last element: " << sa->getLast() << endl;
                break;
            
            case 3:
                {
                    int ind;
                    cout << "Enter index: ";
                    cin >> ind;
                    cout << "Element: " << sa->get(ind) << endl;
                }
                break;
            
            case 4:
                {
                    int start, fin;
                    cout << "Enter start, fin: ";
                    cin >> start >> fin;
                    SequenceList<T>* tmpseq = sa->getSubsequence(start, fin);
                    cout << "SubSequence: ";
                    for (int i = 0; i < tmpseq->getLength(); i++)
                    {
                        cout << tmpseq->get(i) << " ";
                    }
                    cout << endl;
                    delete tmpseq;
                }
                break;
                
            case 5:
                cout << "Length: " << sa->getLength() << endl;
                break;
                
            case 6:
                {
                    T item;
                    cout << "Enter item: ";
                    cin >> item;
                    sa->append(item);
                    printSequenceList(*sa);
                }
                break;
                
            case 7:
                {
                    T item;
                    cout << "Enter item: ";
                    cin >> item;
                    sa->prepend(item);
                    printSequenceList(*sa);
                }
                break;
            
            case 8:
                {
                    int ind;
                    T item;
                    cout << "Enter item, index: ";
                    cin >> item >> ind;
                    sa->insertAt(item, ind);
                    printSequenceList(*sa);
                }
                break;
                
            case 9:
                {
                    int n;
                    cout << "Enter n (count) elements: ";
                    cin >> n;
                    T* tmp1 = new T[n];
                    cout << "Enter n elements: ";
                    for (int i = 0; i < n; i++)
                    {
                        cin >> tmp1[i];
                    }
                    SequenceList<T>* helpSeq = new SequenceList<T>(tmp1, n);
                    delete[] tmp1;
                    SequenceList<T>* tmpseq = sa->concat(helpSeq);
                    cout << "New Sequence: ";
                    for (int i = 0; i < tmpseq->getLength(); i++)
                    {
                        cout << tmpseq->get(i) << " ";
                    }
                    cout << endl;
                    delete tmpseq;
                    
                }
                break;
                
            case 10:
                {
                    cout << "Sequence array now: ";
                    for (int i = 0; i < sa->getLength(); i++)
                    {
                        cout << sa->get(i) << " ";
                    }
                    cout << endl;
                }
                break;
            case 12:
                {
                    int ind;
                    cout << "Enter index: ";
                    cin >> ind;
                    sa->deleteAt(ind);
                    printSequenceList(*sa);
                }
                break;
            case 13:
                {
                    int ind;
                    T item;
                    cout << "Enter item, index: ";
                    cin >> item >> ind;
                    sa->set(ind, item);
                    printSequenceList(*sa);
                }
                break;
        }
    }
    delete sa;
};

int main(int argc, const char * argv[]) {
    cout << "Choose type of test:\n1 - Manual\n2 - Automatic\n";
    int buf;
    cin >> buf;
    switch (buf) {
        case 1:
            cout << "Choose type of sequence:\n1 - SequenceArray\n2 - SequenceList\n";
            cin >> buf;
            cout << "Choose type of your data:\n";
            cout << "1 - int\n2 - float\n3 - char\n";
            int typeAr;
            cin >> typeAr;
            switch (buf) {
                case 1: // SequenceArray
                    switch (typeAr) {
                        case 1: // int
                            testingArray<int>();
                            break;
                          
                        case 2: // float
                            testingArray<float>();
                            break;
                            
                        case 3: // char
                            testingArray<char>();
                            break;
                        default:
                            cout << "Handling error.\n";
                            break;
                    }
                    break;
                    
                case 2: // SequenceList
                    switch (typeAr) {
                        case 1: // int
                            testingList<int>();
                            break;
                          
                        case 2: // float
                            testingList<float>();
                            break;
                            
                        case 3: // char
                            testingList<char>();
                            break;
                        default:
                            cout << "Handling error.\n";
                            break;
                    }
                    break;
                    
                default:
                    cout << "Handling error.\n";
                    break;
            }
            break;
        
        case 2:
            tests::startTesting();
            testsSTD::startTesting();
            break;
            
        default:
            cout << "Handling error.\n";
            break;
    }
}
