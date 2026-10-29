int m;

void p(char *buff) {
  printf(buff, m);
}

void n() {
  char buff[512];
  fgets(buff, sizeof(buff), stdin);
  p(buff);
  if (m == 16930116)
	system("/bin/cat /home/user/level4/.pass");
}

int main() {
  n();
  return 0;
}
