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
        Array(std::uint32_t dimensionality, std::initializer_list<std::uint32_t> slices_counters, std::initializer_list<T>)
        {
            this->_dimensionality = dimensionality;
            this->_el_counter = new std::uint32_t[this->_dimensionality];
            std::initializer_list<std::uint32_t>::iterator el = slices_counters.begin();
            for(std::uint32_t i = 0;i<this->_dimensionality;++i)
                this->_el_counter[i] = (*el++);
            
            for(std::uint32_t i = 0;i<this->_dimensionality;++i)
            {
                
            }
        }
        Array(const Array& origin);
        Array(Array&& moved);

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