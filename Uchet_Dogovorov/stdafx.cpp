// stdafx.cpp: �������� ����, ���������� ������ ����������� ���������� ������
// Uchet_Dogovorov.pch ����� ������������������� ����������
// stdafx.obj ����� ��������� �������������� ����������������� �������� � ����

#include "stdafx.h"

char *Rus1(const char * text){		//������������� ������
    char *buf = new char [strlen(text)];
    OemToChar(text, buf);
    return buf;
}

char *Rus(const char * text){		//������������� ������
    char *buf = new char [strlen(text)];
    OemToChar(text, buf);
    return buf;
}


// TODO: ���������� ������ �� ����� ����������� �������������� ��������� � ����� STDAFX.H
// , � �� � ������ �����
