#pragma once

#include <unordered_map>
#include <utility>
#include <iostream>
#include <functional>

template <typename T>
class SparseMatrix
{
    public:

        SparseMatrix(T const& default_val = T())
            : default_val(default_val)
        {   
        }   

        T const& get(int a, int b) const
        {   
            auto key    = getKey(a, b); 
            auto search = data.find(key);
            if (search != data.end())
                return search->second;
            return default_val;
        }   

        void set(int a, int b, T const& val)
        {   
            data.insert(std::make_pair(getKey(a,b), val));
        }   
        void set(int a, int b, T&& val)
        {   
            data.insert(std::make_pair(getKey(a,b), std::move(val)));
        }

        class Row 
        {   
            SparseMatrix const* parent;
            int a;

            public:
            Row(SparseMatrix const* parent, int a)
                : parent(parent)
                , a(a)
            {}  
            T const& operator[](int b) const
            {   
                return parent->get(a, b); 
            }   
        };  
        Row operator[](int a) const {
            return Row{this, a}; 
        }   


    private:
        T default_val;
        using Key = std::pair<int, int>;
        struct PairHash
        {   
            std::size_t operator()(Key const& key) const
            {   
                return std::hash<int>()(key.first) ^ std::hash<int>()(key.second);
            }   
        };  


        Key getKey(int a, int b) const {

            int x = std::min(a, b); 
            int y = std::max(a, b); 
            return std::make_pair(x, y); 
        }   

        std::unordered_map<Key, T, PairHash>  data;
};
