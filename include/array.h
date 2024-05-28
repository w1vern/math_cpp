#pragma once

#include <iostream>
#include <cstdint>

namespace mth
{
    template <class T>
    class Array
    {
    public:
        Array()
        {
            _array = nullptr;
            _el_counter = nullptr;
            dimensionality = 0;
        }
        Array(std::uint32_t dimensionality, std::initializer_list<std::uint32_t> slices_counters, std::initializer_list<T> vars)
        {
            this->_dimensionality = dimensionality;
            this->_el_counter = new std::uint32_t[this->_dimensionality];
            std::initializer_list<std::uint32_t>::iterator el = slices_counters.begin();
            for(std::uint32_t i = 0;i<this->_dimensionality;++i)
                this->_el_counter[i] = (*el++);
            
            std::uint64_t memory = 1;
            for (std::uint32_t i = 0;i<_dimensionality;++i)
                memory *= _el_counter[i];
            _array = new T[memory];

            memory = 0;
            std::initializer_list<T>::iterator var = vars.begin();
            for(std::uint32_t i = 0;i<_dimensionality;++i)
                for(std::uint32_t j = 0;j<_el_counter[i];++j)
                    ((T*)_array)[memory++] = (*el++);
        }
        Array(const Array& origin)
        {
            std::uint64_t memory = 1;
            for (std::uint32_t i = 0;i<origin._dimensionality;++i)
                memory *= origin._el_counter[i];
            _array = new T[memory];  

            memory = 0;
            for(std::uint32_t i = 0;i<origin._dimensionality;++i)
                for(std::uint32_t j = 0;j<origin._el_counter[i];++j)
                {
                    ((T*)_array)[memory] = ((T*)origin._array[memory]);
                    ++memory;
                }
        }
        Array(Array&& moved)
        {
            _dimensionality = moved._dimensionality;
            moved._dimensionality = 0;

            _el_counter = moved._el_counter;
            moved._el_counter = nullptr;

            _array = moved._array;
            moved._array = nullptr;
        }

        ~Array();

        Array& operator[](std::uint32_t index);

        Array operator=(const Array& origin);
        Array operator=(Array&& moved);

        std::uint32_t size(std::uint32_t index);
    private:
        void* _array;
        std::uint32_t* _el_counter;
        std::uint32_t _dimensionality;
    };

}