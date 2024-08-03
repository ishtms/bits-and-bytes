#include <stdint.h>
#include <stdio.h>

/** Display all the bytes in hex format */
void show_short(char *val) {
  for (unsigned int idx = 0; idx < sizeof(short); idx++) {
    printf("%02x ", val[idx]);
  }
  printf("\n\n");
}

/* Check whether the machine uses a big-endian or a little-endian
 * `ByteOrdering`? */
char is_little_endian() {
  short val = 0x2532;
  char *ptr = (char *)&val;

  return ptr[0] == 0x25;
}

// show the least significant byte of a, and rest all bytes of b
int magic(int a, int b) { return (a & 0xff) | ((b >> 8) << 8); }

// replace the byte `i` of the value x, with the contents of byte `b`
unsigned replace_byte(unsigned x, int i, unsigned char b) {
  return (x & ~(0xff << (i << 3)) | (b << (i << 3)));
}

char is_big_endian() { return !is_little_endian(); }

/** Rotate bits of an integer to the left */
unsigned int rotate_left(unsigned int x, int n) {
  return (x << n) | (x >> (32 - n));
}

/** Rotate bits of an integer to the right */
unsigned int rotate_right(unsigned int x, int n) {
  return (x >> n) | (x << (32 - n));
}

/** Extract the nth byte from an integer */
unsigned char extract_byte(unsigned int x, int n) {
  return (x >> (n * 8)) & 0xFF;
}

/** Set the nth bit of an integer */
unsigned int set_bit(unsigned int x, int n) { return x | (1 << n); }

/** Clear the nth bit of an integer */
unsigned int clear_bit(unsigned int x, int n) { return x & ~(1 << n); }

/** Toggle the nth bit of an integer */
unsigned int toggle_bit(unsigned int x, int n) { return x ^ (1 << n); }

/** Check if the nth bit of an integer is set */
int is_bit_set(unsigned int x, int n) { return (x & (1 << n)) != 0; }

/** Reverse the bytes of a 32-bit integer */
unsigned int reverse_bytes(unsigned int x) {
  return ((x & 0xFF) << 24) | ((x & 0xFF00) << 8) | ((x & 0xFF0000) >> 8) |
         ((x >> 24) & 0xFF);
}

/** Count the number of leading zeros in an integer */
int count_leading_zeros(unsigned int x) {
  if (x == 0)
    return 32;
  int count = 0;
  while ((x & 0x80000000) == 0) {
    count++;
    x <<= 1;
  }
  return count;
}

/** Count the number of trailing zeros in an integer */
int count_trailing_zeros(unsigned int x) {
  if (x == 0)
    return 32;
  int count = 0;
  while ((x & 1) == 0) {
    count++;
    x >>= 1;
  }
  return count;
}

int main() {
  char result = is_little_endian();
  char result_big = is_big_endian();
  int magic_number = magic(0x89abcdef, 0x76543210);
  printf("0x%x\n", replace_byte(0x12345678, 0, 0xAB));

  unsigned int x = 0x12345678;

  printf("Original: %08x\n", x);
  printf("Rotate left by 8: %08x\n", rotate_left(x, 8));
  printf("Rotate right by 8: %08x\n", rotate_right(x, 8));
  printf("Extract 2nd byte: %02x\n", extract_byte(x, 2));
  printf("Set 5th bit: %08x\n", set_bit(x, 5));
  printf("Clear 5th bit: %08x\n", clear_bit(x, 5));
  printf("Toggle 5th bit: %08x\n", toggle_bit(x, 5));
  printf("Is 5th bit set: %d\n", is_bit_set(x, 5));
  printf("Reverse bytes: %08x\n", reverse_bytes(x));
  printf("Count leading zeros: %d\n", count_leading_zeros(x));
  printf("Count trailing zeros: %d\n", count_trailing_zeros(x));

  return 0;
}
