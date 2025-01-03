#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
#include <fstream>
#include <ctime>

using namespace std;

class FenwickTree {
public:
    FenwickTree(int n) {
        size = n;
        tree.assign(n + 1, 0);
    }

    void update(int index, int value) {
        while (index <= size) {
            tree[index] = max(tree[index], value);
            index += index & -index;
        }
    }

    int query(int index) {
        int max_val = 0;
        while (index > 0) {
            max_val = max(max_val, tree[index]);
            index -= index & -index;
        }
        return max_val;
    }

private:
    int size;
    vector<int> tree;
};

class Stock {
public:
    vector<int> prices;

    Stock() {}

    void setStockPrices() {
        int n;
        cout << "Enter number of stock prices: ";
        cin >> n;
        prices.resize(n);
        cout << "Enter the stock prices: ";
        for (int i = 0; i < n; ++i) {
            cin >> prices[i];
        }
    }

    pair<int, pair<int, int>> getMaxProfitDP() {
        int n = prices.size();
        if (n == 0) return {0, {-1, -1}};

        int min_price = prices[0], max_profit = 0;
        int buy_index = 0, sell_index = 0;

        for (int i = 1; i < n; i++) {
            if (prices[i] - min_price > max_profit) {
                max_profit = prices[i] - min_price;
                sell_index = i;
                buy_index = min_price == prices[0] ? 0 : buy_index;
            }
            if (prices[i] < min_price) {
                min_price = prices[i];
                buy_index = i;
            }
        }
        return {max_profit, {buy_index, sell_index}};
    }

    pair<int, pair<int, int>> getMaxProfitFenwick() {
        int n = prices.size();
        FenwickTree fenwick(n);
        int max_profit = 0;
        int buy_index = -1, sell_index = -1;

        for (int i = 0; i < n; i++) {
            int max_price_before = fenwick.query(i);
            if (prices[i] - max_price_before > max_profit) {
                max_profit = prices[i] - max_price_before;
                sell_index = i;
            }
            fenwick.update(i + 1, prices[i]);
        }

        for (int i = sell_index - 1; i >= 0; i--) {
            if (prices[i] == prices[sell_index] - max_profit) {
                buy_index = i;
                break;
            }
        }

        return {max_profit, {buy_index, sell_index}};
    }

    pair<int, pair<int, int>> getMaxProfitStack() {
        int n = prices.size();
        stack<int> s;
        int max_profit = 0;
        int buy_index = -1, sell_index = -1;

        for (int i = 0; i < n; i++) {
            while (!s.empty() && prices[s.top()] > prices[i]) {
                s.pop();
            }
            if (!s.empty()) {
                int profit = prices[i] - prices[s.top()];
                if (profit > max_profit) {
                    max_profit = profit;
                    sell_index = i;
                    buy_index = s.top();
                }
            }
            s.push(i);
        }

        return {max_profit, {buy_index, sell_index}};
    }
};

class Transaction {
public:
    int price;
    bool isBuy;

    Transaction(int p, bool buy) : price(p), isBuy(buy) {}
};

class User {
public:
    string username;
    vector<Transaction> transactionHistory;

    User() : username("") {}

    User(string name) : username(name) {}

    void addStock(int price) {
        transactionHistory.push_back(Transaction(price, true));
    }

    void makeBuyAction(int stockPrice) {
        transactionHistory.push_back(Transaction(stockPrice, true));
    }

    void makeSellAction(int stockPrice) {
        for (int i = transactionHistory.size() - 1; i >= 0; --i) {
            if (transactionHistory[i].isBuy && transactionHistory[i].price <= stockPrice) {
                transactionHistory.push_back(Transaction(stockPrice, false));
                break;
            }
        }
    }

    void printPortfolio() {
        cout << username << "'s Portfolio:\n";
        for (auto& t : transactionHistory) {
            if (t.isBuy) {
                cout << "Bought at " << t.price << "\n";
            }
        }
    }

    void printTransactionHistory() {
        cout << username << "'s Transaction History:\n";
        for (auto& t : transactionHistory) {
            cout << (t.isBuy ? "Bought" : "Sold") << " at " << t.price << "\n";
        }
    }

    void calculateNetProfit() {
        int profit = 0;
        for (int i = 0; i < transactionHistory.size(); ++i) {
            if (!transactionHistory[i].isBuy) {
                profit += transactionHistory[i].price;
            } else {
                profit -= transactionHistory[i].price;
            }
        }
        cout << username << "'s Net Profit/Loss: " << profit << "\n";
    }
};

class StockMarketSystem {
public:
    map<string, User> users;
    Stock stock;

    StockMarketSystem() {}

    void registerUser() {
        string username;
        cout << "Enter username to register: ";
        cin >> username;
        cout << "Do you agree to our company policies? (yes/no): ";
        string agreement;
        cin >> agreement;
        if (agreement == "yes") {
            users[username] = User(username);
            cout << "User " << username << " registered successfully!\n";
        } else {
            cout << "Registration failed. You must agree to company policies.\n";
        }
    }

    void makeBuyAction(string username) {
        int stockPrice;
        cout << username << ", enter stock price to buy: ";
        cin >> stockPrice;
        if (users.find(username) != users.end()) {
            users[username].makeBuyAction(stockPrice);
            cout << username << " bought stock at price " << stockPrice << endl;
        }
    }

    void makeSellAction(string username) {
        int stockPrice;
        cout << username << ", enter stock price to sell: ";
        cin >> stockPrice;
        if (users.find(username) != users.end()) {
            users[username].makeSellAction(stockPrice);
            cout << username << " sold stock at price " << stockPrice << endl;
        }
    }

    void calculateProfit() {
        auto [max_profit_dp, indices_dp] = stock.getMaxProfitDP();
        auto [max_profit_fenwick, indices_fenwick] = stock.getMaxProfitFenwick();
        auto [max_profit_stack, indices_stack] = stock.getMaxProfitStack();

        cout << "Max Profit (DP): " << max_profit_dp
             << " (Buy at index " << indices_dp.first << ", Sell at index " << indices_dp.second << ")\n";
        cout << "Max Profit (Fenwick Tree): " << max_profit_fenwick
             << " (Buy at index " << indices_fenwick.first << ", Sell at index " << indices_fenwick.second << ")\n";
        cout << "Max Profit (Monotonic Stack): " << max_profit_stack
             << " (Buy at index " << indices_stack.first << ", Sell at index " << indices_stack.second << ")\n";
    }

    void displayUserPortfolio(string username) {
        if (users.find(username) != users.end()) {
            users[username].printPortfolio();
        }
    }

    void displayTransactionHistory(string username) {
        if (users.find(username) != users.end()) {
            users[username].printTransactionHistory();
        }
    }

    void displayNetProfit(string username) {
        if (users.find(username) != users.end()) {
            users[username].calculateNetProfit();
        }
    }

    void run() {
        cout << "Welcome to [Your Company Name] Stock Market System!\n";
        stock.setStockPrices();

        int choice;
        while (true) {
            cout << "\n1. Register User\n2. Buy Stock\n3. Sell Stock\n4. Calculate Profit\n5. Display Portfolio\n6. Display Transaction History\n7. Display Net Profit\n8. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            string username;
            switch (choice) {
                case 1:
                    registerUser();
                    break;
                case 2:
                    cout << "Enter username: ";
                    cin >> username;
                    makeBuyAction(username);
                    break;
                case 3:
                    cout << "Enter username: ";
                    cin >> username;
                    makeSellAction(username);
                    break;
                case 4:
                    calculateProfit();
                    break;
                case 5:
                    cout << "Enter username: ";
                    cin >> username;
                    displayUserPortfolio(username);
                    break;
                case 6:
                    cout << "Enter username: ";
                    cin >> username;
                    displayTransactionHistory(username);
                    break;
                      case 7:
                    cout << "Enter username: ";
                    cin >> username;
                    displayNetProfit(username);
                    break;
                case 8:
                    cout << "Exiting the system. Thank you for using the Stock Market System!\n";
                    return;
                default:
                    cout << "Invalid choice! Please enter a valid option.\n";
                    break;
            }
        }
    }
};

int main() {
    StockMarketSystem system;
    system.run();
    return 0;
}
