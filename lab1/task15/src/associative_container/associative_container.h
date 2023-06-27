#ifndef ASSOCIATIVE_CONTAINER_H
#define ASSOCIATIVE_CONTAINER_H

#include <utility>

template<
        typename tkey,
        typename tvalue>
class associative_container
{

public:

    struct key_value_pair
    {
        tkey _key;
        tvalue _value;
    };

public:

    virtual void insert(
            tkey const &key,
            tvalue &&value) = 0;

    void operator+=(
            key_value_pair pair);

    virtual bool in(
            tkey const &key) const = 0;

    virtual tvalue get(
            tkey const &key) const = 0;

    tvalue operator[](
            tkey const &key) const;

    virtual tvalue remove(
            tkey const &key) = 0;

    tvalue operator-=(
            key_value_pair pair);

    tvalue operator-=(
            tkey const &key);

    virtual ~associative_container() = default;

};

template<
        typename tkey,
        typename tvalue>
tvalue associative_container<tkey, tvalue>::operator[](
        tkey const &key) const
{
    if (in(key))
    {
        return get(key);
    }

    throw std::invalid_argument("ERROR: There is no such item");
}

template<
        typename tkey,
        typename tvalue>
void associative_container<tkey, tvalue>::operator+=(
        key_value_pair pair)
{
    return insert(pair._key, std::move(pair._value));
}

template<
        typename tkey,
        typename tvalue>
tvalue associative_container<tkey, tvalue>::operator-=(
        key_value_pair pair)
{
    return remove(pair._key);
}

template<
        typename tkey,
        typename tvalue>
tvalue associative_container<tkey, tvalue>::operator-=(
        tkey const &key)
{
    return remove(key);
}

#endif //ASSOCIATIVE_CONTAINER_H