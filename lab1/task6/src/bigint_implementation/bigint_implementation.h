#ifndef BIGINT_IMPLEMENTATION_H
#define BIGINT_IMPLEMENTATION_H

#define BASE (1ll << (sizeof(int) * 8))

#include <vector>
#include <tuple>
#include <cstring>

#include "bigint.h"
#include "bigint_multiplication.h"
#include "bigint_division.h"
#include "memory.h"
#include "memory_holder.h"

class bigint_implementation: public bigint, public memory_holder
{

    friend class multiplication_naive;

    friend class multiplication_karatsuba;

    friend class multiplication_schonhage_strassen;

    friend class division_burnickel_ziegler;

private:

    memory *_memory;
    int _sign;
    unsigned int *_digits;
    size_t _size_number;

private:

    //begin region help methods

    static bool check_string_number(
            std::string const &string_number);

    static bool fit_in_int(
            std::string const &string_number);

    explicit bigint_implementation(
            memory *memory_init,
            int _sign_init,
            unsigned int *digits_init,
            size_t size_number_init);

    static std::tuple<int, unsigned int*, size_t> get_representation_data(
            bigint const *target_get);

    void delete_leading_zeros();

    static void copy(
            bigint *&dest,
            bigint *src);

    //end region help methods

public:

    void output() const override;

    //begin region translate

    [[nodiscard]] std::tuple<int, unsigned int*, size_t> translate_to_array(
            std::string const &str_number) const;

    [[nodiscard]] std::string translate_to_string_number() const;

    //end region translate

    //begin region memory_holder

    [[nodiscard]] memory *get_memory() const override;

    //end region memory_holder


    //begin region addition

    bigint *add(
            bigint const *summand) override;

    //end region addition


    //begin region sum

    bigint *sum(
            bigint const *summand) const override;

    //end region sum


    //begin region subtract

    bigint *subtract(
            bigint const *subtrahend) override;

    //end region subtract


    //begin region subtraction

    bigint *subtraction(
            bigint const *subtrahend) const override;

    //end region subtraction


    //begin region shift

    bigint *shift_left(
            size_t count_digits) override;

    //end region shift


    //begin region comparison

    bool lower_than(
            bigint const *other) const override;

    bool greater_than(
            bigint const *other) const override;

    bool lower_than_or_equal_to(
            bigint const *other) const override;

    bool greater_than_or_equal_to(
            bigint const *other) const override;

    bool equals(
            bigint const *other) const override;

    bool not_equals(
            bigint const *other) const override;

    //end region comparison


    //begin region constructor

    explicit bigint_implementation(
            std::string const &string_number,
            memory *memory_init = nullptr);

    //end region constructor


    //begin region copy/move semantic

    bigint_implementation(
            bigint_implementation const &copy_target);

    bigint_implementation &operator=(
            bigint_implementation const &copy_target);

    bigint_implementation(
            bigint_implementation &&move_target) noexcept;

    bigint_implementation &operator=(
            bigint_implementation &&move_target) noexcept;

    //end region copy/move semantic


    //begin region destructor

    ~bigint_implementation() override;

    //end region destructor
};

#endif // BIGINT_IMPLEMENTATION_H