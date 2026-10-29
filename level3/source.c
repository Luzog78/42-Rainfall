int m;

void v() {
  char buff[512];
  fgets(buff, sizeof(buff), stdin);
  printf(buff, &m);
  if (m == 64)
	system("/bin/sh");
}

int main() {
  v();
  return 0;
}
