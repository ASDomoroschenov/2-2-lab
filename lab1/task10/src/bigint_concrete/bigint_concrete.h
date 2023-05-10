#ifndef BIGINT_CONCRETE_H
#define BIGINT_CONCRETE_H

#define BASE (static_cast<unsigned long>(1) << (sizeof(int) << 3))
#define UPPER_BOUND (((static_cast<long>(1)) << ((sizeof(int) << 3) - 1)) - 1)
#define LOWER_BOUND (-1 * (static_cast<long>(1)) << ((sizeof(int) << 3) - 1))

#include "bigint.h"
#include "memory.h"
#include "long_number.h"
#include "string_number.h"
#include "vector_number.h"
#include "logger.h"
#include "memory_holder.h"
#include "logger_holder.h"

class bigint_concrete : public bigint, protected memory_holder, protected logger_holder
{

private:

    memory *_allocator;
    logger *_logger;
    int _head_digit;
    size_t _size_number;
    unsigned int *_number;

private:

    enum class OPERATION
    {
        SUM,
        SUBTRACT,
        MULTIPLY,
        DIVIDE
    };

private:

    memory *get_memory() const override;

    logger *get_logger() const override;

    size_t get_size_number() const;

    static bool validate_init_value(
            const std::string &value);

    static bool gets_into_int(
            const std::string &number);

    std::string to_10() const;

    bigint *execute_operation(
            const bigint *target,
            OPERATION operation);

    explicit bigint_concrete(
            const bigint_concrete *to_copy);

public:

    vector_type get_vec_number() const;

    explicit bigint_concrete(
            const std::string &target_init,
            memory *allocator_init = nullptr,
            logger *logger_init = nullptr);

    bigint *add(
            const bigint *target_add) override;

    bigint *sum(
            const bigint *target_sum) const override;

    bigint *subtract(
            const bigint *target_sub) override;

    bigint *subtraction(
            const bigint *target_subtraction) const override;

    bigint *multiply(
            const bigint *target_multiply) override;

    bigint *multiplication(
            const bigint *target_multiplication) const override;

    bigint *divide(
            const bigint*) override;

    bigint *division(
            const bigint*) const override;

    bool lower_than(
            const bigint *target_cmp) const override;

    bool greater_than(
            const bigint *target_cmp) const override;

    bool lower_than_or_equal_to(
            const bigint *target_cmp) const override;

    bool greater_than_or_equal_to(
            const bigint *target_cmp) const override;

    bool equals(
            const bigint *target_cmp) const override;

    bool not_equals(
            const bigint *target_cmp) const override;

    ~bigint_concrete() override;

    void output() const override;

    friend std::ostream& operator<<(
            std::ostream &stream,
            const bigint_concrete *target_output);
};

#endif // BIGINT_CONCRETE_H