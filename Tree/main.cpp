// Eric Sanchez @ericd34n on 20180217
// clang formatted: --style=WebKit
#include "Tree.h"
#include <string>

int main()
{
    Tree<std::string, std::string> Emoji("thumbs up", "👍");
    Emoji.insert({ "robot", "🤖" });
    Emoji.insert({ "brain", "🧠" });
    Emoji.insert({ "rocket ship", "‍🚀" });
    Emoji.insert({ "dracula", "🧛️" });
    Emoji.insert({ "legolas", "🧝" });
    Emoji.in_order_print();
    Emoji.pre_order_print();
    Emoji.post_order_print();
    std::cout << Emoji.isBalanced() << std::endl;

    Tree<int, int> A(0, 0);
    A.insert({ -1, -1 });
    A.insert({ 2, 2 });
    std::cout << A.isBalanced() << std::endl;

    return 0;
}
