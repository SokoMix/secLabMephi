#ifndef sequence_h
#define sequence_h
#include <iostream>
#include "customException.h"
#define SIZECON 5

template <class T>
class Item
{
    T data;
    Item<T>* next;
    Item<T>* prev;
public:
    Item(T data) : data(data)
    {
        next = NULL;
        prev = NULL;
    };
    
    void setNext(Item<T>* n)
    {
        next = n;
    };
    
    void setPrev(Item<T>* n)
    {
        prev = n;
    }
    
    Item<T>* getPrev()
    {
        return prev;
    }
    
    Item<T>* getNext()
    {
        return next;
    }
    
    T getData()
    {
        return data;
    }
    
    void setData(T newData)
    {
        data = newData;
    }
};

template <class T>
class Sequence
{
public:
    virtual void append(T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insertAt(T item, int index) = 0;
    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T get(int index) = 0;
    virtual int getLength() = 0;
    virtual void set(int index, T value) = 0;
};

template <class T>
class DynamicArray
{
    int sizeAr = 0;
    int capacity = 0;
    T* data;
public:
    T operator[](const int i)
    {
        try
        {
            if (sizeAr == 0)
                throw IndexOutOfRange(Empty);
            if (i < 0 || i >= sizeAr)
                throw IndexOutOfRange(Invalid);
            return this->data[i];
        } catch (IndexOutOfRange& e) {
            e.printError();
            return NULL;
        }
    };

    DynamicArray(T* items, int count) : sizeAr(count)
    {
        capacity = (count % SIZECON == 0) ? SIZECON * (count / SIZECON) : SIZECON * (count / SIZECON + 1);
        this->data = new T[capacity];
        for (int i = 0; i < count; i++)
        {
            this->data[i] = items[i];
        }
    };
    
    DynamicArray(int size) : capacity(size)
    {
        this->data = new T[size];
    };
    
    DynamicArray()
    {
        this->data = NULL;
        this->sizeAr = 0;
    };
    
    DynamicArray(DynamicArray<T>& dynamicArray) : sizeAr(dynamicArray.sizeAr)
    {
        capacity = (sizeAr % SIZECON == 0) ? SIZECON * (sizeAr / SIZECON) : SIZECON * (sizeAr / SIZECON + 1);
        this->data = new T[capacity];
        for (int i = 0; i < this->sizeAr; i++)
        {
            this->data[i] = dynamicArray.get(i);
        }
    };
    
    ~DynamicArray()
    {
        delete[] data;
    };
    
    void append(T item)
    {
        if (capacity <= sizeAr + 1)
        {
            capacity += SIZECON;
            T* temp = new T[capacity];
            temp[this->sizeAr] = item;
            for (int i = 0; i < this->sizeAr; i++)
            {
                temp[i] = this->data[i];
            }
            delete this->data;
            this->data = temp;
            (this->sizeAr)++;
        }
        else
        {
            data[this->sizeAr] = item;
            (this->sizeAr)++;
        }
    };
    
    void prepend(T item)
    {
        if (capacity == sizeAr + 1)
        {
            capacity += SIZECON;
            T* temp = new T[capacity];
            temp[0] = item;
            for (int i = 0; i < this->sizeAr; i++)
            {
                temp[i + 1] = this->data[i];
            }
            delete this->data;
            this->data = temp;
            (this->sizeAr)++;
        }
        else
        {
            for (int i = sizeAr; i > 0; i--)
            {
                data[i] = data[i - 1];
            }
            data[0] = item;
            sizeAr++;
        }
    };
    
    void set(int index, T value)
    {
        try
        {
            if (sizeAr == 0)
                throw IndexOutOfRange(Empty);
            if (index < 0 || index > sizeAr)
                throw IndexOutOfRange(Invalid);
            data[index] = value;
        } catch (IndexOutOfRange& e)
        {
            e.printError();
        }
    }
    
    void resize(int newSize)
    {
        capacity = (newSize % SIZECON == 0) ? SIZECON * (newSize / SIZECON) : SIZECON * (newSize / SIZECON + 1);
        T* newData = new T[capacity];
        for (int i = 0; i < (newSize > sizeAr ? sizeAr : newSize); i++)
        {
            newData[i] = data[i];
        }
        delete data;
        data = newData;
        sizeAr = newSize;
    }
    
    void insertAt(T item, int index)
    {
        try
        {
            if (sizeAr == 0)
                throw IndexOutOfRange(Empty);
            if (index < 0 || index >= sizeAr)
                throw IndexOutOfRange(Invalid);
            if (capacity == sizeAr + 1)
            {
                capacity += SIZECON;
                T* temp = new T[capacity];
                temp[index] = item;
                for (int i = 0; i < index; i++)
                {
                    temp[i] = this->data[i];
                }
                for (int i = index + 1; i < this->sizeAr + 1; i++)
                {
                    temp[i] = this->data[i - 1];
                }
                delete this->data;
                this->data = temp;
                (this->sizeAr)++;
            }
            else
            {
                for (int i = sizeAr; i > index; i--)
                {
                    data[i] = data[i - 1];
                }
                data[index] = item;
                sizeAr++;
            }
        } catch (IndexOutOfRange& e) {
            e.printError();
        }
    };
    
    DynamicArray<T>* concat(DynamicArray<T>& lst)
    {
        T* newData = new T[this->sizeAr + lst.getSize() + 1];
        for (int i = 0; i < this->sizeAr; i++)
        {
            newData[i] = this->data[i];
        }
        for (int i = 0; i < lst.getSize(); i++)
        {
            newData[i + this->sizeAr] = lst.get(i);
        }
        DynamicArray<T>* nw = new DynamicArray(newData, this->sizeAr + lst.getSize() + 1);
        delete[] newData;
        return nw;
    };

    int getSize()
    {
        return this->sizeAr;
    };
    
    T getFirst()
    {
        try
        {
            if (sizeAr == 0)
                throw IndexOutOfRange(Empty);
            else
                return data[0];
        } catch (IndexOutOfRange& e) {
            e.printError();
            return NULL;
        }
    };
    
    T getLast()
    {
        try
        {
            if (sizeAr == 0)
                throw IndexOutOfRange(Empty);
            else
                return data[sizeAr - 1];
        } catch (IndexOutOfRange& e) {
            e.printError();
            return NULL;
        }
    };

    T get(int index)
    {
        try
        {
            if (sizeAr == 0)
                throw IndexOutOfRange(Empty);
            if (index >= sizeAr || index < 0)
                throw IndexOutOfRange(Invalid);
            return this->data[index];
        } catch (IndexOutOfRange& e) {
            e.printError();
            return NULL;
        }
    };
    
    void deleteIndex(int index)
    {
        try
        {
            if (sizeAr == 0)
                throw IndexOutOfRange(Empty);
            if (index < 0 || index >= sizeAr)
                throw IndexOutOfRange(Invalid);
            for (int i = sizeAr; i > index; i--)
            {
                data[i] = data[i - 1];
            }
            sizeAr--;
            if (sizeAr + SIZECON == capacity)
            {
                capacity -= SIZECON;
                T* temp = new T[capacity];
                for (int i = 0; i < sizeAr; i++)
                {
                    temp[i] = this->data[i];
                }
                delete this->data;
                this->data = temp;
            }
        } catch (IndexOutOfRange& e) {
            e.printError();
        }
    }
    
    DynamicArray<T>* getSubAr(int start, int fin)
    {
        try
        {
            if (start < 0 || start >= sizeAr || fin >= sizeAr || fin < 0 || start > fin)
                throw IndexOutOfRange(Invalid);
            T* ar = new T[fin - start + 1];
            for (int i = start; i <= fin; i++)
            {
                ar[i - start] = data[i];
            }
            DynamicArray<T>* retval = new DynamicArray<T>(ar, fin - start + 1);
            delete[] ar;
            return retval;
        } catch (IndexOutOfRange& e) {
            e.printError();
            return NULL;
        }
    }
};

template <class T>
class LinkedList
{
    Item<T> *first;
    Item<T> *last;
    int sizeList;
public:
    T operator[](const int index)
    {
        try
        {
            if (sizeList == 0)
                throw IndexOutOfRange(Empty);
            else if (index < 0 || index >= sizeList)
                throw IndexOutOfRange(Invalid);
            else if (index > sizeList/2)
            {
                Item<T>* item = last;
                for (int i = sizeList - 1; i > index; i--)
                {
                    item = item->getPrev();
                }
                return item->getData();
            }
            else
            {
                Item<T>* item = first;
                for (int i = 0; i < index; i++)
                {
                    item = item->getNext();
                }
                return item->getData();
            }
        } catch (IndexOutOfRange& e) {
            e.printError();
            return NULL;
        }
    };
    
    int getLength()
    {
        return sizeList;
    };
    
    LinkedList(T* items, int count) : sizeList(count)
    {
        first = new Item<T>(items[0]);
        Item<T> *lst = first;
        for (int i = 1; i < count; i++)
        {
            Item<T> *tmp = new Item<T>(items[i]);
            lst->setNext(tmp);
            tmp->setPrev(lst);
            lst = tmp;
        }
        last = lst;
    };
    
    LinkedList()
    {
        first = NULL;
        last = NULL;
        sizeList = 0;
    };
    
    LinkedList(LinkedList <T>& list)
    {
        sizeList = 0;
        for (int i = 0; i < list.getLength(); i++)
        {
            this->append(list.get(i));
        }
    };
    
    ~LinkedList()
    {
        Item<T>* fst = first;
        if (fst != NULL)
        {
            while (fst != NULL)
            {
                Item<T>* n = fst->getNext();
                delete fst;
                fst = n;
            }
            delete fst;
        }
    };
    
    void append(T item)
    {
        sizeList++;
        if (last != NULL)
        {
            Item<T>* lst = last;
            Item<T>* tmp = new Item<T>(item);
            lst->setNext(tmp);
            tmp->setPrev(lst);
            last = tmp;
        }
        else
        {
            Item<T>* itm = new Item<T>(item);
            first = itm;
            last = itm;
        }
    };
    
    void deleteIndex(int index)
    {
        try
        {
            if (sizeList == 0)
                throw IndexOutOfRange(Empty);
            else if (index < 0 || index >= sizeList)
                throw IndexOutOfRange(Invalid);
            else if (index >= sizeList/2)
            {
                Item<T>* item = last;
                for (int i = sizeList - 1; i > index; i--)
                {
                    item = item->getPrev();
                }
                if (index < sizeList - 1 && index != 0)
                {
                    Item<T>* pr = item->getPrev();
                    Item<T>* nxt = item->getNext();
                    pr->setNext(nxt);
                    nxt->setPrev(pr);
                    delete item;
                }
                else if (index == 0 && sizeList == 1)
                {
                    delete first;
                    first = NULL;
                    last = NULL;
                }
                else if (index == 0)
                {
                    Item<T>* nxt = item->getNext();
                    first = nxt;
                    nxt->setPrev(NULL);
                    delete item;
                }
                else
                {
                    Item<T>* pr = item->getPrev();
                    last = pr;
                    pr->setNext(NULL);
                    delete item;
                }
                sizeList--;
            }
            else
            {
                Item<T>* item = first;
                for (int i = 0; i < index; i++)
                {
                    item = item->getNext();
                }
                if (index > 0 && index != sizeList - 1)
                {
                    Item<T>* pr = item->getPrev();
                    Item<T>* nxt = item->getNext();
                    pr->setNext(nxt);
                    nxt->setPrev(pr);
                    delete item;
                }
                else if (index == 0 && sizeList == 1)
                {
                    delete first;
                    first = NULL;
                    last = NULL;
                }
                else if (index == sizeList - 1)
                {
                    Item<T>* pr = item->getPrev();
                    last = pr;
                    pr->setNext(NULL);
                    delete item;
                }
                else
                {
                    Item<T>* nxt = item->getNext();
                    first = nxt;
                    nxt->setPrev(NULL);
                    delete item;
                }
                sizeList--;
            }
        } catch (IndexOutOfRange& e) {
            e.printError();
        }
    };
    
    void prepend(T item)
    {
        sizeList++;
        Item<T>* mem = first;
        first = new Item<T>(item);
        Item<T>* inst = mem;
        first->setNext(inst);
        inst->setPrev(first);
        if (last == NULL)
        {
            last = inst;
        }
    };
    
    LinkedList<T>* concat(LinkedList<T>& list)
    {
        LinkedList<T> *nw = new LinkedList(*this);
        for (int i = 0; i < list.getLength(); i++)
        {
            nw->append(list.get(i));
        }
        return nw;
    };
    
    T getFirst()
    {
        try
        {
            if (sizeList == 0)
                throw IndexOutOfRange(Empty);
            return first->getData();
        } catch (IndexOutOfRange& e)
        {
            e.printError();
            return NULL;
        }
    };
    
    T getLast()
    {
        try
        {
            if (sizeList == 0)
                throw IndexOutOfRange(Empty);
            return last->getData();
        } catch (IndexOutOfRange& e)
        {
            e.printError();
            return NULL;
        }
    };
    
    T get(int index)
    {
        try
        {
            if (sizeList == 0)
                throw IndexOutOfRange(Empty);
            else if (index < 0 || index >= sizeList)
                throw IndexOutOfRange(Invalid);
            else if (index > sizeList/2)
            {
                Item<T>* item = last;
                for (int i = sizeList - 1; i > index; i--)
                {
                    item = item->getPrev();
                }
                return item->getData();
            }
            else
            {
                Item<T>* item = first;
                for (int i = 0; i < index; i++)
                {
                    item = item->getNext();
                }
                return item->getData();
            }
        } catch (IndexOutOfRange& e) {
            e.printError();
            return NULL;
        }
    };
    
    void set(int index, T value)
    {
        try
        {
            if (sizeList == 0)
                throw IndexOutOfRange(Empty);
            else if (index < 0 || index >= sizeList)
                throw IndexOutOfRange(Invalid);
            else if (index > sizeList/2)
            {
                Item<T>* item = last;
                for (int i = sizeList - 1; i > index; i--)
                {
                    item = item->getPrev();
                }
                item->setData(value);
            }
            else
            {
                Item<T>* item = first;
                for (int i = 0; i < index; i++)
                {
                    item = item->getNext();
                }
                item->setData(value);
            }
        } catch (IndexOutOfRange& e) {
            e.printError();
        }
    };
    
    void insertAt(T item, int index)
    {
        try
        {
            if (sizeList == 0)
                throw IndexOutOfRange(Empty);
            if (index < 0 || index >= sizeList)
                throw IndexOutOfRange(Invalid);
            if (index == 0)
            {
                prepend(item);
            }
            else if (index > sizeList/2)
            {
                Item<T>* itm = last;
                for (int i = sizeList - 1; i >= index; i--)
                {
                    itm = itm->getPrev();
                }
                Item<T>* nw = new Item<T>(item);
                nw->setPrev(itm->getPrev());
                nw->setNext(itm);
                itm->setPrev(nw);
            }
            else
            {
                Item<T>* itm = first;
                for (int i = 0; i < index; i++)
                {
                    itm = itm->getNext();
                }
                Item<T>* nw = new Item<T>(item);
                Item<T>* preit = itm->getPrev();
                preit->setNext(nw);
                itm->setPrev(nw);
                nw->setPrev(preit);
                nw->setNext(itm);
            }
            sizeList++;
        } catch (IndexOutOfRange& e)
        {
            e.printError();
        }
    };
    
    LinkedList<T>* getSubList(int startIndex, int endIndex)
    {
        try
        {
            if (sizeList == 0)
                throw IndexOutOfRange(Empty);
            if (startIndex < 0 || startIndex >= sizeList || endIndex < 0 || endIndex >= sizeList)
                throw IndexOutOfRange(Invalid);
            Item<T>* item = first;
            LinkedList<T>* newList = new LinkedList();
            for (int i = 0; i < startIndex; i++)
            {
                item = item->getNext();
            }
            for (int i = startIndex; i <= endIndex; i++)
            {
                newList->append(item->getData());
                item = item->getNext();
            }
            return newList;
        } catch (IndexOutOfRange &e) {
            e.printError();
            return NULL;
        }
    };
};

template<class T>
class SequenceList : Sequence<T>
{
    LinkedList<T> *data;
public:
    T operator[](const int index)
    {
        return data->get(index);
    };
    
    SequenceList(T* items, int count)
    {
        data = new LinkedList<T>(items, count);
    };
    
    SequenceList()
    {
        data = new LinkedList<T>();
    };
    
    SequenceList(LinkedList<T> &list)
    {
        data = new LinkedList<T>(list);
    };
    
    ~SequenceList()
    {
        delete data;
    }
    
    void append(T item) override
    {
        data->append(item);
    };
    
    void prepend(T item) override
    {
        data->prepend(item);
    };
    
    void insertAt(T item, int index) override
    {
        data->insertAt(item, index);
    };
    
    void deleteAt(int index)
    {
        data->deleteIndex(index);
    }
    
    T getFirst() override
    {
        return data->getFirst();
    };
    
    T getLast() override
    {
        return data->getLast();
    };
    
    T get(int index) override
    {
        return data->get(index);
    };
    
    int getLength() override
    {
        return data->getLength();
    };
    
    LinkedList<T>* getData()
    {
        return data;
    };
    
    void set(int index, T value) override
    {
        data->set(index, value);
    }
    
    SequenceList<T>* getSubsequence(int startIndex, int endIndex)
    {
        LinkedList<T>* copy = data->getSubList(startIndex, endIndex);
        SequenceList<T>* retval = new SequenceList(*copy);
        delete copy;
        return retval;
    };
    
    SequenceList<T>* concat(SequenceList<T>* list)
    {
        return new SequenceList(*data->concat(*list->getData()));
    };
};

template <class T>
class SequenceArray : Sequence<T>
{
    DynamicArray<T> *data;
public:
    T operator[](const int index)
    {
        return data->get(index);
    };
    
    SequenceArray(T* items, int count)
    {
        data = new DynamicArray<T>(items, count);
    };
    
    SequenceArray()
    {
        data = new DynamicArray<T>();
    };
    
    SequenceArray(DynamicArray<T> &list)
    {
        data = new DynamicArray<T>(list);
    };
    
    ~SequenceArray()
    {
        delete data;
    }
    
    void append(T item) override
    {
        data->append(item);
    };
    
    void prepend(T item) override
    {
        data->prepend(item);
    };
    
    void insertAt(T item, int index) override
    {
        data->insertAt(item, index);
    };
    
    T getFirst() override
    {
        return data->getFirst();
    };
    
    T getLast() override
    {
        return data->getLast();
    };
    
    T get(int index) override
    {
        return data->get(index);
    };
    
    int getLength() override
    {
        return data->getSize();
    }
    
    void deleteAt(int index)
    {
        data->deleteIndex(index);
    }
    
    void set(int index, T value) override
    {
        data->set(index, value);
    }
    
    void resize(int newSize)
    {
        data->resize(newSize);
    }
    
    DynamicArray<T>* getData()
    {
        return data;
    };
    
    SequenceArray<T>* getSubsequence(int startIndex, int endIndex)
    {
        return new SequenceArray(*data->getSubAr(startIndex, endIndex));
    };
    
    SequenceArray<T>* concat(SequenceArray<T>* list)
    {
        return new SequenceArray(*data->concat(*list->getData()));
    };
};

#endif
