/*
** $Id: lstring.h,v 1.61 2015/11/03 15:36:01 roberto Exp $
** String table (keep all strings handled by Lua)
** See Copyright Notice in lua.h
*/

#ifndef lstring_h
#define lstring_h

#include "lgc.h"
#include "lobject.h"
#include "lstate.h"

/* lua中字符串会位于UTString结构之后，多一个字符存储'/0' */
#define sizelstring(l)  (sizeof(union UTString) + ((l) + 1) * sizeof(char))

#define sizeludata(l)	(sizeof(union UUdata) + (l))
#define sizeudata(u)	sizeludata((u)->len)

#define luaS_newliteral(L, s)	(luaS_newlstr(L, "" s, \
                                 (sizeof(s)/sizeof(char))-1))


/*
** test whether a string is a reserved word
*/
#define isreserved(s)	((s)->tt == LUA_TSHRSTR && (s)->extra > 0)


/*
** equality for short strings, which are always internalized
*/
#define eqshrstr(a,b)	check_exp((a)->tt == LUA_TSHRSTR, (a) == (b))


LUAI_FUNC unsigned int luaS_hash (const char *str, size_t l, unsigned int seed);
LUAI_FUNC unsigned int luaS_hashlongstr (TString *ts);
LUAI_FUNC int luaS_eqlngstr (TString *a, TString *b);
LUAI_FUNC void luaS_resize (lua_State *L, int newsize);
LUAI_FUNC void luaS_clearcache (global_State *g);
LUAI_FUNC void luaS_init (lua_State *L);
LUAI_FUNC void luaS_remove (lua_State *L, TString *ts);
LUAI_FUNC Udata *luaS_newudata (lua_State *L, size_t s);
LUAI_FUNC TString *luaS_newlstr (lua_State *L, const char *str, size_t l);
LUAI_FUNC TString *luaS_new (lua_State *L, const char *str);
LUAI_FUNC TString *luaS_createlngstrobj (lua_State *L, size_t l);

#define ENABLE_SHORT_STRING_TABLE

LUA_API void luaS_initshr();
LUA_API void luaS_exitshr();
LUA_API void luaS_expandshr(int n);
LUAI_FUNC TString *luaS_clonestring(lua_State *L, TString *);
LUA_API int luaS_shrinfo(lua_State *L);

#endif
