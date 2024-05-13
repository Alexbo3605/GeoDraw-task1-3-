#pragma once

class DataProvider
{
public:
    DataProvider(void);
    virtual ~DataProvider(void);

    //передавати rdInt(--num) num потрібне якщо станеться виключення
    virtual int rdInt(const int remainder =0); // повертає ціле число(int) позиції c (gData[c++])
    
    //передавати rdDouble(--num) num потрібне якщо станеться виключення
    virtual double rdDouble(const int remainder =0); // повертає дробове число(double) позиції c (gData[c++]) також може викликати виключення

private:
    //перевірка чи кінець файлу
    void checkC(); 

    // поточна позиція у масиві gData
    int c; 

    // максимальна позиція у масиві gData(розмір масиву)
    long maxC; 
};
