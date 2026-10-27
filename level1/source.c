int frame_dummy(...) {
	...
}

void run(void) {
  fwrite("Good... Wait what?\n", 1, 0x13, 1);
  system("/bin/sh");
}

int main() {
  char buffer[64];
  gets(buffer);
  return 0;
}
