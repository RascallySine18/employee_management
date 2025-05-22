/*
Файл person.c содержит реализации функций, объявленных в person.h.
Функции обеспечивают полный цикл управления данными сотрудников:
вывод меню, сохранение, вывод, сортировка, добавление, удаление и редактирование.
Все функции включают базовую обработку ошибок
(например, проверку открытия файлов и корректности ввода).
*/
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include "person.h"

/*
Функция print_menu
Выводит на экран меню с опциями программы.
*/
void print_menu(void) {
	printf("\nМеню:\n");
	printf("1. Сортировать по ID\n");
	printf("2. Сортировать по имени\n");
	printf("3. Сортировать по зарплате\n");
	printf("4. Добавить сотрудника\n");
	printf("5. Удалить сотрудника\n");
	printf("6. Редактировать сотрудника\n");
	printf("7. Вывести список\n");
	printf("0. Выход\n");
	printf("Ваш выбор: ");
}

/*
Функция save_to_file
Сохраняет массив сотрудников в текстовый файл с указанным именем.
Параметры:
- ar: массив сотрудников.
- count: количество сотрудников в массиве.
- filename: имя файла для сохранения.
Если файл не удалось открыть, выводит сообщение об ошибке.
*/
void save_to_file(person *ar, int count, const char *filename) {
	FILE *f_out = fopen(filename, "w");
	if (f_out == NULL) {
		printf("Ошибка открытия файла %s для записи!\n", filename);
		return;
	}
	for (int i = 0; i < count; ++i) {
		fprintf(f_out, "%d %s %s %d %d.%d.%d %d.%d.%d\n",
			ar[i].id, ar[i].dept, ar[i].name, ar[i].salary,
			ar[i].begin.year, ar[i].begin.month, ar[i].begin.day,
			ar[i].end.year, ar[i].end.month, ar[i].end.day);
	}
	fclose(f_out);
	printf("Данные сохранены в %s\n", filename);
}

/*
Функция ar_print
Выводит на экран список всех сотрудников в массиве.
Параметры:
- ar: массив сотрудников.
- count: количество сотрудников в массиве.
*/
void ar_print(person *ar, int count) {
	printf("\nТекущий список сотрудников:\n");
	if (count == 0) {
		printf("Список пуст.\n");
		return;
	}
	for (int i = 0; i < count; ++i) {
		printf("%d %s %s %d %d.%d.%d %d.%d.%d\n",
			ar[i].id, ar[i].dept, ar[i].name, ar[i].salary,
			ar[i].begin.year, ar[i].begin.month, ar[i].begin.day,
			ar[i].end.year, ar[i].end.month, ar[i].end.day);
	}
}

/*
Функция swap
Меняет местами два сотрудника (используется в сортировках).
Параметры:
- pa, pb: указатели на записи сотрудников для обмена.
*/
void swap(person *pa, person *pb) {
	person t = *pa;
	*pa = *pb;
	*pb = t;
}

/*
Функция sort_by_id
Сортирует массив сотрудников по ID (по возрастанию).
Параметры:
- ar: массив сотрудников.
- len: длина массива (количество записей).
*/
void sort_by_id(person *ar, int len) {
	for (int i = 0; i < len - 1; ++i) {
		int imin = i;
		for (int j = i + 1; j < len; ++j) {
			if (ar[j].id < ar[imin].id) {
				imin = j;
			}
		}
		if (i != imin) {
			swap(&ar[imin], &ar[i]);
		}
	}
}

/*
Функция sort_by_name
Сортирует массив сотрудников по имени в алфавитном порядке.
Параметры:
- ar: массив сотрудников.
- len: длина массива (количество записей).
*/
void sort_by_name(person *ar, int len) {
	for (int i = 0; i < len - 1; ++i) {
		int imin = i;
		for (int j = i + 1; j < len; ++j) {
			if (strcmp(ar[j].name, ar[imin].name) < 0) {
				imin = j;
			}
		}
		if (i != imin) {
			swap(&ar[imin], &ar[i]);
		}
	}
}

/*
Функция sort_by_salary
Сортирует массив сотрудников по зарплате (по возрастанию).
Параметры:
- ar: массив сотрудников.
- len: длина массива (количество записей).
*/
void sort_by_salary(person *ar, int len) {
	for (int i = 0; i < len - 1; ++i) {
		int imin = i;
		for (int j = i + 1; j < len; ++j) {
			if (ar[j].salary < ar[imin].salary) {
				imin = j;
			}
		}
		if (i != imin) {
			swap(&ar[imin], &ar[i]);
		}
	}
}

/*
Функция add_person
Добавляет нового сотрудника в массив, при необходимости расширяя память.
Параметры:
- ar: массив сотрудников.
- count: указатель на количество записей (увеличивается при добавлении).
- capacity: указатель на текущую емкость массива (увеличивается при необходимости).
Возвращает указатель на обновленный массив.
*/
person *add_person(person *ar, int *count, int *capacity) {
	if (*count >= *capacity) {
		*capacity = *capacity == 0 ? 10 : *capacity * 2;
		person *new_ar = realloc(ar, *capacity * sizeof(person));
		if (new_ar == NULL) {
			printf("Ошибка выделения памяти!\n");
			return ar;
		}
		ar = new_ar;
	}
	printf("Введите данные сотрудника (id отдел имя зарплата дата устройства(год.месяц.день) дата увольнения(год.месяц.день)): ");
	if (scanf("%d %s %s %d %d.%d.%d %d.%d.%d",
		&ar[*count].id, ar[*count].dept, ar[*count].name, &ar[*count].salary,
		&ar[*count].begin.year, &ar[*count].begin.month, &ar[*count].begin.day,
		&ar[*count].end.year, &ar[*count].end.month, &ar[*count].end.day) != 10) {
		printf("Ошибка ввода данных!\n");
		return ar;
	}
	(*count)++;
	printf("Сотрудник успешно добавлен.\n");
	return ar;
}

/*
Функция delete_person
Удаляет сотрудника из массива по ID, заменяя его последним элементом массива.
Параметры:
- ar: массив сотрудников.
- count: указатель на количество записей (уменьшается при удалении).
Возвращает указатель на обновленный массив.
*/
person *delete_person(person *ar, int *count) {
	int id;
	printf("Введите ID для удаления: ");
	if (scanf("%d", &id) != 1) {
		printf("Ошибка ввода ID!\n");
		return ar;
	}
	int found = 0;
	for (int i = 0; i < *count; i++) {
		if (ar[i].id == id) {
			found = 1;
			if (i < *count - 1) {
				ar[i] = ar[*count - 1];
			}
			(*count)--;
			printf("Сотрудник с ID %d удален.\n", id);
			break;
		}
	}
	if (!found) {
		printf("Сотрудник с ID %d не найден.\n", id);
	}
	return ar;
}

/*
Функция edit_person
Редактирует данные сотрудника по указанному ID.
Параметры:
- ar: массив сотрудников.
- count: количество записей в массиве.
Возвращает указатель на обновленный массив.
*/
person *edit_person(person *ar, int count) {
	int id;
	printf("Введите ID для редактирования: ");
	if (scanf("%d", &id) != 1) {
		printf("Ошибка ввода ID!\n");
		return ar;
	}
	int found = 0;
	for (int i = 0; i < count; i++) {
		if (ar[i].id == id) {
			found = 1;
			printf("Введите новые данные (отдел имя зарплата начало.г.м.д конец.г.м.д): ");
			if (scanf("%s %s %d %d.%d.%d %d.%d.%d",
				ar[i].dept, ar[i].name, &ar[i].salary,
				&ar[i].begin.year, &ar[i].begin.month, &ar[i].begin.day,
				&ar[i].end.year, &ar[i].end.month, &ar[i].end.day) != 9) {
				printf("Ошибка ввода данных!\n");
				return ar;
			}
			printf("Сотрудник с ID %d обновлен.\n", id);
			break;
		}
	}
	if (!found) {
		printf("Сотрудник с ID %d не найден.\n", id);
	}
	return ar;
}

/*
Функция load_from_file
Загружает данные сотрудников из текстового файла с динамическим выделением памяти.
Параметры:
- filename: имя входного файла.
- count: указатель на количество загруженных записей.
- capacity: указатель на текущую емкость массива.
Возвращает указатель на массив сотрудников или NULL в случае ошибки.
*/
person *load_from_file(const char *filename, int *count, int *capacity) {
	FILE *f_in = fopen(filename, "r");
	if (f_in == NULL) {
		printf("Ошибка открытия файла %s!\n", filename);
		return NULL;
	}
	person *ar = NULL;
	*count = 0;
	*capacity = 0;
	while (1) {
		if (*count >= *capacity) {
			*capacity = *capacity == 0 ? 10 : *capacity * 2;
			person *new_ar = realloc(ar, *capacity * sizeof(person));
			if (new_ar == NULL) {
				printf("Ошибка выделения памяти!\n");
				fclose(f_in);
				free(ar);
				return NULL;
			}
			ar = new_ar;
		}
		if (fscanf(f_in, "%d %s %s %d %d.%d.%d %d.%d.%d",
			&ar[*count].id, ar[*count].dept, ar[*count].name, &ar[*count].salary,
			&ar[*count].begin.year, &ar[*count].begin.month, &ar[*count].begin.day,
			&ar[*count].end.year, &ar[*count].end.month, &ar[*count].end.day) != 10) {
			break;
		}
		(*count)++;
	}
	fclose(f_in);
	return ar;
}
