#include "../inc/libmx.h"

char *optarg;
int optind = 1, opterr = 1, optopt, __optpos, optreset = 0;

#define optpos __optpos

bool opt_char_check(char flag, char *flags_str) {
    if(!mx_strchr(flags_str, flag)) return false;
    return true;
}

int mx_getopt(int argc, char * const argv[], const char *optstring) {
	int i, c, d;
	int k, l;
	char *optchar;

	if (!optind || optreset) {
		optreset = 0;
		__optpos = 0;
		optind = 1;
	}

	if (optind >= argc || !argv[optind])
		return -1;

	if (argv[optind][0] != '-') {
		if (optstring[0] == '-') {
			optarg = argv[optind++];
			return 1;
		}
		return -1;
	}

	if (!argv[optind][1])
		return -1;

	if (argv[optind][1] == '-' && !argv[optind][2])
		return optind++, -1;

	if (!optpos) optpos++;
	c = argv[optind][optpos], k = 1;
	optchar = argv[optind]+optpos;
    if(!opt_char_check(optchar[0], (char*)optstring)) {
        mx_printerr(mx_strjoin(mx_strjoin(mx_strjoin(argv[0], ": illegal option -- "), mx_strndup(optchar, 1)),"\n"));
		return '?';
    }
	optopt = c;
	optpos += k;

	if (!argv[optind][optpos]) {
		optind++;
		optpos = 0;
	}

	if (optstring[0] == '-' || optstring[0] == '+')
		optstring++;

	i = 0;
	d = 0;
	do {
		d = optstring[i], l = 1;
		if (l > 0) i += l; 
        else i++;
	} while (l && d != c);

	if (d != c) {
		if (optstring[0] != '-' && opterr)
            perror(mx_strjoin(mx_strjoin(argv[0], ": illegal option -- "), optchar));
		return '?';
	}
	return c;
}
