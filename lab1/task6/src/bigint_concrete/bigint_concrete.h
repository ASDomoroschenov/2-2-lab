#ifndef BIGINT_CONCRETE_H
#define BIGINT_CONCRETE_H

#define BASE (static_cast<unsigned long>(1) << (sizeof(int) << 3))
#define UPPER_BOUND (((static_cast<long>(1)) << ((sizeof(int) << 3) - 1)) - 1)
#define LOWER_BOUND (-1 * (static_cast<long>(1)) << ((sizeof(int) << 3) - 1))

#include "bigint.h"
#include "memory.h"
#include "allocator.h"
#include "long_number.h"
#include "string_number.h"
#include "vector_number.h"

class bigint_concrete final : public bigint
{
private:
    void *_number_representation;
protected:
    template<typename T>
    static std::string to_string(
            T);

    static bool validate_value(
            const std::string&);

    [[nodiscard]] void *get_representation() const override;

    static void *to_base(
            std::string,
            memory*);

    [[nodiscard]] std::string to_10() const;

    [[nodiscard]] static bool gets_into_int(
            const std::string&) ;

    [[nodiscard]] size_t get_size() const;

    static void *set_number(
            std::vector<unsigned int>,
            memory*) ;

    static bool is_int_number(
            void*) ;

    [[nodiscard]] unsigned int *get_array_digits() const;

    std::vector<unsigned int> get_vector(
            void*) const;
public:
    explicit bigint_concrete(void*);

    bigint_concrete(
            const std::string&,
            memory*);
    
    bigint *add(
            const bigint*) override;

    bigint *sum(
            const bigint*) const override;

    bigint *subtract(
            const bigint*) override;

    bigint *subtraction(
            const bigint*) const override;

    bool lower_than(
            const bigint*) const override;

    bool greater_than(
            const bigint*) const override;
    
    bool lower_than_or_equal_to(
            const bigint*) const override;

    bool greater_than_or_equal_to(
            const bigint*) const override;

    bool equals(
            const bigint*) const override;

    bool not_equals(
            const bigint*) const override;

    ~bigint_concrete() override;

    friend std::ostream& operator<<(
            std::ostream&,
            const bigint_concrete*);
};

#endif // BIGINT_CONCRETE_H