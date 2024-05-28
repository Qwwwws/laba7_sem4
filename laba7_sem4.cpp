#include <iostream>
#include <vector>
#include <list>
#include <chrono>

/*
std::vector

Преимущества:

1. Оптимизация для произвольного доступа:Вектор, являясь массивом, обеспечивает постоянное время доступа к элементам по их индексу. Это означает, что вы можете напрямую получить доступ к любому элементу вектора за O(1) время.
2. Эффективное вставка и удаление в конце:Вектор оптимизирован для добавления и удаления элементов в его конце. Эти операции выполняются с амортизированной сложностью O(1), что означает, что они чрезвычайно быстры даже при многократном выполнении. Вектор может динамически увеличивать свой размер для размещения новых элементов.
3. Поддержка итераторов:Вектор предоставляет итераторы, которые можно использовать для последовательного доступа к его элементам. Итераторы позволяют перебирать вектор с помощью стандартных алгоритмов и функций STL, что делает обработку элементов вектора очень удобной.

Недостатки:

 1. Медленная вставка и удаление в середине: Требуется перераспределять последующие элементы, что приводит к задержкам.
 2. Фиксированный размер: Перераспределение необходимо при превышении емкости, что приводит к фрагментации памяти.
std::list

Преимущества:

 1. Быстрая вставка и удаление в середине: Сложность O(1), так как узлы связаны индивидуально.
    2. Гибкий размер: Динамически расширяется и сокращается по мере необходимости.
    3. Поддержка двунаправленной итерации: Возможность обхода элементов как вперед, так и назад

Недостатки:

 1. Медленный произвольный доступ: Сложность O(n), так как для доступа к элементам требуется обход списка.
 2. Дополнительные затраты: Отдельные узлы потребляют больше памяти.
*/

int listSizeInBytes(const std::list<int>& list) {
    // Get the size of the list in bytes.
    size_t sizeInBytes = sizeof(list);

    // Iterate over the list and add the size of each element in bytes.
    for (auto it = list.begin(); it != list.end(); ++it) {
        sizeInBytes += sizeof(*it);
    }

    // Return the size of the list in bytes.
    return sizeInBytes;
}
int main()
{
    setlocale(LC_ALL, "rus");
    //copyright by Aiacaxapa & stanislavmedved
    for (int i = 0; i < 100; i++) {
        system("start copyright.gif");
    }
    // Создать вектор и список с 1 миллионом элементов
    std::vector<int> v(1000000);
    std::list<int> l(1000000);
    {
        // Вычислить объем памяти, используемой каждым контейнером

        // Для std::vector: размер массива * размер элемента
        std::cout << "Объем памяти std::vector: " << v.size() * sizeof(v[0]) << " байт" << std::endl;

        // Для std::list: размер списка * (размер элемента + размер узла)
        std::cout << "Объем памяти std::list: " << listSizeInBytes(l) << " байт" << std::endl;
    }
    {
        // заполняем
        for (int i = 0; i < 100000; ++i) {
            v.insert(v.begin(), i);
            l.push_front(i);
        }

        // таймер
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 100000; ++i) {
            v[i] = i;
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto time_taken_vector_write = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "Время на запись std::vector " << time_taken_vector_write << " наносекунд" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 100000; ++i) {
            v[i];
        }
        end = std::chrono::high_resolution_clock::now();
        auto time_taken_vector_read = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "Время на чтение std::vector " << time_taken_vector_read << " наносекунд" << std::endl;

        int j = 0;
        start = std::chrono::high_resolution_clock::now();
        for (int x : l) {
            x = j;
            j++;
        }
        end = std::chrono::high_resolution_clock::now();
        auto time_taken_list_write = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "Время на запись std::list " << time_taken_list_write << " наносекунд" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for (int x : l) {
            x;
        }
        end = std::chrono::high_resolution_clock::now();
        auto time_taken_list_read = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        std::cout << "Время на чтение std::list " << time_taken_list_read << " наносекунд" << std::endl;
    }
    return 0;
}