
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

int main() {
  char result = is_little_endian();
  char result_big = is_big_endian();
  int magic_number = magic(0x89abcdef, 0x76543210);
  printf("0x%x\n", replace_byte(0x12345678, 0, 0xAB));
}
