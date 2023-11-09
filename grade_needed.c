/* This program calculates the grade you need on the final
to pass the class with your desired grade. */

#include <stdio.h>

int main() {
    char desiredLetterGrade;
    double desiredPercentGrade;
    double currentPercentGrade;
    double finalWeight;
    double gradeNeeded;
    double currentWeight;

    printf("Enter the grade you want in the class: ");
    scanf("%c", &desiredLetterGrade);
    printf("Enter the percent you need to get that grade: ");
    scanf("%lf", &desiredPercentGrade);
    printf("Enter your current percent in the class: ");
    scanf("%lf", &currentPercentGrade);
    printf("Enter the weight of the final: ");
    scanf("%lf", &finalWeight);

    currentWeight = (100 - finalWeight) / 100;
    
    gradeNeeded = (desiredPercentGrade - (currentPercentGrade * currentWeight)) / (finalWeight/100);

    printf("You need to get at least %.2lf%% on the final to get a %c in the class.\n", gradeNeeded, desiredLetterGrade);
}