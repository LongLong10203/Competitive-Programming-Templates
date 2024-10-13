#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T, typename Comp = less<T>>
using OrdTreeBase = tree<T, null_type, Comp, rb_tree_tag, tree_order_statistics_node_update>;

// modified from https://codeforces.com/blog/entry/110668
template<typename T, typename Comp = less<T>>
class OrderedSet : public OrdTreeBase<T, Comp> {
public:
    using Base = OrdTreeBase<T, Comp>;
    
    OrderedSet() : Base() { }
    OrderedSet(const vector<T>& pack) : Base(pack.begin(), pack.end()) { }
    
    size_t count_less(const T &key) const {
        return this->order_of_key(key);
    }
    
    size_t count_greater(const T &key) const {
        return this->size() - count_less_equal(key);
    }
    
    // only applicable to integers
    size_t count_less_equal(const T &key) const {
        return count_less(key + 1);
    }

    // only applicable to integers
    size_t count_equal(const T &key) const {
        return count_less_equal(key) - count_less(key);
    }
    
    template<typename Compare = Comp>
    pair<typename Base::const_iterator, size_t>
    lower_bound_with_order(const T &key) const {
        auto prev = this->m_p_head;
        auto curr = this->m_p_head->m_p_parent;
        size_t order{};
        while (curr != 0)
            if (Compare()(curr->m_value, key)) {
                order += curr->m_metadata;
                if ((curr = curr->m_p_right))
                    order -= curr->m_metadata;
            } else {
                prev = curr;
                curr = curr->m_p_left;
            }
        return make_pair(prev, order);
    }
    
    template<typename Compare = Comp>
    pair<typename Base::const_iterator, size_t>
    upper_bound_with_order(const T &key) const {
        auto prev = this->m_p_head;
        auto curr = this->m_p_head->m_p_parent;
        size_t order{};
        while (curr != 0)
            if (Compare()(key, curr->m_value)) {
                prev = curr;
                curr = curr->m_p_left;
            } else {
                order += curr->m_metadata;
                if ((curr = curr->m_p_right))
                    order -= curr->m_metadata;
            }
        return make_pair(prev, order);
    }

    void insert(const T &value) {
        Base::insert(value);
    }

    // doesn't work :(
    // void erase(const T &value) {
    //     Base::erase(value);
    // }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    
}