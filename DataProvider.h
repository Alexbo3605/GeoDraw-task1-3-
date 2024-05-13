#pragma once

class DataProvider
{
public:
    DataProvider(void);
    virtual ~DataProvider(void);

    //���������� rdInt(--num) num ������� ���� ��������� ����������
    virtual int rdInt(const int remainder =0); // ������� ���� �����(int) ������� c (gData[c++])
    
    //���������� rdDouble(--num) num ������� ���� ��������� ����������
    virtual double rdDouble(const int remainder =0); // ������� ������� �����(double) ������� c (gData[c++]) ����� ���� ��������� ����������

private:
    //�������� �� ����� �����
    void checkC(); 

    // ������� ������� � ����� gData
    int c; 

    // ����������� ������� � ����� gData(����� ������)
    long maxC; 
};
