#include "cstringstack.h"
#include <iostream>

int main() {
    // Создаем объект CStringStack
    CStringStack stack;

    // Добавляем несколько строк в стек
    stack.push("Hello");
    stack.push("World");
    stack.push("C++");

    // Выводим верхний элемент стека
    std::cout << "Top element: " << stack.top() << std::endl;

    // Удаляем верхний элемент стека
    stack.pop();

    // Выводим верхний элемент стека после удаления
    std::cout << "Top element after pop: " << stack.top() << std::endl;

    // Проверяем, пуст ли стек
    if (stack.is_empty()) {
        std::cout << "Stack is empty." << std::endl;
    }
    else {
        std::cout << "Stack is not empty." << std::endl;
    }

    // Добавляем еще одну строку в стек
    stack.push("Programming");

    // Выводим верхний элемент стека
    std::cout << "Top element after push: " << stack.top() << std::endl;

    // Создаем копию стека с использованием конструктора копирования
    CStringStack stack_copy(stack);

    // Выводим верхний элемент копии стека
    std::cout << "Top element of stack copy: " << stack_copy.top() << std::endl;

    // Создаем перемещенный стек с использованием конструктора перемещения
    CStringStack stack_moved(std::move(stack_copy));

    // Выводим верхний элемент перемещенного стека
    std::cout << "Top element of moved stack: " << stack_moved.top() << std::endl;

    // Проверяем, пуст ли копируемый стек после перемещения
    if (stack_copy.is_empty()) {
        std::cout << "Stack copy is empty after move." << std::endl;
    }

    // Завершение программы
    return 0;
}
