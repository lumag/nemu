/*
 * dtc.l
 *
 * Copyright (C) 2009 Dmitry Eremin-Solenikov
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

%option noyywrap nounput yylineno debug noinput nodefault

%{
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "y.tab.h"

#define YY_USER_INIT	yy_flex_debug = 0;

%}

PROPNAMECHAR	[a-zA-Z0-9,._+*#?@-]

%x LITERAL

%%

"/dts-v1/"		return DTS_V1;

<*>[[:space:]]		;
<*>"//".*\n		;
<*>"/*"([^*]|\*+[^*/])*"*/" ;

{PROPNAMECHAR}+		return DTS_PROPNAME;
\"([^\\"]|\\.)*\"	return DTS_STRING;

[/;{}=]			return yytext[0];

\<			BEGIN(LITERAL); return '<';
<LITERAL>[0-9]+|0x[0-9A-Fa-f]+	return DTS_LITERAL;
<LITERAL>\>		BEGIN(INITIAL); return '>';

