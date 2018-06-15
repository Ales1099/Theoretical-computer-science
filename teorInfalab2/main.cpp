#include <iostream>
#include <cmath>
#include <fstream>
#include <ctime>
/*Базовые обозначения для программы*/
#define DELETE "delete" //удалить
#define INSERT "insert" //вставить
#define EXIT "exit" //выйти, завершить работу со списком
#define WRITE "print" //напечатать список
#define FIND "find" //поиск эелемента в списке по его целочисленноу значению
/*Вспомогательные обозначения*/
#define NO "NO!"
/*Список*/
struct Spisok{
   int data;
   Spisok* next;
};
/*Перечисление возможных операций над спиком, создаём с целью не загромождать main*/
void instruction();
/*Список создаём по умолчанию*/
//Spisok * firstForAllFunction= NULL;
/*Генерация случайных чисел*/
int RandomizeNumber();
/*Записываем случайные числа в 16 системе счисления в файл*/
void GenerateDataSateInFail(char * filename, int * number);
/*Выводим целочисленное значение из списка на экран*/
void printValue(Spisok * top);
/*Выводим список*/
void printDataOfSpisok(Spisok * top);
/*Вставка элементов в список из файла*/
Spisok * inputFromFile(Spisok * top, int * number, char * filename);
/*Вставка како-либо желемента в список, вводимого пользователем*/
Spisok * insertUserNumberInSpisok(Spisok * top);
/*Функция вставки элементов в список*/
Spisok * insertDataInSpisok(Spisok * top, int number);
/*Безжалостное уничтожение всего, что есть в списке*/
Spisok * destroyTheSpisok(Spisok * top);
/*Функция поиска элмента по его цлочисленному значению*/
Spisok * findDataInTheSpisok(Spisok * top);
int main(){
    Spisok * firstForAllFunction= NULL;
    int numberUser;
    std::cout<<"How many much number are you going to see?    number="; std::cin>>numberUser;
    char * name = "C:\\c++\\teorInfaLab2\\randomNumber.txt";
    GenerateDataSateInFail(name, &numberUser);
    std::cout<<"File 'randomNumber.txt' is generate"<<std::endl;
    firstForAllFunction=inputFromFile(firstForAllFunction, &numberUser,name);
    printDataOfSpisok(firstForAllFunction);
    std::cout<<"What are you going to do with this list?\n";
    instruction();
    std::string operationUser;//="";
    while(true) {
        std::cout<<"Enter an action above the list - ";
        std::cin>>operationUser;
        if (operationUser == DELETE) firstForAllFunction=destroyTheSpisok(firstForAllFunction);
        else if (operationUser == INSERT) firstForAllFunction= insertUserNumberInSpisok(firstForAllFunction);
        else if (operationUser == WRITE) printDataOfSpisok(firstForAllFunction);
        else if(operationUser==FIND) { Spisok * spisok = findDataInTheSpisok(firstForAllFunction); printValue(spisok);}
        else if (operationUser == EXIT) break;
    }
    printDataOfSpisok(firstForAllFunction);
    system("pause");
    return 0;
}

void instruction(){
    std::cout<<"Delete the number - 'delete'\n";
    std::cout<<"Inset the number - 'insert'\n";
    std::cout<<"Print the list - 'print'\n";
    std::cout<<"Finding a number in the list - 'find'\n";
    std::cout<<"Exit - 'exit'\n";
}

int RandomizeNumber(){
    return rand();
}

void GenerateDataSateInFail(char * filename, int * number){
    std::ofstream file(filename,std::ios_base::out);
    srand(time(NULL));// эта функция помогает нам генерировать новые случайные числа в 16 систему счисления каждый раз при вызове функции GenerateDtaSateFail
    for(int i=0; i<*number; ++i){
      file << std::hex << RandomizeNumber() <<std::endl;
    }

    file.close();
}

void printValue(Spisok * top){
    if(top==NULL) std::cout<<NO<<std::endl;
    else std::cout<<std::hex<<top->data<<std::endl;
}

void printDataOfSpisok(Spisok * top){

    std::cout<<"Data from list: \n---------------------\n"<<std::endl;

    if(top==NULL) {std::cout<<"NULL\n";}
    else{
    Spisok * spisok=top;
    do {
        printValue(spisok);
        spisok=spisok->next;
    }while (spisok!=top);
}
    std::cout<<"\n---------------------\n";
}

Spisok * insertUserNumberInSpisok(Spisok * top){
    int  number;
    std::cout<<"Please enter the number: "; std::cin>>number;
    top=insertDataInSpisok(top,number);
    return top;
}

Spisok * inputFromFile(Spisok * top, int * number, char * filename){
    int *buffer=new int[*number];
    std::ifstream file;
    file.open(filename, std::ios_base::in);

    for(int u=0; u<*number; ++u){
        file>>std::hex>>buffer[u];
    }
    for(int u=*number-1; u>=0; --u){
        top=insertDataInSpisok(top,buffer[u]);
    }

    file.close();

    return top;
}

Spisok * insertDataInSpisok(Spisok * top, int  number){
    Spisok * pointer=new Spisok;
    pointer->data=number;
    if(top==NULL){
        top=pointer;
        pointer->next=pointer;
        return top;
    }
    pointer->next=top;
    Spisok * cur;
    for(cur=top; cur->next!=top; cur=cur->next);
    cur->next=pointer;
    top=pointer;
    return top;
}

Spisok * destroyTheSpisok(Spisok * top){
    if(top==NULL) {std::cout<<NO<<std::endl;
        return NULL;}
    Spisok * pointer=top;
    if(pointer->next==top){std::cout<<"List is empty!"<<std::endl; top=NULL; free(pointer);
        return top;}
    else {
        /*top->data=top->data+top->next->data;
        top->next->data=top->data-top->next->data;
        top->data=top->data-top->next->data;*/
        Spisok *spisok = top->next;
        top->next = top->next->next;
        free(spisok);
        top=destroyTheSpisok(top);
        return top;
    }
}

Spisok * findDataInTheSpisok(Spisok * top)
{
    int number;
    std::cout<<"Please enter the number: "; std::cin>>number;
    Spisok * spisok=top;
    do {
        if(spisok->data==number) return spisok;
        spisok=spisok->next;
    } while (spisok!= top);
    return NULL;
}