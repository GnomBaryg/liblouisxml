/*See the copyright notice in louisxml.h*/

#ifndef __choices_h_
#define __choices_h_

/* Three variables, DEVELOPERPATH, USERPATH and USERISCONFIG are used to 
tell liblouisxml where to find configuration files, semantic-action 
files and liblouis tables and where to put temporary files and log 
files. If all of these variables are undefined (with the #undef 
statement) liblouisxml assumes that all of these files are either in the 
lbx_files subdirectory in your home directory or, if the first 
configuration file used by a program contains a path name, on that path. 
All paths must be absolute and must end with a slash or backslash. In 
the distribution of liblouisxml DEVELOPERPATH and USERPATH are undefined 
while USERISCONFIG is defined. This causes liblouisxml to look for files 
provided by the developer in the lbx_files directory of your home 
directory. The user path is determined by the first configuration file 
used by a program. If this file has no path component the user path is 
the current directory. If it does have a path component the user path is 
that component. liblouisxml searches for data files first on the user 
path and then on the developer path. Temporary files and log files are 
placed on the user path. 
*/

#undef DEVELOPERPATH
// #define DEVELOPERPATH "/etc/lbx_files/"
#undef USERPATH
// #define USERPATH ""
// #undef USERISCONFIG
#define USERISCONFIG

#endif /*__choices_h_*/