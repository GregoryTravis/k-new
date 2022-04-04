#ifndef BISON_KP_TAB_H
# define BISON_KP_TAB_H

#ifndef YYSTYPE
typedef union {
  char *c;
  sexp s;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	_TOK___u0	257
# define	_TOK___u1	258
# define	_TOK___u10	259
# define	_TOK___u11	260
# define	_TOK___u12	261
# define	_TOK___u13	262
# define	_TOK___u14	263
# define	_TOK___u15	264
# define	_TOK___u16	265
# define	_TOK___u17	266
# define	_TOK___u18	267
# define	_TOK___u19	268
# define	_TOK___u2	269
# define	_TOK___u20	270
# define	_TOK___u21	271
# define	_TOK___u22	272
# define	_TOK___u23	273
# define	_TOK___u24	274
# define	_TOK___u25	275
# define	_TOK___u26	276
# define	_TOK___u3	277
# define	_TOK___u4	278
# define	_TOK___u5	279
# define	_TOK___u6	280
# define	_TOK___u7	281
# define	_TOK___u8	282
# define	_TOK___u9	283
# define	_TOK_boolconst	284
# define	_TOK_equals	285
# define	_TOK_genop	286
# define	_TOK_identifier	287
# define	_TOK_integer	288
# define	_TOK_level02	289
# define	_TOK_level03	290
# define	_TOK_level05	291
# define	_TOK_level06	292
# define	_TOK_level07	293
# define	_TOK_level08	294
# define	_TOK_level09	295
# define	_TOK_level10	296
# define	_TOK_level11	297
# define	_TOK_nil	298
# define	_TOK_quotetick	299
# define	_TOK_string	300


extern YYSTYPE yylval;

#endif /* not BISON_KP_TAB_H */
