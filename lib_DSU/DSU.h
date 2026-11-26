// Copyright 2026 Kutyaev Egor
#ifndef LIB_DSU_H_
#define LIB_DSU_H_

class DSU {
  unsigned int* _parent;
  size_t _size;
  unsigned int* _rank;

 public:
  explicit DSU(size_t size) {
    _size = size;
    _parent = new unsigned int[size];
    _rank = new unsigned int[size];
  }
  ~DSU() {
    delete[] _parent;
    delete[] _rank;
  }

  void join(unsigned int elem1, unsigned int elem2) {
    elem1 = find(elem1);
    elem2 = find(elem2);
    if (_rank[elem1] == _rank[elem2]) {
      _parent[elem2] = elem1;
      _rank[elem1] += 1;
    } else if (_rank[elem1] > _rank[elem2]) {
      _parent[elem2] = elem1;
    } else if (_rank[elem1] < _rank[elem2]) {
      _parent[elem1] = elem2;
    }
  }

  unsigned int find(unsigned int elem) {
    if (elem == (_parent[elem] - 1)) return elem;
    return _parent[elem] = find(_parent[elem]);
  }
};

#endif  // LIB_DSU_H_
