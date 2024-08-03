#include <stdint.h>
#include <stdio.h>

/** Pack two 16-bit integers into a 32-bit integer */
uint32_t pack_16bit(uint16_t high, uint16_t low) {
  return ((uint32_t)high << 16) | low;
}

/** Unpack a 32-bit integer into two 16-bit integers */
void unpack_16bit(uint32_t packed, uint16_t *high, uint16_t *low) {
  *high = (packed >> 16) & 0xFFFF;
  *low = packed & 0xFFFF;
}

/** Pack four 8-bit integers into a 32-bit integer */
uint32_t pack_8bit(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
  return ((uint32_t)a << 24) | ((uint32_t)b << 16) | ((uint32_t)c << 8) | d;
}

/** Unpack a 32-bit integer into four 8-bit integers */
void unpack_8bit(uint32_t packed, uint8_t *a, uint8_t *b, uint8_t *c,
                 uint8_t *d) {
  *a = (packed >> 24) & 0xFF;
  *b = (packed >> 16) & 0xFF;
  *c = (packed >> 8) & 0xFF;
  *d = packed & 0xFF;
}

/** Swap the nibbles of a byte */
uint8_t swap_nibbles(uint8_t x) {
  return ((x & 0x0F) << 4) | ((x & 0xF0) >> 4);
}

/** Reverse the bits of a byte */
uint8_t reverse_bits_byte(uint8_t x) {
  x = ((x & 0xAA) >> 1) | ((x & 0x55) << 1);
  x = ((x & 0xCC) >> 2) | ((x & 0x33) << 2);
  x = ((x & 0xF0) >> 4) | ((x & 0x0F) << 4);
  return x;
}

/** Compute the parity of a byte (1 if odd number of 1s, 0 if even) */
int compute_parity(uint8_t x) {
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return x & 1;
}

/** Find the position of the first set bit (1-based index) */
int first_set_bit_position(uint32_t x) {
  if (x == 0)
    return 0;
  int pos = 1;
  while ((x & 1) == 0) {
    x >>= 1;
    pos++;
  }
  return pos;
}

/** Find the position of the last set bit (1-based index) */
int last_set_bit_position(uint32_t x) {
  if (x == 0)
    return 0;
  int pos = 32;
  while ((x & 0x80000000) == 0) {
    x <<= 1;
    pos--;
  }
  return pos;
}

/** Check if a number is a palindrome in binary representation */
int is_binary_palindrome(uint32_t x) {
  uint32_t reversed = 0;
  uint32_t original = x;
  while (x > 0) {
    reversed = (reversed << 1) | (x & 1);
    x >>= 1;
  }
  return original == reversed;
}
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

  uint16_t high = 0xABCD, low = 0x1234;
  uint32_t packed16 = pack_16bit(high, low);
  printf("Packed 16-bit: %08x\n", packed16);

  uint16_t unpacked_high, unpacked_low;
  unpack_16bit(packed16, &unpacked_high, &unpacked_low);
  printf("Unpacked 16-bit: high=%04x, low=%04x\n", unpacked_high, unpacked_low);

  uint8_t a = 0x12, b = 0x34, c = 0x56, d = 0x78;
  uint32_t packed8 = pack_8bit(a, b, c, d);
  printf("Packed 8-bit: %08x\n", packed8);

  uint8_t unpacked_a, unpacked_b, unpacked_c, unpacked_d;
  unpack_8bit(packed8, &unpacked_a, &unpacked_b, &unpacked_c, &unpacked_d);
  printf("Unpacked 8-bit: a=%02x, b=%02x, c=%02x, d=%02x\n", unpacked_a,
         unpacked_b, unpacked_c, unpacked_d);

  uint8_t byte = 0xAB;
  printf("Original byte: %02x, Swapped nibbles: %02x\n", byte,
         swap_nibbles(byte));
  printf("Original byte: %02x, Reversed bits: %02x\n", byte,
         reverse_bits_byte(byte));
  printf("Parity of byte %02x: %d\n", byte, compute_parity(byte));

  uint32_t num = 0xF0F0F0F0;
  printf("First set bit position in %08x: %d\n", num,
         first_set_bit_position(num));
  printf("Last set bit position in %08x: %d\n", num,
         last_set_bit_position(num));

  uint32_t palindrome = 0x0F0F0F0F;
  printf("Is %08x a binary palindrome? %d\n", palindrome,
         is_binary_palindrome(palindrome));
  return 0;
}
