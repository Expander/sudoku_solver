
#include "options.hpp"
#include "config.hpp"

#include <cstdlib>
#include <cstring>
#include <getopt.h>

TOptions parseOptions(int argc, char* argv[])
{
   TOptions options;

   // check if number of command line arguments is reasonable
   static const int MAX_ARGC = 10;
   if (argc > MAX_ARGC || argc < 1)
      return options;

   // do not try to process very long argument strings for security
   // reasons
   static const size_t MAX_ARGV_LEN = 255;
   for (int i = 0; i < argc; ++i) {
      if (strlen(argv[i]) > MAX_ARGV_LEN)
         return options;
   }

   // parse command line options
   while (true) {
      // the available options
      static const struct option long_options[] = {
         {"sudoku-file-name",    required_argument, 0, 'f'},
         {"help",                no_argument,       0, 'h'},
         {"version",             no_argument,       0, 'v'},
         {0, 0, 0, 0}
      };

      // getopt_long stores the option index here.
      int option_index = 0;

      int opt = getopt_long(argc, argv, "f:hv",
                            long_options, &option_index);

      // Detect the end of the options.
      if (opt == -1)
         break;

      switch (opt) {
      case 'f':
         options.sudokuFileName = optarg;
         break;
      case 'h':
         printUsage();
         exit(0);
      case 'v':
         printVersion();
         exit(0);
      default:
         printUsage();
         exit(2);
      }
   }

   return options;
}

void printUsage(std::ostream& fout)
{
   fout << "Usage: sudoku_solver [options]\n"
           "options:\n"
           "  -f, --sudoku-file-name   sudoku input file\n"
           "  -h, --help               Display help text and exit.\n"
           "  -v, --version            Display version information and exit."
        << std::endl;
}

void printVersion(std::ostream& fout)
{
   fout << "Sukodu Solver v" VERSION "\n"
           "Copyright (C) 2012 by Alexander Voigt\n"
           "Sukodu Solver comes with ABSOLUTELY NO WARRANTY.\n"
           "This program is free software: you are free"
           " to change and redistribute\n"
           "it under the terms of the GNU General Public  License, \n"
           "either version 3 of the License, or (at your"
           " option) any later version.\n"
           "See <http://gnu.org/licenses/gpl.html> for more details."
        << std::endl;
}
