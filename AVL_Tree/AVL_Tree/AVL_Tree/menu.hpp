#pragma once


#include <iostream>

using namespace std;

void menu() {
	cout << "Команды:" << endl;
	cout << "[1] Опрос размера дерева" << endl;
	cout << "[2] Очистка дерева " << endl;
	cout << "[3] Проверка дерева на пустоту " << endl;
	cout << "[4] Доступ по чтению к данным по ключу" << endl;
	cout << "[5] Доступ по записи к данным по ключу" << endl;
	cout << "[6] Включение данных с заданным ключом" << endl;
	cout << "[7] Удаление данных с заданным ключом" << endl;
	cout << "[8] Вывод на экран последовательности ключей при обходе узлов дерева по схеме t → Lt → Rt" << endl;
	cout << "[9] Запрос прямого итератора" << endl;
	cout << "[10] Запрос неустановленного прямого итератора " << endl;
	cout << "[11] Доступ по чтению к текущему значению прямого итератора *" << endl;
	cout << "[12] Доступ по записи к текущему значению прямого итератора *" << endl;
	cout << "[13] it++" << endl;
	cout << "[14] Проверка равенства прямого итератора узлу с минимальным ключом" << endl;
	cout << "[15] Проверка равенства прямого итератора \"неустановленному\" прямому итератору" << endl;
	cout << "[16] Проверка неравенства прямого итератора узлу с минимальным ключом" << endl;
	cout << "[17] Проверка неравенства прямого итератора \"неустановленному\" прямому итератору" << endl;
	cout << "[18] Запрос обратного итератора" << endl;
	cout << "[19] Запрос \"неустановленного\" обратного итератора" << endl;
	cout << "[20] Операция доступа по чтению к текущему значению обратного итератора *" << endl;
	cout << "[21] Операция доступа по записи к текущему значению обратного итератора *" << endl;
	cout << "[22] rit++" << endl;
	cout << "[23] Проверка равенства обратного итератора узлу с максимальным ключом" << endl;
	cout << "[24] Проверка равенства обратного итератора \"неустановленному\" обратному итератору" << endl;
	cout << "[25] Проверка неравенства обратного итератора узлу с максимальным ключом" << endl;
	cout << "[26] Проверка неравенства обратного итератора \"неустановленному\" обратному итератору" << endl;
	cout << "[27] тест1" << endl;
	cout << "[28] тест2" << endl;
	cout << "[29] меню" << endl;
	cout << "[30] выходh" << endl;

}