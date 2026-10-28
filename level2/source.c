int frame_dummy(...)
{
	...
}

void p() {
  char buff[64];
  fflush(stdout);
  gets(buff);
  if ((*buff & 0xb0000000) == 0xb0000000)
  {
      printft(...);
      return;
  }
  puts(buff);
  strdup(buff);
}

int main() {
  p();
  return 0;
}
