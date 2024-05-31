// Uchet_Dogovorov.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

char *users_bd   = "c:\\Users.dat";				//���� �� �������������
char *klienty_bd = "c:\\Klienty.dat";			//���� �� � ������� ��������
char *Uslugi_bd	 = "c:\\Uslugi.dat";			//���� �� � ������� �����
char *Sdelki_bd	 = "c:\\Sdelki.dat";			//���� �� � ������� ������

void menu(void);
char *Rus1(const char * );		//������������� ������
void user_dobavl(void);

struct users{			//������������ �������
	char login[15];		//�����
	int admin;			//������������� (1) ��� ������������ (0)
	char parol[15];		//������
};


struct Klienty{				//������ �������
	int KodKlienta;			//��� �������
	char Nazvanie[15];		//��������
	char VidDejat[15];		//��� ������������
	char Adres[15];			//�����
	char Telefon[15];		//�������
};

struct Uslugi{				//������ ������
	int KodUslugi;			//��� ������
	char Nazvanie[15];		//��������
	char Opisanie[15];		//�������� ������
};

struct Data{			//����
	int chislo;			//�����
	int mes;			//�����
	int god;			//���
};

struct Sdelki{				//������ �������
	int KodSdelki;			//��� ������
	int KodKlienta;			//��� �������
	int KodUslugi;			//��� ������
	int Summa;				//�����
	int Komis;				//������������
	struct Data DataSd;		//���� ������
};


int avtorizacija(int adm){	//����������� �������������
	FILE *fp;
	struct users us, user;

	try{				//��������� ����������
		if ((fp = fopen(users_bd, "r+b")) == NULL)
			throw 100;						

		printf("������� ������:\n");
		printf("�����: ");		scanf("%s", &us.login);
		printf("������: ");		scanf("%s", &us.parol);

		while (fread(&user, sizeof(user), 1, fp) != NULL){
				if ((strcmp(user.login, us.login) == 0)&&
					(strcmp(user.parol, us.parol) == 0)&&
					(user.admin == adm)){
					fclose(fp);		
					return 0;
				}
		}
		fclose(fp);		//�������� �����
	}
	catch(int a){
		printf("��� ������.\n");
		user_dobavl();
	}
	
	printf("������������ �� ������.\n");
	system("pause");	//�������� ������� �������
	return 12;
};

struct users user_vvod(void){				//���������� �������� �� �������������
	struct users us;	
	printf("�����: ");								scanf("%s", &us.login);
	printf("������������� (1 - ��, 0 - ���): ");	scanf("%d", &us.admin);
	printf("������: ");								scanf("%s", &us.parol);
	return us;
};

void user_dobavl(void){		//���������� ������ � ���� ������
	FILE *fp;
	fp = fopen(users_bd, "a+b");

	printf("������� ������ ������������:\n");		
	fwrite(&user_vvod(), sizeof(users), 1, fp);	
	fclose(fp);
		
	printf("������ ���������\n");
	system("pause");
};

void user_show(void){		//������������ ������ �������������
	struct users us;
	FILE *fp;
	
	try{					//��������� ����������
		if ((fp = fopen(users_bd, "r+b")) == NULL)
			throw 100;						
		printf("   �����         �������������   ������\n");
		while (fread(&us, sizeof(users), 1, fp) != NULL){
			printf("%-15s        %-9d %-15s\n", Rus1(us.login), us.admin, Rus1(us.parol));
		}
		fclose(fp);		
	}
	catch(int a){
		printf("��� ������.\n");
	}
	system("pause");
}

int user_ud(void){		//�������� ������������
	FILE *fp;
	struct users us, user;

	int fl = -1, i = 0;

	try{				//��������� ����������
		if ((fp = fopen(users_bd, "r+b")) == NULL)
			throw 100;					
	}
	catch(int a){
		printf("��� ������.\n");
		system("pause");
		return 0;
	}

	printf("������� ������ ���������� ������������:\n");
	printf("�����: ");		scanf("%s", &user.login);
	printf("������: ");		scanf("%s", &user.parol);
	
	std::vector<users> v_f_us;			//���������
	std::vector<users>::iterator j;		//��������		

	while (fread(&us, sizeof(users), 1, fp) != NULL){
		if ((strcmp(us.login, user.login) == 0)&&(strcmp(us.parol, user.parol) == 0))
			fl = 1;
		else
			v_f_us.push_back(us);

		i++;
	}

	fclose(fp);		
	
	if (fl == -1){
		printf("������������ �� ������.\n");
		system("pause");
		return 0;
	}
		
	fp = fopen(users_bd, "wb");

	for (j = v_f_us.begin(); j != v_f_us.end(); ++j){
		us = *j;
		fwrite(&us, sizeof(users), 1, fp);
	}

	fclose(fp);
		
	printf("������������ ������.\n");
	system("pause");
	return 0;
};

Klienty Klienty_zapoln(void){			//���������� ������ �������
	struct Klienty d_kl;	

	printf("��� �������: ");			scanf("%d", &d_kl.KodKlienta);
	fflush(stdin);
	printf("��������: ");				gets(d_kl.Nazvanie);
	fflush(stdin);
	printf("��� ������������: ");		gets(d_kl.VidDejat);
	fflush(stdin);
	printf("�����: ");					gets(d_kl.Adres);
	fflush(stdin);
	printf("�������: ");				gets(d_kl.Telefon);

	return d_kl;
};


Uslugi Uslugi_zapoln(void){			//���������� ������ �����
	struct Uslugi d_usl;	

	printf("��� ������: ");			scanf("%d", &d_usl.KodUslugi);
	fflush(stdin);
	printf("��������: ");			gets(d_usl.Nazvanie);
	fflush(stdin);
	printf("��������: ");			gets(d_usl.Opisanie);

	return d_usl;
};


Sdelki Sdelki_zapoln(void){			//���������� ������ ������
	struct Sdelki d_sd;	

	printf("��� ������: ");			scanf("%d", &d_sd.KodSdelki);
	printf("��� �������: ");		scanf("%d", &d_sd.KodKlienta);
	printf("��� ������: ");			scanf("%d", &d_sd.KodUslugi);
	
	printf("�����: ");				scanf("%d", &d_sd.Summa);
	printf("������������: ");		scanf("%d", &d_sd.Komis);

	printf("���� (��.��.��): ");	scanf("%d.%d.%d", &d_sd.DataSd.chislo, &d_sd.DataSd.mes, &d_sd.DataSd.god);

	return d_sd;
};

void dan_kl_zapis(void){		//���������� ������ �������� � ����
	FILE *fp;
	fp = fopen(klienty_bd, "a+b");

	printf("������� ������ �������:\n");		
	fwrite(&Klienty_zapoln(), sizeof(Klienty), 1, fp);	
	fclose(fp);
		
	printf("������ ���������\n");
	system("pause");
};


int dan_kl_udalenie(void){		//�������� ������ �������
	FILE *fp;
	struct Klienty d_kl, d_kl_t;

	int fl = -1, i = 0;
	
	std::vector<Klienty> v_f_zp;			//���������
	std::vector<Klienty>::iterator j;	//��������		

	try{				//��������� ����������
		if ((fp = fopen(klienty_bd, "r+b")) == NULL)
			throw 100;					
	}
	catch(int a){
		printf("��� ������.\n");
		system("pause");
		return 0;
	}

	printf("������� ��� ���������� �������:\n");
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
		printf("������ �� ������.\n");
		system("pause");
		return 0;
	}
		
	fp = fopen(klienty_bd, "wb");

	for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
		d_kl = *j;
		fwrite(&d_kl, sizeof(Klienty), 1, fp);
	}

	fclose(fp);

	printf("������ �������.\n");

	system("pause");
	return 0;
};

void shapka_kl(void){
	printf("|��� �������|    ��������    | ��� ������������ |     �����     |  �������  |\n");
	printf("|-----------+----------------+------------------+---------------+-----------|\n");
};

void stroka_kl(struct Klienty d_kl){
	printf("|%11d|%-16s|%-18s|%-15s|%-11s|\n",
		d_kl.KodKlienta, Rus1(d_kl.Nazvanie), Rus1(d_kl.VidDejat), Rus1(d_kl.Adres), Rus1(d_kl.Telefon));
};

void poloska_kl(void){
	printf(" ---------------------------------------------------------------------------\n");
};


int dan_kl_red(void){			//����� � �������������� ������ �������
	FILE *fp;

	int fl = -1, i = 0;
	
	struct Klienty d_kl, d_kl_t;

	std::vector<Klienty> v_f_zp;			//���������
	std::vector<Klienty>::iterator j;	//��������		
	
	try{				//��������� ����������
		if ((fp = fopen(klienty_bd, "r+b")) == NULL)
				throw 100;					
	}
	catch(int a){
		printf("��� ������.\n");
		system("pause");
		return 0;
	}

	printf("�������:\n");
	printf("��� �������: ");		scanf("%d", &d_kl_t.KodKlienta);
	
	while (fread(&d_kl, sizeof(Klienty), 1, fp) != NULL){
		v_f_zp.push_back(d_kl);

		if (d_kl.KodKlienta == d_kl_t.KodKlienta)
			fl = i;				
		i++;
	}
	fclose(fp);		

	if (fl == -1){
		printf("������ �� �������.\n");
		system("pause");
		return 0;
	}

	poloska_kl();
	shapka_kl();
	stroka_kl(v_f_zp[fl]);
	poloska_kl();

	printf("������� ����� ������ �������:\n");
	d_kl = Klienty_zapoln();
	v_f_zp[fl] = d_kl;

	fp = fopen(klienty_bd, "wb");

	for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
		d_kl = *j;
		fwrite(&d_kl, sizeof(Klienty), 1, fp);
	}
	fclose(fp);

	printf("������ ������� ��������.\n");
	system("pause");
	return 0;
}

void dan_kl_show(void){		//������������ ������ ��������
	FILE *fp;
	struct Klienty d_kl;
	
	try{				//��������� ����������
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
		printf("��� ������.\n");
	}
	system("pause");
}

void dan_kl_poisk_po_kodu(void){		//����� ������� �� ����
	FILE *fp;
	struct Klienty d_kl, d_kl_t;

	try{				//��������� ����������
		if ((fp = fopen(klienty_bd, "r+b")) == NULL)
			throw 100;						
		
		printf("�������: \n");
		printf("��� �������: ");		scanf("%d", &d_kl_t.KodKlienta);
		
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
		printf("��� ������.\n");
	}
	system("pause");
}


//-----
void dan_usl_zapis(void){		//���������� ������ ����� � ����
	FILE *fp;
	fp = fopen(Uslugi_bd, "a+b");

	printf("������� ������ ������:\n");		
	fwrite(&Uslugi_zapoln(), sizeof(Uslugi), 1, fp);	
	fclose(fp);
		
	printf("������ ���������\n");
	system("pause");
};


int dan_usl_udalenie(void){		//�������� ������ �� ������
	FILE *fp;
	struct Uslugi d_usl, d_usl_t;

	int fl = -1, i = 0;
	
	std::vector<Uslugi> v_f_zp;			//���������
	std::vector<Uslugi>::iterator j;	//��������		

	try{				//��������� ����������
		if ((fp = fopen(Uslugi_bd, "r+b")) == NULL)
			throw 100;					
	}
	catch(int a){
		printf("��� ������.\n");
		system("pause");
		return 0;
	}

	printf("������� ��� ��������� ������:\n");
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
		printf("������ �� �������.\n");
		system("pause");
		return 0;
	}
		
	fp = fopen(Uslugi_bd, "wb");

	for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
		d_usl = *j;
		fwrite(&d_usl, sizeof(Uslugi), 1, fp);
	}

	fclose(fp);

	printf("������ �������.\n");

	system("pause");
	return 0;
};

void shapka_usl(void){
	printf("|��� ������|    ��������   |   ��������    |\n");
	printf("|----------+---------------+---------------|\n");
};

void stroka_usl(struct Uslugi d_usl){
	printf("|%10d|%-15s|%-15s|\n",
		d_usl.KodUslugi, Rus1(d_usl.Nazvanie), Rus1(d_usl.Opisanie));
};

void poloska_usl(void){
	printf(" ------------------------------------------\n");
};


int dan_usl_red(void){			//����� � �������������� ������ ������
	FILE *fp;

	int fl = -1, i = 0;
	
	struct Uslugi d_usl, d_usl_t;

	std::vector<Uslugi> v_f_zp;			//���������
	std::vector<Uslugi>::iterator j;	//��������		
	
	try{				//��������� ����������
		if ((fp = fopen(Uslugi_bd, "r+b")) == NULL)
				throw 100;					
	}
	catch(int a){
		printf("��� ������.\n");
		system("pause");
		return 0;
	}

	printf("�������:\n");
	printf("��� ������: ");		scanf("%d", &d_usl_t.KodUslugi);
	
	while (fread(&d_usl, sizeof(Uslugi), 1, fp) != NULL){
		v_f_zp.push_back(d_usl);

		if (d_usl.KodUslugi == d_usl_t.KodUslugi)
			fl = i;				
		i++;
	}
	fclose(fp);		

	if (fl == -1){
		printf("������ �� �������.\n");
		system("pause");
		return 0;
	}

	poloska_usl();
	shapka_usl();
	stroka_usl(v_f_zp[fl]);
	poloska_usl();

	printf("������� ����� ������ ������:\n");
	d_usl = Uslugi_zapoln();
	v_f_zp[fl] = d_usl;

	fp = fopen(Uslugi_bd, "wb");

	for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
		d_usl = *j;
		fwrite(&d_usl, sizeof(Uslugi), 1, fp);
	}
	fclose(fp);

	printf("������ ������ ��������.\n");
	system("pause");
	return 0;
}

void dan_usl_show(void){		//������������ ������ �����
	FILE *fp;
	struct Uslugi d_usl;
	
	try{				//��������� ����������
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
		printf("��� ������.\n");
	}
	system("pause");
}

void dan_usl_poisk_po_kodu(void){		//����� ������ �� ����
	FILE *fp;
	struct Uslugi d_usl, d_usl_t;

	try{				//��������� ����������
		if ((fp = fopen(Uslugi_bd, "r+b")) == NULL)
			throw 100;						
		
		printf("�������: \n");
		printf("��� ������: ");		scanf("%d", &d_usl_t.KodUslugi);
		
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
		printf("��� ������.\n");
	}
	system("pause");
}



//-------

void dan_sd_zapis(void){		//���������� ������ ������ � ����
	FILE *fp;
	fp = fopen(Sdelki_bd, "a+b");

	printf("������� ������ ������:\n");		
	fwrite(&Sdelki_zapoln(), sizeof(Sdelki), 1, fp);	
	fclose(fp);
		
	printf("������ ���������\n");
	system("pause");
};


int dan_sd_udalenie(void){		//�������� ������ ������
	FILE *fp;
	struct Sdelki d_sd, d_sd_t;

	int fl = -1, i = 0;
	
	std::vector<Sdelki> v_f_zp;			//���������
	std::vector<Sdelki>::iterator j;	//��������		

	try{				//��������� ����������
		if ((fp = fopen(Sdelki_bd, "r+b")) == NULL)
			throw 100;					
	}
	catch(int a){
		printf("��� ������.\n");
		system("pause");
		return 0;
	}

	printf("������� ��� ��������� ������:\n");
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
		printf("������ �� �������.\n");
		system("pause");
		return 0;
	}
		
	fp = fopen(Sdelki_bd, "wb");

	for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
		d_sd = *j;
		fwrite(&d_sd, sizeof(Sdelki), 1, fp);
	}

	fclose(fp);

	printf("������ �������.\n");

	system("pause");
	return 0;
};

void shapka_sd(void){
	printf("|��� ������ |��� �������|��� ������ |   �����   | ������������ |   ����   |\n");
	printf("|-----------+-----------+-----------+-----------+--------------+----------|\n");
};

void stroka_sd(struct Sdelki d_sd){
	printf("|%11d|%11d|%11d|%11d|%14d|%2d.%2d.%4d|\n",
		d_sd.KodSdelki, d_sd.KodKlienta, d_sd.KodUslugi, d_sd.Summa, d_sd.Komis, d_sd.DataSd.chislo, d_sd.DataSd.mes, d_sd.DataSd.god);
};

void poloska_sd(void){
	printf(" -------------------------------------------------------------------------\n");
};


int dan_sd_red(void){			//����� � �������������� ������ ������
	FILE *fp;

	int fl = -1, i = 0;
	
	struct Sdelki d_sd, d_sd_t;

	std::vector<Sdelki> v_f_zp;			//���������
	std::vector<Sdelki>::iterator j;	//��������		
	
	try{				//��������� ����������
		if ((fp = fopen(Sdelki_bd, "r+b")) == NULL)
				throw 100;					
	}
	catch(int a){
		printf("��� ������.\n");
		system("pause");
		return 0;
	}

	printf("�������:\n");
	printf("��� ������: ");		scanf("%d", &d_sd_t.KodSdelki);
	
	while (fread(&d_sd, sizeof(Sdelki), 1, fp) != NULL){
		v_f_zp.push_back(d_sd);

		if (d_sd.KodSdelki == d_sd_t.KodSdelki)
			fl = i;				
		i++;
	}
	fclose(fp);		

	if (fl == -1){
		printf("������ �� �������.\n");
		system("pause");
		return 0;
	}

	poloska_sd();
	shapka_sd();
	stroka_sd(v_f_zp[fl]);
	poloska_sd();

	printf("������� ����� ������ ������:\n");
	d_sd = Sdelki_zapoln();
	v_f_zp[fl] = d_sd;

	fp = fopen(Sdelki_bd, "wb");

	for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
		d_sd = *j;
		fwrite(&d_sd, sizeof(Sdelki), 1, fp);
	}
	fclose(fp);

	printf("������ ������ ��������.\n");
	system("pause");
	return 0;
}

void dan_sd_show(void){		//������������ ������ ������
	FILE *fp;
	struct Sdelki d_sd;
	
	try{				//��������� ����������
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
		printf("��� ������.\n");
	}
	system("pause");
}

void dan_sd_poisk_po_kodu(void){		//����� ������ �� ����
	FILE *fp;
	struct Sdelki d_sd, d_sd_t;

	try{				//��������� ����������
		if ((fp = fopen(Sdelki_bd, "r+b")) == NULL)
			throw 100;						
		
		printf("�������: \n");
		printf("��� ������: ");		scanf("%d", &d_sd_t.KodSdelki);
		
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
		printf("��� ������.\n");
	}
	system("pause");
}



bool sort_komis(struct Sdelki i, struct Sdelki j){		//������� ������������ ��� ����������
	return (i.Komis > j.Komis);							//�� �.�.�. ���������
}

void otsort_spis_po_Komis(void){					//��������������� ������ ������ �� �����������
	FILE *fp;
	struct Sdelki d_sd;

	std::vector<Sdelki> v_f_zp;					//���������
	std::vector<Sdelki>::iterator j;			//��������		

	try{				//��������� ����������
		if ((fp = fopen(Sdelki_bd, "r+b")) == NULL)
				throw 100;					
	
		while (fread(&d_sd, sizeof(Sdelki), 1, fp) != NULL)
			v_f_zp.push_back(d_sd);
		
		fclose(fp);		

		std::sort(v_f_zp.begin(), v_f_zp.end(), sort_komis);		//���������� �� ������������

		poloska_sd();
		shapka_sd();

		for (j = v_f_zp.begin(); j != v_f_zp.end(); ++j){
			d_sd = *j;
			stroka_sd(d_sd);
		}
		poloska_sd();
	
	}
	catch(int a){
		printf("��� ������.\n");
	}
	system("pause");
}


void ind_zad(void){					//C����� �� 2 ����� �����, ��������� ���������� ����� ������������ �� ������� ���
	FILE *fp;
	struct Sdelki d_sd;
	int kol = 0;

	std::vector<Sdelki> v_f_zp;					//���������
	std::vector<Sdelki>::iterator j;			//��������		

	try{				//��������� ����������
		if ((fp = fopen(Sdelki_bd, "r+b")) == NULL)
				throw 100;					
	
		while (fread(&d_sd, sizeof(Sdelki), 1, fp) != NULL)
			v_f_zp.push_back(d_sd);
		
		fclose(fp);		

		std::sort(v_f_zp.begin(), v_f_zp.end(), sort_komis);		//���������� �� ������������

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
		printf("��� ������.\n");
	}
	system("pause");
}


void dan_kl_spis_po_tel(void){		//������ �������� � ��������� ����� ��������
	FILE *fp;
	struct Klienty d_kl, d_kl_t;

	try{				//��������� ����������
		if ((fp = fopen(klienty_bd, "r+b")) == NULL)
			throw 100;						
		
		printf("�������: \n");
		fflush(stdin);
		printf("����� ��������: ");			scanf("%d", &d_kl_t.Telefon);
		
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
		printf("��� ������.\n");
	}
	system("pause");
}


void menu_adm(void){		//���� ��������������
	int m;
	
	m = avtorizacija(1);

	while (m < 22){
		system("cls");
		printf("* * * * * * * ����  ��������� � ������������ ������� * * * * * * *\n");
		printf("\t���� ��������������\n");
		printf("\t������� ����� ������:\n");
		printf(" 1. ���������� �������\n");
		printf(" 2. ��������� ������ �������\n");
		printf(" 3. �������� �������\n");
		printf(" 4. ������ ���� ��������\n");
		printf(" 5. ����� ������� �� ����\n");
		printf(" 6. ���������� ������\n");
		printf(" 7. ��������� ������ ������\n");
		printf(" 8. �������� ������\n");
		printf(" 9. ������ ���� �����\n");
		printf("10. ����� ������ �� ����\n");
		printf("11. ���������� ������\n");
		printf("12. ��������� ������ ������\n");
		printf("13. �������� ������\n");
		printf("14. ������ ���� ������\n");
		printf("15. ����� ������ �� ����\n");
		printf("16. ������ �������� � ��������� ������� ��������\n");
		printf("17. ������ ������ � ����������� �� ������������\n");
		printf("18. C����� �� 2 ����� �����, ��������� ���������� ����� ������������ �� ������� ���\n");
		printf("19. �������� ������������\n");
		printf("20. ������������ ������ �������������\n");
		printf("21. ������� ������������\n");
		printf("22. �����\n");
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

void menu_polz(void){			//���� ������������
	int m;

	m = avtorizacija(0);

	while (m < 10){
		system("cls");
		printf("* * * * * * * ����  ��������� � ������������ ������� * * * * * * *\n");
		printf("\t���� ������������\n");
		printf("\t������� ����� ����:\n");
		printf(" 1. ������ ���� ��������\n");
		printf(" 2. ����� ������� �� ����\n");
		printf(" 3. ������ ���� �����\n");
		printf(" 4. ����� ������ �� ����\n");
		printf(" 5. ������ ���� ������\n");
		printf(" 6. ����� ������ �� ����\n");
		printf(" 7. ������ ������ � ����������� �� ������������\n");
		printf(" 8. C����� �� 2 ����� �����, ��������� ���������� ����� ������������ �� ������� ���\n");
		printf(" 9. ������ �������� � ��������� ������� ��������\n");
		printf("10. �����\n");
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

void menu(void){		//������� ���� ���������
	int m = 0;
	while (m < 3){
		system("cls");
		printf("* * * * * * * ����  ��������� � ������������ ������� * * * * * * *\n");
		printf("\t�������� ����� ����:\n");
		printf(" 1. ���� ��� ���������������\n");
		printf(" 2. ���� ��� �������������\n");
		printf(" 3. �����\n");
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
	setlocale(LC_ALL, "rus");		//�����������
	
	menu();

	printf("��� ����������� ������� ����� �������.\n");
	system("pause");
}