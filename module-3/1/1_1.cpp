#include <iostream>
#include <vector>

using namespace std;

const float MAX_CAPACITY = 0.75;

template<class key_t>
struct hash_t {
  int b;
  int a;
  static const int c = 2147483647;
  hash_t(int a = 48295738, int b = 19327432):
          a(a),
          b(b)
  {}

  size_t operator()(const key_t &key) const {
    return (a + b *key) % c;
  }
};

template<>
struct hash_t<string> {
  int a;
  int m;
  hash_t(int a = 17549243, int m = 2147483647):
          a(a),
          m(m)
  {}

  size_t operator()(const std::string &key) const {
    size_t result = 0;
    for (string::const_iterator it = key.begin(); it != key.end(); ++it) {
      result = (result * a + *it) % m;
    }
    return result;
  }
};


struct square_probe_iterator_t {
  int index_curr;
  int iteration;
  int mod;

  square_probe_iterator_t(int index_start, int mod):
          index_curr(index_start),
          iteration(0),
          mod(mod)
  {}

  void next() {
    ++iteration;
    if (iteration < mod) {
      index_curr += iteration;
      index_curr %= mod;
      return;
    }
    index_curr = mod;
  }

  int get() const {
    return index_curr;
  }
};


template<class key_t, class hfunc_t = hash_t<key_t>, class probe_iterator_t = square_probe_iterator_t>
struct hash_map_t {

  struct item_t {
    item_t():
            state(NONE)
    {}

    key_t key;
    enum item_state_t {
      NONE,
      BUSY,
      DELETED
    } state;
  };

  typedef std::vector<item_t> map_t;
  map_t map;
  size_t size;
  hfunc_t hfunc;

  hash_map_t(size_t capacity = 4, const hfunc_t &hfunc = hfunc_t()):
          map(capacity),
          size(0),
          hfunc(hfunc)
  {}

  bool insert(const key_t &key) {
    if (find(key) != 0) {
      return false;
    }

    if (fill_capacity() > max_capacity()) {
      rebuild();
    }

    const size_t capacity_curr = capacity();
    for (probe_iterator_t it(hash(key), capacity_curr);
         it.get() != capacity_curr;
         it.next()) {
      if (map[it.get()].state != item_t::BUSY) {
        map[it.get()].key = key;
        map[it.get()].state = item_t::BUSY;
        ++size;
        return true;
      }
    }
    return false;
  }

  bool remove(const key_t &key) {
    item_t *const item = find(key);

    if (item == 0) {
      return false;
    }

    item->state = item_t::DELETED;
    --size;
    return true;
  }

  const item_t *find(const key_t &key) const {
    const size_t capacity_curr = capacity();
    for (probe_iterator_t it(hash(key), capacity_curr);
         it.get() < capacity_curr;
         it.next()) {

      if (map[it.get()].state == item_t::NONE) {
        return 0;
      }

      if (map[it.get()].state == item_t::BUSY &&
              map[it.get()].key == key) {
        return &map[it.get()];
      }
    }

    return 0;
  }

  item_t *find(const key_t &key) {
    return const_cast<item_t *>(const_cast<const hash_map_t *>(this)->find(key));
  }

  size_t get_size() const {
    return size;
  }

private:
  static void move_to(map_t &new_map, const item_t &item, const hfunc_t &hfunc) {
    const size_t new_capacity = new_map.size();
    const size_t itemHash = hash(item.key, new_capacity, hfunc);
    for (probe_iterator_t it(itemHash, new_capacity);
         it.get() < new_capacity;
         it.next()) {

      if (new_map[it.get()].state != item_t::BUSY) {
        new_map[it.get()] = item;
        return;
      }
    }

  }

  void rebuild() {
    map_t new_map(capacity() *2);

    for (size_t i = 0; i < map.size(); ++i) {
      if (map[i].state != item_t::BUSY) {
        continue;
      }
      move_to(new_map, map[i], hfunc);
    }

    map.swap(new_map);
  }

  static int hash(const key_t &key, size_t mod, const hfunc_t &hfunc) {
    return hfunc(key) % mod;
  }

  int hash(const key_t &key) const {
    return hash(key, capacity(), hfunc);
  }

  size_t capacity() const {
    return map.size();
  }

  float max_capacity() const {
    return MAX_CAPACITY;
  }

  float fill_capacity() const {
    return static_cast<float>(get_size()) / capacity();
  }
};

//=============================================================================
typedef hash_map_t<string> hash_string_t;


int main()
{
  hash_string_t string_set;
  while(true) {
    char action = 0;
    cin >> action;

    if (cin.eof()) break;

    string str;
    cin >> str;

    switch (action) {
      case '+' :
        if (string_set.insert(str)) {
          cout << "OK" << endl;
        } else {
          cout << "FAIL" << endl;
        }
        break;
      case '-':
        if (string_set.remove(str)) {
          cout << "OK" << endl;
        } else {
          cout << "FAIL" << endl;
        }
        break;
      case'?':
        if (string_set.find(str) != 0) {
          cout << "OK" << endl;
        } else {
          cout << "FAIL" << endl;
        }
        break;
    }
  }
  return 0;
}

//=============================================================================
