#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

static void test_example(void) { TEST_ASSERT_EQUAL(0, 0); }

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_example);

  return UNITY_END();
}
