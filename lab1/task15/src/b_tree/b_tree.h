#ifndef B_TREE_H
#define B_TREE_H

#include "associative_container.h"
#include "memory.h"
#include "memory_holder.h"
#include "logger.h"
#include "logger_holder.h"
#include <stack>

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
class b_tree final: public associative_container<tkey, tvalue>, public logger_holder, public memory_holder
{

private:

    struct b_tree_node
    {
        std::vector<std::pair<tkey, tvalue>> key_value_pairs;
        std::vector<b_tree_node*> subtrees;
        size_t current_number_keys;
        bool is_leaf;
    };

public:

    class search_template_method final: public logger_holder
    {

    private:

        b_tree *_tree;

    private:

        logger *get_logger() const override;

    public:

        explicit search_template_method(
                b_tree *tree_init);

        tvalue search(
                tkey const &key);

    };

    class insertion_template_method final: public logger_holder, public memory_holder
    {

    private:

        b_tree *_tree;

    private:

        logger *get_logger() const override;

        memory *get_memory() const override;

    public:

        explicit insertion_template_method(
                b_tree *tree_init);

        void insert(
                tkey const &key,
                tvalue &&value);

    };

    class removal_template_method final: public logger_holder, public memory_holder
    {

    private:

        b_tree *_tree;

    private:

        logger *get_logger() const override;

        memory *get_memory() const override;

    public:

        explicit removal_template_method(
                b_tree *tree_init);

        tvalue remove(
                tkey const &key);

    private:

        tvalue remove_inner(
                tkey const &key,
                size_t index_target,
                b_tree_node *&subtree_address,
                std::stack<b_tree_node**> &path);
    };

public:

    logger *get_logger() const override;

    memory *get_memory() const override;

    void insert(
            tkey const &key,
            tvalue &&value) override;

    bool in(
            tkey const &key) const override;

    tvalue get(
            tkey const &key) const override;

    tvalue remove(
            tkey const &key) override;

    void split(
            b_tree_node **target_split,
            std::stack<b_tree_node**> &path);

    void merge(
            b_tree_node **target_merge,
            std::stack<b_tree_node**> &path);

    void insert_in_leaf(
            tkey const &key,
            tvalue &&value,
            b_tree_node *&leaf);

    void delete_node(
            b_tree_node *&target_delete);

    void copy_node(
            b_tree_node *&dest_copy,
            b_tree_node *&src_copy);

public:

    explicit b_tree(
            size_t number_keys_init,
            logger *logger_init = nullptr,
            memory *memory_init = nullptr);

public:

    b_tree(
            const b_tree &copy_target);

    b_tree &operator=(
            const b_tree &copy_target);

    b_tree(
            b_tree &&move_target) noexcept;

    b_tree &operator=(
            b_tree &&move_target) noexcept;

    ~b_tree();

private:

    logger *_logger{};
    memory *_memory{};
    size_t _number_keys{};
    b_tree_node *_root;
    tkey_comparer _comparator;
    search_template_method *_search;
    insertion_template_method *_insertion;
    removal_template_method *_removal;

};


//begin search_template_method

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
logger *b_tree<tkey, tvalue, tkey_comparer>::search_template_method::get_logger() const
{
    return _tree->_logger;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
b_tree<tkey, tvalue, tkey_comparer>::search_template_method::search_template_method(
        b_tree *tree_init) :
        _tree(tree_init)
{

}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
tvalue b_tree<tkey, tvalue, tkey_comparer>::search_template_method::search(
        tkey const &key)
{
    b_tree_node *node_search = _tree->_root;

    while (node_search != nullptr)
    {
        int i = 0;

        while (i < node_search->current_number_keys &&
               _tree->_comparator(key, node_search->key_value_pairs[i].first) > 0)
        {
            i++;
        }

        if (i < node_search->current_number_keys &&
            _tree->_comparator(key, node_search->key_value_pairs[i].first) == 0)
        {
            return node_search->key_value_pairs[i].second;
        }
        else
        {
            node_search = node_search->subtrees[i];
        }
    }

    throw std::invalid_argument("ERROR: There is no such item");
}

//end search_template_method


//begin insertion_template_method

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
logger *b_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::get_logger() const
{
    return _tree->_logger;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
memory *b_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::get_memory() const
{
    return _tree->_memory;
}


template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
b_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::insertion_template_method(
        b_tree *tree_init) :
        _tree(tree_init)
{

}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void b_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::insert(
        tkey const &key,
        tvalue &&value)
{
    if (_tree->_root == nullptr)
    {
        _tree->_root = reinterpret_cast<b_tree_node*>(allocate_with_guard(sizeof(b_tree_node)));
        new (_tree->_root) b_tree_node{std::vector<std::pair<tkey, tvalue>>(), std::vector<b_tree_node*>(), 1, true};
        _tree->_root->key_value_pairs.push_back({key, std::move(value)});
        _tree->_root->subtrees.push_back(nullptr);
        _tree->_root->subtrees.push_back(nullptr);

        return;
    }

    std::stack<b_tree_node**> path;
    path.push(&_tree->_root);
    b_tree_node *node_to_insert = _tree->_root;

    while (!node_to_insert->is_leaf)
    {
        int i = node_to_insert->current_number_keys - 1;

        while (i >= 0 && _tree->_comparator(key, node_to_insert->key_value_pairs[i].first) < 0)
        {
            i--;
        }

        path.push(&node_to_insert->subtrees[i + 1]);
        node_to_insert = node_to_insert->subtrees[i + 1];
    }

    path.pop();

    _tree->insert_in_leaf(key,
                          std::move(value),
                          node_to_insert);

    if (node_to_insert->current_number_keys == _tree->_number_keys * 2 - 1)
    {
        _tree->split(&node_to_insert, path);
    }
}

//end insertion_template_method


//begin removal_template_method

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
logger *b_tree<tkey, tvalue, tkey_comparer>::removal_template_method::get_logger() const
{
    return _tree->_logger;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
memory *b_tree<tkey, tvalue, tkey_comparer>::removal_template_method::get_memory() const
{
    return _tree->_memory;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
b_tree<tkey, tvalue, tkey_comparer>::removal_template_method::removal_template_method(
        b_tree *tree_init) :
        _tree(tree_init)
{

}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
tvalue b_tree<tkey, tvalue, tkey_comparer>::removal_template_method::remove(
        tkey const &key)
{
    b_tree_node *node_remove = _tree->_root;

    std::stack<b_tree_node**> path;
    path.push(&_tree->_root);

    while (node_remove != nullptr)
    {
        int i = 0;

        while (i < node_remove->current_number_keys &&
               _tree->_comparator(key, node_remove->key_value_pairs[i].first) > 0)
        {
            i++;
        }

        if (i < node_remove->current_number_keys &&
            _tree->_comparator(key, node_remove->key_value_pairs[i].first) == 0)
        {
            path.pop();
            return remove_inner(key, i, node_remove, path);
        }
        else
        {
            path.push(&node_remove->subtrees[i]);
            node_remove = node_remove->subtrees[i];
        }
    }

    throw std::invalid_argument("ERROR: There is no such item");
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
tvalue b_tree<tkey, tvalue, tkey_comparer>::removal_template_method::remove_inner(
        tkey const &key,
        size_t index_target,
        b_tree_node *&subtree_address,
        std::stack<b_tree_node**> &path)
{
    tvalue removed_value;

    removed_value = subtree_address->key_value_pairs[index_target].second;

    if (subtree_address->is_leaf)
    {
        subtree_address->key_value_pairs.erase(subtree_address->key_value_pairs.begin() + index_target);
        subtree_address->subtrees.erase(subtree_address->subtrees.begin() + index_target);
        subtree_address->current_number_keys--;

        if (!path.empty())
        {
            if(subtree_address->current_number_keys < _tree->_number_keys - 1)
            {
                b_tree_node **parent = path.top();
                b_tree_node *left_neighbor = nullptr;
                b_tree_node *right_neighbor = nullptr;
                int index_subtree = 0;

                while (index_subtree < (*parent)->subtrees.size() &&
                       (*parent)->subtrees[index_subtree] != subtree_address)
                {
                    index_subtree++;
                }

                if (index_subtree > 0)
                {
                    left_neighbor = (*parent)->subtrees[index_subtree - 1];
                }

                if (index_subtree < (*parent)->subtrees.size() - 1)
                {
                    right_neighbor = (*parent)->subtrees[index_subtree + 1];
                }

                if ((left_neighbor != nullptr && left_neighbor->current_number_keys > _tree->_number_keys - 1) ||
                    (right_neighbor != nullptr && right_neighbor->current_number_keys > _tree->_number_keys - 1))
                {
                    if (left_neighbor != nullptr && left_neighbor->current_number_keys > _tree->_number_keys - 1)
                    {
                        std::pair<tkey, tvalue> replacement_parent_value = left_neighbor->key_value_pairs.back();
                        std::pair<tkey, tvalue> parent_value = std::move((*parent)->key_value_pairs[index_subtree - 1]);

                        _tree->insert_in_leaf(parent_value.first, std::move(parent_value.second), subtree_address);
                        (*parent)->key_value_pairs[index_subtree - 1] = replacement_parent_value;

                        remove_inner(replacement_parent_value.first,
                                     left_neighbor->current_number_keys - 1,
                                     left_neighbor,
                                     path);
                    }
                    else
                    {
                        std::pair<tkey, tvalue> replacement_parent_value = right_neighbor->key_value_pairs.front();
                        std::pair<tkey, tvalue> parent_value = std::move((*parent)->key_value_pairs[index_subtree]);

                        _tree->insert_in_leaf(parent_value.first, std::move(parent_value.second), subtree_address);
                        (*parent)->key_value_pairs[index_subtree] = replacement_parent_value;

                        remove_inner(replacement_parent_value.first,
                                     0,
                                     right_neighbor,
                                     path);
                    }
                }
                else
                {
                    _tree->merge(&subtree_address, path);
                }
            }
        }
        else
        {
            if (subtree_address->current_number_keys == 0)
            {
                subtree_address->~b_tree_node();
                deallocate_with_guard(subtree_address);
                subtree_address = nullptr;
            }
        }
    }
    else
    {
        b_tree_node *left_child_node = subtree_address->subtrees[index_target];
        b_tree_node *right_child_node = subtree_address->subtrees[index_target + 1];

        if (left_child_node->current_number_keys > _tree->_number_keys - 1)
        {
            subtree_address->key_value_pairs[index_target].first = left_child_node->key_value_pairs[left_child_node->key_value_pairs.size() - 1].first;
            subtree_address->key_value_pairs[index_target].second = std::move(left_child_node->key_value_pairs[left_child_node->key_value_pairs.size() - 1].second);

            path.push(&subtree_address);

            remove_inner(subtree_address->key_value_pairs[index_target].first, left_child_node->key_value_pairs.size() - 1, left_child_node, path);
        }
        else if (right_child_node->current_number_keys > _tree->_number_keys - 1)
        {
            subtree_address->key_value_pairs[index_target].first = right_child_node->key_value_pairs[0].first;
            subtree_address->key_value_pairs[index_target].second = std::move(right_child_node->key_value_pairs[0].second);

            path.push(&subtree_address);

            remove_inner(subtree_address->key_value_pairs[index_target].first, 0, right_child_node, path);
        }
        else
        {
            path.push(&subtree_address);
            _tree->merge(&right_child_node, path);
            right_child_node = left_child_node;
            int index = 0;

            while (index < right_child_node->key_value_pairs.size() &&
                   _tree->_comparator(right_child_node->key_value_pairs[index].first, key) != 0)
            {
                index++;
            }

            remove_inner(key, index, right_child_node, path);
        }
    }

    return removed_value;
}

//end removal_template_method


//begin functional_container

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
logger *b_tree<tkey, tvalue, tkey_comparer>::get_logger() const
{
    return _logger;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
memory *b_tree<tkey, tvalue, tkey_comparer>::get_memory() const
{
    return _memory;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void b_tree<tkey, tvalue, tkey_comparer>::insert(
        tkey const &key,
        tvalue &&value)
{
    return _insertion->insert(key, std::move(value));
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
bool b_tree<tkey, tvalue, tkey_comparer>::in(
        tkey const &key) const
{
    try
    {
        _search->search(key);
    }
    catch (std::exception const &ex)
    {
        return false;
    }

    return true;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
tvalue b_tree<tkey, tvalue, tkey_comparer>::get(
        tkey const &key) const
{
    return _search->search(key);;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
tvalue b_tree<tkey, tvalue, tkey_comparer>::remove(
        tkey const &key)
{
    return _removal->remove(key);
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void b_tree<tkey, tvalue, tkey_comparer>::split(
        b_tree_node **target_split,
        std::stack<b_tree_node**> &path)
{
    if ((*target_split)->current_number_keys == _number_keys * 2 - 1)
    {
        std::pair<tkey, tvalue> upper_value = (*target_split)->key_value_pairs[_number_keys - 1];
        auto *right_node = reinterpret_cast<b_tree_node*>(allocate_with_guard(sizeof(b_tree_node)));
        new (right_node) b_tree_node{};

        right_node->current_number_keys = _number_keys - 1;
        right_node->is_leaf = (*target_split)->is_leaf;
        right_node->key_value_pairs = std::vector<std::pair<tkey, tvalue>>((*target_split)->key_value_pairs.begin() + _number_keys, (*target_split)->key_value_pairs.end());
        right_node->subtrees = std::vector<b_tree_node*>((*target_split)->subtrees.begin() + _number_keys, (*target_split)->subtrees.end());

        (*target_split)->current_number_keys = _number_keys - 1;
        (*target_split)->key_value_pairs = std::vector<std::pair<tkey, tvalue>>((*target_split)->key_value_pairs.begin(), (*target_split)->key_value_pairs.begin() + _number_keys - 1);
        (*target_split)->subtrees = std::vector<b_tree_node*>((*target_split)->subtrees.begin(), (*target_split)->subtrees.begin() + _number_keys);

        if (path.empty())
        {
            auto *new_root = reinterpret_cast<b_tree_node*>(allocate_with_guard(sizeof(b_tree_node)));
            new (new_root) b_tree_node{};

            new_root->key_value_pairs.push_back(upper_value);
            new_root->is_leaf = false;
            new_root->current_number_keys = 1;
            new_root->subtrees.push_back(*target_split);
            new_root->subtrees.push_back(right_node);

            _root = new_root;

            path.push(&_root);
        }
        else
        {
            b_tree_node **parent = path.top();
            path.pop();

            int i = (*parent)->current_number_keys - 1;
            int j = (*parent)->current_number_keys;

            (*parent)->key_value_pairs.resize((*parent)->key_value_pairs.size() + 1);
            (*parent)->subtrees.resize((*parent)->subtrees.size() + 1);

            while (i >= 0 && _comparator(upper_value.first, (*parent)->key_value_pairs[i].first) < 0)
            {
                (*parent)->key_value_pairs[i + 1] = std::move((*parent)->key_value_pairs[i]);
                (*parent)->subtrees[j + 1] = (*parent)->subtrees[j];
                i--;
                j--;
            }

            (*parent)->key_value_pairs[i + 1] = std::move(upper_value);
            (*parent)->subtrees[j + 1] = right_node;
            (*parent)->current_number_keys++;
            
            if ((*parent)->current_number_keys == _number_keys * 2 - 1)
            {
                split(parent, path);
            }

            path.push(parent);
        }
    }
    else
    {
        throw std::invalid_argument("ERROR: This node does not need to be splitted");
    }
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void b_tree<tkey, tvalue, tkey_comparer>::merge(
        b_tree_node **target_merge,
        std::stack<b_tree_node**> &path)
{
    if (!path.empty())
    {
        std::vector<b_tree_node*> unit_subtrees = std::move((*target_merge)->subtrees);
        std::vector<std::pair<tkey, tvalue>> unit_key_value_pairs = std::move((*target_merge)->key_value_pairs);
        std::pair<tkey, tvalue> sift_key_value_pair;

        b_tree_node **parent = path.top();
        b_tree_node *left_neighbor = nullptr;
        b_tree_node *right_neighbor = nullptr;

        path.pop();

        int index = 0;

        while (index < (*parent)->subtrees.size() &&
               (*parent)->subtrees[index] != *target_merge)
        {
            index++;
        }

        if (index > 0)
        {
            left_neighbor = (*parent)->subtrees[index - 1];
        }

        if (index < (*parent)->subtrees.size() - 1)
        {
            right_neighbor = (*parent)->subtrees[index + 1];
        }

        if (index == 0)
        {
            sift_key_value_pair = std::move((*parent)->key_value_pairs[0]);
            (*parent)->key_value_pairs.erase((*parent)->key_value_pairs.begin());
        }
        else
        {
            sift_key_value_pair = std::move((*parent)->key_value_pairs[index - 1]);
            (*parent)->key_value_pairs.erase((*parent)->key_value_pairs.begin() + index - 1);
        }

        (*target_merge)->~b_tree_node();
        deallocate_with_guard(*target_merge);
        *target_merge = nullptr;

        (*parent)->subtrees.erase((*parent)->subtrees.begin() + index);
        (*parent)->current_number_keys--;

        if (left_neighbor == nullptr && right_neighbor != nullptr)
        {
            right_neighbor->key_value_pairs.insert(right_neighbor->key_value_pairs.begin(),
                                                   std::move(sift_key_value_pair));

            right_neighbor->key_value_pairs.insert(right_neighbor->key_value_pairs.begin(),
                                                   unit_key_value_pairs.begin(),
                                                   unit_key_value_pairs.end());

            right_neighbor->subtrees.insert(right_neighbor->subtrees.begin(),
                                            unit_subtrees.begin(),
                                            unit_subtrees.end());

            right_neighbor->current_number_keys = right_neighbor->key_value_pairs.size();
        }
        else
        {
            left_neighbor->key_value_pairs.insert(left_neighbor->key_value_pairs.end(),
                                                  std::move(sift_key_value_pair));

            left_neighbor->key_value_pairs.insert(left_neighbor->key_value_pairs.end(),
                                                  unit_key_value_pairs.begin(),
                                                  unit_key_value_pairs.end());

            left_neighbor->subtrees.insert(left_neighbor->subtrees.end(),
                                           unit_subtrees.begin(),
                                           unit_subtrees.end());

            left_neighbor->current_number_keys = left_neighbor->key_value_pairs.size();
        }

        if ((*parent)->current_number_keys < _number_keys - 1)
        {
            if (*parent == _root)
            {
                b_tree_node *old_root = _root;
                *parent = *target_merge;

                old_root->~b_tree_node();
                deallocate_with_guard(old_root);
            }
            else
            {
                merge(parent, path);
            }
        }

        path.push(parent);
    }
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void b_tree<tkey, tvalue, tkey_comparer>::insert_in_leaf(
        const tkey &key,
        tvalue &&value,
        b_tree::b_tree_node *&leaf)
{
    int i = leaf->current_number_keys - 1;

    leaf->key_value_pairs.resize(leaf->key_value_pairs.size() + 1);

    while (i >= 0 && _comparator(key, leaf->key_value_pairs[i].first) < 0)
    {
        leaf->key_value_pairs[i + 1] = std::move(leaf->key_value_pairs[i]);
        i--;
    }

    leaf->key_value_pairs[i + 1] = {key, std::move(value)};
    leaf->subtrees.push_back(nullptr);
    leaf->current_number_keys++;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void b_tree<tkey, tvalue, tkey_comparer>::delete_node(
        b_tree_node *&target_delete)
{
    if (target_delete != nullptr)
    {
        for (int i = 0; i < target_delete->current_number_keys + 1; i++)
        {
            delete_node(target_delete->subtrees[i]);
        }

        target_delete->~b_tree_node();
        deallocate_with_guard(target_delete);
        target_delete = nullptr;
    }
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void b_tree<tkey, tvalue, tkey_comparer>::copy_node(
        b_tree_node *&dest_copy,
        b_tree_node *&src_copy)
{
    if (src_copy != nullptr)
    {
        dest_copy = src_copy;

        for (int i = 0; i < src_copy->current_number_keys + 1; i++)
        {
            copy_node(dest_copy->subtrees[i], src_copy->subtrees[i]);
        }
    }
}

//end functional_container


//begin constructor

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
b_tree<tkey, tvalue, tkey_comparer>::b_tree(
        size_t number_keys_init,
        logger *logger_init,
        memory *memory_init) :
        _logger(logger_init),
        _memory(memory_init),
        _number_keys(number_keys_init),
        _root(nullptr),
        _comparator(tkey_comparer()),
        _search(new search_template_method(this)),
        _insertion(new insertion_template_method(this)),
        _removal(new removal_template_method(this))
{

}

//end constructor


//begin copy/move semantic

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
b_tree<tkey, tvalue, tkey_comparer>::b_tree(
        const b_tree &copy_target) :
        _logger(copy_target._logger),
        _memory(copy_target._memory),
        _number_keys(copy_target._number_keys),
        _root(nullptr),
        _comparator(copy_target._comparator),
        _search(copy_target._search),
        _insertion(copy_target._insertion),
        _removal(copy_target._removal)
{
    copy_node(_root, copy_target._root);
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
b_tree<tkey, tvalue, tkey_comparer> &b_tree<tkey, tvalue, tkey_comparer>::operator=(
        const b_tree &copy_target)
{
    _logger = copy_target._logger;
    _memory = copy_target._memory;
    _number_keys = copy_target._number_keys;
    _root = nullptr;
    _comparator = copy_target._comparator;
    _search = copy_target._search;
    _insertion = copy_target._insertion;
    _removal = copy_target._removal;

    copy_node(_root, copy_target._root);

    return *this;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
b_tree<tkey, tvalue, tkey_comparer>::b_tree(
        b_tree &&move_target)  noexcept :
        _logger(std::move(move_target._logger)),
        _memory(std::move(move_target._memory)),
        _number_keys(std::move(move_target._number_keys)),
        _root(std::move(move_target._root)),
        _comparator(std::move(move_target._comparator)),
        _search(std::move(move_target._search)),
        _insertion(std::move(move_target._insertion)),
        _removal(std::move(move_target._removal))
{

}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
b_tree<tkey, tvalue, tkey_comparer> &b_tree<tkey, tvalue, tkey_comparer>::operator=(
        b_tree &&move_target) noexcept
{
    _logger = std::move(move_target._logger);
    _memory = std::move(move_target._memory);
    _number_keys = std::move(move_target._number_keys);
    _root = std::move(move_target._root);
    _comparator = std::move(move_target._comparator);
    _search = std::move(move_target._search);
    _insertion = std::move(move_target._insertion);
    _removal = std::move(move_target._removal);

    return *this;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
b_tree<tkey, tvalue, tkey_comparer>::~b_tree()
{
    delete_node(_root);

    delete _search;
    delete _insertion;
    delete _removal;
}

//end copy/move semantic

#endif // B_TREE_H