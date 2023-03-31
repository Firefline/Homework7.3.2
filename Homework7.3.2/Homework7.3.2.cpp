// Homework7.3.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <random>
#include <iterator>
#include <future>
#include <algorithm>

void get_vector(std::vector<int>& vector_, int size_)
{
    std::random_device rd;
    std::mt19937 gen{ rd() };
    std::uniform_int_distribution <> dis(0, 100);

    int value = dis(gen);

    for (int i = 0; i < size_; ++i)
    {
        vector_.push_back(value);
        value = dis(gen);
    }
}

void f_each(std::vector<int>::iterator &it_begin, std::vector<int>::iterator &it_end, void (&function)(int))
{
    std::vector<int> vec_test(it_begin, it_end);
    std::vector<int>::iterator it = vec_test.begin();

    while (it != vec_test.end())
    {
        function(*it);
        ++it;
    };
}

template<typename It, typename T>
T each(It begin, It end, T init)
{
    const int length = distance(begin, end);
    It middle = begin;
    std::for_each(middle, length / 2, init);
    std::future<T> res_first_half = std::async(each<It, T>, begin, middle, init);
    T res_second_half = each(middle, end, T());
    return res_first_half.get() + res_second_half;
}

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");

    std::vector<int> vec;

    get_vector(vec, 10);

    int result = each(vec.begin(), vec.end(), 0);
}