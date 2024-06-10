#include <iostream>
#include <map>
#include <exception>
#include <string>
const std::string WHITESPACE = " \t";

void PrintMap(const std::map<std::string, int> &map)
{
    if (map.empty())
        std::cout << "[empty]\n";
    for (const auto &element : map)
    {
        std::cout << element.first << " : " << element.second << "\n";
    }
}

void PrintAll(std::map<std::string, int> &shop, std::map<std::string, int> &cart)
{
    std::cout << "\t - Shop table:\n";
    PrintMap(shop);
    std::cout << "\t - Cart table:\n";
    PrintMap(cart);
}

std::string getArticleFromCin()
{
    std::cout << "Please enter the article:\n";
    std::string value;
    std::getline(std::cin, value);
    if (value.empty())
        throw std::invalid_argument("article name is empty");
    if (value.find_first_not_of(WHITESPACE) != 0)
        throw std::invalid_argument("article is started from whitespace");
    return value;
}

int getQuantityFromInput()
{
    std::cout << "Please enter the quantity:\n";
    std::string input;
    std::getline(std::cin, input);

    int quantity = std::stoi(input);
    if (quantity < 0)
    {
        throw std::invalid_argument("quantity");
    }
    return quantity;
}

void addArticleToCart(const std::string &article, const int quantity, std::map<std::string, int> &shop, std::map<std::string, int> &cart)
{
    if (quantity < 0)
        throw std::invalid_argument("quantity < 0");
    auto it_shop = shop.find(article);
    if (it_shop == shop.end())
        throw std::invalid_argument("article is not found");
    if (it_shop->second < quantity)
        throw std::invalid_argument("quantity in the shop is not enough");

    it_shop->second -= quantity;
    auto it_cart = cart.find(article);
    if (it_cart == cart.end())
    {
        cart.insert(std::make_pair(article, quantity));
    }
    else
    {
        it_cart->second += quantity;
    }
    std::cout << article << " : " << quantity << " [pcs] added to cart\n";
    PrintAll(shop, cart);
}

void removeArticleFromCart(const std::string &article, int quantity, std::map<std::string, int> &shop, std::map<std::string, int> &cart)
{
    if (quantity < 0)
        throw std::invalid_argument("quantity < 0");
    auto it_cart = cart.find(article);
    if (it_cart == cart.end())
        throw std::invalid_argument("article is not found in cart\n");
    if (it_cart->second < quantity)
        throw std::invalid_argument("quantity in the cart is not enough\n");

    it_cart->second -= quantity;

    auto it_shop = shop.find(article);
    if (it_shop == shop.end())
    {
        shop.insert(std::make_pair(article, quantity));
    }
    else
    {
        it_shop->second += quantity;
    }

    if (it_cart->second == 0)
        cart.erase(it_cart->first);

    std::cout << article << " : " << quantity << " [pcs] removed from cart\n";
    PrintAll(shop, cart);
}

std::map<std::string, int> shop;
std::map<std::string, int> cart;

void AddShop()
{
    std::string article;
    int quantity{0};
    std::cout << "\t - Enter goods for shop:\n"
              << "\t -----------------------\n";
    while (true)
    {
        try
        {
            std::cout << "(Type \"end\" to finish shop preparation)\n"
                      << "----------------------------------------\n\n";
            article = getArticleFromCin();
            if (article == "end")
                break;
            quantity = getQuantityFromInput();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Caught exception: " << e.what() << "\n";
            continue;
        }
        auto it = shop.find(article);
        if (it == shop.end())
            shop.insert(std::make_pair(article, quantity));
        else
            it->second += quantity;
    }
    std::cout << "\t +.....................................+\n"
              << "\t | - Shop is prepared. Goods you have: |\n"
              << "\t +.....................................+\n";
}

void AddCart()
{
    while (true)
    {
        std::cout << "\t +.......................................................................+\n"
                  << "\t | - Please enter the command (\"add\" || \"remove\" || \"exit\" || \"print\"): |\n"
                  << "\t +.......................................................................+\n";
        std::string command;
        std::getline(std::cin, command);
        try
        {
            if (command == "exit")
                break;
            else if (command == "add")
            {
                std::string art = getArticleFromCin();
                int q = getQuantityFromInput();
                addArticleToCart(art, q, shop, cart);
            }
            else if (command == "remove")
            {
                std::string art = getArticleFromCin();
                int q = getQuantityFromInput();
                removeArticleFromCart(art, q, shop, cart);
            }
            else if (command == "print")
            {
                std::cout << "\t - Shop table:\n";
                PrintMap(shop);
                std::cout << "\t - Cart table:\n";
                PrintMap(cart);
            }
            else
            {
                std::cerr << "Bad command.\n";
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Caught exception: " << e.what() << "\n";
        }
        catch (...)
        {
            std::cerr << "Unknown error.\n";
        }
    }
    std::cout << "+.................+\n"
              << "| -Program is END |\n"
              << "+.................+\n";
}