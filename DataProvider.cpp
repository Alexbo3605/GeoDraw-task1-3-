#include "DataProvider.h"
#include "Exceptions.h"

#define PI 3.141 //�� ������ ������� + � CircularArc ����� �� ���� PI
#define THROW_ERR 23000000

double gData[] = {
    8, // -- ����� �������� � �����



    1, // 1 -- ��� "�������" �� ���������, ������������� ���� ���������
    4, // 4 -- ���������� ����� double (������� ���������� � � 2�� �������!!) ��
    0.0, 0.0, // ���������� - ����� ������ ����
    10.0, 10.0, // ���������� - ������ ������� ����



    2, // 2 -- ��� "����������"
    3,
    0.0, 0.0, // ���������� - ����� ����������
    25.0, // ������ ����������



    3, // 3 -- ���� ����������� ���
    5,
    1., 2., 3., 4., 5., // ������



    4, // 4 - ���� ����������
    5,
    150., 150.,  // ���������� -- ����� ����������
    44.,         // ������ ����������
    PI / 4., PI / 2., // ����� -- ������ � ����� ����


    2, // 2 -- ��� "����������"
    3,
    10.0, THROW_ERR, // ��� ������ ������� ���������� ����������
    25.0,



    5, // 5 -- ��� �������������
    10,
    10., 20., // ���������� �����
    20., 30., // ���������� �����
    35., 25., // ���������� �����
    0., 50., // ���������� �����
    0., 0.,   // ���������� �����



    6, // -- ��� "�������"
    10,
    0,0, // ���������� �����
    1,1, // ���������� �����
    0,1, // ���������� �����
    0,2, // ���������� �����
    5,5, // ���������� �����


    28, // ����������� ������
    10,
    90,91,92,93,94,95,96,97,98,99
};

DataProvider::DataProvider(void) : c(0), maxC(sizeof(gData) / sizeof(gData[0]))
{
}

DataProvider::~DataProvider(void)
{
}

int DataProvider::rdInt(const int remainder) {
    checkC();
    int i = (int)gData[c++];
    if (i == THROW_ERR) {
        c += remainder;
        throw ReadError("Error reding Int pos", c - remainder);
    }
    return i;
}

double DataProvider::rdDouble(const int remainder) {
    checkC();
    double d = gData[c++];
    if (d == THROW_ERR) {
        c += remainder;
        throw ReadError("Error reding Double pos", c - remainder);
    }
    return d;
}

void DataProvider::checkC() {
    if (c == maxC) {
        throw EndOfFile();
    }
}
