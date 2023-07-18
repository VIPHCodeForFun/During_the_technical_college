#include "utils/bit.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void testBit() {
  assert(BIT(0) == 1);
  assert(BIT(1) == 0b10);
  assert(BIT(7) == 0b10000000);

  printf("%s: pass \n", __PRETTY_FUNCTION__);
}

void testBitSet() {
  {
    int a = 0b0100;
    BIT_SET(a, 0);
    assert(a == 0b0101);
  }
  {
    int a = 0b0100;
    BIT_SET(a, 3);
    assert(a == 0b1100);
  }
  {
    int a = 0b10000100;
    BIT_SET(a, 6);
    assert(a == 0b11000100);
  }
  {
    const int shouldRemainUnchanged = 0b11000100;
    int a = shouldRemainUnchanged;
    BIT_SET(a, 6);
    assert(a == shouldRemainUnchanged);
  }

  printf("%s: pass \n", __PRETTY_FUNCTION__);
}

void testBitClr() {
  {
    int a = 0b0101;
    BIT_CLR(a, 0);
    assert(a == 0b0100);
  }
  {
    int a = 0b1100;
    BIT_CLR(a, 3);
    assert(a == 0b0100);
  }
  {
    int a = 0b11000100;
    BIT_CLR(a, 7);
    assert(a == 0b01000100);
  }
  {
    const int shouldRemainUnchanged = 0b01000100;
    int a = shouldRemainUnchanged;
    BIT_CLR(a, 7);
    assert(a == shouldRemainUnchanged);
  }
  printf("%s: pass \n", __PRETTY_FUNCTION__);
}

void testBitToggle() {
  {
    int a = 0b0101;
    BIT_TOGGLE(a, 0);
    assert(a == 0b0100);
    BIT_TOGGLE(a, 0);
    assert(a == 0b0101);
  }
  {
    int a = 0b10000100;
    BIT_TOGGLE(a, 6);
    assert(a == 0b11000100);
    BIT_TOGGLE(a, 6);
    assert(a == 0b10000100);
  }
  printf("%s: pass \n", __PRETTY_FUNCTION__);
}

void testBitIsSet() {
  {
    const int a = 1;
    assert(BIT_IS_SET(a, 0) == 1);
    assert(BIT_IS_SET(a, 1) == 0);
  }
  {
    const int a = 0b1100101;
    assert(BIT_IS_SET(a, 6) != BIT(6));
    assert(BIT_IS_SET(a, 6) == 1);
    assert(BIT_IS_SET(a, 4) == 0);
  }
  printf("%s: pass \n", __PRETTY_FUNCTION__);
}

int main() {
  testBit();
  testBitSet();
  testBitClr();
  testBitToggle();
  testBitIsSet();
}
