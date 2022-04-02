#ifndef __CMD_H__
#define __CMD_H__

#define NOHIDDEN_IN_CMDLINE 0
#define HIDDEN_IN_CMDLINE   1
#define NOHIDDEN_IN_GDB     0
#define HIDDEN_IN_GDB       1


struct cli_command;
typedef int(*cli_callback_t) (struct cli_command * cmd, int argc,
	char **argv, void *priv);

struct cli_command
{
	const char *short_name;
	const char *long_name;
	const char *help;
	void *priv;
	cli_callback_t cb;
	int hidden_in_cmdline;
	int hidden_in_gdb;
	struct cli_command *next;
	struct cli_command *child;
	struct cli_command *parent;
};


static inline char *
parse_value(char *s, U64 *dest)
{
	char *p = s;
	int base = 16;
	if (s[0] == '-') {
		WARNING_OUT ("ignore negative\n");
		return p;
	}
	else if (p[0] == '0' && tolower(p[1]) == 'x') {
		p += 2;
		base = 16;
	}
	else if (strchr (s, '.') != NULL) {
		/* Parsing floating.  */
		float value = strtof (p, &p);
		memcpy (dest, &value, 4);
		return p;
	}
	else {
		base = 10;
	}

	*dest = utils_str_to_value64(p, &p, base);

	return p;
}



struct cli_command *
cli_command_register (char *name_of_parent,
                      const char *short_name,
                      const char *long_name,
                      const char *help, cli_callback_t cb,
                      void *priv,
                      int hidden_in_cmdline,
                      int hidden_in_gdb);

//void csky_command_init(struct target *target);


#endif
