#include <iostream>
#include <vector>

struct Tree {
  // each Tree has a label
  int label = std::numeric_limits<int>::min();

  // and branches
  std::vector<Tree> branches;

  // constructor
  explicit Tree(int label) :label(label) {}

  Tree(int label, std::vector<Tree> b) :label(label)  {
    for (const Tree &branch: b) {
      branches.emplace_back(branch);
    }
  }

  // copy constructor: this does kind of feel like
  // cheating
  Tree(const Tree &t) :label(t.label) {
    for (const Tree &branch : t.branches)
      branches.emplace_back((Tree(branch)));
  }
};

// this is obviously unnecessary I just wanted to
// make the translation from python => cpp
bool is_tree(const Tree &tree) {
  if (tree.branches.empty())
    return true;

  for (const Tree &branch: tree.branches)
    if (!is_tree(branch))
      return false;

  return true;
}

int label(const Tree &tree) {
  return tree.label;
}

std::vector<Tree> branches(const Tree &tree) {
  std::vector<Tree> branch(tree.branches.begin(),
                           tree.branches.end());
  return branch;
}

bool is_leaf(const Tree &tree) {
  return tree.branches.empty();
}

int helper(const Tree &tree, int level) {
  if (is_leaf(tree))
    return 0;

  int m = 0;
  for (const Tree &branch : branches(tree)) {
    m = std::max(helper(branch, level + 1), m);
  }
  return std::max(level, m);
}

int height(const Tree &tree) {
  return helper(tree, 0) + 1;
}

void pretty_helper(const Tree &tree, std::size_t step) {
 std::string indent(step, ' ');
 std::cout << indent << std::to_string(tree.label) << std::endl;

 for (const Tree &branch: tree.branches) {
   pretty_helper(branch, step + 2);
 }
}

enum step {one = 1};
void pretty_print(const Tree &tree) {
  pretty_helper(tree, step::one);
  std::cout << '\n';
}

Tree fib_tree(int n) {
  if (n <= 1) {
    return Tree(n);
  } else {
    Tree left = fib_tree(n - 2);
    Tree right = fib_tree(n - 1);
    std::vector<Tree> branch{left, right};
    return Tree(label(left) + label(right), branch);
  }
}

int main()
{
  // manual construction
  auto t = Tree(1);
  t.branches.emplace_back(Tree(3));
  t.branches[0].branches.emplace_back(Tree(5));
  t.branches[0].branches.emplace_back(Tree(3));
  t.branches[0].branches.emplace_back(Tree(10));
  t.branches.emplace_back(Tree(2));

  auto tt = Tree(13);
  tt.branches.emplace_back(Tree(17));
  tt.branches[0].branches.emplace_back(Tree(23));
  t.branches[1].branches.emplace_back(tt);
  t.branches.emplace_back(Tree(6));

  pretty_print(t);

  auto fib_tree_nine = fib_tree(9);
  assert(height(fib_tree_nine) == 8);
  pretty_print(fib_tree_nine);

  auto fib_tree_five = fib_tree(5);
  assert(height(fib_tree_five) == 4);
  pretty_print(fib_tree_five);

  pretty_print(fib_tree(7));
  assert(height(fib_tree(7)) == 6);
  return 0;
}

/*====================== The 61A Python Code =========================
def tree(label, branches=[]):
    for branch in branches:
        # for branch in branches assert that the branch is a tree
        assert is_tree(branch)
        # make sure to convert possible non-list things by calling list
    return [label] + list(branches)


def label(tree):
    return tree[0]


def branches(tree):
    return tree[1:]


def is_tree(tree):
    if type(tree) != list or len(tree) < 1:
        return False
    for branch in branches(tree):
        if not is_tree(branch):
            return False
    return True


def is_leaf(tree):
    # as long as this tree has no branches
    return not branches(tree)


def fib_tree(n):
    if n <= 1:
        return tree(n)
    else:
        left, right = fib_tree(n - 2), fib_tree(n - 1)
        return tree(label(left)+label(right), [left, right])


def count_leaves1(t):
    if is_leaf(t):
        return 1
    else:
        branch_counts = [count_leaves1(b) for b in branches(t)]
        return sum(branch_counts)


def print_tree(t, indent=0):
    print('  ' * indent + str(label(t)))
    for b in branches(t):
        print_tree(b, indent + 1)


def height(t):
    if is_leaf(t):
        return 0
    return 1 + max([height(b) for b in branches(t)])

t = tree(1,
        [tree(3,
            [tree(4),
            tree(5),
            tree(6)]),
        tree(2,
             [tree(2,
                   [tree(4,
                         [tree(6)])]),
              tree(4)])])
======================================================================*/
