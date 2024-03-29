/*
* Usuwanie folderow wraz z zawartoscia.
*/

int unlinkthis(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf)
{
	if(tflag == FTW_DNR) { 
		logparamerr("Wystapil blad podczas proby odczytania jednego z folderow przeznaczonych do usuwania. Proba kontynuacji...", fpath, 0);
		return 0;
	}

	int rv = remove(fpath);
	if (rv) {
		return rv;
	}
	
	logparamerr(
		(tflag == FTW_DP) ? "Usunieto folder nieobecny w folderze zrodlowym." :
		(tflag == FTW_F) ? "Usunieto plik nieobecny w folderze zrodlowym" :
		(tflag == FTW_SL) ? "Usunieto link symboliczny nieobecny w folderze zrodlowym." :
		"????", fpath, 0);
		
	return 0;
}

int rmvdir(char *path)
{
	int flags = 0;
	flags |= FTW_DEPTH;
	flags |= FTW_PHYS;

	if (nftw(path, unlinkthis, 64, flags) == -1) {
		return errno;
	}
	return 0;
}
