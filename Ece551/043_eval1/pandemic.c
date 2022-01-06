#include "pandemic.h"

#include <stdio.h>
country_t parseLine(char * line) {
  //WRITE ME
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  int x = 0;
  long population = 0;
  //parse the input line with specific format, and report error when input has the wrong format
  if ((x = sscanf(line, "%[^,],%ld", ans.name, &population)) != 2) {
    fprintf(stderr, " parse line failed\n");
    exit(EXIT_FAILURE);
  }
  ans.population = population;
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
  if (n_days < 7) {
    return;
  }
  //calculate 7 days' average with increasing start date
  double sum = 0;
  for (u_int start_day = 0; start_day < n_days - 6; start_day++) {
    sum = 0;
    for (u_int i = 0; i < 7; i++) {
      sum = sum + data[i + start_day];
    }
    avg[start_day] = sum / 7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
  if (n_days == 0) {
    return;
  }
  //calculate cumulative cases for every day and then calculate the 100000 average cases.
  double sum = 0;
  for (size_t i = 0; i < n_days; i++) {
    sum += data[i];
    cum[i] = 100000 * sum / pop;
  }
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  if (n_countries == 0 || n_days == 0) {
    return;
  }
  /*
    use max_ofonecountry to hold the number of max daily cases of one country,
    and max_amongcountries to hold the max among max_ofonecountrys through repetitively comparing to
    max_ofonecountry, if max_amongcountries < max_ofonecountry, update the former one and set num_ofmaxcountries
    to be 1. If they are the same, then add one to num_ofmaxcountries.
    In the end, print max_amongcountries if num_ofmaxcountries = 1, else print tie.
   */
  unsigned max_ofonecountry = 0;
  unsigned max_amongcountries = 0;
  unsigned index_maxcountry = 0;
  unsigned num_ofmaxcountries = 1;
  for (size_t i = 0; i < n_countries; i++) {
    max_ofonecountry = 0;
    for (size_t j = 0; j < n_days; j++) {
      if (max_ofonecountry < data[i][j]) {
        max_ofonecountry = data[i][j];
      }
    }
    if (max_ofonecountry > max_amongcountries) {
      num_ofmaxcountries = 1;
      max_amongcountries = max_ofonecountry;
      index_maxcountry = i;
    }
    else if (max_ofonecountry == max_amongcountries) {
      num_ofmaxcountries += 1;
    }
  }
  if (num_ofmaxcountries > 1) {
    printf("There is a tie between at least two countries");
  }
  else {
    printf("%s has the most daily cases with %u\n",
           countries[index_maxcountry].name,
           max_amongcountries);
  }
}
