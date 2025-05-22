/*
Заголовочный файл определяет структуры date и person для хранения информации о сотрудниках,
а также объявляет функции для работы с массивом сотрудников.
Структуры включают поля для ID, отдела, имени, зарплаты и дат,
а функции обеспечивают полный цикл управления данными:
загрузка, сортировка, сохранение, вывод и модификация.
*/
#ifndef PERSON_H
#define PERSON_H

//Структура для хранения даты (год, месяц, день).
typedef struct {
	int year, month, day;
} date;

/*
Структура для хранения информации о сотруднике:
ID, отдел, имя, зарплата, даты приема и увольнения.
*/
typedef struct {
	int id;
	char dept[20];
	char name[20];
	int salary;
	date begin;
	date end;
} person;

//Функция для вывода меню программы на экран.
void print_menu(void);

//Функция для сохранения массива сотрудников в текстовый файл.
void save_to_file(person *ar, int count, const char *filename);

//Функция для вывода списка сотрудников на экран.
void ar_print(person *ar, int count);

//Функция для обмена двух сотрудников местами (используется в сортировках).
void swap(person *pa, person *pb);

//Функция для сортировки массива сотрудников по ID.
void sort_by_id(person *ar, int len);

//Функция для сортировки массива сотрудников по имени.
void sort_by_name(person *ar, int len);

//Функция для сортировки массива сотрудников по зарплате.
void sort_by_salary(person *ar, int len);

//Функция для добавления нового сотрудника в массив с динамическим выделением памяти.
person *add_person(person *ar, int *count, int *capacity);

//Функция для удаления сотрудника из массива по ID.
person *delete_person(person *ar, int *count);

//Функция для редактирования сотрудника в массиве по ID.
person *edit_person(person *ar, int count);

//Функция для загрузки данных сотрудников из текстового файла с динамическим выделением памяти.
person *load_from_file(const char *filename, int *count, int *capacity);

#endif
