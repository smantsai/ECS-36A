/* This program checks if it is better to pay off your loans before investing
or if it is better to make minimum payments and investing the rest of your money. */

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

/**
 * Makes sure the input is valid and following the provided format
 * @param numArgsNeeded: the number of format placeholders that needed to have been read in the last scanf
 * @param numArgsRead: the actual number of placeholders that were read from scanf, ie its return value
 * @return: true if the input is correctly formatted and false otherwise
 */
bool isValidFormat(const int numArgsRead, const int numArgsNeed) {
  bool formatIsGood = numArgsRead == numArgsNeed;
  char character;
  do{
    scanf("%c", &character); //45  bob  \n
		if(!isspace(character)){ //found a non whitespace character on the way to the end of the line
			formatIsGood = false;
		}
	}while(character != '\n'); //read characters until the end of the line
  return formatIsGood;
}

/**
 * Gets a double input from the user
 * @param prompt : Tells the user what to input
 * @return: a double if the input is valid
 */
double getValidDouble(const char* prompt){
  double num;
  const int numArgsNeeded = 1;
  int numArgsRead;
  do{
    printf("%s", prompt);
    numArgsRead = scanf(" %lf", &num); //waffles\n
  }while(!isValidFormat(numArgsRead, numArgsNeeded));

  return num;
}

/**
 * Gets a double input from the user that is at least a certain value
 * @param min_val : the minimum double value the user can input
 * @param min_val tells the user what to input (is passed to a different function)
 * @return: a double if the input is valid
 */
double getDoubleAtLeast(double min_val, const char* prompt){
  double num;
  do{
    num = getValidDouble(prompt);
  }while(!(num >= min_val));

  return num;
}

/**
 * Finds out how long it takes for a loan to be paid off
 * @param loanAmount: the principal of the loan
 * @param monthlyInterestRate: the monthly interest rate of the loan
 * @param payment: how much the user is paying every month for the loan
 * @param range: how many months until the user retires
 * @return: a double with the amount of months it takes for the user to pay off the loan
 */
double monthsToPayOffLoan(double loanAmount, double monthlyInterestRate, double payment, double range) {
    double months = 0;
     // need to check if able to pay off loan
    while (loanAmount > 0) {
        loanAmount = loanAmount + (loanAmount * monthlyInterestRate);
        loanAmount = loanAmount - payment;
        if (payment < (loanAmount * monthlyInterestRate)) {
            months = range + 1;
            return months;
        }
        months++;
    }

    return months;
}

/**
 * Finds out how much money is left over when the loan is paid off
 * @param loanAmount: the principal of the loan
 * @param monthlyInterestRate: the monthly interest rate of the loan
 * @param payment: how much the user is paying every month for the loan
 * @param range: how many months until the user retires
 * @return: a double with the remaining amount of money the user has the month they pay off the loan
 */
double findLeftoverMoney(double loanAmount, double monthlyInterestRate, double payment, double range) {
    double months = monthsToPayOffLoan(loanAmount, monthlyInterestRate, payment, range);
    for (int i = 0; i < months; i++) {
        loanAmount = loanAmount + (loanAmount * monthlyInterestRate);
        loanAmount = loanAmount - payment;

        if (loanAmount < 0) {
            return fabs(loanAmount);
        }
    } 
    return 0;
}

/**
 * Finds out how much money the user makes by paying off their loan first and then investing until retirement
 * @param range: how many months until the user retires
 * @param monthFinish: the month the user pays off their loan
 * @param investInterest: the monthly interest rate of their investment
 * @param monthlyMoney: the amount of money the user can use to invest or pay off their loan
 * @param leftovers: the remaining amount of money the user has the month they pay off their loan
 * @param loan: the principal of the loan
 * @param loanInterest: how monthly interest rate of the user's loan
 * @return: how much money the user makes by paying off their loan entirely and then investing
 */
double payLoansOffFirst(double range, double monthFinish, double investInterest, double monthlyMoney, double leftovers, double loan, double loanInterest) {
    double moneyMade = 0;

    // from month the user finishes paying off
    if (monthFinish < range){
        moneyMade = leftovers;
    }

    for (int i = 0; i < range; i++) {
        if (i < monthFinish) { // loan not paid off yet
            loan += (loan * loanInterest);
            loan -= monthlyMoney;
        } else { // after loan is paid off, can start investing
            moneyMade += (moneyMade * investInterest) + (monthlyMoney);
        }
    }
    
    if (loan > 0) { // if loan is still not yet paid off
        moneyMade -= loan;
    }

    return moneyMade;
}

/**
 * Finds out how much money the user makes by making minimal payments and investing at the same time until retirement
 * @param range: how many months until the user retires
 * @param monthFinish: the month the user pays off their loan
 * @param investInterest: the monthly interest rate of their investment
 * @param monthlyMoney: the amount of money the user can use to invest or pay off their loan
 * @param loanPayment: the minimum payment the user makes every month towards their loan
 * @param leftovers: the remaining amount of money the user has the month they pay off their loan
 * @param loan: the principal of the loan
 * @param loanInterest: how monthly interest rate of the user's loan
 * @return: how much money the user makes by investing and paying off their loan at the same time
 */
double payMinimum(double range, double monthFinish, double investInterest, double monthlyMoney, double loanPayment, double leftovers, double loan, double loanInterest) {
    double moneyMade = 0;
    double investingMoney = monthlyMoney - loanPayment;
    for (int i = 0; i < range; i++) {
        if (i < monthFinish) { // loan not paid off yet
            moneyMade += (moneyMade * investInterest);
            loan += (loan * loanInterest) - loanPayment;
            if (loan < 0) {
                moneyMade -= loan;
            }
            moneyMade += investingMoney;
        } else { // after loan is paid off
            moneyMade += (moneyMade * investInterest) + (monthlyMoney);
        }
    }

    if (loan > 0) { // if loan is not yet paid off
        moneyMade -= loan;
    }

    return moneyMade;
}

int main( ) {
    // getting input from user
    double loanAmount = getDoubleAtLeast(0, "Enter how much you owe in loans: ");
    double loanAnnualInterestRate = getDoubleAtLeast(0, "Enter the annual interest rate of the loans: ");
    double loanMinPayment = getDoubleAtLeast(0, "Enter your minimum monthly loan payment: ");
    double monthlyMoney = getDoubleAtLeast(loanMinPayment, "Enter how much money you will be putting towards loans/retirement each month: ");
    double currentAge = getDoubleAtLeast(0, "Enter your current age: ");
    double retirementAge = getDoubleAtLeast(currentAge, "Enter the age you plan to retire at: ");
    double investAnnualReturns = getDoubleAtLeast(0, "Enter your predicted annual rate of return: ");

    // variables for easier calculation
    double loanMonthlyInterestRate = loanAnnualInterestRate / 12.0;
    double investMonthlyReturns = investAnnualReturns / 12.0;
    double range = (retirementAge - currentAge) * 12.0; // period of time to calculate
    double monthFinish;
    double leftoverMoney;
    double moneyIfPayLoansFirst;
    double moneyIfInvestAndPay;
    
    // calling functions
    monthFinish = monthsToPayOffLoan(loanAmount, loanMonthlyInterestRate, monthlyMoney, range);
    leftoverMoney = findLeftoverMoney(loanAmount, loanMonthlyInterestRate, monthlyMoney, range);

    moneyIfPayLoansFirst = payLoansOffFirst(range, monthFinish, investMonthlyReturns, monthlyMoney, leftoverMoney, loanAmount, loanMonthlyInterestRate);
    
    // update variables for next call
    monthFinish = monthsToPayOffLoan(loanAmount, loanMonthlyInterestRate, loanMinPayment, range);
    leftoverMoney = findLeftoverMoney(loanAmount, loanMonthlyInterestRate, loanMinPayment, range);

    moneyIfInvestAndPay = payMinimum(range, monthFinish, investMonthlyReturns, monthlyMoney, loanMinPayment, leftoverMoney, loanAmount, loanMonthlyInterestRate);

    if (moneyIfInvestAndPay >= moneyIfPayLoansFirst) {
        printf("You should only make the minimum payments on your loan and apply the rest towards retirement.\n");
        printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you paid off your loan before investing.", moneyIfInvestAndPay, moneyIfPayLoansFirst);
    } else {
        printf("You should apply all $%.2lf towards your loan before making any investments.\n", monthlyMoney);
        printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you only made minimum payments.", moneyIfPayLoansFirst, moneyIfInvestAndPay);
    }
}