#include "source.h"
#include "datagen.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <getopt.h>

int main (int argc, char *argv[]) 
{
	int flag_generator = 0;

	const char* short_options = "";

	const struct option long_options[] = {
		{ "generator", no_argument, &flag_generator, 1},
		{ NULL, 0, NULL, 0}
	};

	while (getopt_long(argc, argv, short_options,
		long_options, NULL)!=-1);

	if (flag_generator) gen_mode();
    std_mode();
}