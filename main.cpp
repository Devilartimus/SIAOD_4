/*Напишите программу, которая формирует бинарное дерево поиска,
 * выводит построенное дерево на экран и находит элемент, который является следующим по значению от числа, которое вводится с клавиатуры.
 * Данные для построения дерева могут вводится с клавиатуры, из файла или генерироваться с помощью генератора случайных чисел.
 * Выбор способа ввода данных выполняется во время работы программы.
 * Для реализации АТД "Дерево" используйте динамическое распределение памяти. Перед завершением работы программы освободить занимаемую динамическую память.
 * Для этого используйте поэлементное удаление элементов динамической структуры данных. */

#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

int GetInt(int left = -2147483648, int right = 2147483647);
int val = 100;

class NodeTree
{
private:
    int* key;
    NodeTree* left;
    NodeTree* right;

public:
    //done
    NodeTree(int* number = nullptr) : key{ number }, left{ nullptr }, right{ nullptr } {}   //конструктор

    //done
    ~NodeTree() //деструктор
    {
        if (key)
        {
            delete left;
            delete right;
            delete key;
            key = nullptr;
        }
    }

    //done
    const NodeTree& AddNode(int number) //добавление элемента
    {
        if(!key)
        {
            key = new int;
            *key = number;
        }
        else if(number < *key)
        {
            if(!left)
                left = new NodeTree;
            left->AddNode(number);
        }
        else
        {
            if(!right)
                right = new NodeTree;
            right->AddNode(number);
        }
        return *this;
    }

    //методы заполнения дерева
    //done
    const NodeTree& InputDataTree() //ввод с клавиатуры
    {
        int number, size;
        cout << "\nEnter number of tree elements: ";
        size = GetInt(1);
        do
        {
            number = GetInt();
            AddNode(number);
            size--;
        } while (size > 0);
        return *this;
    }

    //done
    const NodeTree& InputFileTree()  //заполнение из файла
    {
        ifstream FileIn("E:/3 term/SIAOD/lab5/bintree.txt");
        if(!FileIn.is_open())
            throw "\nEntering File <bintree> can't be oppened\n";
        else
        {
            int number;
            while(!FileIn.eof())
            {
                FileIn >> number;
                cout << "Number: " << number << endl;
                AddNode(number);
            }
        }
        FileIn.close();
        return *this;
    }

    //done
    const NodeTree& RandomTree(int size = 25)   //заполнение рандомом
    {
        srand(time(0));
        rand();
        for(; size > 0; size--)
            AddNode(rand() % 100);
        return *this;
    }

    //done
        bool Delete(int number) //удаление элемента
        {
            if(number < *key)
            {
                if(left->Delete(number))
                    left = nullptr;
            }
            else if(number > *key)
            {
                    if(right->Delete(number))
                        right = nullptr;
            }
            else
            {
                if(!left && !right)
                {
                    delete this;
                    return true;
                }
                else if(!left)
                {
                    delete key;
                    *this = *right;
                }
                else if(!right)
                {
                    delete key;
                    *this = *left;
                }
                else
                    right = right->Del(*this);
            }
            return false;

        }

        //done
        NodeTree* Del(NodeTree& P)  //вспомогательное удаление
        {
            if(!left)
            {
                delete P.key;
                P.key = key;
                key = nullptr;
                return right;
            }
            else
            {
                left = left->Del(P);
                return this;
            }
        }

    //done
    const NodeTree& PrintTree(int height = 1)   //вывод дерева
    {
        if(right)
            right->PrintTree(height + 1);
        for(int i = 0; i < height; i++)
            cout << ' ';
        cout << *key << endl;
        if(left)
            left->PrintTree(height + 1);
        return *this;
    }

    int FindGreater(int n = 0) const  //нахождение следующего элемента
    {
        if(*key > n && *key < val)
            val = *key;
        if(right)
            val = right->FindGreater(n);
        if(left)
            val = left->FindGreater(n);
        return val;
    }

    bool IsEmpty()
    {
        if (*key == NULL)
        {
            cout << "Your tree is empty" << endl;
            return true;
        }
        else
        {
            cout << "Your tree isn't empty" << endl;
            return false;
        }
    }
};

int main()
{
    cout << "\nThe program generates a binary search tree:"
         <<"\nChoose the way to build the tree (1,2 or 3):"
         <<"\n1) keyboard input;"
         <<"\n2) reading from a file;"
         <<"\n3) generation of a given number of elements by random values\n";
    int choose = GetInt(1, 3);

    NodeTree BinaryTree;
    switch (choose)
    {
    case 1: //ручной ввод
        BinaryTree.InputDataTree();
        break;
    case 2: //ввод из файла
        BinaryTree.InputFileTree();
        break;
    case 3: //заполнение рандомом
        BinaryTree.RandomTree();
        break;
    default:
        cout << "\nSomething wrong!\n";
    }

    cout << endl;
    BinaryTree.PrintTree();

    cout << endl << endl << "Enter any number: ";
    int val;
    cin >> val;
    cout << "\nNext number after " << val << ": ";
    if (val!= 100)
        cout << BinaryTree.FindGreater(val) << endl;
    else
        cout << "There are no elements in the tree larger than " << val << endl;

    return 0;
}
//done
int GetInt(int left, int right)
{
    while(true) //цикл продолжается пока не введено неверное значение
    {
        int number;
        cin >> number;

        // Проверка на предыдущее извлечение
        if(cin.fail())  //то возвращаем cin в 'обычный' режим работы
        {
            cin.clear();    // то возвращаем cin в 'обычный' режим работы
            cin.ignore(32767, '\n'); //и удаляем значения предыдущего ввода из входного буфера
        }
        else
        {
            cin.ignore(32767, '\n'); // удаляем лишние значения
            if (number >= left && number <= right)
                return number;
        }
        cout << "Error! Wrong input" << endl;
    }
}
