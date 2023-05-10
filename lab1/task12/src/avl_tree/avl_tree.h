#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "binary_search_tree.h"
#include <iostream>

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
class avl_tree : public binary_search_tree<tkey, tvalue, tkey_comparer>
{

protected:

    struct avl_node : binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node
    {
        size_t height = 0;
    };

protected:

    class avl_insertion_template_method : public binary_search_tree<tkey, tvalue, tkey_comparer>::bin_insertion_template_method
    {

    private:

        size_t get_node_size() const override;

    private:

        avl_tree<tkey, tvalue, tkey_comparer> *_tree;

    protected:

        void after_insert_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node**> &path_to_subtree_root_exclusive) override;

    public:

        explicit avl_insertion_template_method(
                avl_tree<tkey, tvalue, tkey_comparer> *tree);

    };

    class avl_removing_template_method : public binary_search_tree<tkey, tvalue, tkey_comparer>::bin_removing_template_method
    {

    private:

        avl_tree<tkey, tvalue, tkey_comparer> *_tree;

    protected:

        void after_remove_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node**> &path_to_subtree_root_exclusive) override;

    public:

        explicit avl_removing_template_method(
                avl_tree<tkey, tvalue, tkey_comparer> *tree);

    };

public:

    explicit avl_tree(
            memory *allocator_binary_search_tree = nullptr,
            logger *logger_tree = nullptr);

    ~avl_tree() final;

private:

    int get_height(
            typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node *node);

    void fix_height(
            typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node **subtree_address);

    size_t balance_factor(
            typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node *subtree_address);

public:

    avl_tree(
            const avl_tree<tkey, tvalue, tkey_comparer> &target_copy);

    avl_tree& operator=(
            const avl_tree<tkey, tvalue, tkey_comparer> &target_copy);

    avl_tree(
            avl_tree<tkey, tvalue, tkey_comparer> &&target_copy) noexcept;

    avl_tree& operator=(
            avl_tree<tkey, tvalue, tkey_comparer> &&target_copy) noexcept;

};

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
int avl_tree<tkey, tvalue, tkey_comparer>::get_height(
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node *node)
{
    return node == nullptr ? 0 : reinterpret_cast<avl_node*>(node)->height;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::fix_height(
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node **subtree_address)
{
    size_t height_left = *subtree_address != nullptr ? get_height((*subtree_address)->left_subtree) : 0;
    size_t height_right = *subtree_address != nullptr ? get_height((*subtree_address)->right_subtree) : 0;

    if (*subtree_address != nullptr)
    {
        reinterpret_cast<avl_node*>(*subtree_address)->height = std::max(height_left, height_right) + 1;
    }
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
size_t avl_tree<tkey, tvalue, tkey_comparer>::balance_factor(
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node *subtree_address)
{
    size_t height_left = get_height(subtree_address->left_subtree);
    size_t height_right = get_height(subtree_address->right_subtree);

    return height_left - height_right;
}

//begin region after_insert_inner

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
size_t avl_tree<tkey, tvalue, tkey_comparer>::avl_insertion_template_method::get_node_size() const
{
    return sizeof(avl_node);
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::avl_insertion_template_method::after_insert_inner(
        tkey const &key,
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node *&subtree_root_address,
        std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node**> &path_to_subtree_root_exclusive)
{
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node **parent = nullptr;

    if (!path_to_subtree_root_exclusive.empty())
    {
        parent = path_to_subtree_root_exclusive.top();
        path_to_subtree_root_exclusive.pop();
    }

    _tree->fix_height(&subtree_root_address);
    size_t bal_factor = _tree->balance_factor(subtree_root_address);

    if (bal_factor == 2)
    {
        if (_tree->balance_factor(subtree_root_address->left_subtree) == -1)
        {
            _tree->left_rotate(&(subtree_root_address->left_subtree), &subtree_root_address);
            _tree->fix_height(&(subtree_root_address->left_subtree));
            _tree->fix_height(&(subtree_root_address->left_subtree->right_subtree));
        }

        _tree->right_rotate(&subtree_root_address, parent);
        _tree->fix_height(&subtree_root_address);
        _tree->fix_height(&(subtree_root_address->left_subtree));
    }

    if (bal_factor == -2)
    {
        if (_tree->balance_factor(subtree_root_address->right_subtree) == 1)
        {
            _tree->right_rotate(&(subtree_root_address->right_subtree), &subtree_root_address);
            _tree->fix_height(&(subtree_root_address->right_subtree));
            _tree->fix_height(&(subtree_root_address->right_subtree->left_subtree));
        }

        _tree->left_rotate(&subtree_root_address, parent);
        _tree->fix_height(&subtree_root_address);
        _tree->fix_height(&(subtree_root_address->right_subtree));
    }

    if (parent != nullptr)
    {
        path_to_subtree_root_exclusive.push(parent);
    }
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::avl_insertion_template_method::avl_insertion_template_method(
        avl_tree<tkey, tvalue, tkey_comparer> *tree) :
        _tree(tree),
        binary_search_tree<tkey, tvalue, tkey_comparer>::bin_insertion_template_method(tree)
{

}

//end region after_insert_inner


//begin region after_remove_inner

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void avl_tree<tkey, tvalue, tkey_comparer>::avl_removing_template_method::after_remove_inner(
        tkey const &key,
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node *&subtree_root_address,
        std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node**> &path_to_subtree_root_exclusive)
{
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_node **parent = nullptr;

    if (!path_to_subtree_root_exclusive.empty())
    {
        parent = path_to_subtree_root_exclusive.top();
        path_to_subtree_root_exclusive.pop();
    }

    _tree->fix_height(&subtree_root_address);
    size_t bal_factor = _tree->balance_factor(subtree_root_address);

    if (bal_factor == 2)
    {
        if (_tree->balance_factor(subtree_root_address->left_subtree) == -1)
        {
            _tree->left_rotate(&(subtree_root_address->left_subtree), &subtree_root_address);
            _tree->fix_height(&(subtree_root_address->left_subtree));
            _tree->fix_height(&(subtree_root_address->left_subtree->right_subtree));
        }

        _tree->right_rotate(&subtree_root_address, parent);
        _tree->fix_height(&subtree_root_address);
        _tree->fix_height(&(subtree_root_address->left_subtree));
    }

    if (bal_factor == -2)
    {
        if (_tree->balance_factor(subtree_root_address->right_subtree) == 1)
        {
            _tree->right_rotate(&(subtree_root_address->right_subtree), &subtree_root_address);
            _tree->fix_height(&(subtree_root_address->right_subtree));
            _tree->fix_height(&(subtree_root_address->right_subtree->left_subtree));
        }

        _tree->left_rotate(&subtree_root_address, parent);
        _tree->fix_height(&subtree_root_address);
        _tree->fix_height(&(subtree_root_address->right_subtree));
    }

    if (parent != nullptr)
    {
        path_to_subtree_root_exclusive.push(parent);
    }
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::avl_removing_template_method::avl_removing_template_method(
        avl_tree<tkey, tvalue, tkey_comparer> *tree) :
        _tree(tree),
        binary_search_tree<tkey, tvalue, tkey_comparer>::bin_removing_template_method(tree)
{

}

//end region after_remove_inner


//begin region constructor

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::avl_tree(
        memory *allocator_binary_search_tree,
        logger *logger_tree) :
        binary_search_tree<tkey, tvalue, tkey_comparer>(
                new typename binary_search_tree<tkey, tvalue, tkey_comparer>::bin_find_template_method(),
                new avl_insertion_template_method(this),
                new avl_removing_template_method(this),
                allocator_binary_search_tree,
                logger_tree,
                nullptr)
{

}

//end region constructor


//begin region destructor

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::~avl_tree()
{

}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::avl_tree(
        const avl_tree<tkey, tvalue, tkey_comparer> &target_copy) :
        binary_search_tree<tkey, tvalue, tkey_comparer>(
                this->_find,
                this->_insertion,
                this->_removing,
                this->_allocator,
                this->_logger,
                this->_root)
{

}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>& avl_tree<tkey, tvalue, tkey_comparer>::operator=(
        const avl_tree<tkey, tvalue, tkey_comparer> &target_copy)
{
    *this = target_copy;

    return *this;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>::avl_tree(
        avl_tree<tkey, tvalue, tkey_comparer> &&target_copy) noexcept
{
    *this = std::move(target_copy);
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
avl_tree<tkey, tvalue, tkey_comparer>& avl_tree<tkey, tvalue, tkey_comparer>::operator=(
        avl_tree<tkey, tvalue, tkey_comparer> &&target_copy) noexcept
{
    *this = std::move(target_copy);

    return *this;
}

//end region destructor

#endif // AVL_TREE_H