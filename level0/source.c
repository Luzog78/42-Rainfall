int main(int argc, char **argv) {
	if (atoi(argv[1]) == 0x1a7) {
		int gid = getegid();
		int uid = geteuid();
		setresgid(gid, gid, gid);
		setresuid(uid, uid, uid);

		execv("/bin/sh", ...);
	} else {
		fwrite(1, "No !\n", 5);
	}

	return (0);
}
