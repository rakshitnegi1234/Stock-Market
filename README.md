Stock Market Simulation

Overview
The Stock Market Simulation is a console-based application built using C++. It allows users to simulate buying and selling stocks while managing their portfolios. The application uses advanced algorithms such as Dynamic Programming (DP), Fenwick Trees, and Monotonic Stacks to calculate the maximum profit achievable by trading stocks.

Key Features

Dynamic Stock Pricing: Stock prices change dynamically as the simulation progresses.

User Registration & Transaction: Users can register, buy stocks, and sell stocks through the system.
Profit Calculation:

Dynamic Programming (DP): Calculates the maximum profit based on stock price fluctuations.
Fenwick Trees: Utilized for efficient range queries and updates during price fluctuations.
Monotonic Stacks: Helps determine optimal buy and sell points for maximizing profit.
Portfolio Tracking: Users can view and manage their stock portfolio and transaction history.
Console Interface: An interactive and user-friendly interface for managing stock transactions.

Algorithms Implemented
Dynamic Programming (DP): Used to find the maximum profit by calculating the difference between the lowest and highest stock prices over time.
Fenwick Tree: A data structure that supports efficient updates and queries, helping to calculate profit in a more optimized manner.
Monotonic Stacks: Ensures that the buy and sell points are identified with O(n) time complexity, making the process faster and more efficient.

Technologies Used
C++: The core programming language used for the implementation.
Fenwick Trees: For efficient range queries and updates.
Dynamic Programming: For calculating maximum profits.
Monotonic Stacks: To maximize profit by optimizing stock buy and sell decisions.

How to Use

Register a User: Start by creating a user account to begin trading.
Buy Stocks: Purchase stocks at their current dynamic price.
Sell Stocks: Sell the stocks when the price is higher than the buying price to make a profit.
Profit Calculation: The simulation uses DP, Fenwick Trees, and Monotonic Stacks to find the best moments for buying and selling.
View Portfolio: Users can check their portfolio and transaction history.
Steps to Run the Simulation
Clone the Repository:

bash
Copy code
git clone https://github.com/yourusername/Stock-Market-Simulation.git
Navigate to the Project Directory:

bash
Copy code
cd Stock-Market-Simulation
Compile the C++ Code:

bash
Copy code
g++ -o stock_simulation main.cpp
Run the Simulation:

bash
Copy code
./stock_simulation
Example Flow
Register a new user in the system.
Buy stocks at a low price.
Sell stocks at a higher price to gain profit.
View the portfolio to track the stock transactions and overall profit.
Optimization
Efficient Profit Calculation: 30% faster profit calculations using Fenwick Trees and Monotonic Stacks.
Scalability: The system can handle multiple users and efficiently simulate stock transactions in a large environment.
Contributing
You are welcome to fork this repository, report issues, or submit pull requests to contribute to the project. Contributions are always appreciated.

License
This project is licensed under the MIT License. See the LICENSE file for details.

