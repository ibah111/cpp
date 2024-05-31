// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// Uchet_Dogovorov.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

char *Rus1(const char * text){		//Перекодировка текста
    char *buf = new char [strlen(text)];
    OemToChar(text, buf);
    return buf;
}

char *Rus(const char * text){		//Перекодировка текста
    char *buf = new char [strlen(text)];
    OemToChar(text, buf);
    return buf;
}


// TODO: Установите ссылки на любые требующиеся дополнительные заголовки в файле STDAFX.H
// , а не в данном файле
