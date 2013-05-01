/**
 * main.cc - Driver/Wrapper for our lumail script.
 */


#include <iostream>
#include <fstream>
#include <getopt.h>

#include "lua.h"
#include "maildir.h"
#include "version.h"

using namespace std;




/**
 * Entry point to our code.
 */
int main( int argc, char *argv[] )
{

  //
  //   parse arguments
  //
  int c;

  //
  // Flags set
  //
  bool verbose = false;
  bool version = false;
  std::string rcfile = "";

  while (1)
    {
      static struct option long_options[] =
        {
          {"verbose", no_argument,  0, 'v'},
          {"version", no_argument,  0, 'V'},
          {"rcfile", required_argument, 0, 'r'},
          {0, 0, 0, 0}
        };

      /* getopt_long stores the option index here. */
      int option_index = 0;

      c = getopt_long (argc, argv, "vVr:", long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 'r':
          rcfile = optarg;
          break;
        case 'v':
          verbose = true;
          break;
        case 'V':
          version = true;
          break;
        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          cerr << "Unknown argument" << endl;
          return(2);
        }
    }

  if ( verbose )
    {
      cout << "--verbose" << endl;
    }
  if ( version )
    {
      cout << "lumail v" << LUMAIL_VERSION << endl;
      return 0;
    }
//   setup console
//
//   load lua environment

  CLua *lua = CLua::Instance();
  lua->loadFile("./lumail.lua");

  if ( ! rcfile.empty() )
      lua->loadFile( rcfile.c_str() );

  lua->callFunction("on_idle");

  std::string * v = lua->getGlobal("VERSION");
  cout << "Version is " << *v << endl;
  delete(v);

  cout <<endl;
  if ( CMaildir::isMaildir( "/home/skx/Maildir" ) )
    cout << "\t~/Maildir is OK" << endl;
  if ( CMaildir::isMaildir( "/home/skx/Maildir/.steve.org.uk" ) )
    cout << "\t~/Maildir/.steve.org.uk is OK" << endl;

//
//   while( true )
//        call: on_idle
  while( true )
    {

      lua->callFunction("on_idle");

//        process events
//        process keyboard
//        refresh screen
      sleep( 1);


//   end
    }
//
//   cleanup

  return 0;
}
