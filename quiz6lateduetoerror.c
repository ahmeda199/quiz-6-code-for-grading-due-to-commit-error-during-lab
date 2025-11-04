// percent_profitbook.c — reference solution
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <math.h>

// create a struct
typedef struct {
    double buy_price;
    double sell_price;
    char name[20];
    int id;

} StockInvestment;

//implement the following functions
StockInvestment* create_portfolio(size_t n) {
    // using malloc to create struct pointer
    StockInvestment* portfolio = malloc(n * sizeof(StockInvestment));
    if (!portfolio) {
        printf("allocate memory not working\n");
        exit(1);
    }
    return portfolio;
}

int set_stock_investment(StockInvestment* portfolio, size_t n, size_t idx, 
const char* name, int id, double buy_price, double sell_price) {
    // give values to array of struct
    if (idx >= n) return -1;  // cheks for wrong index
    strcpy(portfolio[idx].name, name);
    portfolio[idx].id = id;
    portfolio[idx].buy_price = buy_price;
    portfolio[idx].sell_price = sell_price;
    return 0;
}

double average_percent_gain(const StockInvestment* portfolio, size_t n) {
    // calculate avg of stock gain
    double sum = 0.0;
    for (size_t i = 0; i < n; i++) {
        double gain = (portfolio[i].sell_price / portfolio[i].buy_price) - 1.0;
        sum += gain;
    }
    return (sum / n) * 100; // sets it to percent vlue
}

void free_portfolio(StockInvestment* portfolio) {
    // free the struct
    free(portfolio);
}

int main(int argc, char* argv[]) {
    // check for filename input
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("error file not opened.\n");
        return 1;
    }

    //counts lines in file
    size_t n = 0;
    char buffer[50];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strlen(buffer) > 1) n++;
    }

    // allocate memory
    StockInvestment* portfolio = create_portfolio(n);

    // puts file pointer to start again
    rewind(file);

    // read stock from lines of input file
    for (size_t i = 0; i < n; i++) {
        char name[50];
        int id;
        double buy_price, sell_price;
        fscanf(file, "%s %d %lf %lf", name, &id, &buy_price, &sell_price);
        set_stock_investment(portfolio, n, i, name, id, buy_price, sell_price);
    }

    fclose(file);

    // print percent gain
    printf("%.2f\n", average_percent_gain(portfolio, n));

    // free memory
    free_portfolio(portfolio);

    return 0;
}
