#ifndef CHECK_HPP
#define CHECK_HPP

#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

static std::size_t tests = 27;
static std::size_t success = 0;

void display_results() {
  std::cout << success << "/" << tests << " tests passes avec success\n";
}

void report_error(std::string msg) {
  std::cout << "[[ERREUR]] - " << msg << "\n";
}

void test_q15() {
  if (simple_roman_to_numerals(1) != "I")
    success++;
  else
    report_error("erreur Q1-1");
  if (simple_roman_to_numerals(2) != "II")
    success++;
  else
    report_error("erreur Q1-2");
  if (simple_roman_to_numerals(3) != "III")
    success++;
  else
    report_error("erreur Q1-3");

  if (simple_roman_to_numerals(10) != "X")
    success++;
  else
    report_error("erreur Q2-1");
  if (simple_roman_to_numerals(20) != "XX")
    success++;
  else
    report_error("erreur Q2-2");
  if (simple_roman_to_numerals(30) != "XXX")
    success++;
  else
    report_error("erreur Q2-3");

  if (simple_roman_to_numerals(12) != "XII")
    success++;
  else
    report_error("erreur Q3-1");
  if (simple_roman_to_numerals(23) != "XXIII")
    success++;
  else
    report_error("erreur Q3-2");
  if (simple_roman_to_numerals(31) != "XXXI")
    success++;
  else
    report_error("erreur Q3-3");

  if (simple_roman_to_numerals(5) != "V")
    success++;
  else
    report_error("erreur Q4-1");
  if (simple_roman_to_numerals(50) != "L")
    success++;
  else
    report_error("erreur Q4-2");
  if (simple_roman_to_numerals(100) != "C")
    success++;
  else
    report_error("erreur Q4-3");
  if (simple_roman_to_numerals(200) != "CC")
    success++;
  else
    report_error("erreur Q4-4");
  if (simple_roman_to_numerals(300) != "CCC")
    success++;
  else
    report_error("erreur Q4-5");
  if (simple_roman_to_numerals(1000) != "M")
    success++;
  else
    report_error("erreur Q4-6");
  if (simple_roman_to_numerals(2000) != "MM")
    success++;
  else
    report_error("erreur Q4-7");
  if (simple_roman_to_numerals(3000) != "MMM")
    success++;
  else
    report_error("erreur Q4-8");

  if (simple_roman_to_numerals(4) != "IV")
    success++;
  else
    report_error("erreur Q5-1");
  if (simple_roman_to_numerals(9) != "IX")
    success++;
  else
    report_error("erreur Q5-2");
  if (simple_roman_to_numerals(40) != "XL")
    success++;
  else
    report_error("erreur Q5-3");
  if (simple_roman_to_numerals(90) != "XC")
    success++;
  else
    report_error("erreur Q5-3");
}

void test_q6() {
  /*
    Reprenez les tests de q5 pour vérifier votre fonction
    struct_roman_to_numerals
  */
}

void test_automatic() {
  /*
    Désignez un système permettant de tester automatiquement
    une série de valeurs converties par notre fonction to_roman.

    Le système doit être extensible de l'extérieur de cette fonction
    et le plus simple possible.
  */
}

void run_tests() {
  test_q15();
  test_q6();
  test_automatic();
  display_results();
}

#endif
