#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double cal_money(double initial, retire_info cal) {
  double money = initial;
  money = (money) * (1 + cal.rate_of_return) + cal.contribution;
  return money;
}

void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  int totalAge = startAge;
  double money = initial;
  printf("Age %3d month %2d you have $%.2lf\n", totalAge / 12, totalAge % 12, money);
  for (int t = 1; t <= working.months; t++) {
    money = cal_money(money, working);
    totalAge = startAge + t;
    printf("Age %3d month %2d you have $%.2lf\n", totalAge / 12, totalAge % 12, money);
  }
  for (int t = 1; t < retired.months; t++) {
    money = cal_money(money, retired);
    totalAge = startAge + working.months + t;
    printf("Age %3d month %2d you have $%.2lf\n", totalAge / 12, totalAge % 12, money);
  }
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345, working, retired);
  return EXIT_SUCCESS;
}
