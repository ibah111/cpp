// Uchet_Dogovorov.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

char *users_bd   = "c:\\Users.dat";				//Файл БД пользователей
char *klienty_bd = "c:\\Klienty.dat";			//Файл БД с данными клиентов
char *Uslugi_bd	 = "c:\\Uslugi.dat";			//Файл БД с данными услуг
char *Sdelki_bd	 = "c:\\Sdelki.dat";			//Файл БД с данными сделок

void menu(void);
char *Rus1(const char * );		//Перекодировка текста
void user_dobavl(void);

struct users{			//Пользователи системы
	char login[15];		//Логин
	int admin;			//Администратор (1) или пользователь (0)
	char parol[15];		//Пароль
};


struct Klienty{				//Данные клиента
	int KodKlienta;			//Код клиента
	char Nazvanie[15];		//Название
	char VidDejat[15];		//Вид деятельности
	char Adres[15];			//Адрес
	char Telefon[15];		//Телефон
};

struct Uslugi{				//Данные услуги
	int KodUslugi;			//Код услуги
	char Nazvanie[15];		//Название
	char Opisanie[15];		//Описание услуги
};

struct Data{			//Дата
	int chislo;			//Число
	int mes;			//Месяц
	int god;			//Год
};

struct Sdelki{				//Данные клиента
	int KodSdelki;			//Код сделки
	int KodKlienta;			//Код клиента
	int KodUslugi;			//Код услуги
	int Summa;				//Сумма
	int Komis;				//Комиссионные
	struct Data DataSd;		//Дата сделки
};


int avtorizacija(int adm){	//Авторизация пользователей
	FILE *fp;
	struct users us, user;

	try{				//Обработка исключений
		if ((fp = fopen(users_bd, "r+b")) == NULL)
			throw 100;						

		printf("Введите данные:\n");
		printf("Логин: ");		scanf("%s", &us.login);
		printf("Пароль: ");		scanf("%s", &us.parol);

		while (fread(&user, sizeof(user), 1, fp) != NULL){
				if ((strcmp(user.login, us.login) == 0)&&
					(strcmp(user.parol, us.parol) == 0)&&
					(user.admin == adm)){
					fclose(fp);		
					return 0;
				}
		}
		fclose(fp);		//Закрытие файла
	}
	catch(int a){
		printf("Нет данных.\n");
		user_dobavl();
	}
	
	printf("Пользователь не найден.\n");
	system("pause");	//Ожидание нажатия клавиши
	return 12;
};

struct users user_vvod(void){				//Заполнение элемента БД пользователей
	struct users us;	
	printf("Логин: ");								scanf("%s", &us.login);
	printf("Администратор (1 - да, 0 - нет): ");	scanf("%d", &us.admin);
	printf("Пароль: ");								scanf("%s", &us.parol);
	return us;
};

void user_dobavl(void){		//Добавление данных в базу данных
	FILE *fp;
	fp = fopen(users_bd, "a+b");

	printf("Введите данные пользователя:\n");		
	fwrite(&user_vvod(), sizeof(users), 1, fp);	
	fclose(fp);
		
	printf("Данные добавлены\n");
	system("pause");
};

void user_show(void){		//Формирование списка пользователей
	struct users us;
	FILE *fp;
	
	try{					//Обработка исключений
		if ((fp = fopen(users_bd, "r+b")) == NULL)
			throw 100;						
		printf("   Логин         Администратор   Пароль\n");
		while (fread(&us, sizeof(users), 1, fp) != NULL){
			printf("%-15s        %-9d %-15s\n", Rus1(us.login), us.admin, Rus1(us.parol));
		}
		fclose(fp);		
	}
	catch(int a){
		printf("Нет данных.\n");
	}
	system("pause");
}

int user_ud(void){		//Удаление пользователя
	FILE *fp;
	struct users us, user;

	int fl = -1, i = 0;

	try{				//Обработка исключений
		if ((fp = fopen(users_bd, "r+b")) == NULL)
			throw 100;					
	}
	catch(int a){
		printf("Нет данных.\n");
		system("pause");
		return 0;
	}

	printf("Введите данные удаляемого пользователя:\n");
	printf("Логин: ");		scanf("%s", &user.login);
	printf("Пароль: ");		scanf("%s", &user.parol);
	
	std::vector<users> v_f_us;			//Контейнер
	std::vector<users>::iterator j;		//Итератор		

	while (fread(&us, sizeof(users), 1, fp) != NULL){
		if ((strcmp(us.login, user.login) == 0)&&(strcmp(us.parol, user.parol) == 0))
			fl = 1;
		else
			v_f_us.push_back(us);

		i++;
	}

	fclose(fp);		
	
	if (fl == -1){
		printf("Пользователь не найден.\n");
		system("pause");
		return 0;
	}
		
	fp = fopen(users_bd, "wb");

	for (j = v_f_us.begin(); j != v_f_us.end(); ++j){
		us = *j;
		fwrite(&us, sizeof(users), 1, fp);
	}

	fclose(fp);
		
	printf("Пользователь удален.\n");
	system("pause");
	return 0;
};

Klienty Klienty_zapoln(void){			//Заполнение данных клиента
	struct Klienty d_kl;	

	printf("Код клиента: ");			scanf("%d", &d_kl.KodKlienta);
	fflush(stdin);
	printf("Название: ");				gets(d_kl.Nazvanie);
	fflush(stdin);
	printf("Вид деятельности: ");		gets(d_kl.VidDejat);
	fflush(stdin);
	printf("Адрес: ");					gets(d_kl.Adres);
	fflush(stdin);
	printf("Телефон: ");				gets(d_kl.Telefon);

	return d_kl;
};


Uslugi Uslugi_zapoln(void){			//Заполнение данных услуг
	struct Uslugi d_usl;	

	printf("Код услуги: ");			scanf("%d", &d_usl.KodUslugi);
	fflush(stdin);
	printf("Название: ");			gets(d_usl.Nazvanie);
	fflush(stdin);
	printf("Описание: ");			gets(d_usl.Opisanie);

	return d_usl;
};


Sdelki Sdelki_zapoln(void){			//Заполнение данных сделки
	struct Sdelki d_sd;	

	printf("Код сделки: ");			scanf("%d", &d_sd.KodSdelki);
	printf("Код клиента: ");		scanf("%d", &d_sd.KodKlienta);
	printf("Код услуги: ");			scanf("%d", &d_sd.KodUslugi);
	
	printf("Сумма: ");				scanf("%d", &d_sd.Summa);
	printf("Комиссионные: ");		scanf("%d", &d_sd.Komis);

	printf("Дата (ЧЧ.ММ.ГГ): ");	scanf("%d.%d.%d", &d_sd.DataSd.chislo, &d_sd.DataSd.mes, &d_sd.DataSd.god);

	return d_sd;
};

void dan_kl_zapis(void){		//Добавление данных клиентов в базу
	FILE *fp;
	fp = fopen(klienty_bd, "a+b");

	printf("Внесите данные клиента:\n");		
	fwrite(&Klienty_zapoln(), sizeof(Klienty), 1, fp);	
	fclose(fp);
		
	printf("Запись добавлена\n");
	system("pause");
};


int dan_kl_udalenie(void){		//Удаление данных клиента
	FILE *fp;
	struct Klienty d_kl, d_kl_t;

	int fl = -1, i = 0;
	
	std::vector<Klienty> v_f_zp;			//Контейнер
	std::vector<Klienty>::iterator j;	//Итератор		

	try{				//Обработка исключений
		if ((fp = fopen(klienty_bd, "r+b")) == NULL)
			throw 100;					
	}
	catch(int a){
		printf("Нет данных.\n");
		system("pause");
		return 0;
	}

	printf("Введите код удаляемого клиента:\n");
	printf(": ");		scanf("%d", &d_kl_t.KodKlienta);
		
	while (fread(&d_kl, sizeof(Klienty), 1, fp) != NULL){
		if (d_kl.KodKlienta == d_kl_t.KodKlienta)
			fl = 1;
		else
			v_f_zp.push_back(d_kl);

		i++;
	}
	fclose(fp);		

	if (fl == -1){
		printf("Клиент не найден.\n");
		system("pause");
		return 0;
	}
		
	fp = fopen(klienty_bd, "wb");

	for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
		d_kl = *j;
		fwrite(&d_kl, sizeof(Klienty), 1, fp);
	}

	fclose(fp);

	printf("Запись удалена.\n");

	system("pause");
	return 0;
};

void shapka_kl(void){
	printf("|Код клиента|    Название    | Вид деятельности |     Адрес     |  Телефон  |\n");
	printf("|-----------+----------------+------------------+---------------+-----------|\n");
};

void stroka_kl(struct Klienty d_kl){
	printf("|%11d|%-16s|%-18s|%-15s|%-11s|\n",
		d_kl.KodKlienta, Rus1(d_kl.Nazvanie), Rus1(d_kl.VidDejat), Rus1(d_kl.Adres), Rus1(d_kl.Telefon));
};

void poloska_kl(void){
	printf(" ---------------------------------------------------------------------------\n");
};


int dan_kl_red(void){			//Поиск и редактирование данных клиента
	FILE *fp;

	int fl = -1, i = 0;
	
	struct Klienty d_kl, d_kl_t;

	std::vector<Klienty> v_f_zp;			//Контейнер
	std::vector<Klienty>::iterator j;	//Итератор		
	
	try{				//Обработка исключений
		if ((fp = fopen(klienty_bd, "r+b")) == NULL)
				throw 100;					
	}
	catch(int a){
		printf("Нет данных.\n");
		system("pause");
		return 0;
	}

	printf("Введите:\n");
	printf("Код клиента: ");		scanf("%d", &d_kl_t.KodKlienta);
	
	while (fread(&d_kl, sizeof(Klienty), 1, fp) != NULL){
		v_f_zp.push_back(d_kl);

		if (d_kl.KodKlienta == d_kl_t.KodKlienta)
			fl = i;				
		i++;
	}
	fclose(fp);		

	if (fl == -1){
		printf("Запись не найдена.\n");
		system("pause");
		return 0;
	}

	poloska_kl();
	shapka_kl();
	stroka_kl(v_f_zp[fl]);
	poloska_kl();

	printf("Введите новые данные клиента:\n");
	d_kl = Klienty_zapoln();
	v_f_zp[fl] = d_kl;

	fp = fopen(klienty_bd, "wb");

	for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
		d_kl = *j;
		fwrite(&d_kl, sizeof(Klienty), 1, fp);
	}
	fclose(fp);

	printf("Данные клиента изменены.\n");
	system("pause");
	return 0;
}

void dan_kl_show(void){		//Формирование списка клиентов
	FILE *fp;
	struct Klienty d_kl;
	
	try{				//Обработка исключений
		if ((fp = fopen(klienty_bd, "r+b")) == NULL)
			throw 100;						
		poloska_kl();
		shapka_kl();
		while (fread(&d_kl, sizeof(Klienty), 1, fp) != NULL){
			stroka_kl(d_kl);
		}
		poloska_kl();

		fclose(fp);		
	}
	catch(int a){
		printf("Нет данных.\n");
	}
	system("pause");
}

void dan_kl_poisk_po_kodu(void){		//Поиск клиента по коду
	FILE *fp;
	struct Klienty d_kl, d_kl_t;

	try{				//Обработка исключений
		if ((fp = fopen(klienty_bd, "r+b")) == NULL)
			throw 100;						
		
		printf("Введите: \n");
		printf("Код клиента: ");		scanf("%d", &d_kl_t.KodKlienta);
		
		poloska_kl();
		shapka_kl();
		while (fread(&d_kl, sizeof(Klienty), 1, fp) != NULL){
			if (d_kl.KodKlienta == d_kl_t.KodKlienta)
				stroka_kl(d_kl);
		}
		poloska_kl();

		fclose(fp);		
	}
	catch(int a){
		printf("Нет данных.\n");
	}
	system("pause");
}


//-----
void dan_usl_zapis(void){		//Добавление данных услуг в базу
	FILE *fp;
	fp = fopen(Uslugi_bd, "a+b");

	printf("Внесите данные услуги:\n");		
	fwrite(&Uslugi_zapoln(), sizeof(Uslugi), 1, fp);	
	fclose(fp);
		
	printf("Запись добавлена\n");
	system("pause");
};


int dan_usl_udalenie(void){		//Удаление данных об услуге
	FILE *fp;
	struct Uslugi d_usl, d_usl_t;

	int fl = -1, i = 0;
	
	std::vector<Uslugi> v_f_zp;			//Контейнер
	std::vector<Uslugi>::iterator j;	//Итератор		

	try{				//Обработка исключений
		if ((fp = fopen(Uslugi_bd, "r+b")) == NULL)
			throw 100;					
	}
	catch(int a){
		printf("Нет данных.\n");
		system("pause");
		return 0;
	}

	printf("Введите код удаляемой услуги:\n");
	printf(": ");		scanf("%d", &d_usl_t.KodUslugi);
		
	while (fread(&d_usl, sizeof(Klienty), 1, fp) != NULL){
		if (d_usl.KodUslugi == d_usl_t.KodUslugi)
			fl = 1;
		else
			v_f_zp.push_back(d_usl);

		i++;
	}
	fclose(fp);		

	if (fl == -1){
		printf("Услуга не найдена.\n");
		system("pause");
		return 0;
	}
		
	fp = fopen(Uslugi_bd, "wb");

	for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
		d_usl = *j;
		fwrite(&d_usl, sizeof(Uslugi), 1, fp);
	}

	fclose(fp);

	printf("Запись удалена.\n");

	system("pause");
	return 0;
};

void shapka_usl(void){
	printf("|Код услуги|    Название   |   Описание    |\n");
	printf("|----------+---------------+---------------|\n");
};

void stroka_usl(struct Uslugi d_usl){
	printf("|%10d|%-15s|%-15s|\n",
		d_usl.KodUslugi, Rus1(d_usl.Nazvanie), Rus1(d_usl.Opisanie));
};

void poloska_usl(void){
	printf(" ------------------------------------------\n");
};


int dan_usl_red(void){			//Поиск и редактирование данных услуги
	FILE *fp;

	int fl = -1, i = 0;
	
	struct Uslugi d_usl, d_usl_t;

	std::vector<Uslugi> v_f_zp;			//Контейнер
	std::vector<Uslugi>::iterator j;	//Итератор		
	
	try{				//Обработка исключений
		if ((fp = fopen(Uslugi_bd, "r+b")) == NULL)
				throw 100;					
	}
	catch(int a){
		printf("Нет данных.\n");
		system("pause");
		return 0;
	}

	printf("Введите:\n");
	printf("Код услуги: ");		scanf("%d", &d_usl_t.KodUslugi);
	
	while (fread(&d_usl, sizeof(Uslugi), 1, fp) != NULL){
		v_f_zp.push_back(d_usl);

		if (d_usl.KodUslugi == d_usl_t.KodUslugi)
			fl = i;				
		i++;
	}
	fclose(fp);		

	if (fl == -1){
		printf("Запись не найдена.\n");
		system("pause");
		return 0;
	}

	poloska_usl();
	shapka_usl();
	stroka_usl(v_f_zp[fl]);
	poloska_usl();

	printf("Введите новые данные услуги:\n");
	d_usl = Uslugi_zapoln();
	v_f_zp[fl] = d_usl;

	fp = fopen(Uslugi_bd, "wb");

	for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
		d_usl = *j;
		fwrite(&d_usl, sizeof(Uslugi), 1, fp);
	}
	fclose(fp);

	printf("Данные услуги изменены.\n");
	system("pause");
	return 0;
}

void dan_usl_show(void){		//Формирование списка услуг
	FILE *fp;
	struct Uslugi d_usl;
	
	try{				//Обработка исключений
		if ((fp = fopen(Uslugi_bd, "r+b")) == NULL)
			throw 100;						
		poloska_usl();
		shapka_usl();
		while (fread(&d_usl, sizeof(Uslugi), 1, fp) != NULL){
			stroka_usl(d_usl);
		}
		poloska_usl();

		fclose(fp);		
	}
	catch(int a){
		printf("Нет данных.\n");
	}
	system("pause");
}

void dan_usl_poisk_po_kodu(void){		//Поиск услуги по коду
	FILE *fp;
	struct Uslugi d_usl, d_usl_t;

	try{				//Обработка исключений
		if ((fp = fopen(Uslugi_bd, "r+b")) == NULL)
			throw 100;						
		
		printf("Введите: \n");
		printf("Код услуги: ");		scanf("%d", &d_usl_t.KodUslugi);
		
		poloska_usl();
		shapka_usl();
		while (fread(&d_usl, sizeof(Uslugi), 1, fp) != NULL){
			if (d_usl.KodUslugi == d_usl_t.KodUslugi)
				stroka_usl(d_usl);
		}
		poloska_usl();

		fclose(fp);		
	}
	catch(int a){
		printf("Нет данных.\n");
	}
	system("pause");
}



//-------

void dan_sd_zapis(void){		//Добавление данных сделки в базу
	FILE *fp;
	fp = fopen(Sdelki_bd, "a+b");

	printf("Внесите данные сделки:\n");		
	fwrite(&Sdelki_zapoln(), sizeof(Sdelki), 1, fp);	
	fclose(fp);
		
	printf("Запись добавлена\n");
	system("pause");
};


int dan_sd_udalenie(void){		//Удаление данных сделки
	FILE *fp;
	struct Sdelki d_sd, d_sd_t;

	int fl = -1, i = 0;
	
	std::vector<Sdelki> v_f_zp;			//Контейнер
	std::vector<Sdelki>::iterator j;	//Итератор		

	try{				//Обработка исключений
		if ((fp = fopen(Sdelki_bd, "r+b")) == NULL)
			throw 100;					
	}
	catch(int a){
		printf("Нет данных.\n");
		system("pause");
		return 0;
	}

	printf("Введите код удаляемой сделки:\n");
	printf(": ");		scanf("%d", &d_sd_t.KodSdelki);
		
	while (fread(&d_sd, sizeof(Sdelki), 1, fp) != NULL){
		if (d_sd.KodSdelki == d_sd_t.KodSdelki)
			fl = 1;
		else
			v_f_zp.push_back(d_sd);

		i++;
	}
	fclose(fp);		

	if (fl == -1){
		printf("Сделка не найдена.\n");
		system("pause");
		return 0;
	}
		
	fp = fopen(Sdelki_bd, "wb");

	for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
		d_sd = *j;
		fwrite(&d_sd, sizeof(Sdelki), 1, fp);
	}

	fclose(fp);

	printf("Запись удалена.\n");

	system("pause");
	return 0;
};

void shapka_sd(void){
	printf("|Код сделки |Код клиента|Код услуги |   Сумма   | Комиссионные |   Дата   |\n");
	printf("|-----------+-----------+-----------+-----------+--------------+----------|\n");
};

void stroka_sd(struct Sdelki d_sd){
	printf("|%11d|%11d|%11d|%11d|%14d|%2d.%2d.%4d|\n",
		d_sd.KodSdelki, d_sd.KodKlienta, d_sd.KodUslugi, d_sd.Summa, d_sd.Komis, d_sd.DataSd.chislo, d_sd.DataSd.mes, d_sd.DataSd.god);
};

void poloska_sd(void){
	printf(" -------------------------------------------------------------------------\n");
};


int dan_sd_red(void){			//Поиск и редактирование данных сделки
	FILE *fp;

	int fl = -1, i = 0;
	
	struct Sdelki d_sd, d_sd_t;

	std::vector<Sdelki> v_f_zp;			//Контейнер
	std::vector<Sdelki>::iterator j;	//Итератор		
	
	try{				//Обработка исключений
		if ((fp = fopen(Sdelki_bd, "r+b")) == NULL)
				throw 100;					
	}
	catch(int a){
		printf("Нет данных.\n");
		system("pause");
		return 0;
	}

	printf("Введите:\n");
	printf("Код сделки: ");		scanf("%d", &d_sd_t.KodSdelki);
	
	while (fread(&d_sd, sizeof(Sdelki), 1, fp) != NULL){
		v_f_zp.push_back(d_sd);

		if (d_sd.KodSdelki == d_sd_t.KodSdelki)
			fl = i;				
		i++;
	}
	fclose(fp);		

	if (fl == -1){
		printf("Запись не найдена.\n");
		system("pause");
		return 0;
	}

	poloska_sd();
	shapka_sd();
	stroka_sd(v_f_zp[fl]);
	poloska_sd();

	printf("Введите новые данные сделки:\n");
	d_sd = Sdelki_zapoln();
	v_f_zp[fl] = d_sd;

	fp = fopen(Sdelki_bd, "wb");

	for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
		d_sd = *j;
		fwrite(&d_sd, sizeof(Sdelki), 1, fp);
	}
	fclose(fp);

	printf("Данные сделки изменены.\n");
	system("pause");
	return 0;
}

void dan_sd_show(void){		//Формирование списка сделок
	FILE *fp;
	struct Sdelki d_sd;
	
	try{				//Обработка исключений
		if ((fp = fopen(Sdelki_bd, "r+b")) == NULL)
			throw 100;						
		poloska_sd();
		shapka_sd();
		while (fread(&d_sd, sizeof(Sdelki), 1, fp) != NULL){
			stroka_sd(d_sd);
		}
		poloska_sd();

		fclose(fp);		
	}
	catch(int a){
		printf("Нет данных.\n");
	}
	system("pause");
}

void dan_sd_poisk_po_kodu(void){		//Поиск сделки по коду
	FILE *fp;
	struct Sdelki d_sd, d_sd_t;

	try{				//Обработка исключений
		if ((fp = fopen(Sdelki_bd, "r+b")) == NULL)
			throw 100;						
		
		printf("Введите: \n");
		printf("Код сделки: ");		scanf("%d", &d_sd_t.KodSdelki);
		
		poloska_sd();
		shapka_sd();
		while (fread(&d_sd, sizeof(Sdelki), 1, fp) != NULL){
			if (d_sd.KodSdelki == d_sd_t.KodSdelki)
				stroka_sd(d_sd);
		}
		poloska_sd();

		fclose(fp);		
	}
	catch(int a){
		printf("Нет данных.\n");
	}
	system("pause");
}



bool sort_komis(struct Sdelki i, struct Sdelki j){		//Функция используемая для сортировок
	return (i.Komis > j.Komis);							//По Ф.И.О. участницы
}

void otsort_spis_po_Komis(void){					//Отсортированный список сделок по комиссионым
	FILE *fp;
	struct Sdelki d_sd;

	std::vector<Sdelki> v_f_zp;					//Контейнер
	std::vector<Sdelki>::iterator j;			//Итератор		

	try{				//Обработка исключений
		if ((fp = fopen(Sdelki_bd, "r+b")) == NULL)
				throw 100;					
	
		while (fread(&d_sd, sizeof(Sdelki), 1, fp) != NULL)
			v_f_zp.push_back(d_sd);
		
		fclose(fp);		

		std::sort(v_f_zp.begin(), v_f_zp.end(), sort_komis);		//Сортировка по комиссионным

		poloska_sd();
		shapka_sd();

		for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
			d_sd = *j;
			stroka_sd(d_sd);
		}
		poloska_sd();
	
	}
	catch(int a){
		printf("Нет данных.\n");
	}
	system("pause");
}


void ind_zad(void){					//Cписок из 2 видов услуг, принесших наибольшие суммы комиссионных за текущий год
	FILE *fp;
	struct Sdelki d_sd;
	int kol = 0;

	std::vector<Sdelki> v_f_zp;					//Контейнер
	std::vector<Sdelki>::iterator j;			//Итератор		

	try{				//Обработка исключений
		if ((fp = fopen(Sdelki_bd, "r+b")) == NULL)
				throw 100;					
	
		while (fread(&d_sd, sizeof(Sdelki), 1, fp) != NULL)
			v_f_zp.push_back(d_sd);
		
		fclose(fp);		

		std::sort(v_f_zp.begin(), v_f_zp.end(), sort_komis);		//Сортировка по комиссионным

		poloska_sd();
		shapka_sd();

		for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
			d_sd = *j;

			if ((d_sd.DataSd.god == 2024)&(kol < 2)){
				stroka_sd(d_sd);
				kol++;
			}

		}
		poloska_sd();
	
	}
	catch(int a){
		printf("Нет данных.\n");
	}
	system("pause");
}


void dan_kl_spis_po_tel(void){		//Список клиентов с указанным номер телефона
	FILE *fp;
	struct Klienty d_kl, d_kl_t;

	try{				//Обработка исключений
		if ((fp = fopen(klienty_bd, "r+b")) == NULL)
			throw 100;						
		
		printf("Введите: \n");
		fflush(stdin);
		printf("Номер телефона: ");			scanf("%d", &d_kl_t.Telefon);
		
		poloska_kl();
		shapka_kl();
		while (fread(&d_kl, sizeof(Klienty), 1, fp) != NULL){
			if (d_kl.Telefon == d_kl_t.Telefon)
				stroka_kl(d_kl);
		}
		poloska_kl();

		fclose(fp);		
	}
	catch(int a){
		printf("Нет данных.\n");
	}
	system("pause");
}


void menu_adm(void){		//Меню администратора
	int m;
	
	m = avtorizacija(1);

	while (m < 22){
		system("cls");
		printf("* * * * * * * Учет  договоров в нотариальной конторе * * * * * * *\n");
		printf("\tМеню администратора\n");
		printf("\tВведите номер пункта:\n");
		printf(" 1. Добавление клиента\n");
		printf(" 2. Изменение данных клиента\n");
		printf(" 3. Удаление клиента\n");
		printf(" 4. Список всех клиентов\n");
		printf(" 5. Поиск клиента по коду\n");
		printf(" 6. Добавление услуги\n");
		printf(" 7. Изменение данных услуги\n");
		printf(" 8. Удаление услуги\n");
		printf(" 9. Список всех услуг\n");
		printf("10. Поиск услуги по коду\n");
		printf("11. Добавление сделки\n");
		printf("12. Изменение данных сделки\n");
		printf("13. Удаление сделки\n");
		printf("14. Список всех сделок\n");
		printf("15. Поиск сделки по коду\n");
		printf("16. Список клиентов с указанным номером телефона\n");
		printf("17. Список сделок с сортировкой по комиссионным\n");
		printf("18. Cписок из 2 видов услуг, принесших наибольшие суммы комиссионных за текущий год\n");
		printf("19. Добавить пользователя\n");
		printf("20. Формирование списка пользователей\n");
		printf("21. Удалить пользователя\n");
		printf("22. Выход\n");
		printf("  : ");
		scanf("%d", &m);

		switch(m){
		case  1: dan_kl_zapis(); break;
		case  2: dan_kl_red(); break;
		case  3: dan_kl_udalenie(); break;
		case  4: dan_kl_show(); break;
		case  5: dan_kl_poisk_po_kodu(); break;
		case  6: dan_usl_zapis(); break;
		case  7: dan_usl_red(); break;
		case  8: dan_usl_udalenie(); break;
		case  9: dan_usl_show(); break;
		case 10: dan_usl_poisk_po_kodu(); break;
		case 11: dan_sd_zapis(); break;
		case 12: dan_sd_red(); break;
		case 13: dan_sd_udalenie(); break;
		case 14: dan_sd_show(); break;
		case 15: dan_sd_poisk_po_kodu(); break;
		case 16: dan_kl_spis_po_tel(); break;
		case 17: otsort_spis_po_Komis(); break;
		case 18: ind_zad(); break;

		case 19: user_dobavl(); break;
		case 20: user_show(); break;
		case 21: user_ud(); break;
		default: m = 22; break;
		}	
	}
}

void menu_polz(void){			//Меню пользователя
	int m;

	m = avtorizacija(0);

	while (m < 10){
		system("cls");
		printf("* * * * * * * Учет  договоров в нотариальной конторе * * * * * * *\n");
		printf("\tМеню пользователя\n");
		printf("\tВведите пункт меню:\n");
		printf(" 1. Список всех клиентов\n");
		printf(" 2. Поиск клиента по коду\n");
		printf(" 3. Список всех услуг\n");
		printf(" 4. Поиск услуги по коду\n");
		printf(" 5. Список всех сделок\n");
		printf(" 6. Поиск сделки по коду\n");
		printf(" 7. Список сделок с сортировкой по комиссионным\n");
		printf(" 8. Cписок из 2 видов услуг, принесших наибольшие суммы комиссионных за текущий год\n");
		printf(" 9. Список клиентов с указанным номером телефона\n");
		printf("10. Выход\n");
		printf("  : ");
		scanf("%d", &m);

		switch(m){
		case  1: dan_kl_show(); break;
		case  2: dan_kl_poisk_po_kodu(); break;
		case  3: dan_usl_show(); break;
		case  4: dan_usl_poisk_po_kodu(); break;
		case  5: dan_sd_show(); break;
		case  6: dan_sd_poisk_po_kodu(); break;
		case  7: otsort_spis_po_Komis(); break;
		case  8: ind_zad(); break;
		case  9: dan_kl_spis_po_tel(); break;
		default: m = 14; break;
		}	
	}
}

void menu(void){		//Главное меню программы
	int m = 0;
	while (m < 3){
		system("cls");
		printf("* * * * * * * Учет  договоров в нотариальной конторе * * * * * * *\n");
		printf("\tВыберите пункт меню:\n");
		printf(" 1. Вход под администратором\n");
		printf(" 2. Вход под пользователем\n");
		printf(" 3. Выход\n");
		printf("  : ");
		
		scanf("%d", &m);

		switch(m){
		case 1: menu_adm(); break;
		case 2: menu_polz(); break;
		default: m = 14; break;
		}	
	}
}

void main(void)
{
	setlocale(LC_ALL, "rus");		//Локализация
	
	menu();

	printf("Для продолжения нажмите любую клавишу.\n");
	system("pause");
}