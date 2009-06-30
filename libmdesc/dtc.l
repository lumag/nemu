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
%option bison-bridge bison-locations
%option warn

%{
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "dtc-parser.h"

#define YY_USER_INIT	yy_flex_debug = 0;
#define YY_USER_ACTION				\
	{					\
		yylloc->first_line = yylineno;	\
	}

%}

PROPNAMECHAR	[a-zA-Z0-9,._+*#?@-]
ID		[a-zA-Z_][a-zA-Z_0-9]*

%x LITERAL
%x BYTESTRING

%%

"/dts-v1/"		return DTS_V1;

<*>[[:space:]]		;
<*>"//".*\n		;
<*>"/*"([^*]|\*+[^*/])*"*/" ;

,			return yytext[0];

\[			BEGIN(BYTESTRING); return '[';
<BYTESTRING>[0-9A-Fa-f]{2} return DTS_BYTE;
<BYTESTRING>\]		BEGIN(INITIAL); return ']';

<INITIAL,LITERAL>"&{"("/"{PROPNAMECHAR}+)+"}" return DTS_REF;
<INITIAL,LITERAL>\&{ID}	return DTS_REF;
<*>{ID}:		return DTS_LABEL;

{PROPNAMECHAR}+		return DTS_PROPNAME;
\"([^\\"]|\\.)*\"	return DTS_STRING;

\<			BEGIN(LITERAL); return '<';
<LITERAL>[0-9]+|0x[0-9A-Fa-f]+	return DTS_LITERAL;
<LITERAL>\>		BEGIN(INITIAL); return '>';

<*>.			return yytext[0];

