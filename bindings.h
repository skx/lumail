/**
 * bindings.h - Bindings for all fucntions callable from Lua.
 */

#ifndef _bindings_h
#define _bindings_h  1

#include "lua.h"


/* exit the program */
int exit(lua_State * L);

/* execute a program */
int exec(lua_State * L);

/* get/set the global mode: maildir/index/message */
int global_mode(lua_State * L);

/* limit the display of folders. */
int maildir_limit(lua_State * L);

/* get/set the global maildir-prefix */
int maildir_prefix(lua_State * L);

/* scroll up/down the maildir list. */
int scroll_maildir_down(lua_State *L);
int scroll_maildir_up(lua_State *L);

/* scroll to the folder matching the pattern. */
int scroll_maildir_to(lua_State *L);

/* get the current mailbox name. */
int current_maildir(lua_State *L);

/* draw a string at the foot of the screen. */
int msg(lua_State * L);

/* prompt for input */
int prompt(lua_State * L);

/* clear the screen */
int clear(lua_State * L);

/**
 * folder selection code.
 */
int clear_selected_folders(lua_State * L);
int add_selected_folder(lua_State * L);


#endif				/* _bindings_h */
