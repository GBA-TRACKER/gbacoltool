/*
	
	gbacoltool.c
	
	BSD 3-Clause License
	
	Copyright (c) 2021, ASDj Dev Team
	All rights reserved.
	
	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	
	1. Redistributions of source code must retain the above copyright notice, this
	   list of conditions and the following disclaimer.
	
	2. Redistributions in binary form must reproduce the above copyright notice,
	   this list of conditions and the following disclaimer in the documentation
	   and/or other materials provided with the distribution.
	
	3. Neither the name of the copyright holder nor the names of its
	   contributors may be used to endorse or promote products derived from
	   this software without specific prior written permission.
	
	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
	
*/

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "gbacoltool.h"

static inline void printLicenseMsg ();

int main (int argc, char* argv[]) {
	
	if (argc == 1) {
		fprintf(stderr, "Error: No command line parameters specified.\nUse %s -h for help.\n", argv[0]);
		return EXIT_SUCCESS;
	}
	
	// Process command line arguments.
	while (argc > optind) {
		
		static int nOpt; // Return value from getopt.
		static int iLongOpt; // Index of long options.
		
		// Long options structure.
		static struct option optLongOpts[] = {
			{ "help", no_argument, 0, 'h' },
			{ "license", no_argument, 0, 0 },
			{ "color-format", required_argument, 0, 'f' },
			{ 0, 0, 0, 0 }
		};
		
		iLongOpt = 0;
		if ((nOpt = getopt_long(argc, argv, "hf:", optLongOpts, &iLongOpt)) == -1) break;
		
		switch (nOpt) {
		case 0:
			switch (iLongOpt) {
			case 1:
				printLicenseMsg();
				return EXIT_SUCCESS;
			default:
				fprintf(stderr, "Error: Unsupported or unimplemented long option \"--%s\".\n", optLongOpts[iLongOpt].name);
				return EXIT_FAILURE;
			}
		case 'h':
			// TODO: add help message.
			printf("Help message not yet added.\n");
			return EXIT_SUCCESS;
		case 'f':
			break;
		case '?':
		default:
			fprintf(stderr, "Error: Unrecognized return value from getopt_long (0x%X).\n", nOpt);
			return EXIT_FAILURE;
		}
	}
	
	while (argc > optind) {
		printf("Found color: 0x%X\n", (uint16_t)strtoul(argv[optind], NULL, 0));
		optind++;
	}
	
	return EXIT_SUCCESS;
	
}

static inline void printLicenseMsg () {
	
	printf("BSD 3-Clause License\n\
\n\
Copyright (c) 2021, ASDj Dev Team\n\
All rights reserved.\n\
\n\
Redistribution and use in source and binary forms, with or without\n\
modification, are permitted provided that the following conditions are met:\n\
\n\
1. Redistributions of source code must retain the above copyright notice, this\n\
   list of conditions and the following disclaimer.\n\
\n\
2. Redistributions in binary form must reproduce the above copyright notice,\n\
   this list of conditions and the following disclaimer in the documentation\n\
   and/or other materials provided with the distribution.\n\
\n\
3. Neither the name of the copyright holder nor the names of its\n\
   contributors may be used to endorse or promote products derived from\n\
   this software without specific prior written permission.\n\
\n\
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS \"AS IS\"\n\
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE\n\
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE\n\
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE\n\
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL\n\
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR\n\
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER\n\
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,\n\
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE\n\
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.\n");
	
}

// EOF
